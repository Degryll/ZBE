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
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

#include "ZBE/core/entities/adaptorentities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/adaptors/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"

namespace game {

/** \brief Adapts a gameball to a Collisionator.
 */
class GameBallCollisionatorAdaptor : public zbe::Adaptor<zbe::Collisionator<GameReactor> > {
public:
  GameBallCollisionatorAdaptor(const GameBallCollisionatorAdaptor&) = delete;
  void operator=(const GameBallCollisionatorAdaptor&) = delete;

  GameBallCollisionatorAdaptor(GameBall* ball): b(ball), c(nullptr) {}
  ~GameBallCollisionatorAdaptor() {delete c;}
  zbe::Collisionator<GameReactor>* getAvatar() {
      delete c;
      std::shared_ptr<zbe::CollisionObject<GameReactor> > co = std::make_shared<zbe::ConstantMovingCircle<GameReactor> >(zbe::ConstantMovingCircle<GameReactor>(zbe::Circle(b->getPosition(), b->getWidth()), b->getVelocity()));
      std::shared_ptr<zbe::ReactObject<GameReactor> > ro = std::make_shared<zbe::VoidReactObject<GameReactor> >();
      zbe::Bouncer<2>* bouncer;
      ((zbe::AvatarEntity<zbe::Bouncer<2> >*)b)->assignAvatar(&bouncer);
      zbe::Collisionator<GameReactor>* c = new zbe::CollisionatorCommon<zbe::Bouncer<2>, GameReactor>(bouncer, co, ro, b->getActuatorsList() ,b->getCollisionablesList());
      return (c);
    }

private:
	GameBall* b;
	zbe::Collisionator<GameReactor>* c;
};

}  // namespace game

#endif  // GAME_ENTITIES_ADAPTORS_GAMEBALLCOLLISIONATORADAPTOR_H_
