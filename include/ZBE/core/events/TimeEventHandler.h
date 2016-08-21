/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventHandler.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Degryll
 * @brief Handle time events.
 */

#ifndef CORE_EVENTS_TIMEEVENTHANDLER_H
#define CORE_EVENTS_TIMEEVENTHANDLER_H

#include <cstdint>
#include <map>

#include "ZBE/core/guards/TimeGuard.h"
#include "ZBE/core/events/eventDispatcher.h"

namespace zbe {

/** \brief Handle collision events.
 */
class TimeEventHandler {
  public:
      TimeEventHandler(TimeEventHandler const&)  = delete;  //!< Needed for singleton.
      void operator=(TimeEventHandler const&)    = delete;  //!< Needed for singleton.

      /** \brief Singleton implementation.
       *  \return The unique instance of the EventStore.
       */
      static TimeEventHandler& getInstance() {
        static TimeEventHandler instance;
        return (instance);
      }

//    /** \brief Empty destructor.
//    */
//    ~TimeEventGenerator() {};

    /** Add a guard to a timer event.
     * \param id Id of the Timer
     * \param guard Guard to run when this timer triggers
     */
    inline void addOnceGuard(uint64_t id, *TimeGuard guard) {once[id] = guard;}

    /** Add a guard to a timer event.
     * \param id Id of the Timer
     * \param guard Guard to run when this timer triggers
     */
    inline void addGuard(uint64_t id, *TimeGuard guard) {many[id] = guard;}

    /** Erase a Guard.
     * \param id Id of the timer
     */
    inline void eraseGuard(uint64_t id) {many.erase(id);}

    /** Run the guard associated to the Timer.
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
    TimeEventHandler() : guards() {};

    std::map<uint64_t id, *TimeGuard> once;
    std::map<uint64_t id, *TimeGuard> many;
};

}  // namespace zbe

#endif // CORE_EVENTS_TIMEEVENTHANDLER_H
