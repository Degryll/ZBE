/**
 * Copyright 2016 Batis Degryll Ludo
 * @file NetBuffer.h
 * @since 2016-08-21
 * @date 2018-03-20
 * @author Ludo
 * @brief Stores a ordered collection of NetMessages.
 * Its in charge of keep them ordered and discard those that have expired.
 */

#ifndef ZBE_CORE_IO_NETBUFFER_H
#define ZBE_CORE_IO_NETBUFFER_H

#include "ZBE/core/tools/containers/TimedBuffer.h"
#include "ZBE/core/io/NetMessage.h"

namespace zbe {

typedef TimedBuffer<NetMessage> NetBuffer;

}  // namespace zbe

#endif  // ZBE_CORE_IO_NETBUFFER_H
