/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameApp.h
 * @since 2014-09-09
 * @date 2014-09-22
 * @author Degryll
 * @brief Main game application.
 */

#ifndef CORE_SYSTEM_GAMEAPP_H_
#define CORE_SYSTEM_GAMEAPP_H_

#include "ZBE/core/system/App.h"
#include "ZBE/core/Timer.h"
#include "ZBE/core/CollisionData.h"
#include "ZBE/core/Behavior.h"
#include "ZBE/core/Drawer.h"

#include <forward_list>
#include <algorithm>

namespace zbe {

template <typename BehaviorIterator, typename CollisionadorIterator, typename DrawerIterator>
class GameApp : App {
public:
  virtual ~GameApp() {}

  void behaveviorAndPhysics();

  void behaveUntil(double time);

  void draw();

protected:
  double collisionDetection(std::forward_list<CollisionData> *cdata, double timeRemain);
  void reportCollision(const std::forward_list<CollisionData>& cdata, double collisionTime);

private:
    Timer *t;
    BehaviorIterator firstB;
    BehaviorIterator lastB;
    CollisionadorIterator firstC;
    CollisionadorIterator lastC;
    DrawerIterator firstD;
    DrawerIterator lastD;
};

template <typename BehaviorIterator, typename CollisionadorIterator, typename DrawerIterator>
void GameApp<BehaviorIterator,CollisionadorIterator>::behaveviorAndPhysics() {
  double timeRemain = t->getMilliseconds();
  double collisionTime = 0.0;
  std::forward_list<CollisionData> cdata;

  while(timeRemain > 0.0){
    collisionTime = collisionDetection(&cdata, timeRemain);
    if (!cdata.empty()) reportCollision(cdata, collisionTime);
    behaveUntil(collisionTime);

    timeRemain -= collisionTime;
  }  // while timeRemain
}

template <typename BehaviorIterator, typename CollisionadorIterator, typename DrawerIterator>
void GameApp<BehaviorIterator,CollisionadorIterator>::behaveUntil(double time) {
  for(auto it = firstB; it != lastB; ++it) {
    static_cast<Behavior*>(*it)->behaveUntil(time);
  }
}

template <typename BehaviorIterator, typename CollisionadorIterator, typename DrawerIterator>
double GameApp<BehaviorIterator,CollisionadorIterator>::collisionDetection(std::forward_list<CollisionData> *cdata, double timeRemain) {
  double bestTime = timeRemain;
  for(auto it = firstC; it != lastC; ++it) {
    bestTime = static_cast<Collisionador*>(*it)->collisionDetection(cdata, bestTime);
  }

  return bestTime;
}

template <typename BehaviorIterator, typename CollisionIterator, typename DrawerIterator>
void GameApp<BehaviorIterator,CollisionIterator>::reportCollision(std::forward_list<CollisionData> *cdata, double collisionTime) {
  for(auto it = cdata->begin(); it < cdata->end(); ++it) {
    CollisionData *cd = &(*it);
    Collisionador *d = cd->getCollisionador();
    Collisionador *b = cd->getCollisionable();
    Vector2D &n = cd->getNormal();
    Vector2D &p = cd->getPoint();
    d->react(b,n,p,collisionTime);
    b->react(d,n,p,collisionTime);
  }
}

template <typename BehaviorIterator, typename CollisionIterator, typename DrawerIterator>
void GameApp<BehaviorIterator,CollisionIterator>::paint() {
  for(auto it = firstD; it != lastD; ++it) {
    static_cast<Drawer*>(*it)->draw();
  }
}

}  // namespace zbe

#endif  // CORE_SYSTEM_GAMEAPP_H_
