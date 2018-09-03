/**
 * Copyright 2018 Batis Degryll Ludo
 * @file OALAudioStore.h
 *
 * @since 2018-08-28
 * @date 2018-08-28
 * @author Degryll Ludo
 * @brief Utility functions for OAL
 */

#ifndef ZBE_OAL_TOOLS_OALUTILS_H_
#define ZBE_OAL_TOOLS_OALUTILS_H_

#include <string>

#include <AL/al.h>
#include <AL/alc.h>

namespace zbe {

std::string formattedOALError(ALCenum error);

bool isOALError(ALCenum error);

}  // namespace zbe

#endif  // ZBE_OAL_TOOLS_OALUTILS_H_
