/**
* Copyright 2015 Batis Degryll Ludo
* @file OGLGraphics.h
* @since 2020-07-23
* @date 2020-07-23
* @author Batis Degryll Ludo
* @brief Stores OGL references to all data loaded from a gltf file
*/

#ifndef ZBE_OGL_GRAPHICS_OGLGRAPHICS_H_
#define ZBE_OGL_GRAPHICS_OGLGRAPHICS_H_

#include "ZBE/core/system/system.h"

namespace zbe {

struct OGLGraphics {
    GLuint vao;
    GLsizei nvertex; // Sera una coleccion offset/nvertex
    GLuint texid; // Sera una coleccion
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_OGLGRAPHICS_H_
