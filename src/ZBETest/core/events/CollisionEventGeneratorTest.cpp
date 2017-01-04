#include "gtest/gtest.h"

#include <vector>

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

TEST(CollisionEventGenerator, DISABLED_Generate) {
  zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> ctl;
  zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> cnl;

  zbe::ConstantMovingCircle<R> cc(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  zbe::StaticAABB2D<R> sbox(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));

  DummyCollisionatorEntity a(&cc);
  DummyCollisionerEntity b(&sbox);

  zbe::TicketedElement<zbe::CollisionatorEntity<R>*>* ta = ctl.push_front(&a);
  zbe::TicketedElement<zbe::CollisionerEntity<R>*>* tb = cnl.push_front(&b);
  //ctl.push_front(&a);
  //cnl.push_front(&b);

  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >::getInstance();
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >& lmcn = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >::getInstance();

  lmct.insert(1, &ctl);
  lmcn.insert(2, &cnl);

  //a.addToCollisionablesLists(1);

  zbe::CollisionEventGenerator<R> ceg(1, 1);

  ceg.generate(0,2 * zbe::VELOCITYTOTIME);
  zbe::EventStore &es = zbe::EventStore::getInstance();
  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  std::forward_list<zbe::Event*> events = es.getEvents();
  zbe::CollisionEvent2D<R>* e1 = (zbe::CollisionEvent2D<R>*)(events.front());
  events.pop_front();
  zbe::CollisionEvent2D<R>* e2 = (zbe::CollisionEvent2D<R>*)(events.front());
  events.pop_front();
  EXPECT_EQ((uint64_t)1, e1->getId()) << "must be stored with id 1";
  EXPECT_DOUBLE_EQ(0.25 * zbe::VELOCITYTOTIME,e1->getTime()) << "Time of collision.";
  EXPECT_DOUBLE_EQ(2.75, e1->getCollisionData().getPoint()[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(5.0, e1->getCollisionData().getPoint()[1]) << "Point of collision (y).";
  EXPECT_EQ(b.object, (e1->getCollisioner())->getCollisionObject()) << "Collisionable.";
  EXPECT_EQ(a.object, (e2->getCollisioner())->getCollisionObject()) << "Collisionator.";

  delete e1;
  delete e2;
}
