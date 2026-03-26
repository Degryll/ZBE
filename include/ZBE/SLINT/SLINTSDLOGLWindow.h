/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SLINTSDLOGLWindow.h
 * @since 2018-05-28
 * @date 2018-05-28
 * @author Degryll Ludo
 * @brief Defines the following structures:
 *  - SDLOGLWindow: Create a windows using SDL 2.0. with OpenGL support
 *  - OGLTextureStore:
 */

#ifndef ZBE_SLINT_SLINTSDLOGLWINDOW_H_
#define ZBE_SLINT_SLINTSDLOGLWINDOW_H_

#include <memory>
#include <SDL.h>
#include <SDL_opengl.h>

#include "ZBE/factories/Factory.h"
#include <optional>  // for optional Slint UI handle

// Suprimir todos los warnings en headers de Slint (plataforma independiente)
#ifdef _MSC_VER
  #pragma warning(push, 0)
#else
  #pragma GCC system_header
#endif

#include "ui.h"

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

namespace zbe {

class ZBEAPI SLINTSDLOGLWindow : public SDLOGLWindow {
public:
  SLINTSDLOGLWindow(const SLINTSDLOGLWindow&) = delete;  //!< Does not make sense to "copy" a SLINTSDLOGLWindow.
  void operator=(const SLINTSDLOGLWindow&) = delete;  //!< Does not make sense to "copy" a SLINTSDLOGLWindow.

  /** \brief Creates a new SLINTSDLOGLWindow and a Renderer.
   *  Creates a new SLINTSDLOGLWindow wihtout configuration. 
   */
  SLINTSDLOGLWindow() = default;  // optional defaults to empty

  /** \brief Creates a new SLINTSDLOGLWindow and a Renderer.
   *
   *  Creates a new SLINTSDLOGLWindow and a Renderer with the size and flags specified.
   *  \param title Title of the Window.
   *  \param width Width of the Window.
   *  \param height Height of the Window.
   *  \param window_flags Flags for the SLINTSDLOGLWindow creation. Default no flags.
   *  \param rederer_flags Flags for the Renderer creation. Default no flags.
   */
  SLINTSDLOGLWindow(const char* title, int width, int height, Uint32 window_flags = 0, Uint32 renderer_flags = 0)
    : SDLOGLWindow(title, width, height, window_flags, renderer_flags) {}

  /** \brief Creates a new SLINTSDLOGLWindow and a Renderer in a specific position.
   *
   *  Creates a new SLINTSDLOGLWindow and a Renderer with the position, size and flags specified.
   *  \param title Title of the Window.
   *  \param x X coordinates of the initial position of the window.
   *  \param y Y coordinates of the initial position of the window..
   *  \param width Width of the Window.
   *  \param height Height of the Window.
   *  \param window_flags Flags for the SLINTSDLOGLWindow creation. Default no flags.
   *  \param rederer_flags Flags for the Renderer creation. Default no flags.
   */
  SLINTSDLOGLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 renderer_flags = 0)
    : SDLOGLWindow(title, x, y, width, height, window_flags | SDL_WINDOW_OPENGL, renderer_flags) {}

  /** \brief Free resources and destroy the Renderer and the SLINTSDLOGLWindow.
   */
  virtual ~SLINTSDLOGLWindow() = default;

  void createSLINTContext() {
    // platform initialization is handled elsewhere (SDLPlatform class
    // not provided by Slint headers).  Simply create the UI handle.
    ui = SlintUi::create();

    // TODO: Lo que parece que esta: Se construye el contexto de Slint y se crea la UI. Luego, en el post loop, se renderiza la UI.
    // Lo que falta: Pasar el objeto de la UI a la clase del post loop, para que pueda renderizarla. 
    // Factorias para todo.
  }

  void run() {
    createSLINTContext();
  }

  /** \brief Return a copy of the Slint UI handle if available. */
  std::optional<slint::ComponentHandle<SlintUi>> getUI() const {
    return ui;
  }
private:
  // handle optionalised because ComponentHandle has no default ctor
  std::optional<slint::ComponentHandle<SlintUi>> ui;
};

class SLINTSDLOGLWindowFtry : virtual public Factory, public SDLOGLWindowFtry {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;

    auto sdlwin = std::make_shared<SLINTSDLOGLWindow>();
    slintSdloglWindowRsrc.insert("SLINTSDLOGLWindow."s + name, sdlwin);
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
      } else {
        auto sdlED = std::make_shared<SDLEventDispatcher>();
        sdlEvenDWindowRsrc.insert("SDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
      }
    } else {
      SysError::setError("SLINTSDLOGLWindowFtry config for "s + name + " not found."s);
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
      auto sdloglwin = slintSdloglWindowRsrc.get("SLINTSDLOGLWindow."s + name);
      SDLOGLWindowFtry sldogWinFtry = SDLOGLWindowFtry();
      sldogWinFtry.configure(cfg, sdloglwin, "SLINTSDLOGLWindowFtry");
      sdloglwin->run();
    } else {
      SysError::setError("SLINTSDLOGLWindowFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SLINTSDLOGLWindow> &slintSdloglWindowRsrc = RsrcStore<SLINTSDLOGLWindow>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
};

} // namespace zbe

#endif  // ZBE_SLINT_SLINTSDLOGLWINDOW_H_