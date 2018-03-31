/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ItemBuilder.h
 * @since 2017-10-08
 * @date 2017-10-08
 * @author Degryll Ludo Batis
 * @brief A tool capable of build an item with the same position an velocity as a given movable
 */

#ifndef ZBE_MAIN_ZOMBIENOID_TOOLS_ITEMBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_TOOLS_ITEMBUILDER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Positionable.h"

#include "ZBE/entities/ActiveElement2D.h"

#include "entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "entities/adaptors/ItemCatorAdaptor.h"

namespace zombienoid {

/** \brief A tool capable of build a ball with the same position an velocity as a given movable
*/
template<typename R, typename CTL,typename ASL, typename BL>
class ItemBuilder : virtual public zbe::Behavior<zbe::Positionable<2> > {
public:

  /** \brief Parametrized constructor.
   *  \param alId:   actuator list id
   *  \param cbslId: colisionables list id
   *  \param g:      graphics id

   *  \param s:      item size
   *  \param v:      item fall speed

   *  \param ctId:   collision ticket id
   *  \param dtId:   draw ticket id
   *  \param btId:   behavior ticket id

   *  \param ctl;    collisionator list
   *  \param asl;    animated sprite list
   *  \param iteml;  item list
   */

  ItemBuilder( uint64_t alId, uint64_t cbslId, uint64_t g, int64_t width, int64_t height, int64_t maxState, double vel,
               uint64_t ctId, uint64_t dtId, uint64_t btId, std::shared_ptr<CTL> ctl,
               std::shared_ptr<ASL> asl,  std::shared_ptr<BL> iteml)
               : alId(alId), cbslId(cbslId),g(g), width(width), height(height), maxState(maxState), velocity({0,vel}),
               ctId(ctId), dtId(dtId), btId(btId), ctl(ctl),
               asl(asl), iteml(iteml){}

  /** \brief It will build an item with the same position as the given positionable.
   */
  void apply(std::shared_ptr<zbe::AvatarEntityContainer< zbe::Positionable<2> > > aecm) {
    zbe::Positionable<2>* pable;
    assignAvatar(aecm->get(), &pable);

    std::shared_ptr<zbe::ActiveElement2D<R> > item(new zbe::ActiveElement2D<R>(pable->getPosition(), velocity, alId, cbslId, width, height, g));
    int64_t state = (rand() % maxState);
    item->setState(state);

    std::shared_ptr<zbe::Adaptor<zbe::AnimatedSprite> > itemSpriteAdaptor(new ActiveElement2DAnimatedSpriteAdaptor<R>(item));
    setAdaptor(item, itemSpriteAdaptor);

    std::shared_ptr<zbe::Adaptor<zbe::Collisionator<R> > > itemCollisionatorAdaptor(new ItemCatorAdaptor<R>(item));
    setAdaptor(item, itemCollisionatorAdaptor);

    std::shared_ptr<zbe::AvatarEntityContainer<zbe::AnimatedSprite> > aecas = std::make_shared<zbe::AvatarEntityContainer<zbe::AnimatedSprite> >(item);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Bouncer<2>, zbe::Avatar> > aecb2 = std::make_shared<zbe::AvatarEntityContainer<zbe::Bouncer<2>, zbe::Avatar > >(item, item);

    item->addToList(ctId, ctl->push_front(item));
    item->addToList(dtId, asl->push_front(aecas));
    item->addToList(btId, iteml->push_front(aecb2));
  }

private:
  uint64_t alId; //<! actuator list id
  uint64_t cbslId; //<! colisionables list id
  uint64_t g; //<! graphics id

  int64_t width; //<! ball size
  int64_t height; //<! ball size
  int64_t maxState;
  zbe::Vector<2> velocity;

  uint64_t ctId; //<! collision ticket id
  uint64_t dtId; //<! draw ticket id
  uint64_t btId; //<! behavior ticket id

  std::shared_ptr<CTL> ctl; //<! collisionator list
  std::shared_ptr<ASL> asl; //<! animated sprite list
  std::shared_ptr<BL> iteml;   //<! ball list

};


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_TOOLS_ITEMBUILDER_H
