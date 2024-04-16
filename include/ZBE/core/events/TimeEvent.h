/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventDispatcher.h
 * @since 2016-12-27
 * @date 2018-03-20
 * @author Degryll Ludo
 * @brief An event caused by time.
 */

#ifndef CORE_EVENTS_TIMEEVENT_H
#define CORE_EVENTS_TIMEEVENT_H

#include <cstdint>
#include <memory>

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/events/Event.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief An event caused by time.
 */
class ZBEAPI TimeEvent : public Event {
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
  TimeEvent(uint64_t id, uint64_t time, std::shared_ptr<TimeHandler> handler) : Event(id, time), handler(handler) {}

  /** \brief base destructor.
   */
  ~TimeEvent() {}

  /** \brief Return the handler that will be executed when the event is triggered.
   *
   * \return The TimeHandler.
   *
   */
  std::shared_ptr<TimeHandler> getHandler() {
      return (handler);
  }

  /** \brief Manage the current event and, presumably,
   * do the actions associated with it.
   */
  void manage() {
      handler->run(getTime());
  };

private:
  std::shared_ptr<TimeHandler> handler;
};

}  // namespace zbe

#endif  // CORE_EVENTS_TIMEEVENT_H
