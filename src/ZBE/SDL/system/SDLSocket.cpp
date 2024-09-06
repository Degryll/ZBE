/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLSocket.h
 * @since 2018-08-12
 * @date 2018-08-12
 * @author Degryll
 * @brief A simplification of SDL TCP and UDP sockets.
 */

#include "ZBE/SDL/system/SDLSocket.h"

namespace zbe {

bool SDLSocket::isReady() {
  if (type == TCP) {
    return (SDLNet_SocketReady(tcp));
  } else {
    return (SDLNet_SocketReady(udp));
  }
}

int SDLSocket::getMsg(uint64_t &sequence, std::vector<char> &msg) {
  if (type == TCP) {
    return (getTCPMsg(sequence, msg));
  } else {
    return (getUDPMsg(sequence, msg));
  }
}

int SDLSocket::putMsg(uint64_t sequence, std::vector<char> msg) {
  if (type == TCP) {
    return (putTCPMsg(sequence, msg));
  } else {
    return (putUDPMsg(sequence, msg));
  }
}

int SDLSocket::getTCPMsg(uint64_t &sequence, std::vector<char> &msg) {
  msg.clear();
	Uint32 len;
  unsigned result;
  result = static_cast<unsigned>(SDLNet_TCP_Recv(tcp, static_cast<void*>(&len), sizeof(len)));
	if(result < sizeof(len)) {
    // TODO Use System & logger
    printf("ERROR receiving message length from a TCP socket: %s\n", SDLNet_GetError());
		return (1);
	}

	len = SDL_SwapBE32(len);
	if(!len)
		return (0);

  result = static_cast<unsigned>(SDLNet_TCP_Recv(tcp, &sequence, sizeof(sequence)));
	if(result < sizeof(sequence)) {
    // TODO Use System & logger
    printf("ERROR receiving message sequence from a TCP socket: %s\n", SDLNet_GetError());
		return (1);
	}

	sequence = SDL_SwapBE32(static_cast<unsigned>(sequence));

  msg.reserve(len);

	/* get the string buffer over the socket */
	result = static_cast<unsigned>(SDLNet_TCP_Recv(tcp, msg.data(), static_cast<int>(len)));
	if(result < len) {
    // TODO Use System & logger
    printf("ERROR receiving message from a TCP socket: %s\n", SDLNet_GetError());
    msg.clear();
    return (2);
	}

	return (0);
}

int SDLSocket::putTCPMsg(uint64_t sequence, std::vector<char> msg) {
	Uint32 len;
  unsigned result;

	len =  static_cast<Uint32>(msg.size());
	Uint32 l = SDL_SwapBE32(len);

	result = static_cast<unsigned>(SDLNet_TCP_Send(tcp, &l, sizeof(l)));
	if(result < sizeof(l)) {
    // TODO Use System & logger
    printf("ERROR sending message length to a TCP socket: %s\n", SDLNet_GetError());
		return(1);
	}

	Uint32 s = SDL_SwapBE32(static_cast<unsigned>(sequence));
	result = static_cast<unsigned>(SDLNet_TCP_Send(tcp, &s, sizeof(s)));
	if(result < sizeof(s)) {
    // TODO Use System & logger
    printf("ERROR sending message sequence to a TCP socket: %s\n", SDLNet_GetError());
		return(1);
	}

	result = static_cast<unsigned>(SDLNet_TCP_Send(tcp, msg.data(), static_cast<int>(len)));
	if(result < len) {
    // TODO Use System & logger
		printf("ERROR sending message to a TCP socket: %s\n", SDLNet_GetError());
		return(2);
	}

	return(0);
}

void SDLSocket::remove(SDLNet_SocketSet sset) {
  if (type == TCP) {
    SDLNet_TCP_DelSocket(sset, tcp);
  } else {
    SDLNet_UDP_DelSocket(sset, udp);
  }
}

}  // namespace zbe
