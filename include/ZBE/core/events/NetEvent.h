/**
 * Copyright 2012 Batis Degryll Ludo
 * @file NetEvent.h
 * @since 2018-08-15
 * @date 2018-08-16
 * @author Degryll
 * @brief An event caused by a network message.
 */

#ifndef ZBE_CORE_EVENTS_NETEVENT_H
#define ZBE_CORE_EVENTS_NETEVENT_H

#include <cstdint>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/handlers/NetHandler.h"
#include "ZBE/SDL/system/SDLSocket.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief An event caused by input devices.
*/
class ZBEAPI NetEvent : public Event {
public:

  /** \brief Copy Constructor.
   */
  NetEvent(const NetEvent&) = delete;
  void operator=(const NetEvent&) = delete;

  /** \brief Builds a NetEvent with a sequence number, the socket and the message.
   *
   * \param id Represents the global id of this event.
   * \param time Moment in which its read from the socket.
   * \param sequence An id related to the sender.
   * \param socket Socket to communicate with the sender.
   * \param msg Message received.
   *
   */
  NetEvent(uint64_t id, uint64_t time, uint64_t sequence, SDLSocket socket, std::vector<char> msg, NetHandler* handler) : Event(id, time), sequence(sequence), socket(socket), msg(msg), handler(handler) {}

  /** \brief base destructor.
   */
  ~NetEvent() {}

  /** \brief Get the id of the key related with this event.
   * \return An integer that identifies the key.
   */
  inline uint64_t getSequence() {
      return sequence;
  }

  /** \brief Get the socket to the sender of the message.
   * \return A socket to the sender.
   */
  inline SDLSocket getSocket() {
      return socket;
  }

  /** \brief Get the network message.
   * \return The message.
   */
  inline std::vector<char> getMessage() {
      return msg;
  }

  /** \brief Manage the current event and, presumably,
   * do the actions associated with it.
   */
  void manage() override {
    handler->run(sequence, socket, msg);
  }

private:
  uint64_t sequence;
  SDLSocket socket;
  std::vector<char> msg;
  NetHandler* handler;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_NETEVENT_H
