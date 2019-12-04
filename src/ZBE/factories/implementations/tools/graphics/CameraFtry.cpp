/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CameraFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for master daemons.
 */

#include "ZBE/factories/implementations/tools/graphics/CameraFtry.h"

namespace zbe {

void CameraFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  uint64_t id = cameraRsrc.insert("Camera."s + name, std::make_shared<Camera>());
}

void CameraFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json eyeName = j["eyevalue"];
    json targetName = j["targetvalue"];
    json upName = j["upvalue"];
    json fovName = j["fov"];
    json aspectName = j["aspect"];
    json znearName = j["znear"];
    json zfarName = j["zfar"];

    std::shared_ptr<Value<Vector3D> > eye;
    std::shared_ptr<Value<Vector3D> > target;
    std::shared_ptr<Value<Vector3D> > up;

    float fov;
    float aspect;
    float znear;
    float zfar;

    if (eyeName.is_string()){
      eye = vec3DValues.get(eyeName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for eyevalue is invalid or missing."s);
    }

    if (targetName.is_string()){
      target = vec3DValues.get(targetName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for targetvalue is invalid or missing."s);
    }

    if (upName.is_string()){
      up = vec3DValues.get(upName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for upvalue is invalid or missing."s);
    }

    if (fovName.is_string()){
      fov = (float) doubleStore.get(fovName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for fov is invalid or missing."s);
    }

    if (aspectName.is_string()){
      aspect = (float) doubleStore.get(aspectName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for aspect is invalid or missing."s);
    }

    if (znearName.is_string()){
      znear = (float) doubleStore.get(znearName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for znear is invalid or missing."s);
    }

    if (zfarName.is_string()){
      zfar = (float) doubleStore.get(zfarName.get<std::string>());
    } else {
      SysError::setError("CameraFtry handler daemon config for zfar is invalid or missing."s);
    }

    std::shared_ptr<Camera> cam = cameraRsrc.get("Camera."s + name);

    cam->setEyeValue(eye);
    cam->setTargetValue(target);
    cam->setUpValue(up);

    cam->set_perspective(fov, aspect, znear, zfar);

  } else {
    SysError::setError("CameraFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
