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

namespace zbe {

/** \brief Structure representing from where and where to draw a graphic element.
 */
struct OGLModel {

  OGLModel() : vao(), nvertex(), textures(), modelMat() {}

  OGLModel(GLuint vao, GLsizei nvertex, std::vector<GLuint> textures, glm::mat4 modelMat) : vao(vao), nvertex(nvertex), textures(textures), modelMat(modelMat) {}

  GLuint vao; //!<
  GLsizei nvertex;
  std::vector<GLuint> textures;
  glm::mat4 modelMat;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_OGLMODEL_H_
