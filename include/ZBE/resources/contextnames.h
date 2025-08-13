/**
 * Copyright 2015 Batis Degryll Ludo
 * @file contextnames.h
 * @since 2018-07-08
 * @date 2018-07-08
 * @author Batis Degryll Ludo
 * @brief Constant's file for context names.
 */

#ifndef ZBE_RESOURCES_CONTEXTNAMES_H_
#define ZBE_RESOURCES_CONTEXTNAMES_H_

#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {
struct cn {
DISABLE_DLL_WARN
  ZBEAPI static const std::string SEPARATOR;

  ZBEAPI static const std::string IMGDEF;
  ZBEAPI static const std::string AUDIO;
  ZBEAPI static const std::string STATE;
  ZBEAPI static const std::string SPRTSHEET;

DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_RESOURCES_CONTEXTNAMES_H_
