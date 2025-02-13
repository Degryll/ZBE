/**
 * Copyright 2011 Batis Degryll Ludo
 * @file zbe.h
 * @since 2015-05-16
 * @date 2018-03-27
 * @author Degryll Ludo Batis
 * @brief all zbe container tools.
 */

#ifndef ZBE_CORE_ZBE_H_
#define ZBE_CORE_ZBE_H_

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/containers.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/io/Input.h"

namespace zbe {
ZBEAPI void init(RsrcDictionary<ZBE_K>& zbekRsrc = RsrcDictionary<ZBE_K>::getInstance());
}  // namespace zbe

#endif  // ZBE_CORE_ZBE_H_
