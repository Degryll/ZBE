/**
* Copyright 2015 Batis Degryll Ludo
* @file GlTFResourceLoader.h
* @since 2020-07-14
* @date 2020-07-14
* @author Batis Degryll Ludo
* @brief Resource loader for glTF files.
* Uses TinyglTF https://github.com/syoyo/tinygltf
*/


#ifndef ZBE_GLTF_RESOURCES_GLTFRESOURCELOADER_H_
#define ZBE_GLTF_RESOURCES_GLTFRESOURCELOADER_H_

#include <algorithm>
#include <filesystem>
#include <memory>
#include <iostream>

#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/gtc/matrix_transform.hpp>

//#include "shaders.h"
//#include "window.h"

// TODO maybe we should replace stb_image with other technologies like... SDL?
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define TINYGLTF_NOEXCEPTION
//#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/OGL/graphics/OGLGraphics.h"


namespace zbe {

class ZBEAPI GlTFResourceLoader : public RsrcLoader {
public:

GlTFResourceLoader() : ext(".gltf"), texStore(), modelStore() {
}

GlTFResourceLoader(OGLTextureStore* texStore,  OGLModelStore* modelStore) : ext(".gltf"), texStore(texStore), modelStore(modelStore) {
}

void setup(OGLTextureStore* texStore,  OGLModelStore* modelStore) {
  this->texStore = texStore;
  this->modelStore = modelStore;
}

// TODO añadir soporte para RsrcDefLoader.
// Renombrar load a loadGLTF
// Crear load que llame a loadGLTF y luego a RsrcDefLoader::load


bool isLoadable(std::filesystem::path extension) {
  return (ext.compare(extension) == 0);
}

void load(std::filesystem::path filePath) {
  using namespace std::string_literals;
  tinygltf::TinyGLTF loader;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filePath.c_str());

  //SysError::setError(std::string("ERROR: Json failed to parse. Key ") + name + std::string(" contains an invalid value type. Value: ") + value.dump());
  if (!warn.empty()) {
    SysError::setError(std::string("WARNING: GlTFResourceLoader:") + warn);
  }

  if (!err.empty()) {
    SysError::setError(std::string("ERROR: GlTFResourceLoader:") + err);
  }

  if (!res) {
    SysError::setError("ERROR: Failed to load glTF "s + filePath.u8string());
  }

  GLuint vao = bindModel(model);
  auto modelName = model.meshes[0].name;
  GLsizei nvertex = model.accessors[model.meshes[0].primitives[0].indices].count;
  uint64_t modelId = modelStore->storeModel(vao, nvertex);
  dict.insert("model."s + modelName, modelId);

  GLuint texId = bindTextures(model);

  // TODO This name will be replaced for another name extracted from a model sheet.
  graphicsStore.insert("graphics."s + modelName, std::make_shared<OGLGraphics>(OGLGraphics{vao, nvertex, texId}));
}

private:

const std::filesystem::path ext;

OGLTextureStore* texStore;
OGLModelStore* modelStore;

RsrcStore<OGLGraphics>& graphicsStore = RsrcStore<OGLGraphics>::getInstance();
NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();

GLuint bindModel(tinygltf::Model &model) {
  std::vector<GLuint> vbos;
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  const tinygltf::Scene &scene = model.scenes[model.defaultScene];
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
    //bindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
    bindModelNodes(vbos, model, scene.nodes[i]);
  }

  glBindVertexArray(0);
  for (auto vbo : vbos) {
    glDeleteBuffers(1, &vbo);
  }
  return vao;
}

void bindModelNodes(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Node &node*/ int nodeIdx) {
  tinygltf::Node &node = model.nodes[nodeIdx];
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    //bindMesh(vbos, model, model.meshes[node.mesh]);
    bindMesh(vbos, model, node.mesh);
  }

  for (size_t i = 0; i < node.children.size(); i++) {
    assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
    //bindModelNodes(vbos, model, model.nodes[node.children[i]]);
    bindModelNodes(vbos, model, node.children[i]);
  }
}


