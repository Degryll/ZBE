/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventManager.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Degryll
 * @brief Handle time events.
 */

#ifndef ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H
#define ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/events/EventDispatcher.h"

namespace zbe {

/** \brief Handle collision events.
 */
class TimeEventManager {
  public:
      TimeEventManager(TimeEventManager const&)  = delete;  //!< Needed for singleton.
      void operator=(TimeEventManager const&)    = delete;  //!< Needed for singleton.

      /** \brief Singleton implementation.
       *  \return The unique instance of the EventStore.
       */
      static TimeEventManager& getInstance() {
        static TimeEventManager instance;
        return (instance);
      }

//    /** \brief Empty destructor.
//    */
//    ~TimeEventGenerator() {};

    /** Run the handler associated to the Timer.
     * \param id Timer id
     */
    void run(TimeEvent *event) {
      event->getHandler()->run();
      delete event;
    }

  private:
    /** \brief Empty Constructor.
     */
    TimeEventManager() {};
};

}  // namespace zbe

#endif // ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H
