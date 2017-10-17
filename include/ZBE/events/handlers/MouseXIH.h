/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MouseXIH.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that uses the MouseKeeper to store the mouse X into a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_MOUSEXIH
#define ZBE_EVENTS_HANDLERS_MOUSEXIH

#include <cstdlib>

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/events/handlers/InputHandler.h"

namespace zbe {

class MouseXIH : public zbe::InputHandler {
public:
  MouseXIH(const MouseXIH&) = delete; //!< Deleted copy constructor.
  void operator=(const MouseXIH&) = delete; //!< Deleted operator.

  /** brief Parametrized constructor
    * param entity Positionable whose x will be modified.
   */
  MouseXIH(std::shared_ptr<zbe::Value<double> > xValue) : x(xValue) {}

  /** brief Stores the X position from the mouse on given Value<double>.
    * param status value from input.
   */
  void run(float status) {
    x->setValue(status);
  }

private:
  std::shared_ptr<zbe::Value<double> > x;
};
} //namespace zbe

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_MOUSEXIH
