/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CameraFtry.cpp
 * @since 2020-09-22
 * @date 2020-09-22
 * @author Ludo Degryll Batis
 * @brief Factory for Camera.
 */

#include "ZBE/tools/graphics/CameraFtry.h"

namespace zbe {

void CameraFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto camera = std::make_shared<Camera>();
  cameraRsrc.insert("Camera."s + name, camera);
}

void CameraFtry::setup(std::string name, uint64_t cfgId) {
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

}  // namespace zbe
