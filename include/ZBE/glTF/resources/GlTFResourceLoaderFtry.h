/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GlTFResourceLoaderFtry.h
 * @since 2020-09-13
 * @date 2020-09-13
 * @author Degryll
 * @brief Factory for GlTFResourceLoader.
 */

#ifndef ZBE_GLTF_RESOURCES_GLTFRESOURCELOADERFTRY_H_
#define ZBE_GLTF_RESOURCES_GLTFRESOURCELOADERFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/glTF/resources/GlTFResourceLoader.h"

namespace zbe {

/** \brief Factory for SDLImgLoader.
 */
class ZBEAPI GlTFResourceLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a GlTFResourceLoader.
   *  \param name Name for the created SDLImgLoader.
   *  \param cfgId SDLImgLoader's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<GlTFResourceLoader> &gltfLoaderRsrc = RsrcStore<GlTFResourceLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<SDLOGLWindow> &sdlWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_GLTF_RESOURCES_GLTFRESOURCELOADERFTRY_H_
