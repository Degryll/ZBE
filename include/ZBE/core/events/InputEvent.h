/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventDispatcher.h
 * @since 2016-08-15
 * @date 2018-03-20
 * @author Degryll Batis Ludo
 * @brief An event caused by input devices.
 */

#ifndef ZBE_CORE_EVENTS_EVENT_INPUTEVENT_H
#define ZBE_CORE_EVENTS_EVENT_INPUTEVENT_H

#include <cstdint>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief An event caused by input devices.
*/
class ZBEAPI InputEvent : public Event {
public:

  /** \brief Copy Constructor.
   */
  InputEvent(const InputEvent&) = delete;
  void operator=(const InputEvent&) = delete;

  /** \brief Builds an InputEvent with the status and id of the associated input.
   *
   * \param id Represents the global id of this event.
   * \param time Exact moment in which it occurred
   * \param key Id of the input related with this event.
   * \param state The state of the related input as a value in the range (-1.0 .. +1.0).
   * \param handler The handler that manages the event.
   *
   */
  InputEvent(uint64_t id, int64_t time, uint32_t key, float state, InputHandler* handler) : Event(id, time), key(key), state(state), handler(handler) {}

  /** \brief base destructor.
   */
  ~InputEvent() {}

  /** \brief Get the id of the key related with this event.
   * \return An integer that identifies the key.
   */
  inline uint32_t getKey() {
      return key;
  }

  /** \brief Get the state of the related key as a value in the range (-1.0 .. +1.0).
   * \return An float representing the state.
   */
  inline float getState() {
      return state;
  }

  /** \brief Manage the current event and, presumably,
   * do the actions associated with it.
   */
  void manage();

private:
  uint32_t key;
  float state;
  InputHandler* handler;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_EVENT_INPUTEVENT_H
