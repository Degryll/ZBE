#ifndef ZBE_MAIN_LUDO_GAMEREACTOR
#define ZBE_MAIN_LUDO_GAMEREACTOR

#include "ZBE/reactobjects/VoidReactObject.h"

namespace ludo {

class VoidReactObject;

class LudoReactor {
public:
  virtual ~LudoReactor() {}

  virtual void act(zbe::VoidReactObject<LudoReactor>*) {}
};

}  // namespace

#endif // ZBE_MAIN_LUDO_GAMEREACTOR
