/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallScorer.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of increase point when ball hit breakables.
 */

#ifndef ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BallScorer
#define ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BallScorer

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "entities/avatars/Scorer.h"
#include "entities/avatars/Wall.h"
#include "entities/avatars/Breakable.h"

namespace zombienoid {

/** @brief Actuator capable of increase point when ball hit breakables.
 */
template <typename R>
class BallScorer: public zbe::Actuator<zbe::WeakAvatarEntityContainer<Scorer>, R> {
public:

  BallScorer(std::shared_ptr<zbe::Value<int64_t> > totalPoints, int64_t accumTime, int64_t extraAccumTime, int64_t pointsPerAccum)
    : totalPoints(totalPoints), accumTime(accumTime), extraAccumTime(extraAccumTime), pointsPerAccum(pointsPerAccum), contextTime(zbe::SysTime::getInstance()) {}

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<Wall> >) {
      Scorer* scorer;
      std::shared_ptr<zbe::WeakAvatarEntityContainer<Scorer> > waecs = zbe::Actuator<zbe::WeakAvatarEntityContainer<Scorer>, R>::getCollisioner();
      waecs->get()->assignAvatar(&scorer);
      scorer->reset();
      scorer->setLastScoreTime(0);
  }

  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<Breakable> >) {
    Scorer* scorer;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<Scorer> > waecs = zbe::Actuator<zbe::WeakAvatarEntityContainer<Scorer>, R>::getCollisioner();
    waecs->get()->assignAvatar(&scorer);
    int64_t time = contextTime->getEventTime() - scorer->getLastScoreTime();
    if(time>accumTime){
      scorer->reset();
    } else if(time<extraAccumTime){
      scorer->accum();
    }
    scorer->accum();
    scorer->setLastScoreTime(contextTime->getEventTime());
    totalPoints->add(scorer->getTotal()*pointsPerAccum);
  }

private:
  std::shared_ptr<zbe::Value<int64_t> > totalPoints;
  int64_t accumTime;
  int64_t extraAccumTime;
  int64_t pointsPerAccum;
  std::shared_ptr<zbe::ContextTime> contextTime;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BallScorer
