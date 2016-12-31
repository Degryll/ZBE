/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventManager.cpp
 * @since 2016-12-27
 * @date 2016-12-27
 * @author Ludo
 * @brief Manage input events.
 */

#include "ZBE/core/events/managers/TimeEventManager.h"
#include "ZBE/core/events/TimeEvent.h"

namespace zbe {

void TimeEventManager::run(TimeEvent * event) {
  event->getHandler()->run();
}

} //namespace zbe
