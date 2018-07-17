/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2018-03-27
 * @author Ludo Batis Degryll
 * @brief Input event generator, implementation file.
 */

#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zbe {

void InputEventGenerator::run() {
  std::vector<InputStatus> currentInput;
  inputBuffer->getRange(contextTime->getInitFrameTime(), contextTime->getEndFrameTime(), currentInput);
  for(auto input : currentInput) {
    for(auto manager : managers){
      manager->generate(input);
    }
  } // for each currentInput
}

}  // namespace zbe
