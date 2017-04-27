#ifndef ZBE_MAIN_LUDO_GAMEREACTOR
#define ZBE_MAIN_LUDO_GAMEREACTOR

#include "ZBE/reactobjects/VoidReactObject.h"

#include "ludo/entities/LudoEntities.h"

namespace ludo {

class VoidReactObject;

class LudoReactor {
public:
  virtual ~LudoReactor() {}

  virtual void act(zbe::VoidReactObject<LudoReactor>*) {}

  virtual void act(DestroyerReactObject<LudoReactor>*) {}

};

}  // namespace

#endif // ZBE_MAIN_LUDO_GAMEREACTOR
