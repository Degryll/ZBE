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

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/events/handlers/Actuator.h"

namespace zbe {

template<typename R>
class CollisionEvent2D;

/** \brief Handle collision events.
 */
template<typename R>
class CollisionEventManager {
  public:
    CollisionEventManager(CollisionEventManager<R> const&)  = delete;  //!< Needed for singleton.
    void operator=(CollisionEventManager<R> const&)    = delete;  //!< Needed for singleton.

    ~CollisionEventManager();

    /** \brief Singleton implementation.
     *  \return The unique instance of the CollisionEventManager.
     */
    static CollisionEventManager<R>& getInstance() {
      static CollisionEventManager<R> instance;
      return (instance);
    }

    /** Run the handler associated to the Timer.
     * \param id Timer id
     */
    void run(CollisionEvent2D<R> * event) {
      Collisioner<R>*  c = event->getCollisioner();
    }

  private:
    /** \brief Empty Constructor.
     */
    CollisionEventManager() {};

};

template<typename R>
CollisionEventManager<R>::~CollisionEventManager(){}

}  // namespace zbe

#endif // CORE_EVENTS_MANAGERS_TIMEEVENTHANDLER_H
