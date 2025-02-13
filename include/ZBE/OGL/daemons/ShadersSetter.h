/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ShadersSetter.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGL_DAEMONS_SHADERSSETTER_H
#define ZBE_OGL_DAEMONS_SHADERSSETTER_H

#include <memory>
#include <cstdio>
#include <GL/glew.h>
#include <nlohmann/json.hpp>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class ShadersSetter3D : public Daemon {
public:
  friend class ShadersSetter3DFtry;
  /** \brief Destructor.
   */
  virtual ~ShadersSetter3D() = default;

  /** \brief Do the actual Daemon job.
   */
  void run() override {
    glUseProgram(gProgramID);

// glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
// glBindVertexArray(1);
// glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
//
// glBindVertexArray(0);

    GLint projectLoc = glGetUniformLocation(gProgramID, "projection" );
    GLint viewLoc = glGetUniformLocation(gProgramID, "view" );
    glUniformMatrix4fv(projectLoc, 1, true, cam->getProjectionMat().data());
    glUniformMatrix4fv(viewLoc, 1, false, cam->getTransformMat().data());
  }

  void setProgram(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
    gProgramID = window->getShaderStore()->getShader(programId);
  }

  void setCamera(std::shared_ptr<Camera> cam) {
    this->cam = cam;
  }

private:
  GLuint gProgramID;
  std::shared_ptr<Camera> cam;
};

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class ShadersSetter2D : public Daemon {
public:
  /** \brief Destructor.
   */
  virtual ~ShadersSetter2D() = default;

  /** \brief Do the actual Daemon job.
   */
  void run() override {
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(gProgramID);
  }

  void setProgram(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
    gProgramID = window->getShaderStore()->getShader(programId);
  }

private:
  GLuint gProgramID;
};

/** \brief Factory for ShadersSetter3DFtry.
 */
class ZBEAPI ShadersSetter3DFtry : virtual public Factory {
public:
  /** \brief Builds a ShadersSetter3D.
   *  \param name Name for the created ShadersSetter3D.
   *  \param cfgId ShadersSetter3D's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<ShadersSetter3D>& shadersSetter3DStore = RsrcStore<ShadersSetter3D>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<SDLOGLWindow>& windowStore = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<Camera>& cameraStore = RsrcStore<Camera>::getInstance();
};

/** \brief Factory for ShadersSetter2DFtry.
 */
class ShadersSetter2DFtry : virtual public Factory {
public:
  /** \brief Builds a ShadersSetter2D.
   *  \param name Name for the created ShadersSetter2D.
   *  \param cfgId ShadersSetter2D's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ShadersSetter2D> ss2D = std::shared_ptr<ShadersSetter2D>(new ShadersSetter2D);
    daemonStore.insert("Daemon."s + name, ss2D);
    shadersSetter2DStore.insert("ShadersSetter2D."s + name, ss2D);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
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
        SysError::setError("ShadersSetter2DFtry config for gProgramID: must be a uint64_t name."s);
        return;
      }
      std::string windowName = j["window"].get<std::string>();
      if(!windowStore.contains("SDLOGLWindow."s + windowName)) {
        SysError::setError("ShadersSetter3DFtry config for window: "s + windowName + " is not a window literal."s);
        return;
      }

      std::string gProgramIDName = j["gProgramID"].get<std::string>();
      // if(!uintDict.contains(gProgramIDName)) {
      //   SysError::setError("ShadersSetter2DFtry config for gProgramID: "s + gProgramIDName + " is not an OGL program id literal."s);
      //   return;
      // }

      auto window = windowStore.get("SDLOGLWindow."s + windowName);
      auto gPid = uintDict.get(gProgramIDName);
      auto ss = shadersSetter2DStore.get("ShadersSetter2D."s + name);
      ss->setProgram(window, gPid);

    } else {
      SysError::setError("ShadersSetter2DFtry config for "s + name + " not found."s);
    }

  }

private:
  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<ShadersSetter2D>& shadersSetter2DStore = RsrcStore<ShadersSetter2D>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<SDLOGLWindow>& windowStore = RsrcStore<SDLOGLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OGL_DAEMONS_SHADERSSETTER_H
