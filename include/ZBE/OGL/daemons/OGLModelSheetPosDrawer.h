/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetPosDrawer.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGLE_DAEMONS_OGLMODELSHEETPosDRAWER_H
#define ZBE_OGLE_DAEMONS_OGLMODELSHEETPosDRAWER_H

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class OGLModelSheetPosDrawer {
public:

  OGLModelSheetPosDrawer() {}

  /** \brief Destructor.
   */
  ~OGLModelSheetPosDrawer() {}

  /** \brief Do the actual Daemon job.
   */
  void run() {
    glBindVertexArray(0);
    glUseProgram(0);
  }
};

}  // namespace zbe

#endif  // ZBE_OGLE_DAEMONS_OGLMODELSHEETPosDRAWER_H
