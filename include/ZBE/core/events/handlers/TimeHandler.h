/**
 * Copyright 2015 Batis Degryll Ludo
 * @file TimeHandler.h
 * @since 2016-08-21
 * @date 2018-03-18
 * @author Degryll, Ludo, Batis
 * @brief Receives a time event and reacts to that.
 */

#ifndef ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H
#define ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Receives a time event and reacts to it.
 */
class ZBEAPI TimeHandler {
public:

  /** \brief Destructor.
   */
  virtual ~TimeHandler() {}

  /** \brief Do the Handler job.
   */
  virtual void run(uint64_t time) = 0;

};

}  // namespace zbe

#endif // ZBE_CORE_EVENTS_HANDLERS_TIMEHANDLER_H
