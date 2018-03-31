/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallExploder.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of increase point when ball hit breakables.
 */

#ifndef ZOMBIENOID_EVENTS_HANDLERS_BALLEXPLODER
#define ZOMBIENOID_EVENTS_HANDLERS_BALLEXPLODER

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/ResourceManager.h"

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"

#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/events/generators/util/IntersectionCollisionSelector.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
//
#include "ZBE/events/handlers/time/TicketEraser.h"

#include "entities/avatars/implementations/SimpleScorer.h"
#include "entities/avatars/Scorer.h"
#include "entities/avatars/Solid.h"

namespace zombienoid {

template<typename R, typename BHL, typename CTL, typename CNL, typename ASL>
class BallExploder : public zbe::TimeHandler {
 public:

  BallExploder(const BallExploder&) = delete;
  void operator=(const BallExploder&) = delete;

  BallExploder(std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Resizable,zbe::Stated> > waecPRS,
               uint64_t eventId, uint64_t catorListId, uint64_t conerListId, uint64_t actuatorListId, uint64_t catorTicketId, uint64_t behavTicketId, uint64_t behavListId,
               uint64_t spriteListId, uint64_t graphsId, uint64_t state, int64_t graphTime, double ratio, uint64_t ticketId, std::shared_ptr<zbe::TimeEventGenerator> teg)
    : teg(teg), asList(zbe::ResourceManager<ASL>::getInstance().get(spriteListId)), catorList(zbe::ResourceManager<CTL>::getInstance().get(catorListId)),
      behavList(zbe::ResourceManager<BHL>::getInstance().get(behavListId)), iaeg(new InteractionGenerator(catorListId, eventId, new zbe::IntersectionCollisionSelector<R>())),
      waecPRS(waecPRS), state(state), conerListId(conerListId), actuatorListId(actuatorListId), catorTicketId(catorTicketId), behavTicketId(behavTicketId),
      behavListId(behavListId), graphsId(graphsId), graphTime(graphTime), ratio(ratio), ticketId(ticketId), ro() {
    auto aes = std::make_shared<zbe::AvatarEntityFixed<Solid> > (new Solid());
    std::shared_ptr<zbe::WeakAvatarEntityContainer<Solid> > weakAEC = std::make_shared<zbe::WeakAvatarEntityContainer<Solid> >(aes);
    ro = std::make_shared<zbe::ReactObjectCommon<R, Solid> >(weakAEC);
  }

  void run(uint64_t) {
    //Delete text timer
    //Avatars
    zbe::Avatar* avatar;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar> > waecA = waecPRS;
    std::shared_ptr<zbe::AvatarEntity<zbe::Avatar> > aea = waecA->get();
    if(!aea){return;}
    aea->assignAvatar(&avatar);
    avatar->setERASED(ticketId);

    zbe::Resizable* resizable;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Resizable> > waecR = waecPRS;
    std::shared_ptr<zbe::AvatarEntity<zbe::Resizable> > aer = waecR->get();
    if(!aer){return;}
    aer->assignAvatar(&resizable);

    zbe::Positionable<2>* pos2d;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Positionable<2> > > waecP2 = waecPRS;
    std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > aep2 = waecP2->get();
    if(!aep2){return;}
    aep2->assignAvatar(&pos2d);

    zbe::Stated* stated;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Stated > > waecS = waecPRS;
    std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = waecS->get();
    if(!aes){return;}
    aes->assignAvatar(&stated);

    //std::shared_ptr<zbe::WeakAvatarEntityContainer<> > waecVoid = std::make_shared<zbe::WeakAvatarEntityContainer<> >();
    //std::shared_ptr<zbe::ReactObjectCommon<R> > ro = std::make_shared<zbe::ReactObjectCommon<R> >();

    double radius = resizable->getSize() * ratio;

    zbe::Entity* ent = new zbe::Entity();
    std::shared_ptr<zbe::AvatarEntity<zbe::Avatar> > entity = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ent);
    std::shared_ptr<zbe::AvatarEntity<Scorer> > scorer = std::make_shared<zbe::AvatarEntityFixed<Scorer> >(new SimpleScorer());
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar, Scorer> > entityContainer = std::make_shared<zbe::AvatarEntityContainer<zbe::Avatar, Scorer> >(entity, scorer);
    std::shared_ptr<zbe::ConstantMovingCircle<R> > cObject = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle(pos2d->getPosition(), radius), zbe::Vector2D({0.0, 0.0}));
    zbe::CollisionatorCommon<R, Scorer>* cator;
    cator = new zbe::CollisionatorCommon<R, Scorer>(std::make_shared<zbe::WeakAvatarEntityContainer<Scorer> >(scorer), cObject, ro, actuatorListId, conerListId);
    std::shared_ptr<zbe::AvatarEntity<zbe::Collisionator<R> > > aeCator = std::make_shared<zbe::AvatarEntityFixed<zbe::Collisionator<R> > >(cator);
    ent->addToList(catorTicketId, catorList->push_front(aeCator));
    ent->addToList(behavTicketId, behavList->push_front(entityContainer));
    //std::shared_ptr<zbe::Ticket> catorTicket = ;
    //Collision detection
    iaeg->run();
    //Explosion Collionator erase
    // catorTicket->setERASED(); // A post-event behavior must do this
    //Ball restore.
    stated->setState(state);
    //Graphic entity erase timer.
    zbe::Point2D p = pos2d->getPosition();
    zbe::AnimatedSprite* as = new zbe::SimpleAnimatedSprite(p.x-radius, p.y-radius, radius*2, radius*2, graphsId, 0.0, 0, zbe::SysTime::getInstance().getEventTime());
    std::shared_ptr<zbe::AvatarEntity<zbe::AnimatedSprite> > aeAS = std::make_shared<zbe::AvatarEntityFixed<zbe::AnimatedSprite> >(as);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::AnimatedSprite> > aecAS = std::make_shared<zbe::AvatarEntityContainer<zbe::AnimatedSprite> >(aeAS);
    std::shared_ptr<zbe::Ticket> spriteTicket = asList->push_front(aecAS);
    //Graphic entity erase.
    teg->addTimer(std::make_shared<zbe::TicketEraser>(spriteTicket), zbe::SysTime::getInstance().getEventTime() + graphTime);

    //Return ball size to 1
    resizable->setSize(1);
  }

 private:
  using InteractionGenerator = zbe::InstantInteractionEventGenerator<R, zbe::CollisionSelector<R>, CNL, CTL>;
  std::shared_ptr<zbe::TimeEventGenerator> teg;
  std::shared_ptr<ASL> asList;
  std::shared_ptr<CTL> catorList;
  std::shared_ptr<BHL> behavList;
  std::shared_ptr<InteractionGenerator> iaeg;
  std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Resizable, zbe::Stated> > waecPRS;
  uint64_t state;
  uint64_t conerListId;
  uint64_t actuatorListId;
  uint64_t catorTicketId;
  uint64_t behavTicketId;
  uint64_t behavListId;
  uint64_t graphsId;
  int64_t graphTime;
  double ratio;
  uint64_t ticketId;
  std::shared_ptr<zbe::ReactObject<R> > ro;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_EVENTS_HANDLERS_BALLEXPLODER
