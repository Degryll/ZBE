#ifndef ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H
#define ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/events/generators/util/Reactor.h"
#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"

#include "ZBE/entities/avatars/InteractionTester.h"
#include "ZBE/entities/avatars/Stated.h"

#include "entities/avatars/CustomVector.h"
#include "entities/avatars/Solid.h"
#include "entities/avatars/Breakable.h"
#include "entities/avatars/Wall.h"
#include "entities/avatars/Magnet.h"
#include "entities/avatars/Boombizer.h"

namespace zombienoid {

typedef zbe::Reactor<zbe::CollisionData, zbe::CollisionObject, zbe::InteractionTester, zbe::Stated, CustomVector, Solid, Magnet<2>, Breakable, Wall, Boombizer> ZombienoidReactor;

}  // zombienoid

#endif // ZBE_MAIN_ZOMBIENOID_ZOMBIENOIDREACTOR_H
