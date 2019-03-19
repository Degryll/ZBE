/**
 * Copyright 2015 Batis Degryll Ludo
 * @file SDLWindowDaemon.h
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Degryll
 * @brief Daemon that generates a SDLWindow.
 */

#ifndef ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_
#define ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_

#include <string>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"


namespace zbe {
  /** \brief
   */
class ZBEAPI SDLWindowDaemon : public Daemon {
public:

  SDLWindowDaemon(const SDLWindowDaemon&) = delete; //!< Avoid copy.
  void operator=(const SDLWindowDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  SDLWindowDaemon() :  name(""), title(""), x(0), y(0), width(0), height(0), window_flags(0), renderer_flags(0) {}

  /** \brief Sets the name of the generated SDLWindow.
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
  std::string name;
  const char* title;
  int x, y, width, height;
  Uint32 window_flags, renderer_flags;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_
