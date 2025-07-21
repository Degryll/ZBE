/**
 * Copyright 2025 Batis Degryll Ludo
 * @file OglStaticGlew.h
 * @since 2025-07-21
 * @author Degryll Ludo Batis
 * @brief 
 */

#pragma once

#ifndef ZBE_OGL_OGLSTATICGLEW_H_
#define ZBE_OGL_OGLSTATICGLEW_H_

  #ifndef GLEW_STATIC
    #define GLEW_STATIC
  #endif  // GLEW_STATIC
  #include <GL/glew.h>

#else

  #include <GL/glew.h>

#endif  // ZBE_OGL_OGLSTATICGLEW_H_
