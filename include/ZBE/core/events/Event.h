/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEvent.h
 * @since 2016-03-26
 * @date 2016-03-26
 * @author Ludo
 * @brief Base event.
 */

#ifndef CORE_EVENTS_EVENT_H
#define CORE_EVENTS_EVENT_H

#include <cstdint>

namespace zbe {

/** \brief Represents a basic event. An event its something that, when it occurs, can cause some element of the game to change its state.
 */
class Event {
  public:

    /** \brief Basic constructor.
    *
    * \param id Represents the global id of this event.
    * \param time Exact moment in which it occurred
    *
    */
    Event(uint64_t id, uint64_t time):id(id),time(time){}

    virtual ~Event() {};

    /** \brief Get the exact moment in which event occurred
    *
    * \return An integer representing the time.
    *
    */
    inline uint64_t getTime() const{
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

    bool operator<(const Event & e) {
      return getTime() < e.getTime();
    }

  private:

    uint64_t id;
    uint64_t time;
};

}
#endif // CORE_EVENTS_EVENT_H
