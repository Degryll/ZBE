/**
 * Copyright 2015 Batis Degryll Ludo
 * @file InputHandler.h
 * @since 2016-08-21
 * @date 2018-03-18
 * @author Batis Degryll Ludo
 * @brief Receives a input(keyboard, mouse, etc) event and reacts to that.
 */

#ifndef ZBE_CORE_EVENTS_HANDLERS_INPUTHANDLER_H
#define ZBE_CORE_EVENTS_HANDLERS_INPUTHANDLER_H

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Receives a input(keyboard, mouse, etc) event and reacts to that.
 */
class ZBEAPI InputHandler {
public:

  /** \brief Destructor.
   */
  virtual ~InputHandler() {}

  /** \brief Do the Handler job.
   */
  virtual void run(uint32_t key, float state) = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_HANDLERS_INPUTHANDLER_H
