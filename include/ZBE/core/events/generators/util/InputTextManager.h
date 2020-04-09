/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputTextManager.h
 * @since 2020-04-01
 * @date 2020-04-01
 * @author Degryll
 * @brief Text event manager to be used in the inputEvent Generator.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTTEXTMANAGER_H
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTTEXTMANAGER_H

#include <memory>

#include "ZBE/core/io/InputText.h"
#include "ZBE/core/events/handlers/TextHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TextEvent.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI InputTextManager {
public:
  InputTextManager(int eventId) : eventId(eventId), store(EventStore::getInstance()), handler(nullptr) {}

  ~InputTextManager() {}

  void setHandler(std::shared_ptr<TextHandler> handler) {
    this->handler = handler;
  }

  /** \brief Generate the event for the text if a TextHandler is attached.
   *  \param it InputText to check
   */
  void generate(const InputText& it) {
    if (handler != nullptr) {
      TextEvent* e = new TextEvent(eventId, it.getTime(), it.getText(), handler);
      store.storeEvent(e);
    }
  }

private:
  uint64_t eventId;
  EventStore &store;
  std::shared_ptr<TextHandler> handler;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_INPUTTEXTMANAGER_H
