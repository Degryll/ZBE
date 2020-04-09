/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputTextBuffer.h
 * @since 2016-08-21
 * @date 2018-03-20
 * @author Ludo
 * @brief Stores a ordered collection of InputStatus.
 * Its in charge of keep them ordered and discard those that have expired.
 */

#ifndef ZBE_CORE_IO_INPUTTEXTBUFFER_H
#define ZBE_CORE_IO_INPUTTEXTBUFFER_H

#include "ZBE/core/tools/containers/TimedBuffer.h"
#include "ZBE/core/io/InputText.h"

namespace zbe {

typedef TimedBuffer<InputText> InputTextBuffer;

}  // namespace zbe

#endif  // ZBE_CORE_IO_INPUTTEXTBUFFER_H
