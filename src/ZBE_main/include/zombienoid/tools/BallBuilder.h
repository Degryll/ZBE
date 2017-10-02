/**
 * Copyright 2015 Batis Degryll Ludo
 * @file BallBuilder.h
 * @since 2017-08-26
 * @date 2017-08-26
 * @author Degryll Ludo Batis
 * @brief A tool capable of build a ball with the same position an velocity as a given movable
 */

#ifndef ZBE_MAIN_ZOMBIENOID_TOOLS_BALLBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_TOOLS_BALLBUILDER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/ActiveElement2D.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"

#include "zombienoid/ZombienoidReactor.h"


namespace zombienoid {
/** \brief A tool capable of build a ball with the same position an velocity as a given movable
*/

template<typename T>
class Builder {
  public:
    virtual ~Builder(){};
    virtual void build(T* t) = 0;
};

template<typename CTL,typename ASL, typename BL>
class BallBuilder : virtual public Builder<zbe::Movable<2> > {
public:

  /** \brief Parametrized constructor.
   *  \param alId:   actuator list id
   *  \param cbslId: colisionables list id
   *  \param g:      graphics id

   *  \param s:      ball size
   *  \param nballs: ball count

   *  \param ctId:   collision ticket id
   *  \param dtId:   draw ticket id
   *  \param btId:   behavior ticket id

   *  \param ctl;    collisionator list
   *  \param asl;    animated sprite list
   *  \param bl;     ball list
   */
  BallBuilder( uint64_t alId, uint64_t cbslId, uint64_t g, int64_t s, std::shared_ptr<zbe::Value<int64_t> > nballs,
               uint64_t ctId, uint64_t dtId, uint64_t btId, std::shared_ptr<CTL> ctl,
               std::shared_ptr<ASL> asl,  std::shared_ptr<BL> bl)
               : alId(alId), cbslId(cbslId),g(g), s(s), nballs(nballs),
               ctId(ctId), dtId(dtId), btId(btId), ctl(ctl),
               asl(asl), bl(bl){}

  /** \brief It will build a ball with the same position an velocity as the given movable
   */
  void build(zbe::Movable<2>* movable){

    std::shared_ptr<zbe::ActiveElement2D<ZombienoidReactor> > ball(new zbe::CActiveElement2D<ZombienoidReactor>(nballs, movable->getPosition(), movable->getVelocity(), alId, cbslId, s, s, g));

    std::shared_ptr<zbe::Adaptor<zbe::AnimatedSprite> > ballSpriteAdaptor(new zbe::ActiveElement2DAnimatedSpriteAdaptor<ZombienoidReactor>(ball));
    setAdaptor(ball, ballSpriteAdaptor);

    std::shared_ptr<zbe::Adaptor<zbe::Collisionator<ZombienoidReactor> > > ballCollisionatorAdaptor(new BallCatorAdaptor<ZombienoidReactor>(ball));
    setAdaptor(ball, ballCollisionatorAdaptor);

    std::shared_ptr<zbe::AvatarEntityContainer<zbe::AnimatedSprite> > aecas;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2>, zbe::Bouncer<2> > > aecb2;

    zbe::wrapAEC(&aecas, ball);
    zbe::wrapAEC(&aecb2, ball);

    ball->addToList(ctId, ctl->push_front(ball));
    ball->addToList(dtId, asl->push_front(aecas));
    ball->addToList(btId, bl->push_front(aecb2));
  }

private:
  uint64_t alId; //<! actuator list id
  uint64_t cbslId; //<! colisionables list id
  uint64_t g; //<! graphics id

  int64_t s; //<! ball size
  std::shared_ptr<zbe::Value<int64_t> > nballs; //<! ball count

  uint64_t ctId; //<! collision ticket id
  uint64_t dtId; //<! draw ticket id
  uint64_t btId; //<! behavior ticket id

  std::shared_ptr<CTL> ctl; //<! collisionator list
  std::shared_ptr<ASL> asl; //<! animated sprite list
  std::shared_ptr<BL> bl;   //<! ball list

};


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_TOOLS_BALLBUILDER_H
