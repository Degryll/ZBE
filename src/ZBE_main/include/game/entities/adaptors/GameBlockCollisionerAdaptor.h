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
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"
#include "game/entities/GameBlock.h"

namespace game {

/** \brief Adapts a gameBrick to a Collisioner.
 */
class GameBlockCollisionerAdaptor : public zbe::Adaptor<zbe::Interactioner<GameReactor> > {
public:
  GameBlockCollisionerAdaptor(const GameBlockCollisionerAdaptor&) = delete;
  void operator=(const GameBlockCollisionerAdaptor&) = delete;

  GameBlockCollisionerAdaptor(std::weak_ptr<GameBlock> block): b(block), c(nullptr) {}
  ~GameBlockCollisionerAdaptor() {delete c;}
  zbe::Interactioner<GameReactor>* getAvatar() {
      delete c;
      std::shared_ptr<GameBlock> ball = b.lock();
      zbe::Point<2> max {ball->getPosition()[0] + ball->getW(), ball->getPosition()[1] + ball->getH()};
      std::shared_ptr<zbe::CollisionObject > co = std::make_shared<zbe::StaticSolidAABB2D >(zbe::AABB2D(ball->getPosition(), max));
      std::shared_ptr<zbe::ReactObject<GameReactor> > ro = std::make_shared<zbe::ReactObjectCommon<GameReactor> >();
      c = new zbe::InteractionerCommon<GameReactor, void>(std::make_shared<zbe::WeakAvatarEntityContainer<void> >(), co, ro, ball->getActuatorsList());
      return (c);
    }

private:
	std::weak_ptr<GameBlock> b;
	zbe::Interactioner<GameReactor>* c;
};

}  // namespace game

#endif  // GAME_ENTITIES_ADAPTORS_GAMEBLOCKCOLLISIONERADAPTOR_H_
