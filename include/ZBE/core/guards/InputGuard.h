/**
 * Copyright 2015 Batis Degryll Ludo
 * @file InputGuard.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Batis
 * @brief Receives a keyboard event and reacts to that.
 */

#include "ZBE/core/events/InputEvent.h"
#ifndef CORE_GUARDS_INPUTGUARD_H
#define CORE_GUARDS_INPUTGUARD_H

namespace zbe {
  /** \brief Receives a keyboard event and reacts to that.
   */
  class InputGuard {
    public:

      /** \brief Do the Guard job.
       */
      virtual void run(InputEvent* e) = 0;

      /** \brief Destructor.
       */
      virtual ~InputGuard(){};
  };
}

#endif // CORE_GUARDS_INPUTGUARD_H
