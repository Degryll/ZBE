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

#include <forward_list>
#include <algorithm>

#include "any_iterator.hpp"

#include "ZBE/core/system/App.h"
#include "ZBE/core/Timer.h"
#include "ZBE/core/CollisionData.h"
#include "ZBE/core/Behavior.h"
#include "ZBE/core/Drawer.h"

namespace zbe {

//typedef IteratorTypeErasure::make_any_iterator_type<zbe::ArrayListTicketedIterator<int> >::type anyticketediterator;
typedef IteratorTypeErasure::any_iterator<
    Behavior, // value type
    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
    Behavior&, // reference type
    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
  > BehaviorIterator;

typedef IteratorTypeErasure::any_iterator<
    Collisioner, // value type
    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
    Collisioner&, // reference type
    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
  > CollisionerIterator;

typedef IteratorTypeErasure::any_iterator<
    Drawer, // value type
    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
    Drawer&, // reference type
    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
  > DrawerIterator;

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
    CollisionerIterator firstC;
    CollisionerIterator lastC;
    DrawerIterator firstD;
    DrawerIterator lastD;
};

// Degryll TODO en lugar de collision, que se llame event
// una entidad puede reaccionar a una colision, un evento de windows (click) u otra cosa (ha muerto otra entidad, una entidad se acerca...)
void GameApp::behaveviorAndPhysics() {
  double timeRemain = t->getMilliseconds();
  double collisionTime = 0.0;
  std::forward_list<CollisionData> cdata;

  while(timeRemain > 0.0){
    collisionTime = collisionDetection(&cdata, timeRemain);
    behaveUntil(collisionTime);
    if (!cdata.empty()) reportCollision(cdata, collisionTime);

    timeRemain -= collisionTime;
  }  // while timeRemain
}

void GameApp::behaveUntil(double time) {
  for(auto it = firstB; it != lastB; ++it) {
    it->behaveUntil(time);
  }
}

double GameApp::collisionDetection(std::forward_list<CollisionData> *cdata, double timeRemain) {
  double bestTime = timeRemain;
  for(auto it = firstC; it != lastC; ++it) {
    bestTime = it->collisionDetection(cdata, bestTime);
  }

  return bestTime;
}

void GameApp::reportCollision(const std::forward_list<CollisionData> &cdata, double collisionTime) {
  for(auto it = cdata.begin(); it < cdata.end(); ++it) {
    it->react(collisionTime);
  }
}

void GameApp::paint() {
  for(auto it = firstD; it != lastD; ++it) {
    it->draw();
  }
}

}  // namespace zbe

#endif  // CORE_SYSTEM_GAMEAPP_H_
