/**
 * Copyright 2015 Batis Degryll Ludo
 * @file NetHandler.h
 * @since 2016-08-16
 * @date 2018-08-16
 * @author Degryll
 * @brief Receives a net event and reacts to that.
 */

#ifndef ZBE_CORE_EVENTS_HANDLERS_NETHANDLER_H
#define ZBE_CORE_EVENTS_HANDLERS_NETHANDLER_H

namespace zbe {

class SDLSocket;

/** \brief Receives a net event and reacts to that.
 */
class NetHandler {
public:

  /** \brief Destructor.
   */
  virtual ~NetHandler() {}

  /** \brief Do the Handler job.
   */
  virtual void run(uint32_t sequence, SDLSocket socket, std::vector<char> msg) = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_HANDLERS_NETHANDLER_H
