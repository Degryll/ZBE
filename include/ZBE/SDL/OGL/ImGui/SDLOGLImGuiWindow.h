/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDLOGLImGuiWindow.h
 * @since 2018-05-28
 * @date 2018-05-28
 * @author Degryll Ludo
 * @brief Defines the following structures:
 *  - SDLOGLWindow: Create a windows using SDL 2.0. with OpenGL support
 *  - OGLTextureStore:
 */

#ifndef ZBE_SDL_SYSTEM_SDLOGLIMGUIWINDOW_H_
#define ZBE_SDL_SYSTEM_SDLOGLIMGUIWINDOW_H_

#include <memory>
#include <mutex>
#include <vector>
#include <tuple>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/**
 * @class ZBEAPI SDLOGLWindow
 * @brief Used to create windows using SDL 2.0. with OpenGL support.
 */
class SDLOGLImGuiWindow : public SDLOGLWindow {
public:
  SDLOGLImGuiWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0) : SDLOGLWindow(title, x, y, width, height, window_flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI, rederer_flags)/*, gl_context(SDL_GL_CreateContext(this->getSDL_Window()))*/, io() {
    const char* glsl_version = "#version 130";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(this->getSDL_Window(), this->getGLContext());
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  int getDisplayX() {
    return (int)io.DisplaySize.x;
  }

  int getDisplayY() {
    return (int)io.DisplaySize.y;
  }

private:
  ImGuiIO io;
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLOGLIMGUIWINDOW_H_
