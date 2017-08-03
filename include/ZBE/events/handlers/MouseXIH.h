/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MouseXIH.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that uses the MouseKeeper to store the mouse X
 */

#ifndef ZBE_EVENTS_HANDLERS_MOUSEXIH
#define ZBE_EVENTS_HANDLERS_MOUSEXIH

#include <cstdlib>

#include "ZBE/core/events/handlers/InputHandler.h"

namespace zbe {

class MouseXIH : public zbe::InputHandler {
public:
  MouseXIH(const MouseXIH&) = delete; //!< Deleted copy constructor.
  void operator=(const MouseXIH&) = delete; //!< Deleted operator.

  /** brief Parametrized constructor
    * param entity Positionable whose x will be modified.
   */
  MouseXIH(std::shared_ptr<AvatarEntity<Positionable<2> > > entity) : e(entity) {}

  /** brief Modifies the X position of an entity with the x position from the mouse.
    * param entity Entity whose x will be modified.
   */
  void run(float status) {

    Positionable<2>* avatar;
    e->assignAvatar(&avatar);
    avatar->getPosition()[0] = status;
  }

private:
  std::shared_ptr<AvatarEntity<Positionable<2> > > e;
};
} //namespace zbe

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_MOUSEXIH
