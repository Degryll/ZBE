#ifndef ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H
#define ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H

#include "ZBE/reactobjects/VoidReactObject.h"
#include "ZBE/events/reactobjects/InteractionTesterRO.h"

namespace zombienoid {

class VoidReactObject;

class ZombienoidReactor {
public:
  virtual ~ZombienoidReactor() {}

  virtual void act(zbe::VoidReactObject<ZombienoidReactor>*) {}

  virtual void act(zbe::InteractionTesterRO<ZombienoidReactor>*) {}

  virtual void act(zbe::Stated*) {}

};

}  // zombienoid

#endif // ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H
