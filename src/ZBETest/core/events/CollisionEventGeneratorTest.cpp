#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/CollisionEventGenerator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/entities/CollisionatorEntity.h"
//#include "ZBE/core/tools/math/objects.h"

class DummyCollisionator : public zbe::CollisionatorEntity {
public:
  DummyCollisionator(zbe::CollisionObject* object) : zbe::CollisionatorEntity(object) {}
};

class DummyCollisionable : public zbe::CollisionerEntity {
public:
  DummyCollisionable(zbe::CollisionObject* object) : zbe::CollisionerEntity(object) {}
};

TEST(CollisionEventGenerator, Generate) {
  zbe::TicketedForwardList<zbe::CollisionatorEntity*> ctl;
  zbe::TicketedForwardList<zbe::CollisionerEntity*> cbl;

  zbe::ConstantMovingCircle cc(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  zbe::StaticAABB2D sbox(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));

  DummyCollisionator a(&cc);
  DummyCollisionator b(&sbox);

  //zbe::TicketedElement<zbe::CollisionatorEntity*>* ta = ctl.push_front(&a);
  //zbe::TicketedElement<zbe::CollisionerEntity*>* tb = cbl.push_front(&b);
  ctl.push_front(&a);
  cbl.push_front(&b);

  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity*> >::getInstance();
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity*> >& lmcn = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity*> >::getInstance();

  lmct.insert(1, &ctl);
  lmcn.insert(1, &cbl);

  a.addToCollisionablesLists(1);

  zbe::CollisionEventGenerator ceg(1, 1);

  ceg.generate(0,2 * zbe::VELOCITYTOTIME);
  zbe::EventStore &es = zbe::EventStore::getInstance();
  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  std::forward_list<zbe::Event*> events = es.getEvents();
  zbe::CollisionEvent2D* e1 = (zbe::CollisionEvent2D*)(events.front());
  events.pop_front();
  zbe::CollisionEvent2D* e2 = (zbe::CollisionEvent2D*)(events.front());
  events.pop_front();
  EXPECT_EQ((uint64_t)1, e1->getId()) << "must be stored with id 1";
  EXPECT_DOUBLE_EQ(0.25 * zbe::VELOCITYTOTIME,e1->getTime()) << "Time of collision.";
  EXPECT_DOUBLE_EQ(2.75, e1->getPoint()[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(5.0, e1->getPoint()[1]) << "Point of collision (y).";
  EXPECT_EQ(&b, e1->getEntity()) << "Collisionable.";
  EXPECT_EQ(&a, e2->getEntity()) << "Collisionator.";

  delete e1;
  delete e2;
}
