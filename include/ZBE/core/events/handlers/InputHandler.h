/**
 * Copyright 2015 Batis Degryll Ludo
 * @file InputHandler.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Batis
 * @brief Receives a input(keyboard, mouse, etc) event and reacts to that.
 */

#ifndef CORE_GUARDS_INPUTGUARD_H
#define CORE_GUARDS_INPUTGUARD_H

#include "ZBE/core/events/InputEvent.h"

namespace zbe {

  /** \brief Receives a input(keyboard, mouse, etc) event and reacts to that.
   */
  class InputHandler {
    public:

      /** \brief Do the Handler job.
       */
      virtual void run(float state) = 0;

      /** \brief Destructor.
       */
      virtual ~InputHandler(){};
  };

}  // namespace zbe

#endif // CORE_GUARDS_INPUTGUARD_H
