#include "gtest/gtest.h"
#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
//#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"

namespace CollisionEventGeneratorTest {

//class DummyTimer : public zbe::Timer {
//  public:
//    void start() {}
//    int64_t stop() {return (0);}
//    void reset() {}
//    int64_t lapTime() {return (0);}
//    int64_t totalTime() {return ((i++)*zbe::SECOND);}
//    bool isRunning() {return (true);}
//
//  private:
//    int i = 0;
//};
//
//class Robject;
//class R { // Reactor mock
//  public:
//    virtual ~R(){};
//    virtual void act(Robject *) {};
//};
//
//class Robject : public zbe::ReactObjectCommon<Robject, R> {
//  public:
//  	Robject(int id) : zbe::ReactObjectCommon<Robject, R>(this), id(id) {};
//  	int id;
//};
//
//class Coner : public zbe::CollisionerCommon<Coner, R> {
//  public:
//    Coner(std::shared_ptr<zbe::CollisionObject<R> > co, uint64_t actuators, int id) : zbe::CollisionerCommon<Coner, R>(this, co, std::make_shared<Robject>(id), actuators),  id(id), vs(0){}
//    ~Coner(){}
//    int id;
//  	int vs;
//};
//
//class Cator : public zbe::CollisionatorCommon<Cator, R> {
//  public:
//    Cator(std::shared_ptr<zbe::CollisionObject<R> > co, uint64_t actuators, int id, uint64_t listId) : zbe::CollisionatorCommon<Cator, R>(this, co, std::make_shared<Robject>(id), actuators, listId),  id(id), vs(0) {}
//    ~Cator(){}
//    int id;
//  	int vs;
//};
//
//class ConerActuator: public zbe::Actuator<Coner, R> {
//  public:
//    void act(Robject * b) {
//      collisioner->vs = b->id;
//    }
//};
//
//class CatorActuator: public zbe::Actuator<Cator, R> {
//  public:
//    void act(Robject * b) {
//      collisioner->vs = b->id;
//    }
//};
//
//class DummyCollisionerEntity : public zbe::AvatarEntityFixed<zbe::Collisioner<R> > {
//public:
//  DummyCollisionerEntity(const DummyCollisionerEntity&) = delete;
//  void operator=(const DummyCollisionerEntity&) = delete;
//
//  DummyCollisionerEntity(std::shared_ptr<zbe::CollisionObject<R> > object, uint64_t actuators) : c(new Coner(object, actuators, 42)) {
//    setAvatar(c);
//  }
//
//  int getId(){return c->id;}
//  int getVs(){return c->vs;}
//  Coner* c;
//};
//
//class DummyCollisionatorEntity : public zbe::AvatarEntityFixed<zbe::Collisionator<R> > {
//public:
//  DummyCollisionatorEntity(const DummyCollisionatorEntity&) = delete;
//  void operator=(const DummyCollisionatorEntity&) = delete;
//
//  DummyCollisionatorEntity(std::shared_ptr<zbe::CollisionObject<R> >  object, uint64_t actuators, uint64_t listId) : c(new Cator(object, actuators, 37, listId)) {
//  	setAvatar(c);
//  }
//
//  int getId(){return c->id;}
//  int getVs(){return c->vs;}
//  Cator* c;
//};

TEST(CollisionEventGenerator, DISABLED_Generate) {
//  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
//  sysTime.setMaxFrameTime(zbe::SECOND*2);
//
//  DummyTimer* sysTimer = new DummyTimer;
//  sysTime.setSystemTimer(sysTimer);
//
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > cnl;
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > ctl;
//
//  std::shared_ptr<zbe::CollisionObject<R> > sbox = std::make_shared<zbe::StaticSolidAABB2D<R> >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
//  std::shared_ptr<zbe::CollisionObject<R> > cc = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
//
//  std::forward_list<zbe::Actuator<Coner,R>* > actconer;
//  std::forward_list<zbe::Actuator<Cator,R>* > actcator;
//
//  zbe::RsrcStore<std::forward_list<zbe::Actuator<Coner,R>* > >& lmaconer = zbe::RsrcStore<std::forward_list<zbe::Actuator<Coner,R>* > >::getInstance();
//  zbe::RsrcStore<std::forward_list<zbe::Actuator<Cator,R>* > >& lmacator = zbe::RsrcStore<std::forward_list<zbe::Actuator<Cator,R>* > >::getInstance();
//  lmaconer.insert(1, &actconer);
//  lmacator.insert(1, &actcator);
//
//  ConerActuator cna;
//  CatorActuator cta;
//
//  actconer.push_front(&cna);
//  actcator.push_front(&cta);
//
//  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >& lmcn = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >::getInstance();
//  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance();
//
//  lmcn.insert(1, &cnl);
//  lmct.insert(2, &ctl);
//
//  std::shared_ptr<DummyCollisionerEntity > dconer= std::make_shared<DummyCollisionerEntity>(sbox, 1);
//  std::shared_ptr<DummyCollisionatorEntity> dcator= std::make_shared<DummyCollisionatorEntity>(cc, 1, 1);
//
//  cnl.push_front(dconer);
//  ctl.push_front(dcator);
//  zbe::CollisionSelector<R>* cs = new zbe::BaseCollisionSelector<R>();
//
//  zbe::CollisionEventGenerator<R> ceg(2, 1, cs);
//
//  sysTime.update();
//  sysTime.update();
//  sysTime.setPartialFrameTime(zbe::SECOND*2);
//
//  zbe::EventStore &es = zbe::EventStore::getInstance();
//  ceg.generate();
//  es.manageCurrent();
//
//  EXPECT_EQ(42, dconer->getId()) << "Coner id must be 42";
//  EXPECT_EQ(37, dconer->getVs()) << "Coner is must be 37";
//  EXPECT_EQ(37, dcator->getId()) << "Cator id must be 37";
//  EXPECT_EQ(42, dcator->getVs()) << "Cator is must be 42";
}

} //namespace CollisionEventGeneratorTest
