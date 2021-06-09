/**
* Copyright 2015 Batis Degryll Ludo
* @file ShadersSetter.cpp
* @since 2021-05-13
* @date 2021-05-13
* @author Batis Degryll Ludo
* @brief implementation of a ShadersSetter.
*/

#include "ZBE/OGL/daemons/ShadersSetter.h"

namespace zbe {

/** \brief Builds a ShadersSetter3D.
 *  \param name Name for the created ShadersSetter3D.
 *  \param cfgId ShadersSetter3D's configuration id.
 */
void ShadersSetter3DFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<ShadersSetter3D> ss3d = std::shared_ptr<ShadersSetter3D>(new ShadersSetter3D);
  daemonStore.insert("Daemon."s + name, ss3d);
  shadersSetter3DStore.insert("ShadersSetter3D."s + name, ss3d);
}

/** \brief Setup the desired tool. The tool will be complete after this step.
 *  \param name Name of the tool.
 *  \param cfgId Tool's configuration id.
 */
void ShadersSetter3DFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configStore.get(cfgId);

  if(cfg) {

    auto j = *cfg;
    if (!j["window"].is_string()) {
      SysError::setError("ShadersSetter3DFtry config for window: must be a window name."s);
      return;
    }

    if (!j["gProgramID"].is_string()) {
      SysError::setError("ShadersSetter3DFtry config for gProgramID: must be a uint64_t name."s);
      return;
    }

    if (!j["camera"].is_string()) {
      SysError::setError("ShadersSetter3DFtry config for camera: must be a camera name."s);
      return;
    }

    std::string windowName = j["window"].get<std::string>();
    if(!windowStore.contains("SDLOGLWindow."s + windowName)) {
      SysError::setError("ShadersSetter3DFtry config for window: "s + windowName + " is not a window literal."s);
      return;
    }

    std::string gProgramIDName = j["gProgramID"].get<std::string>();
    // if(!uintDict.contains(gProgramIDName)) {
    //   SysError::setError("ShadersSetter3DFtry config for gProgramID: "s + gProgramIDName + " is not an OGL program id literal."s);
    //   return;
    // }

    std::string cameraName = j["camera"].get<std::string>();
    if(!cameraStore.contains("Camera."s + cameraName)) {
      SysError::setError("ShadersSetter3DFtry config for camera: "s + cameraName + " is not a camera literal."s);
      return;
    }

    auto window = windowStore.get("SDLOGLWindow."s + windowName);
    auto gPid = uintDict.get(gProgramIDName);
    auto camera = cameraStore.get("Camera."s + cameraName);
    auto ss = shadersSetter3DStore.get("ShadersSetter3D."s + name);
    ss->setProgram(window, gPid);
    ss->setCamera(camera);

  } else {
    SysError::setError("ShadersSetter3DFtry config for "s + name + " not found."s);
  }

}

}  // namespace zbe
