#include "gtest/gtest.h"

#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/ReactObject.h"

namespace CollisionEventGeneratorTest {
class Robject;
class R { // Reactor mock
  public:
    ~R(){};
    virtual void act(Robject *) {};
};

class Coner : public zbe::CollisionerCommon<Coner, R> {
  public:
    Coner(zbe::CollisionObject<R> * co, std::forward_list<zbe::Actuator<Coner, R>* >* actuators, int id) : zbe::CollisionerCommon<Coner, R>(this, co, actuators),  id(id), vs(0){}
    ~Coner(){}
    int id;
  	int vs;
};

class Cator : public zbe::CollisionatorCommon<Cator, R> {
  public:
    Cator(zbe::CollisionObject<R> * co, std::forward_list<zbe::Actuator<Cator, R>* >* actuators, int id) : zbe::CollisionatorCommon<Cator, R>(this, co, actuators),  id(id), vs(0) {}
    ~Cator(){}
    int id;
  	int vs;
};

class Robject : public zbe::ReactObjectCommon<Robject, R> {
  public:
  	Robject(int id) : zbe::ReactObjectCommon<Robject, R>(this), id(id) {};
  	int id;
};

class ConerActuator: public zbe::Actuator<Coner, R> {
  public:
    void act(Robject * b) {
      collisioner->vs = b->id;
    }
};

class CatorActuator: public zbe::Actuator<Cator, R> {
  public:
    void act(Robject * b) {
      collisioner->vs = b->id;
    }
};

class DummyCollisionerEntity : public zbe::CollisionerEntity<R> {
public:
  DummyCollisionerEntity(const DummyCollisionerEntity&) = delete;
  void operator=(const DummyCollisionerEntity&) = delete;

  DummyCollisionerEntity(zbe::CollisionObject<R> * object, std::forward_list<zbe::Actuator<Coner,R>* >* actuators)
    : object(object), actuators(actuators), c(std::make_shared<Coner>(object, actuators, 42)), r(std::make_shared<Robject>(42)) {}

  std::shared_ptr<zbe::Collisioner<R> > getCollisioner() { return c;}
  std::shared_ptr<zbe::ReactObject<R> > getReactObject() { return r;}
  int getId(){return c->id;}
  int getVs(){return c->vs;}
  zbe::CollisionObject<R>* object;
  std::forward_list<zbe::Actuator<Coner,R>* >* actuators;
  std::shared_ptr<Coner> c;
  std::shared_ptr<Robject> r;
};

class DummyCollisionatorEntity : public zbe::CollisionatorEntity<R> {
public:
  DummyCollisionatorEntity(const DummyCollisionatorEntity&) = delete;
  void operator=(const DummyCollisionatorEntity&) = delete;

  DummyCollisionatorEntity(zbe::CollisionObject<R>* object, std::forward_list<zbe::Actuator<Cator,R>* >* actuators)
    : object(object), actuators(actuators), c(std::make_shared<Cator>(object, actuators, 37)), r(std::make_shared<Robject>(37)) {}

  std::shared_ptr<zbe::ReactObject<R> >   getReactObject()   { return r;}
  std::shared_ptr<zbe::Collisioner<R> >   getCollisioner() { return c;}
  std::shared_ptr<zbe::Collisionator<R> > getCollisionator() { return c;}
  int getId(){return c->id;}
  int getVs(){return c->vs;}
  zbe::CollisionObject<R>* object;
  std::forward_list<zbe::Actuator<Cator,R>* >* actuators;
  std::shared_ptr<Cator > c;
  std::shared_ptr<Robject> r;
};

TEST(CollisionEventGenerator, Generate) {
  zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> cnl;
  zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> ctl;

  zbe::StaticAABB2D<R> sbox(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  zbe::ConstantMovingCircle<R> cc(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  std::forward_list<zbe::Actuator<Coner,R>* > actconer;
  std::forward_list<zbe::Actuator<Cator,R>* > actcator;

  ConerActuator cna;
  CatorActuator cta;

  actconer.push_front(&cna);
  actcator.push_front(&cta);

  DummyCollisionerEntity dconer(&sbox, &actconer);
  DummyCollisionatorEntity dcator(&cc, &actcator);

  cnl.push_front(&dconer);
  ctl.push_front(&dcator);

  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<R>*> >::getInstance();
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >& lmcn = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<R>*> >::getInstance();

  lmcn.insert(1, &cnl);
  lmct.insert(2, &ctl);

  dcator.getCollisionator()->addToCollisionablesLists(1);

  zbe::CollisionEventGenerator<R> ceg(2, 1);

  zbe::EventStore &es = zbe::EventStore::getInstance();
  ASSERT_TRUE(es.getEvents().empty()) << "List must be empty.";
  ceg.generate(0, 2 * zbe::VELOCITYTOTIME);
  es.manageCurrent();

  EXPECT_EQ(42, dconer.getId()) << "Coner id must be 42";
  EXPECT_EQ(37, dconer.getVs()) << "Coner is must be 37";
  EXPECT_EQ(37, dcator.getId()) << "Cator id must be 37";
  EXPECT_EQ(42, dcator.getVs()) << "Cator is must be 42";
}
} //namespace CollisionEventGeneratorTest
