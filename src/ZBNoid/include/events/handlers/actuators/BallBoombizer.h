/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallBoombizer.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of increase point when ball hit breakables.
 */

#ifndef ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BALLBOOMBIZER
#define ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BALLBOOMBIZER

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "entities/avatars/Boombizer.h"
#include "entities/avatars/implementations/PositionableTimerSprite.h"
#include "events/handlers/BallExploder.h"

namespace zombienoid {

/** @brief Actuator capable of increase point when ball hit breakables.
 */
template <typename R, typename BHL, typename CTL, typename CNL, typename TSL, typename ASL>
class BallBoombizer: public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated, zbe::Resizable>, R> {
 public:
  BallBoombizer(std::shared_ptr<zbe::TimeEventGenerator> teg, uint64_t eventId, uint64_t ticketId, uint64_t actuatorListId,  uint64_t catorTicketId,
                uint64_t behavTicketId, uint64_t behavListId,uint64_t catorListId, uint64_t conerListId, uint64_t asListId, uint64_t tsListId,
                uint64_t graphsId, int64_t time, int64_t timeGraphsId, int64_t timeGraphsW, int64_t timeGraphsH, int64_t boombState, double sizeRatio, double sizeStep)
    : teg(teg), eventId(eventId), ticketId(ticketId), catorListId(catorListId), conerListId(conerListId), asListId(asListId), tsListId(tsListId),
      actuatorListId(actuatorListId),  catorTicketId(catorTicketId), behavTicketId(behavTicketId), behavListId(behavListId), graphsId(graphsId),
      time(time), timeGraphsId(timeGraphsId), timeGraphsW(timeGraphsW), timeGraphsH(timeGraphsH), boombState(boombState), sizeRatio(sizeRatio), sizeStep(sizeStep) {
  }

  void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<zombienoid::Boombizer> >) {
    zbe::Stated* stated;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Stated> > waecs = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated, zbe::Resizable>, R>::getCollisioner();
    waecs->get()->assignAvatar(&stated);

    zbe::Resizable* resizable;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Resizable> > waecr = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated, zbe::Resizable>, R>::getCollisioner();
    waecr->get()->assignAvatar(&resizable);

    if(stated->getState() == boombState) {
      resizable->increaseSize(sizeStep);
    } else {
      int64_t prevState = stated->getState();
      stated->setState(boombState);

      zbe::Avatar* avatar;
      std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar> > waeca = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated, zbe::Resizable>, R>::getCollisioner();
      waeca->get()->assignAvatar(&avatar);

      std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Positionable<2> > > waecp2 = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated, zbe::Resizable>, R>::getCollisioner();
      auto waecPRS = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Resizable, zbe::Stated> >(waeca->get(), waecp2->get(), waecr->get(), waecs->get());

      PositionableTimerSprite* timerSprite = new PositionableTimerSprite(waecp2->get(), timeGraphsId, timeGraphsW, timeGraphsH, -(timeGraphsW / 2) , -(timeGraphsH / 2));

      auto aecs = std::make_shared<zbe::AvatarEntityContainer<zbe::SingleTextSprite> >(std::make_shared<zbe::AvatarEntityFixed<zbe::SingleTextSprite> >(timerSprite));
      auto tsList = zbe::RsrcStore<TSL>::getInstance().get(tsListId);
      avatar->addToList(ticketId, tsList->push_front(aecs));

      std::shared_ptr<zbe::TimeHandler> exploder = std::make_shared<BallExploder<R, BHL, CTL, CNL, ASL> >(waecPRS, eventId, catorListId, conerListId,
                                                                                                            actuatorListId, catorTicketId, behavTicketId,
                                                                                                            behavListId, asListId, graphsId, prevState,
                                                                                                            zbe::SECOND / 2, sizeRatio, ticketId, teg);
      std::shared_ptr<zbe::TimerTicket> timerTicket = teg->addTimer(exploder, zbe::SysTime::getInstance()->getEventTime() + time);

      timerSprite->setTimer(timerTicket);
    }
  }

 private:
  std::shared_ptr<zbe::TimeEventGenerator> teg;
  uint64_t eventId;
  uint64_t ticketId;
  uint64_t catorListId;
  uint64_t conerListId;
  uint64_t asListId;
  uint64_t tsListId;
  uint64_t actuatorListId;
  uint64_t catorTicketId;
  uint64_t behavTicketId;
  uint64_t behavListId;
  uint64_t graphsId;
  int64_t time;
  int64_t timeGraphsId;
  int64_t timeGraphsW;
  int64_t timeGraphsH;
  int64_t boombState;
  double sizeRatio;
  double sizeStep;

};

}  // namespace zombienoid

#endif // ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BALLBOOMBIZER
