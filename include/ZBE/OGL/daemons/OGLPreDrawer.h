/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPreDrawer.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGL_DAEMONS_OGLPREDRAWER_H
#define ZBE_OGL_DAEMONS_OGLPREDRAWER_H

#include <memory>

#include <GL/glew.h>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class ZBEAPI OGLPreDrawer : public Daemon {
public:

  OGLPreDrawer(std::shared_ptr<SDLOGLWindow> window, uint64_t programId, std::shared_ptr<Camera> cam)
    : gProgramID(window->getShaderStore()->getShader(programId)),  cam(cam) {}

  /** \brief Destructor.
   */
  ~OGLPreDrawer() {}

  /** \brief Do the actual Daemon job.
   */
  void run();

private:
  GLuint gProgramID;
  std::shared_ptr<Camera> cam;
};

}  // namespace zbe

#endif  // ZBE_OGL_DAEMONS_OGLPREDRAWER_H
