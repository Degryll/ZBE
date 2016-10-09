/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventManager.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Degryll
 * @brief Handle time events.
 */

#ifndef CORE_EVENTS_TIMEEVENTHANDLER_H
#define CORE_EVENTS_TIMEEVENTHANDLER_H

#include <cstdint>
#include <map>

#include "ZBE/core/handlers/TimeHandler.h"
#include "ZBE/core/events/eventDispatcher.h"

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

    /** Add a handler to a timer event.
     * \param id Id of the Timer
     * \param handler Handler to run when this timer triggers
     */
    inline void addOnceHandler(uint64_t id, *TimeHandler handler) {once[id] = handler;}

    /** Add a handler to a timer event.
     * \param id Id of the Timer
     * \param handler Handler to run when this timer triggers
     */
    inline void addHandler(uint64_t id, *TimeHandler handler) {many[id] = handler;}

    /** Erase a Handler.
     * \param id Id of the timer
     */
    inline void eraseHandler(uint64_t id) {many.erase(id);}

    /** Run the handler associated to the Timer.
     * \param id Timer id
     */
    void run(TimeEvent event) {
      auto it = once.find(event.getId());
      if (it != once.end()) {
        (*it)->run(event);
        once.erase(it);
      }

      auto jt = many.find(event.getId());
      if (it != many.end()) {
        (*it)->run(event);
      }
    }

  private:
    /** \brief Empty Constructor.
     */
    TimeEventManager() : handlers() {};

    std::map<uint64_t id, *TimeHandler> once;
    std::map<uint64_t id, *TimeHandler> many;
};

}  // namespace zbe

#endif // CORE_EVENTS_TIMEEVENTHANDLER_H
