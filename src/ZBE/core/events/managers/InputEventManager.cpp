/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputEventManager.cpp
 * @since 2016-12-27
 * @date 2016-12-27
 * @author Ludo
 * @brief Manage input events.
 */

#include "ZBE/core/events/managers/InputEventManager.h"

namespace zbe {

void InputEventManager::run(InputEvent * event) {
  uint32_t id = event->getKey();
  handlers[id]->run(event->getState());
}

} //namespace zbe
