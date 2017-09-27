/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBlockCollisionerAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Adapts a gameBlock to a Collisioner.
 */

#ifndef GAME_ENTITIES_ADAPTORS_GAMEBLOCKCOLLISIONERADAPTOR_H_
#define GAME_ENTITIES_ADAPTORS_GAMEBLOCKCOLLISIONERADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/implementations/VoidCollisioner.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"
#include "game/entities/GameBlock.h"

namespace game {

/** \brief Adapts a gameBrick to a Collisioner.
 */
class GameBlockCollisionerAdaptor : public zbe::Adaptor<zbe::Collisioner<GameReactor> > {
public:
  GameBlockCollisionerAdaptor(const GameBlockCollisionerAdaptor&) = delete;
  void operator=(const GameBlockCollisionerAdaptor&) = delete;

  GameBlockCollisionerAdaptor(std::shared_ptr<GameBlock> block): b(block), c(nullptr) {}
  ~GameBlockCollisionerAdaptor() {delete c;}
  zbe::Collisioner<GameReactor>* getAvatar() {
      delete c;
    	zbe::Point<2> max {b->getPosition()[0] + b->getW(), b->getPosition()[1] + b->getH()};
      std::shared_ptr<zbe::CollisionObject<GameReactor> > co = std::make_shared<zbe::StaticSolidAABB2D<GameReactor> >(zbe::AABB2D(b->getPosition(), max));
      std::shared_ptr<zbe::ReactObject<GameReactor> > ro = std::make_shared<zbe::VoidReactObject<GameReactor> >();
      c = new zbe::VoidCollisioner<GameReactor>(co, ro, b->getActuatorsList());
      return (c);
    }

private:
	std::shared_ptr<GameBlock> b;
	zbe::Collisioner<GameReactor>* c;
};

}  // namespace game

#endif  // GAME_ENTITIES_ADAPTORS_GAMEBLOCKCOLLISIONERADAPTOR_H_
