#include "gtest/gtest.h"

#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/ReactObject.h"


class R { // Reactor mock
};

class Coner : public zbe::Collisioner<R> {
  public:
    Coner(zbe::CollisionObject<R> * co):zbe::Collisioner<R>(co){};
    void react(zbe::CollisionData * collisionData, zbe::ReactObject<R> * reactObject) {};
};

class Cator : public zbe::Collisionator<R> {
  public:
    Cator(zbe::CollisionObject<R> * co):zbe::Collisionator<R>(co){};
    ~Cator(){};
    void react(zbe::CollisionData * collisionData, zbe::ReactObject<R> * reactObject) {};
};

class Robject : public zbe::ReactObject<R> {
  public:
    void act(R* reactor) {};
};

class DummyCollisionerEntity : public zbe::CollisionerEntity<R> {
public:
  DummyCollisionerEntity(zbe::CollisionObject<R> * object): object(object) {}
  std::shared_ptr<zbe::Collisioner<R> > getCollisioner() { return std::make_shared<Coner>(object); };
  std::shared_ptr<zbe::ReactObject<R> > getReactObject() { return std::make_shared<Robject>(); };
  zbe::CollisionObject<R>* object;
};

class DummyCollisionatorEntity : public zbe::CollisionatorEntity<R> {
public:
  DummyCollisionatorEntity(zbe::CollisionObject<R>* object): object(object) {}
  std::shared_ptr<zbe::Collisioner<R> > getCollisioner() { return std::make_shared<Coner>(object); };
  std::shared_ptr<zbe::ReactObject<R> > getReactObject() { return std::make_shared<Robject>(); };
  std::shared_ptr<zbe::Collisionator<R> > getCollisionator() {
    std::shared_ptr<zbe::Collisionator<R> > ct = std::make_shared<Cator>(object);
    ct->addToCollisionablesLists(1);
    return ct;
  };
  zbe::CollisionObject<R>* object;
};

TEST(CollisionEventGenerator, Generate) {
  printf("Generate start\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> ctl;
  zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> cnl;

  zbe::ConstantMovingCircle<R> cc(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  zbe::StaticAABB2D<R> sbox(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));

  DummyCollisionatorEntity a(&cc);
  DummyCollisionerEntity b(&sbox);

  printf("Generate instanciados \n");fflush(stdout);
  zbe::TicketedElement<zbe::CollisionatorEntity<R>*>* ta = ctl.push_front(&a);
  zbe::TicketedElement<zbe::CollisionerEntity<R>*>* tb = cnl.push_front(&b);
  ctl.push_front(&a);
  cnl.push_front(&b);

  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >::getInstance();
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >& lmcn = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >::getInstance();

  lmct.insert(1, &ctl);
  lmcn.insert(2, &cnl);
  printf("Generate insertados\n");fflush(stdout);

  //a.addToCollisionablesLists(1);

  zbe::CollisionEventGenerator<R> ceg(1, 1);

  printf("Generate ceg\n");fflush(stdout);

  ceg.generate(0,2 * zbe::VELOCITYTOTIME);
  zbe::EventStore &es = zbe::EventStore::getInstance();

  printf("Generate end\n");fflush(stdout);
}
