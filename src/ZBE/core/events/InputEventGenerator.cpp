/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2016-04-10
 * @author Ludo
 * @brief Input event generator.
 */

#include "ZBE/core/events/InputEventGenerator.h"

namespace zbe {

    void InputEventGenerator::generate(uint64_t initTime, uint64_t finalTime) {
      std::list<uint32_t>* changes = inputReader->changes();
      EventStore &store = EventStore::getInstance();
      for(auto it = changes->begin(); it != changes->end(); it++) {
        uint32_t c = (*it);
        uint32_t t = inputReader->getTime(c);
        if(t>initTime && t<=finalTime){
            InputEvent* e = new InputEvent(eventId, t, c, inputReader->getStatus(c));
            store.storeEvent(e);
        }
      }

    }

} // namespace zbe
