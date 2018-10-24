/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysIdGenerator.cpp
 * @since 2017-05-15
 * @date 2018-03-27
 * @author Degryll Batis Ludo
 * @brief A system class ZBEAPI to get unique Ids.
 */

#include "ZBE/core/system/SysIdGenerator.h"

namespace zbe {

std::atomic<uint64_t> SysIdGenerator::id(1);

uint64_t SysIdGenerator::getId() {
  return (id++);
}

}  // namespace zbe
