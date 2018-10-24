/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetPreDrawer.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGLE_DAEMONS_OGLMODELSHEETPREDRAWER_H
#define ZBE_OGLE_DAEMONS_OGLMODELSHEETPREDRAWER_H

namespace zbe {

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class ZBEAPI OGLModelSheetPreDrawer {
public:

  OGLModelSheetPreDrawer(std::shared_ptr<SDLOGLWindow> window, uint64_t programId, std::shared_ptr<std::vector<GLfloat> > projection, std::shared_ptr<std::vector<GLfloat> > view)
    : gProgramID(window->getShaderStore()->getShader(programId)),  projection(projection), view(view) {}

  /** \brief Destructor.
   */
  ~OGLModelSheetPreDrawer() {}

  /** \brief Do the actual Daemon job.
   */
  void run() {
    glUseProgram(gProgramID);
    GLuint projectLoc = glGetUniformLocation(gProgramID, "projection" );
    GLuint viewLoc = glGetUniformLocation(gProgramID, "view" );
    glUniformMatrix4fv(projectLoc, 1, true, &((*projection)[0]));
    glUniformMatrix4fv(viewLoc, 1, false, &((*view)[0]));
  }

private:
  GLuint gProgramID;
  std::shared_ptr<std::vector<GLfloat> > projection;
  std::shared_ptr<std::vector<GLfloat> > view;
};

}  // namespace zbe

#endif  // ZBE_OGLE_DAEMONS_OGLMODELSHEETPREDRAWER_H
