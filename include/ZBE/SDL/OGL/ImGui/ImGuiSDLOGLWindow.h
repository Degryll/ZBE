/**
 * Copyright 2010 Batis Degryll Ludo
 * @file ImGuiSDLOGLWindow.h
 * @since 2018-05-28
 * @date 2018-05-28
 * @author Degryll Ludo
 * @brief Defines the following structures:
 *  - SDLOGLWindow: Create a windows using SDL 2.0. with OpenGL support
 *  - OGLTextureStore:
 */

#ifndef ZBE_SDL_SYSTEM_ImGuiSDLOGLWindow_H_
#define ZBE_SDL_SYSTEM_ImGuiSDLOGLWindow_H_

#include <memory>
#include <mutex>
#include <vector>
#include <tuple>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "ZBE/SDL/sdl_warning_suppressor.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/**
 * @class ZBEAPI SDLOGLWindow
 * @brief Used to create windows using SDL 2.0. with OpenGL support.
 */
class ZBEAPI ImGuiSDLOGLWindow : public SDLOGLWindow {
public:
  ImGuiSDLOGLWindow() : SDLOGLWindow(), io() {}

  ImGuiSDLOGLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0) : SDLOGLWindow(title, x, y, width, height, window_flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI, rederer_flags), io() {
    initImGui();
  }

  void run() override {
    SDLOGLWindow::run();
    if (!imguiInitialized) {
      initImGui();
    }
  }

  int getDisplayX() {
    return static_cast<int>(io.DisplaySize.x);
  }

  int getDisplayY() {
    return static_cast<int>(io.DisplaySize.y);
  }

private:
  void initImGui() {
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

    imguiInitialized = true;
  }

  ImGuiIO io;
  bool imguiInitialized = false;
};


class ImGuiSDLOGLWindowFtry : virtual public Factory, public SDLOGLWindowFtry {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;

    auto sdlwin = std::make_shared<ImGuiSDLOGLWindow>();
    imguiSdloglWindowRsrc.insert("ImGuiSDLOGLWindow."s + name, sdlwin);
    sdloglWindowRsrc.insert("SDLOGLWindow."s + name, sdlwin);

    auto ib = std::make_shared<InputBuffer>();
    ibuffRsrc.insert("SDLOGLWindow."s + name + ".InputBuffer", ib);

    auto itb = std::make_shared<InputTextBuffer>();
    itBuffRsrc.insert("SDLOGLWindow."s + name + ".InputTextBuffer", itb);

    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json eventDispatcher = j["eventdispatcher"];
      if(eventDispatcher.is_string()) {
        // TODO traerse el event distpatcher de la config
        // TODO Naming de espacios de nombres aquí, que es un poco raro
        auto sdlED = sdlEvenDWindowRsrc.get("SDLEventDispatcher."s + eventDispatcher.get<std::string>());
        sdlEvenDWindowRsrc.insert("SDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
        sdlEvenDWindowRsrc.insert("ImGuiSDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
      } else {
        auto sdlED = std::make_shared<SDLEventDispatcher>();
        sdlEvenDWindowRsrc.insert("SDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
        sdlEvenDWindowRsrc.insert("ImGuiSDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
      }
    } else {
      SysError::setError("ImGuiSDLOGLWindowFtry config for "s + name + " not found."s);
    }
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto sdloglwin = imguiSdloglWindowRsrc.get("ImGuiSDLOGLWindow."s + name);
      SDLOGLWindowFtry sldogWinFtry = SDLOGLWindowFtry();
      sldogWinFtry.configure(cfg, sdloglwin, "ImGuiSDLOGLWindowFtry");
      sdloglwin->run();
    } else {
      SysError::setError("ImGuiSDLOGLWindowFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ImGuiSDLOGLWindow> &imguiSdloglWindowRsrc = RsrcStore<ImGuiSDLOGLWindow>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_ImGuiSDLOGLWindow_H_
