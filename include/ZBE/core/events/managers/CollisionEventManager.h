/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventManager.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Ludo
 * @brief Manage collision events.
 */

#ifndef CORE_EVENTS_MANAGERS_TIMEEVENTHANDLER_H
#define CORE_EVENTS_MANAGERS_TIMEEVENTHANDLER_H

#include "ZBE/core/handlers/Actuator.h"
#include "ZBE/core/events/EventDispatcher.h"

namespace zbe {

/** \brief Handle collision events.
 */
class CollisionEventManager {
  public:
    CollisionEventManager(CollisionEventManager const&)  = delete;  //!< Needed for singleton.
    void operator=(CollisionEventManager const&)    = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The unique instance of the CollisionEventManager.
     */
    static CollisionEventManager& getInstance() {
      static CollisionEventManager instance;
      return (instance);
    }

    /** Run the handler associated to the Timer.
     * \param id Timer id
     */
    /*void run(TimeEvent *event) {
      uint64_t id = event->getTimerId();
      handlers[id]->run(event);
      handlers.erase(id);
    }*/

  private:
    /** \brief Empty Constructor.
     */
    TimeEventManager() : handlers() {};

    std::map<uint64_t, TimeHandler*> handlers;
};

}  // namespace zbe

#endif // CORE_EVENTS_MANAGERS_TIMEEVENTHANDLER_H
