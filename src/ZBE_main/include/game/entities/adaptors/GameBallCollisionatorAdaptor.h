/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBallCollisionatorAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Adapts a gameball to a Collisionator.
 */

#ifndef GAME_ENTITIES_ADAPTORS_GAMEBALLCOLLISIONATORADAPTOR_H_
#define GAME_ENTITIES_ADAPTORS_GAMEBALLCOLLISIONATORADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Interactionator.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"
#include "game/entities/GameBall.h"

namespace game {

/** \brief Adapts a gameball to a Collisionator.
 */
class GameBallCollisionatorAdaptor : public zbe::Adaptor<zbe::Interactionator<GameReactor> > {
public:
  GameBallCollisionatorAdaptor(const GameBallCollisionatorAdaptor&) = delete;
  void operator=(const GameBallCollisionatorAdaptor&) = delete;

  GameBallCollisionatorAdaptor(std::weak_ptr<GameBall> ball): b(ball), c(nullptr) {}
  ~GameBallCollisionatorAdaptor() {delete c;}
  zbe::Interactionator<GameReactor>* getAvatar() {
      delete c;
      std::shared_ptr<GameBall> ball = b.lock();
      std::shared_ptr<zbe::CollisionObject > co = std::make_shared<zbe::ConstantMovingCircle>(zbe::ConstantMovingCircle(zbe::Circle(ball->getPosition(), ball->getWidth()), ball->getVelocity()));
      std::shared_ptr<zbe::ReactObject<GameReactor> > ro = std::make_shared<zbe::ReactObjectCommon<GameReactor> >();
      //zbe::Bouncer<2>* bouncer;
      //((zbe::AvatarEntity<zbe::Bouncer<2> >*)b)->assignAvatar(&bouncer);
      c = new zbe::InteractionatorCommon<GameReactor, zbe::Bouncer<2> >(std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >(ball), co, ro, ball->getActuatorsList() ,ball->getCollisionablesList());
      return (c);
    }

private:
	std::weak_ptr<GameBall> b;
	zbe::Interactionator<GameReactor>* c;
};

}  // namespace game

#endif  // GAME_ENTITIES_ADAPTORS_GAMEBALLCOLLISIONATORADAPTOR_H_