void bindMesh(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Mesh &mesh*/ int meshIdx) {
  tinygltf::Mesh &mesh = model.meshes[meshIdx];
  for (size_t i = 0; i < model.bufferViews.size(); ++i) {
    const tinygltf::BufferView &bufferView = model.bufferViews[i];
    if (bufferView.target == 0) {  // TODO impl drawarrays
      std::cout << "WARN: bufferView.target is zero" << std::endl;
      vbos.push_back(0);
      continue;  // Unsupported bufferView.
                 /*
                   From spec2.0 readme:
                   https://github.com/KhronosGroup/glTF/tree/master/specification/2.0
                            ... drawArrays function should be used with a count equal to
                   the count            property of any of the accessors referenced by the
                   attributes            property            (they are all equal for a given
                   primitive).
                 */
    }

    const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
    // std::cout << "bufferview.target " << bufferView.target << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    vbos.push_back(vbo);
    glBindBuffer(bufferView.target, vbo);

    // std::cout << "buffer.data.size = " << buffer.data.size() << ", bufferview.byteOffset = " << bufferView.byteOffset << std::endl;

    glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
  }

  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    tinygltf::Primitive primitive = mesh.primitives[i];
    tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

    for (auto &attrib : primitive.attributes) {
      tinygltf::Accessor accessor = model.accessors[attrib.second];
      int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
      glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

      int size = 1;
      if (accessor.type != TINYGLTF_TYPE_SCALAR) {
        size = accessor.type;
      }

      int vaa = -1;
      if (attrib.first.compare("POSITION") == 0) vaa = 0;
      if (attrib.first.compare("NORMAL") == 0) vaa = 1;
      if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
      if (vaa > -1) {
        glEnableVertexAttribArray(vaa);
        glVertexAttribPointer(vaa, size, accessor.componentType,
                              accessor.normalized ? GL_TRUE : GL_FALSE,
                              byteStride, (const GLvoid *)(accessor.byteOffset));
      } else {
        std::cout << "vaa missing: " << attrib.first << std::endl;
      }
    }  // for attributes
  }  // for primitives

// return vbos;
} // bindMesh

GLuint bindTextures(tinygltf::Model &model) {
  using namespace std::string_literals;
  if (model.textures.size() > 0) {
    // fixme: Use material's baseColor
    tinygltf::Texture &tex = model.textures[0];

    if (tex.source > -1) {

      GLuint texid;
      glGenTextures(1, &texid);

      tinygltf::Image &image = model.images[tex.source];

      glBindTexture(GL_TEXTURE_2D, texid);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      GLenum format = GL_RGBA;

      if (image.component == 1) {
        format = GL_RED;
      } else if (image.component == 2) {
        format = GL_RG;
      } else if (image.component == 3) {
        format = GL_RGB;
      } else {
        // ???
      }

      GLenum type = GL_UNSIGNED_BYTE;
      if (image.bits == 8) {
        // ok
      } else if (image.bits == 16) {
        type = GL_UNSIGNED_SHORT;
      } else {
        // ???
      }

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
                   format, type, &image.image.at(0));

      uint64_t textureId = texStore->storeTexture(texid);
      auto textureName = image.uri; //

      //std::replace(textureName.begin(), textureNames.end(), '.', '_');
      std::replace(textureName.begin(), textureName.end(), '\\', '.');
      std::replace(textureName.begin(), textureName.end(), '/', '.');
      // "textures.zbe.data.images.Cube_BaseColor.png"
      dict.insert("texture."s + textureName, textureId);
      return texid;
    }  // if tex.source
  }  // if model.textures.size
  return 0;
}

// void bindMaterials(tinygltf::Model &model) {
//   // Por ahora solo busca en el material de la primera primitiva la textura base
//   // compone el nombre y busca el id guardado en el diccionario.
//
//   // De forma general tendrá que recorrer todas las primitivas, y por cada
//   // material recuperar del diccionario el id de la textura asociada
//   // ... y algo de samplers
//
//         using namespace std::string_literals;
//
//         tinygltf::Texture &tex = model.textures[0];
//         tinygltf::Image &image = model.images[tex.source];
//         auto textureName = image.uri;
//
//         //std::replace(textureName.begin(), textureNames.end(), '.', '_');
//         std::replace(textureName.begin(), textureName.end(), '\\', '.');
//         std::replace(textureName.begin(), textureName.end(), '/', '.');
//         // "textures.zbe.data.images.Cube_BaseColor.png"
//         uint64_t textureId = dict.get("texture."s + textureName);
// }

};

}  // namespace zbe

#endif  // ZBE_GLTF_RESOURCES_GLTFRESOURCELOADER_H_
