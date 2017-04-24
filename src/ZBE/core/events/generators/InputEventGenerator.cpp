/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2016-04-10
 * @author Ludo
 * @brief Input event generator, implementation file.
 */

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include <inttypes.h>
#include <iostream>

namespace zbe {

    void InputEventGenerator::generate() {
      std::vector<InputStatus> currentInput;
      inputBuffer->getRange(sysTime.getInitFrameTime(), sysTime.getEndFrameTime(), currentInput);
      for(auto it = currentInput.begin(); it != currentInput.end(); it++) {
        auto hit = handlers.find(it->getId());
        if (hit != handlers.end()) {
            InputEvent* e = new InputEvent(eventId, it->getTime(), it->getId(), it->getStatus(), hit->second);
            store.storeEvent(e);
        }
      }
    }

} // namespace zbe
