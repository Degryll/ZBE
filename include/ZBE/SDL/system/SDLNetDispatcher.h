/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLNetDispatcher.h
 * @since 2018-08-10
 * @date 2018-08-10
 * @author Degryll
 * @brief Dispatcher for SDL network messages.
 */

#ifndef ZBE_SDL_SYSTEM_SDLNETDISPATCHER_H
#define ZBE_SDL_SYSTEM_SDLNETDISPATCHER_H

#include <memory>
#include <forward_list>

#include <SDL2/SDL.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/core/io/NetBuffer.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Dispatcher for SDL network messages.
 */
class ZBEAPI SDLNetDispatcher {
public:
  SDLNetDispatcher(SDLNetDispatcher const&)    = delete;  //!< Needed for singleton.
  void operator=(SDLNetDispatcher const&) = delete;  //!< Needed for singleton.

  /** \brief Destructor. It will shutdown SDL subsystems.
   */
  ~SDLNetDispatcher();

  /** \brief Singleton implementation.
   *  \return The only instance of the SDLNetDispatcher.
   */
  static SDLNetDispatcher& getInstance() {
    static SDLNetDispatcher instance;
    return (instance);
  }

  /** \brief Add a TCP socket to listen.
   *  \param socket The TCP socket to be added.
   */
  SDLSocket addTCPSocket(const char *host, Uint16 port, NetHandler* handler) {
    IPaddress ip;
    SDLNet_ResolveHost(&ip, host, port);
    TCPsocket socket = SDLNet_TCP_Open(&ip);
    SDLNet_TCP_AddSocket(sset, socket);
    SDLSocket s(socket, handler);
    sockets.push_front(s);
    return s;
  }

//  /** \brief Add a UDP socket to listen.
//   *  \param socket The UDP socket to be added.
//   */
//  SDLSocket addUDPSocket(const char *host, Uint16 port, NetHandler* handler) {
//    IPaddress ip;
//    SDLNet_ResolveHost(&ip, host, port);
//    UDPsocket  socket = SDLNet_UDP_Open(&ip);
//    SDLNet_UDP_AddSocket(sset, socket);
//    SDLSocket s(socket, handler);
//    sockets.push_front(s);
//    return s;
//  }

  /** \brief Remove a TCP socket.
   *  \param socket The TCP socket to be removed.
   */
  void removeSocket(SDLSocket socket) {
    socket.remove(sset);
    sockets.remove(socket);
  }

  /** \brief Returns the NetBuffer where the network info will be written.
   *  \return The NetBuffer.
   */
  std::shared_ptr<NetBuffer> getNetBuffer() {return netBuffer;}

  /** \brief Distribute SDL events in the appropriate structures of the system.
   */
  void run();

private:
  SDLNetDispatcher()
    : sdl(SDL_Starter::getInstance(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS, SDL_Starter::SDLNET)),
      netBuffer(std::make_shared<NetBuffer>()), contextTime(SysTime::getInstance()), sset(SDLNet_AllocSocketSet(64)), sockets() {}

  SDL_Starter &sdl;
  std::shared_ptr<NetBuffer> netBuffer;
  std::shared_ptr<ContextTime> contextTime;
  SDLNet_SocketSet sset;
  std::forward_list<SDLSocket> sockets;
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLNETDISPATCHER_H
