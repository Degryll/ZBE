/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputStatusManager.h
 * @since 2018-05-09
 * @date 2018-05-09
 * @author Batis Ludo Degryll
 * @brief Interface for tools that manage an InpustStatus and generate events. Used in the inputEvent Generator.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTSTATUSMANAGER_H
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTSTATUSMANAGER_H

#include <memory>
#include <unordered_map>

#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"

namespace zbe {

class InputStatusManager {
public:
  virtual ~InputStatusManager() {}

  /** \brief Generate events if the InputStatus match some condition.
   *  Implementation dependant.
   *  \param is InputStatus to check
   */
  virtual void generate(const InputStatus& is) = 0;

};

class MappedInputStatusManager : public InputStatusManager {
public:
  MappedInputStatusManager(int eventId) : eventId(eventId), store(EventStore::getInstance()), handlers() {}
  virtual ~MappedInputStatusManager() {}

  /** Add a handler to an input event.
   * \param id Id of the key
   * \param handler Handler to run when key pressed
   */
  inline void addHandler(uint32_t inputId, InputHandler* handler) {handlers[inputId] = handler;}

  /** Remove a handler from an input event.
   * \param id Id of the key
   */
  inline void removeHandler(uint32_t inputId) {handlers.erase(inputId);}

  void generate(const InputStatus& is) {
    auto hit = handlers.find(is.getId());
    if (hit != handlers.end()) {
        InputEvent* e = new InputEvent(eventId, is.getTime(), is.getId(), is.getStatus(), hit->second);
        store.storeEvent(e);
    }
  }

private:

  uint64_t eventId;
  EventStore &store;
  std::unordered_map<uint32_t, InputHandler*> handlers;

};

class RangedInputStatusManager : public InputStatusManager {
public:
  virtual ~RangedInputStatusManager() {}

  virtual void generate(const InputStatus& is) = 0;

};

class AnyInputStatusManager : public InputStatusManager {
public:
  virtual ~AnyInputStatusManager() {}

  virtual void generate(const InputStatus& is) = 0;

};


}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTSTATUSMANAGER_H
