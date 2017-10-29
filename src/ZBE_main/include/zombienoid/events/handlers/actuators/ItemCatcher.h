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

namespace zombienoid {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R>
class ItemCatcher: public zbe::Actuator<zbe::Stated, R> {
public:

  ItemCatcher(): items(){}

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<zbe::Stated> > weakAEC) {
      zbe::Stated* stated;
      weakAEC->get()->assignAvatar(&stated);
      uint64_t state = stated->getState();
      if (state>=0 && state<items.size()) {
        items[state]->run();
      }
  }

  void addItem(std::shared_ptr<zbe::Daemon> d){
      items.push_back(d);
  }

private:
  std::vector<std::shared_ptr<zbe::Daemon> > items;
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_ITEMCATCHER
