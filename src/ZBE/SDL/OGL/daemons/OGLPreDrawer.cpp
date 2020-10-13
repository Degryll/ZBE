/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPreDrawer.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#include "ZBE/OGL/daemons/OGLPreDrawer.h"

namespace zbe {

void OGLPreDrawer::run() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cam->update();
  printf("Predrawer ogl programId %u\n", gProgramID); fflush(stdout);
  glUseProgram(gProgramID);
  GLuint projectLoc = glGetUniformLocation(gProgramID, "projection" );
  GLuint viewLoc = glGetUniformLocation(gProgramID, "view" );
  glUniformMatrix4fv(projectLoc, 1, true, cam->getProjectionMat().data());
  glUniformMatrix4fv(viewLoc, 1, false, cam->getTransformMat().data());
}

}  // namespace zbe
