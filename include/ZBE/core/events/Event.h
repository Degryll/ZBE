/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEvent.h
 * @since 2016-03-26
 * @date 2018-03-20
 * @author Ludo Degryll Batis
 * @brief Base event.
 */

#ifndef ZBE_CORE_EVENTS_EVENT_H
#define ZBE_CORE_EVENTS_EVENT_H

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI EventDispatcher;

/** \brief Represents a basic event. An event its something that, when it occurs, can cause some element of the game to change its state.
 */
class ZBEAPI Event {
  public:

    /** \brief Basic constructor.
     *
     * \param id Represents the global id of this event.
     * \param time Exact moment in which it occurred
     *
     */
    Event(uint64_t id, uint64_t time) : id(id), time(time) {}

    virtual ~Event() {};  //!< Empty destructor

    /** \brief Get the exact moment in which event occurred
     *
     * \return An integer representing the time.
     *
     */
    inline int64_t getTime() const{
      return time;
    }

    /** \brief Get the id from this even.
     *
     * \return An integer that identifies the event.
     *
     */
    inline uint64_t getId() const{
      return id;
    }

    /** \brief Sort events by time.
     * \param e The event to compare this with.
     *
     * \return Return true if this occurs earlier than e.
     */
    bool operator<(const Event & e) {
      return getTime() < e.getTime();
    }

    /** \brief Manage the current event and, presumably,
     * do the actions associated with it.
     */
    virtual void manage() = 0;

  private:

    uint64_t id;    //!< Event id
    uint64_t time;  //!< Time when the event occurs
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_EVENT_H
