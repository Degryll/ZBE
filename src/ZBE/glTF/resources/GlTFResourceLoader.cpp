/**
* Copyright 2015 Batis Degryll Ludo
* @file GlTFResourceLoader.cpp
* @since 2021-05-17
* @date 2021-05-17
* @author Batis Degryll Ludo
*/

#include <forward_list>
#include "ZBE/glTF/resources/GlTFResourceLoader.h"

namespace zbe {
  void GlTFResourceLoader::load(std::filesystem::path filePath) {
    using namespace std::string_literals;
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filePath.u8string());

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
    auto modelName = model.meshes[0u].name;
    GLsizei nvertex = model.accessors[static_cast<unsigned>(model.meshes[0u].primitives[0u].indices)].count;
    uint64_t modelId = modelStore->storeModel(vao, nvertex);

    GLenum  mode = model.meshes[0u].primitives[0u].mode;
    GLenum  type = model.accessors[model.meshes[0u].primitives[0u].indices].componentType;
    const GLvoid* offset = (GLvoid*)(model.accessors[model.meshes[0u].primitives[0u].indices].byteOffset);
    NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
    dict.insert("model."s + modelName, modelId);
    GLuint texId = bindTextures(model);

    // TODO This name will be replaced for another name extracted from a model sheet.
    graphicsStore.insert("graphics."s + modelName, std::make_shared<OGLGraphics>(OGLGraphics{vao, texId, mode, nvertex, type, offset}));
  }

  GLuint GlTFResourceLoader::bindModel(tinygltf::Model &model) {
    std::vector<GLuint> vbos;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const tinygltf::Scene &scene = model.scenes[static_cast<unsigned>(model.defaultScene)];
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

  void GlTFResourceLoader::bindModelNodes(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Node &node*/ int nodeIdx) {
    tinygltf::Node &node = model.nodes[static_cast<unsigned>(nodeIdx)];
    if ((node.mesh >= 0u) && (node.mesh < model.meshes.size())) {
      //bindMesh(vbos, model, model.meshes[node.mesh]);
      bindMesh(vbos, model, node.mesh);
    }

    for (size_t i = 0; i < node.children.size(); i++) {
      assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
      //bindModelNodes(vbos, model, model.nodes[node.children[i]]);
      bindModelNodes(vbos, model, node.children[i]);
    }
  }

  void GlTFResourceLoader::bindMesh(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Mesh &mesh*/ int meshIdx) {
    using namespace std::string_literals;
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
      }  // if bufferView.target == 0

      const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
      // std::cout << "bufferview.target " << bufferView.target << std::endl;

      GLuint vbo;
      glGenBuffers(1, &vbo);
      vbos.push_back(vbo);
      glBindBuffer(bufferView.target, vbo);

      glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
      if(i==0) { // TODO sacar este codigo de aqui usando ek indices que se lee mas abajo para "POSITION" en lugar de asumir que es el cero.
        // o, simplemente, leer antes ese indice y usarlo en este if...
        std::shared_ptr<std::forward_list<Triangle3D>> listT3D = std::make_shared<std::forward_list<Triangle3D>>();

        float* p = (float*)&buffer.data.at(0) + bufferView.byteOffset;
        int ne = bufferView.byteLength / (sizeof(float) * 3 * 3);
        auto modelName = model.meshes[0].name;
        for(int j = 0; j < ne; ++j) {
          uint64_t index = j*9;
          Point3D a{p[index+0],p[index+1],p[index+2]};
          Point3D b{p[index+3],p[index+4],p[index+5]};
          Point3D c{p[index+6],p[index+7],p[index+8]};
          Triangle3D t{a,b,c};
          listT3D->push_front(t);
        }
        triangle3DListRsrc.insert("TriangleList."s + modelName, listT3D);
      }
    }  // for model.bufferViews

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
        if (attrib.first.compare("POSITION") == 0) { vaa = 0; }
        if (attrib.first.compare("NORMAL") == 0) { vaa = 2; }
        if (attrib.first.compare("TEXCOORD_0") == 0) { vaa = 1; }
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
  }  // bindMesh

  GLuint GlTFResourceLoader::bindTextures(tinygltf::Model &model) {
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
  }  // bindTextures



}  // namespace zbe
