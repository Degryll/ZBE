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
class CameraFtry : public Factory {
public:


  /** \brief Builds a Camera.
   *  \param name Name for the created Camera.
   *  \param cfgId OGLPostDraw's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto camera = std::make_shared<Camera>();
    cameraRsrc.insert("Camera."s + name, camera);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json eyecfg = j["eye"];
      json targetcfg = j["target"];
      json upcfg = j["up"];
      json fovcfg = j["fov"];
      json aspectcfg = j["aspect"];
      json znearcfg = j["znear"];
      json zfarcfg = j["zfar"];

      if(!eyecfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - eye."s + eyecfg.get<std::string>());
        return;
      }
      if(!targetcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - target."s + targetcfg.get<std::string>());
        return;
      }
      if(!upcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - up."s + upcfg.get<std::string>());
        return;
      }
      if(!fovcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - fov."s + fovcfg.get<std::string>());
        return;
      }
      if(!aspectcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - aspect."s + aspectcfg.get<std::string>());
        return;
      }
      if(!znearcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - znear."s + znearcfg.get<std::string>());
        return;
      }
      if(!zfarcfg.is_string()) {
        SysError::setError("Bad config for CameraFtry - zfar."s + zfarcfg.get<std::string>());
        return;
      }


      auto eyename = eyecfg.get<std::string>();
      auto targetname = targetcfg.get<std::string>();
      auto upname = upcfg.get<std::string>();
      auto fovname = fovcfg.get<std::string>();
      auto aspectname = aspectcfg.get<std::string>();
      auto znearname = znearcfg.get<std::string>();
      auto zfarname = zfarcfg.get<std::string>();

      auto eye = vv3Rsrc.get(/*"Value."s +*/ eyename);
      auto target = vv3Rsrc.get(/*"Value."s +*/ targetname);
      auto up = vv3Rsrc.get(/*"Value."s +*/ upname);

      auto fov = vfloatRsrc.get(/*"Value."s +*/ fovname);
      auto aspect = vfloatRsrc.get(/*"Value."s +*/ aspectname);
      auto znear = vfloatRsrc.get(/*"Value."s +*/ znearname);
      auto zfar = vfloatRsrc.get(/*"Value."s +*/ zfarname);

      auto cam = cameraRsrc.get("Camera."s + name);
      cam->setPerspectiveValues(fov, aspect, znear, zfar);
      cam->setEyeValue(eye);
      cam->setTargetValue(target);
      cam->setUpValue(up);
    } else {
      SysError::setError("OGLPreDrawFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Value<float> > &vfloatRsrc = RsrcStore<Value<float> >::getInstance();
  RsrcStore<Value<Vector3D> > &vv3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_TOOLS_GRAPHICS_CAMERAFTRY_H_
