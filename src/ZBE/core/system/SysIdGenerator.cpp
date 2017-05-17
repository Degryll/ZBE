/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysIdGenerator.cpp
 * @since 2017-05-15
 * @date 2017-05-15
 * @author Degryll
 * @brief A system class to get unique Ids.
 */

#include <cstdint>

#include "ZBE/core/system/SysIdGenerator.h"

namespace zbe {

std::atomic<uint64_t> SysIdGenerator::id(0);

uint64_t SysIdGenerator::getId() {
  return (id++);
}

}  // namespace zbe
