#ifndef ZBE_MAIN_LUDO_GAMEREACTOR
#define ZBE_MAIN_LUDO_GAMEREACTOR

#include <memory>

#include "ludo/entities/LudoEntities.h"

#include "ZBE/core/entities/AvatarEntity.h"

namespace ludo {

class VoidReactObject;

class LudoReactor {
public:
  virtual ~LudoReactor() {}

  virtual void act() {}

  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Destroyer> >) {}

};

}  // namespace

#endif // ZBE_MAIN_LUDO_GAMEREACTOR
