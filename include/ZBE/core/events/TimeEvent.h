/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventDispatcher.h
 * @since 2016-12-27
 * @date 2016-12-27
 * @author Degryll Ludo
 * @brief An event caused by time.
 */

#ifndef CORE_EVENTS_TIMEEVENT_H
#define CORE_EVENTS_TIMEEVENT_H

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/events/Event.h"

namespace zbe {

/** \brief An event caused by time.
 */
class TimeEvent : public Event {
  public:

    TimeEvent(const TimeEvent& rhs) = delete;       //!< Avoid copy.
    void operator=(const TimeEvent& rhs) = delete;  //!< Avoid copy.

    /** \brief Basic constructor
     *
     * \param id Represents the global id of this event.
     * \param time Exact moment in which it occurred
     * \param handler Time handler that will be executed when the event is triggered.
     *
     */
    TimeEvent(uint64_t id, int64_t time, TimeHandler* handler) : Event(id, time), handler(handler) {}

    /** \brief base destructor.
    */
    ~TimeEvent() {delete handler;}

    /** \brief Return the handler that will be executed when the event is triggered.
    *
    * \return The TimeHandler.
    *
    */
    TimeHandler* getHandler() {
        return (handler);
    }

    /** \brief Manage the current event and, presumably,
     * do the actions associated with it.
     */
    void manage() {
        handler->run();
    };

  private:
    TimeHandler* handler;
};

} // namespace zbe
#endif // CORE_EVENTS_TIMEEVENT_H
