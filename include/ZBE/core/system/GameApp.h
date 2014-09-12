/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameApp.h
 * @since 2014-09-09
 * @date 2014-09-09
 * @author Degryll
 * @brief Main game application.
 */

#ifndef CORE_SYSTEM_GAMEAPP_H_
#define CORE_SYSTEM_GAMEAPP_H_

#include "ZBE/core/system/App.h"
#include "ZBE/core/Timer.h"
#include "ZBE/core/CollisionData.h"
#include "ZBE/core/Behavior.h"

#include <forward_list>

namespace zbe {

template <typename BehaviorIterator, typename CollisionIterator>
class GameApp : App {
public:
  virtual ~GameApp() {}

  virtual void setup() {}
  void app();
  virtual void shutdown() {}

  virtual void pause() {}
  virtual void resume() {}
  virtual void restart() {}

  void behaveviorAndPhysics();
  void updateBehaviors(double time);
  void behaveUntil(double time);
  double collisionDetection(std::forward_list<CollisionData> *cdata, double timeRemain);
  void collisionReaction(const std::forward_list<CollisionData>& cdata, double collisionTime);

  void paint();

private:
    Timer *t;
    BehaviorIterator beginB;
    BehaviorIterator endB;
    CollisionIterator beginC;
    CollisionIterator endC;
};

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::app() {

}

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::behaveviorAndPhysics() {
  double timeRemain = t->getMilliseconds();
  double collisionTime = 0.0;
  std::forward_list<CollisionData> cdata;

  while(remainFrameTime > 0.0){
    updateBehaviors(timeRemain);
    collisionTime = collisionDetection(&cdata, timeRemain);
    behaveUntil(collisionTime);
    if (!cdata.empty()) collisionReaction(cdata, collisionTime);

    timeRemain -= collisionTime;
  }  // while
}

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::updateBehaviors(double time) {
  for(BehaviorIterator it = beginB; it != endB; ++it) {
    static_cast<Behavior>(*it).updateBehaviors(time);
  }
}

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::behaveUntil(double time) {
  for(BehaviorIterator it = beginB; it != endB; ++it) {
    static_cast<Behavior>(*it).behaveUntil(time);
  }
}

template <typename BehaviorIterator, typename CollisionIterator>
double GameApp<BehaviorIterator,CollisionIterator>::collisionDetection(cdata, timeRemain) {

}

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::collisionReaction(cdata, collisionTime) {

}

template <typename BehaviorIterator, typename CollisionIterator>
void GameApp<BehaviorIterator,CollisionIterator>::paint() {
  // for each entitie
  //   draw(entitie);
}

}  // namespace zbe

#endif  // CORE_SYSTEM_GAMEAPP_H_
