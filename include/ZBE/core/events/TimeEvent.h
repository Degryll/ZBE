#ifndef CORE_EVENTS_TIMEEVENT_H
#define CORE_EVENTS_TIMEEVENT_H

#include "./Event.h"

namespace zbe {
/** \brief An event caused by time.
 */
class TimeEvent : public Event {
    public:

        /** \brief Basic constructor
         *
         * \param timerId
         * \param id Represents the global id of this event.
         * \param time Exact moment in which it occurred
         *
         */
        TimeEvent(uint64_t id, uint64_t time, uint64_t timerId):Event(id,time),timerId(timerId) {}

        ~TimeEvent() {}

        /** \brief Get the id from this even as timer.
        *
        * \return An integer that identifies the time event.
        *
        */
        uint64_t getTimerId() {
            return timerId;
        }

    private:

        uint64_t timerId;
};
}

#endif // CORE_EVENTS_TIMEEVENT_H
