/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputToValue.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUTTOVALUE_H_
#define ZBE_EVENTS_HANDLERS_INPUTTOVALUE_H_

#include <cstdlib>
#include <memory>

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Handler that stores input value to a Value<double>
 */
class InputToValue : public InputHandler {
public:
  InputToValue(const InputToValue&) = delete; //!< Deleted copy constructor.
  void operator=(const InputToValue&) = delete; //!< Deleted operator.

  /** brief Parametrized constructor
    * param value where to store input.
   */
  InputToValue(std::shared_ptr<zbe::Value<double> > val) : val(val) {}

  /** brief stores input value to the value.
    * param status value from input.
   */
  void run(uint32_t, float status) {
    val->set(status);
  }

private:
  std::shared_ptr<zbe::Value<double> > val;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUTTOVALUE_H_
