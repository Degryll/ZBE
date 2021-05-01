/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModel.h
 * @since 2018-06-09
 * @date 2018-06-09
 * @author Degryll Ludo
 * @brief
 */

#ifndef ZBE_OGL_GRAPHICS_OGLMODEL_H_
#define ZBE_OGL_GRAPHICS_OGLMODEL_H_

#include <cstdint>
#include <vector>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Structure representing from where and where to draw a graphic element.
 */
struct ZBEAPI OGLModel {

  // OGLModel() = default;

  OGLModel(GLuint vao, std::vector<GLuint> textures, GLenum  mode, GLsizei nvertex, GLenum  type, const GLvoid* offset, glm::mat4 modelMat, glm::mat4 texCoordMat) : vao(vao), textures(textures), mode(mode), nvertex(nvertex), type(type), offset(offset), modelMat(modelMat), texCoordMat(texCoordMat) {}

  GLuint vao; //!<
  std::vector<GLuint> textures;
  GLsizei nvertex;
  glm::mat4 modelMat;
  glm::mat4 texCoordMat;

  GLenum  mode;
  GLenum  type;
  const GLvoid* offset;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_OGLMODEL_H_
