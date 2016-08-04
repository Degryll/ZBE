/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputEvent.h
 * @since 2016-03-26
 * @date 2016-03-26
 * @author Ludo
 * @brief An event for input devices.
 */

#ifndef CORE_EVENTS_INPUTEVENT_H
#define CORE_EVENTS_INPUTEVENT_H

#include "ZBE/core/events/Event.h"

namespace zbe {
/** \brief An event caused by input devices.
 */
class InputEvent : public Event {
    public:

        /** \brief Builds an InputEvent with the status and id of the associated input.
         *
         * \param id Represents the global id of this event.
         * \param time Exact moment in which it occurred
         * \param key Id of the input related with this event.
         * \param state The state of the related input as a value in the range (-1.0 .. +1.0).
         *
         */
        InputEvent(uint64_t id, uint64_t time, uint32_t key, float state):Event(id,time), key(key),state(state) {}

        ~InputEvent() {}

        /** \brief Get the id of the key related with this event.
        *
        * \return An integer that identifies the key.
        *
        */
        inline uint32_t getKey() {
            return key;
        }

        /** \brief Get the state of the related key as a value in the range (-1.0 .. +1.0).
        *
        * \return An float representing the state.
        *
        */
        inline float getState() {
            return state;
        }

    private:

        uint32_t key;

        float state;

};
}

#endif // CORE_EVENTS_INPUTEVENT_H
