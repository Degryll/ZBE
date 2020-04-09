/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TextEvent.cpp
 * @since 2020-04-01
 * @date 2020-04-01
 * @author Degryll
 * @brief  A text event caused by input devices.
 */

#include "ZBE/core/events/TextEvent.h"

namespace zbe {

void TextEvent::manage() {
  handler->run(text);
}

}  // namespace zbe
