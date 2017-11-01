/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ItemCatcher.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity.
 */

#ifndef ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H
#define ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H

#include <cstdio>

#include "ZBE/entities/avatars/Bouncer.h"

#include "zombienoid/entities/avatars/CustomVector.h"
#include "zombienoid/entities/avatars/Magnet.h"

namespace zombienoid {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R>
class MagnetSticker : public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> >, R>  {
public:

  MagnetSticker(): value(0){}

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<CustomVector> >) {
      value++;
  }

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<Magnet<2> > >) {
      value++;
  }

  void act(){
    if(value == 2) {
      printf("Flop!\n");fflush(stdout);
    }
    value = 0;
  }

private:
  int value;
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H
