/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TextEvent.h
 * @since 2020-04-01
 * @date 2020-04-01
 * @author Degryll
 * @brief A text event caused by input devices.
 */

#ifndef ZBE_CORE_EVENTS_EVENT_TEXTEVENT_H
#define ZBE_CORE_EVENTS_EVENT_TEXTEVENT_H

#include <cstdint>
#include <memory>
#include <string>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/handlers/TextHandler.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief An event caused by input devices.
*/
class ZBEAPI TextEvent : public Event {
public:

  /** \brief Copy Constructor.
   */
  TextEvent(const TextEvent&) = delete;
  void operator=(const TextEvent&) = delete;

  /** \brief Builds a TextEvent.
   *
   * \param id Represents the global id of this event.
   * \param time Exact moment in which it occurred
   * \param text The text of the input.
   * \param handler The handler that manages the event.
   *
   */
  TextEvent(uint64_t id, uint64_t time, std::string text, std::shared_ptr<TextHandler> handler) : Event(id, time), text(text), handler(handler) {}

  /** \brief base destructor.
   */
  ~TextEvent() {}

  /** \brief Get the text of this event.
   * \return A string.
   */
  inline std::string getText() {
      return text;
  }

  /** \brief Manage the current event and, presumably,
   * do the actions associated with it.
   */
  void manage();

private:
  std::string text;
  std::shared_ptr<TextHandler> handler;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_EVENT_TEXTEVENT_H
