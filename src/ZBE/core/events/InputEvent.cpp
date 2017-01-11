/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputEvent.cpp
 * @since 2016-12-28
 * @date 2016-12-28
 * @author Ludo
 * @brief  An event caused by input devices.
 */

#include "ZBE/core/events/InputEvent.h"

namespace zbe {


void InputEvent::manage() {
  handler->run(state);
}

}
