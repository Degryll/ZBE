/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ItemCatcher.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity.
 */

#ifndef ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_ITEMCATCHER
#define ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_ITEMCATCHER

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"

namespace zbe {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R>
class ItemCatcher: public zbe::Actuator<Stated, R> {
public:

  ItemCatcher(std::shared_ptr<Value<int64_t> > lifes): l(lifes){}
  void act(zbe::Stated*) {
      l->add(1);
  }

private:
  std::shared_ptr<Value<int64_t> > l;
};

}  // namespace zbe

#endif // ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_ITEMCATCHER
