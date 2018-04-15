#ifndef ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H
#define ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/InteractionTester.h"
#include "ZBE/entities/avatars/Stated.h"

#include "entities/avatars/CustomVector.h"
#include "entities/avatars/Solid.h"
#include "entities/avatars/Breakable.h"
#include "entities/avatars/Wall.h"
#include "entities/avatars/Magnet.h"
#include "entities/avatars/Boombizer.h"

namespace zombienoid {

class ZombienoidReactor {
public:
  virtual ~ZombienoidReactor() {}

  virtual void act() {}

  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::InteractionTester> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Stated> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<CustomVector> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Solid> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Magnet<2> > >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Breakable> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Wall> >) {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Boombizer> >) {}

};

}  // zombienoid

#endif // ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H