/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CameraFtry.h
 * @since 2020-09-22
 * @date 2020-09-22
 * @author Batis
 * @brief Factory for OGLPreDrawer
 */

#ifndef ZBE_TOOLS_GRAPHICS_CAMERAFTRY_H_
#define ZBE_TOOLS_GRAPHICS_CAMERAFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

/** \brief Factory for OGLPreDrawer
 */
class CameraFtry : virtual public Factory {
public:

  /** \brief Builds a Camera.
   *  \param name Name for the created Camera.
   *  \param cfgId OGLPostDraw's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Value<float> > &vfloatRsrc = RsrcStore<Value<float> >::getInstance();
  RsrcStore<Value<Vector3D> > &vv3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_TOOLS_GRAPHICS_CAMERAFTRY_H_
