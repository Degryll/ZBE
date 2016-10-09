/**
 * Copyright 2015 Batis Degryll Ludo
 * @file TimeHandler.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Degryll
 * @brief Receives a time event and reacts to that.
 */

#ifndef CORE_GUARDS_INPUTGUARD_H
#define CORE_GUARDS_INPUTGUARD_H

#include "ZBE/core/events/TimeEvent.h"

namespace zbe {

  /** \brief Receives a time event and reacts to that.
   */
  class TimeHandler {
    public:

      /** \brief Do the Handler job.
       */
      virtual void run(TimeEvent* e) = 0;

      /** \brief Destructor.
       */
      virtual ~TimeHandler(){};
  };

}  // namespace zbe

#endif // CORE_GUARDS_INPUTGUARD_H
