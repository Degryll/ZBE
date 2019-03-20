/**
 * Copyright 2015 Batis Degryll Ludo
 * @file SDLOGLWindowDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis
 * @brief Daemon that generates a SDLOGLWindow.
 */

#ifndef ZBE_SDL_DAEMONS_SDLOGLWINDOWDAEMON_H_
#define ZBE_SDL_DAEMONS_SDLOGLWINDOWDAEMON_H_

#include <memory>

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {
  /** \brief Daemon that generates a SDLOGLWindow.
   */
class ZBEAPI SDLOGLWindowDaemon : public Daemon {
public:

  SDLOGLWindowDaemon(const SDLOGLWindowDaemon&) = delete; //!< Avoid copy.
  void operator=(const SDLOGLWindowDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  SDLOGLWindowDaemon() :  name(""), title(""), x(0), y(0), width(0), height(0), window_flags(0), renderer_flags(0) {}

  /** \brief Sets the name of the generated SDLOGLWindow.
   */
  void setName         (std::string name)      {this->name  = name;}
  /** \brief Sets the window title.
   */
  void setTitle        (const char* title)     {this->title = title;}
  /** \brief Sets the window initial X position.
   */
  void setX            (int x)                 {this->x = x;}
  /** \brief Sets the window initial y position.
   */
  void setY            (int y)                 {this->y = y;}
  /** \brief Sets the window initial width.
   */
  void setWidth        (int width)             {this->width  = width;}
  /** \brief Sets the window initial height.
   */
  void setHeight       (int height)            {this->height = height;}
  /** \brief Sets the window flags.
   */
  void setWindowFlags  (Uint32 window_flags)   {this->window_flags   = window_flags;}
  /** \brief Sets the renderer flags.
   */
  void setRendererFlags(Uint32 renderer_flags) {this->renderer_flags = renderer_flags;}

  /** \brief Runs the daemon.
   */
  void run();

private:
  zbe::RsrcStore<SDLOGLWindow>& rs = zbe::RsrcStore<SDLOGLWindow>::getInstance();

  std::string name;
  const char* title;
  int x, y, width, height;
  Uint32 window_flags, renderer_flags;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_SDLOGLWINDOWDAEMON_H_
