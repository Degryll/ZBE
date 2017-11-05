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
class ItemCatcher: public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, R> {
public:

  ItemCatcher(std::shared_ptr<zbe::Value<int64_t> > totalPoints): items(), daemonPoints(), totalPoints(totalPoints) {}

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<zbe::Stated> > weakAEC) {
      zbe::Stated* stated;
      weakAEC->get()->assignAvatar(&stated);
      uint64_t state = stated->getState();
      if (state>=0 && state<items.size()) {
        items[state]->run();
        totalPoints->add(daemonPoints[state]);
      }
  }

  void addItem(std::shared_ptr<zbe::Daemon> daemon, int64_t points){
      items.push_back(daemon);
      daemonPoints.push_back(points);
  }

private:

  std::vector<std::shared_ptr<zbe::Daemon> > items;
  std::vector<int64_t> daemonPoints;
  std::shared_ptr<zbe::Value<int64_t> > totalPoints;

};

class DummyItem : virtual public zbe::Daemon {
  void run() {};
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_ITEMCATCHER
