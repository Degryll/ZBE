/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoundedWrapperPositionable2D.h
 * @since 2017-10-17
 * @date 2017-10-17
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that can be positioned but keep itse
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_POSITIONABLETIMERSPRITE_H_
#define ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_POSITIONABLETIMERSPRITE_H_

#include <memory>

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/entities/avatars/Positionable.h"

namespace zombienoid {

class PositionableTimerSprite : virtual public zbe::SingleTextSprite {
public:
  PositionableTimerSprite(const PositionableTimerSprite&) = delete;
  void operator=(const PositionableTimerSprite&) = delete;

  PositionableTimerSprite(std::weak_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > position, uint64_t graphics
                          , uint64_t width, uint64_t height, int64_t xOffset, int64_t yOffset)
    : p2d(nullptr), position(position), timer(nullptr), graphics(graphics), width(width), height(height), xOffset(xOffset), yOffset(yOffset), text() {
  }

  int64_t getX() {return (getP2D()->getPosition().x + xOffset);}
  int64_t getY() {return (getP2D()->getPosition().y + yOffset);}
  int64_t getW() {return (width);}
  int64_t getH() {return (height);}
  uint64_t getGraphics() {return (graphics);}

  const std::string& getText() {
    text = std::to_string(((timer->getTime()-zbe::SysTime::getInstance().getEndFrameTime())/zbe::SECOND+1));
    return (text);
  }

  void setTimer(std::shared_ptr<zbe::TimerTicket> timerTicket){
    timer = timerTicket;
  }

private:
  zbe::Positionable<2>* getP2D(){
    auto p = position.lock();
    p->assignAvatar(&p2d);
    return p2d;
  }

  zbe::Positionable<2>* p2d;
  std::weak_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > position;
  std::shared_ptr<zbe::TimerTicket> timer;
  uint64_t graphics;
  int64_t width;
  int64_t height;
  int64_t xOffset;
  int64_t yOffset;
  std::string text;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_POSITIONABLETIMERSPRITE_H_
