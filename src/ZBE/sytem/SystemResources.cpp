/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SystemResources.cpp
 * @since 2019-06-19
 * @date 2019-06-19
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all system resources.
 */


#include "ZBE/system/SystemResources.h"

namespace zbe {

static void SystemResources::load() {
  uint64_t id = RsrcStore<ContexTime>::getInstance().insert("ContexTime.SYSTEM"s, SysTime::getInstance());
  RsrcStore<SysTime>::getInstance().insert(id, SysTime::getInstance());
  dict.insert("SysTime.SYSTEM"s, id);
}

}  // namespace zbe
