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

    void InputEventGenerator::generate(uint64_t initTime, uint64_t finalTime) {
      std::vector<InputStatus> currentInput;
      inputBuffer->getRange(initTime, finalTime, currentInput);
      for(auto it = currentInput.begin(); it != currentInput.end(); it++) {
        InputEvent* e = new InputEvent(eventId, (*it).getTime(), (*it).getId(), (*it).getStatus());
        store.storeEvent(e);
      }
    }

} // namespace zbe