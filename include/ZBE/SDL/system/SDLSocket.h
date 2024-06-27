/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLSocket.h
 * @since 2018-08-12
 * @date 2018-08-12
 * @author Degryll
 * @brief A simplification of SDL TCP and UDP sockets.
 */

#ifndef ZBE_SDL_SYSTEM_SDLSOCKET_H
#define ZBE_SDL_SYSTEM_SDLSOCKET_H

#include <cstdint>
#include <vector>

#include <SDL3_net/SDL_net.h>

#include "ZBE/core/events/handlers/NetHandler.h"
#include "ZBE/core/system/SysError.h"

#include "ZBE/core/system/system.h"

namespace zbe {

struct ZBEAPI SDLSocketHasher;

class ZBEAPI SDLSocket {
public:
  enum Type {TCP = 0, UDP = 1};

  SDLSocket() : type(TCP), tcp(nullptr), udp(nullptr), handler(nullptr) {}
  SDLSocket(TCPsocket tcp, NetHandler* handler) : type(TCP), tcp(tcp), udp(nullptr), handler(handler) {}
  SDLSocket(UDPsocket udp, NetHandler* handler) : type(UDP), tcp(nullptr), udp(udp), handler(handler) {}

  bool operator==(const SDLSocket &other) const {
    return (type == other.type
         && tcp  == other.tcp
         && udp  == other.udp);
  }

  //SDLNet_GenericSocket getSocket() {return (type == TCP) ? tcp : udp;}

  bool isReady();

  int getMsg(uint64_t &sequence, std::vector<char> &msg);
  int putMsg(uint64_t sequence, std::vector<char> msg);

  void remove(SDLNet_SocketSet sset);

  NetHandler* getHandler() {return(handler);}

  void setHandler(NetHandler* handler) {this->handler = handler;}

  friend struct ZBEAPI SDLSocketHasher;

private:
  int getTCPMsg(uint64_t &sequence, std::vector<char> &msg);
  int putTCPMsg(uint64_t sequence, std::vector<char> msg);

  int getUDPMsg(uint64_t &, std::vector<char> &) {zbe::SysError::setError("TODO, empty getUDPMsg function."); return (17);}
  int putUDPMsg(uint64_t , std::vector<char> ) {zbe::SysError::setError("TODO, empty putUDPMsg function."); return (17);}

  Type type;
  TCPsocket tcp;
  UDPsocket udp;
  NetHandler* handler;
};

struct ZBEAPI SDLSocketHasher {
  std::size_t operator()(const SDLSocket& k) const {
    using std::size_t;
    using std::hash;
    using std::string;

    return ((hash<int>()(k.type)
             ^ (hash<void*>()(k.tcp) << 1)) >> 1)
             ^ (hash<void*>()(k.udp) << 1);
  }
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLSOCKET_H
