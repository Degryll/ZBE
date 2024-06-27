/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGenerator.h
 * @since 2016-08-17
 * @date 2018-03-18
 * @author Degryll
 * @brief Generate time events.
 */

#ifndef ZBE_CORE_EVENTS_TIMEEVENTGENERATOR_H
#define ZBE_CORE_EVENTS_TIMEEVENTGENERATOR_H

#include <cstdint>
#include <memory>
#include <set>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysError.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Stores de time of a timer, and the handler that will be launched when timer reaches 0;
 */
struct ZBEAPI TimerData {
  std::shared_ptr<TimeHandler> handler;    //!< A handler that will be executed when the event is triggered.
  uint64_t time;  //!< When time reaches 0, the time event is triggered.

  /** \brief Builds a TimerData with the TimeHandler and the time.
   *
   */
  TimerData(std::shared_ptr<TimeHandler> handler, uint64_t time) : handler(handler), time(time) {}
  inline bool operator<(const TimerData& rhs) const {return (this->time < rhs.time);}
};

/** \brief It gives access to a timer.
 *
 */
class ZBEAPI TimerTicket : public Ticket {
public:

  TimerTicket(const TimerTicket&) = delete;  //!< Avoid copy.
  void operator=(const TimerTicket&) = delete;  //!< Avoid copy.

  /** \brief Parametrized constructor
   *  \param iter Iterator from the timers multiset.
   *  \param timers The multiset where the timer is stored.
   *  \param eventId Event Id.
   */
  TimerTicket(std::multiset<TimerData>::iterator iter, std::multiset<TimerData>& timers, int eventId, std::shared_ptr<ContextTime> contextTime) : s(ACTIVE), iter(iter), timers(timers), eventId(eventId), es(EventStore::getInstance()), contextTime(contextTime), td((*iter)) {}

  void setACTIVE();    //!< Set the state as ACTIVE.
  void setINACTIVE();  //!< Set the state as INACTIVE.
  void setERASED();    //!< Set the state as ERASED
  void toggle();  //!< Set the state as state.

  void setState(State state);  //!< Set the state as state.

  inline bool isACTIVE()    {return (s == ACTIVE);}    //!< True if state is ACTIVE.
  inline bool isNotACTIVE() {return (s != ACTIVE);}    //!< True if state is not ACTIVE, either INACTIVE or ERASED.
  inline bool isINACTIVE()  {return (s == INACTIVE);}  //!< True if state is INACTIVE.
  inline bool isERASED()    {return (s == ERASED);}    //!< True if state is ERASED.

  State getState() {return (s);}  //!< Return the state of the ticket.

  /** \brief Increases the time in a given amount (that can be negative). If the incremented time is zero or less, the event is triggered.
   * return true if the increment makes the timer go to zero or less.
   */
  bool increaseTime(uint64_t increment);

  /** \brief Returns the event time.
   * \return The event time.
  */
  int64_t getTime() {
    return (iter->time);
  }

private:
  State s;  //!< State of the object
  std::multiset<TimerData>::iterator iter;
  std::multiset<TimerData>& timers;
  int eventId;
  EventStore& es;
  std::shared_ptr<ContextTime> contextTime;
  TimerData td;
};

/** \brief Generate collision events.
 */
class ZBEAPI TimeEventGenerator : virtual public Daemon {
  public:
    /** \brief Empty Constructor.
     */
    TimeEventGenerator() : eventId(), es(EventStore::getInstance()), timers(), contextTime() {}

    /** \brief Parametrized constructor.
     *  \param eventId event id.
     *  \param contextTime ContextTime to use.
     */
    TimeEventGenerator(uint64_t eventId, std::shared_ptr<ContextTime> contextTime = SysTime::getInstance()) : eventId(eventId), es(EventStore::getInstance()), timers(), contextTime(contextTime) {}

    /** Add a new Timer that only triggers onces.
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time The amount of time to wait until the time event is triggered
     * \return return A ticket used to modify or erase the timer.
     * \sa eraseTimer
     */
    inline std::shared_ptr<TimerTicket> addAbsoluteTimer(std::shared_ptr<TimeHandler> handler, uint64_t time) {
      return (std::make_shared<TimerTicket>(timers.insert(TimerData(handler,quantizeTime(time))), timers, eventId, contextTime));
    }

    /** Add a new Timer that only triggers onces.
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time The amount of time to wait until the time event is triggered
     * \return return A ticket used to modify or erase the timer.
     * \sa eraseTimer
     */
    inline std::shared_ptr<TimerTicket> addRelativeTimer(std::shared_ptr<TimeHandler> handler, uint64_t time) {
      return addAbsoluteTimer(handler, contextTime->getEventTime() + time);
    }

    /** Set the event id that created events will have.
     * \param eventId event id.
     */
    void setEventId(uint64_t eventId) {
      this->eventId = eventId;
    }

    /** Set the ContextTime to use.
     * \param contextTime ContextTime to use.
     */
    void setContextTime(std::shared_ptr<ContextTime> contextTime) {
      this->contextTime = contextTime;
    }

    /** \brief It will look for time events occurred within the available.
     */
    void run() override;

  private:
    uint64_t eventId;
    EventStore& es;
    std::multiset<TimerData> timers;
    std::shared_ptr<ContextTime> contextTime;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_TIMEEVENTGENERATOR_H
