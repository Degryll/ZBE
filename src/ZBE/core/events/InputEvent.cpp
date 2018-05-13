/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputEvent.cpp
 * @since 2016-12-28
 * @date 2018-03-27
 * @author Ludo Degryll Batis
 * @brief  An event caused by input devices.
 */

#include "ZBE/core/events/InputEvent.h"

namespace zbe {

void InputEvent::manage() {
  handler->run(key, state);
}

}  // namespace zbe
