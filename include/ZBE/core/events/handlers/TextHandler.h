/**
 * Copyright 2015 Batis Degryll Ludo
 * @file TextHandler.h
 * @since 2020-04-01
 * @date 2020-04-01
 * @author Degryll
 * @brief Receives a text input(keyboard) event and reacts to that.
 */

#ifndef ZBE_CORE_EVENTS_HANDLERS_TEXTHANDLER_H
#define ZBE_CORE_EVENTS_HANDLERS_TEXTHANDLER_H

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Receives a  text input(keyboard) event and reacts to that.
 */
class TextHandler {
public:

  /** \brief Destructor.
   */
  virtual ~TextHandler() {}

  /** \brief Do the Handler job.
   */
  virtual void run(std::string text) = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_HANDLERS_TEXTHANDLER_H
