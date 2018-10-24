/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysIdGenerator.h
 * @since 2017-05-15
 * @date 2017-05-15
 * @author Degryll
 * @brief A system class ZBEAPI to get unique Ids.
 */

#ifndef ZBE_CORE_SYSTEM_SYSIDGENERATOR_H_
#define ZBE_CORE_SYSTEM_SYSIDGENERATOR_H_

#include <cstdint>
#include <atomic>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A system class ZBEAPI to get unique Ids.
 */
class ZBEAPI SysIdGenerator {
public:

  /** \brief Each time it's called return an unique id.
   * \return A new Id.
   */
  static uint64_t getId();

private:
    SysIdGenerator() {};

    static std::atomic<uint64_t> id;
};

}  // namespace zbe

#endif  // ZBE_CORE_SYSTEM_SYSIDGENERATOR_H_
