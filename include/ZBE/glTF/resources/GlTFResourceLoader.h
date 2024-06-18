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

#include <cstdio>

#include <algorithm>
#include <filesystem>
#include <memory>
#include <iostream>
#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>
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
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/objects.h"

#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/OGL/graphics/OGLGraphics.h"

#include "ZBE/glTF/resources/GlTFResourceLoader.h"

namespace zbe {

class ZBEAPI GlTFResourceLoader : public RsrcLoader {
public:

// __declspec(noinline) GlTFResourceLoader() : ext(".gltf"), texStore(nullptr), modelStore(nullptr), graphicsStore(RsrcStore<OGLGraphics>::getInstance()), dict(NameRsrcDictionary::getInstance()) {
// }

// GlTFResourceLoader(OGLTextureStore* texStore,  OGLModelStore* modelStore) : ext(".gltf"), texStore(texStore), modelStore(modelStore) {
// }

// TODO añadir soporte para RsrcDefLoader.
// Renombrar load a loadGLTF
// Crear load que llame a loadGLTF y luego a RsrcDefLoader::load

void setup(OGLTextureStore* texStore,  OGLModelStore* modelStore) {
  this->texStore = texStore;
  this->modelStore = modelStore;
}

bool isLoadable(std::filesystem::path extension) {
  static const std::filesystem::path ext(".gltf");
  return (ext.compare(extension) == 0);
}

void load(std::filesystem::path filePath);

private:
  OGLTextureStore* texStore = nullptr;
  OGLModelStore* modelStore = nullptr;

  RsrcStore<OGLGraphics>& graphicsStore = RsrcStore<OGLGraphics>::getInstance();
  RsrcStore<std::forward_list<Triangle3D>> &triangle3DListRsrc = RsrcStore<std::forward_list<Triangle3D>>::getInstance();
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();

  GLuint bindModel(tinygltf::Model &model);

  void bindModelNodes(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Node &node*/ int nodeIdx);

  void bindMesh(std::vector<GLuint> vbos, tinygltf::Model &model, /*tinygltf::Mesh &mesh*/ int meshIdx);

  GLuint bindTextures(tinygltf::Model &model);

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

class GlTFResourceLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a GlTFResourceLoader.
   *  \param name Name for the created SDLImgLoader.
   *  \param cfgId SDLImgLoader's configuration id.
   */
   void create(std::string name, uint64_t) {
     using namespace std::string_literals;

     auto loader = std::make_shared<GlTFResourceLoader>();
     gltfLoaderRsrc.insert("GlTFResourceLoader."s + name, loader);
     rsrcLoaderRsrc.insert("RsrcLoader."s + name, loader);
   }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
   void setup(std::string name, uint64_t cfgId) {
     using namespace std::string_literals;
     using namespace nlohmann;
     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

     if(cfg) {
       auto j = *cfg;
       json windowname = j["window"];
       //json extension = j["extension"];

       if(!windowname.is_string()) {
         SysError::setError("Bad config for GlTFResourceLoaderFtry - window."s + windowname.get<std::string>());
         return;
       }

       auto loader = gltfLoaderRsrc.get("GlTFResourceLoader."s + name);
       auto win = sdlWindowRsrc.get("SDLOGLWindow."s + windowname.get<std::string>());

       loader->setup(win->getTextureStore(),  win->getModelStore());

       // if(extension.is_string()) {
       //   loader->setExtension(extension.get<std::string>());
       // }

     } else {
       SysError::setError("GlTFResourceLoader config for "s + name + " not found."s);
     }
   }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<GlTFResourceLoader> &gltfLoaderRsrc = RsrcStore<GlTFResourceLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<SDLOGLWindow> &sdlWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
};


}  // namespace zbe

#endif  // ZBE_GLTF_RESOURCES_GLTFRESOURCELOADER_H_
