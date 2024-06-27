/**
 * Copyright 2016 Batis Degryll Ludo
 * @file NetMessage.h
 * @since 2018-08-11
 * @date 2018-08-11
 * @author Degryll
 * @brief Single network message representation.
 */

#ifndef ZBE_CORE_IO_NETMESSAGE_H
#define ZBE_CORE_IO_NETMESSAGE_H

#include <cstdint>

#include <SDL3_net/SDL_net.h>

#include "ZBE/SDL/system/SDLSocket.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Single input status representation.
 */
class ZBEAPI NetMessage {
public:
  /** \brief Empty constructor for dummy messages.
   */
  NetMessage() : sequence(-1), socket(), msg(), time(-1) {}

  /** \brief Construct an input status.
   *  \param id Id of the input (key, button, mouse move, etc.).
   *  \param status Status of the input (pressed, moved, etc.).
   *  \param time When the input was changed.
   */
  NetMessage(Uint32 sequence, SDLSocket socket, std::vector<char> msg, uint64_t time) : sequence(sequence), socket(socket), msg(msg), time(time) {}

  /** \brief Returns the sequence number the network message.
   *  \return The sequence number.
   */
  Uint32 getSequence() const { return sequence;}

  /** \brief Returns the socket that received the message.
   *  \return Socket that received the message.
   */
  SDLSocket getSocket() const { return socket;}

  /** \brief Returns the message received from the network.
   *  \return Message received from the network.
   */
  std::vector<char> getMsg() const { return msg;}

  /** \brief Returns the timestamp in which this state is reached.
   *  \return Timestamp in which this state is reached.
   */
  uint64_t getTime() const { return time;}

  /** \brief "Less than" operator overloading.
   *  \return true if left hand element is less than right hand one.
   */
  bool operator<(const NetMessage& rhs) const {return time < rhs.getTime();}

private:
  Uint32 sequence;
  SDLSocket socket;
  std::vector<char> msg;
  uint64_t time;
};

}  // namespace zbe

#endif  // ZBE_CORE_IO_NETMESSAGE_H
