#include "gtest/gtest.h"
#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/IntersectionCollisionSelector.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"

namespace InteractionEventGeneratorTest {

class DummyTimer : public zbe::Timer {
  public:
    void start() {}
    int64_t stop() {return (0);}
    void reset() {}
    int64_t lapTime() {return (0);}
    int64_t totalTime() {return ((i++)*zbe::SECOND);}
    bool isRunning() {return (true);}

  private:
    int i = 0;
};

struct A {
  using Base = void;
  A(int id):  id(id), vs(0) {}
  int id;
  int vs;
};

class Robject;
class R { // Reactor mock
  public:
    virtual ~R(){};
    virtual void act(A *) {};
};

class Coner : public zbe::AvatarEntityFixed<A>, public zbe::AvatarEntityFixed<zbe::Collisioner<R> > {
  public:
    Coner() {}
    ~Coner(){}
};

class Cator :  public zbe::AvatarEntityFixed<A>, public zbe::AvatarEntityFixed<zbe::Collisionator<R> > {
  public:
    Cator() {}
    ~Cator(){}
};

class AActuator: public zbe::Actuator<A, R> {
  public:
    void act(A * a) {
      collisioner->vs = a->id;
    }
};

TEST(IntersectionEventGenerator, run) {
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime.setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > >());

  std::shared_ptr<zbe::CollisionObject<R> > sbox = std::make_shared<zbe::StaticSolidAABB2D<R> >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject<R> > cc = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >& lma = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, A>* > > act(new std::forward_list<zbe::ActuatorWrapper<R, A>* >());
  lma.insert(1, act);

  zbe::ActuatorWrapper<R, A>* actwrap = new  zbe::ActuatorWrapperCommon<R, A, A>(new AActuator());
  act->push_front(actwrap);

  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >& lmcn = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >::getInstance();
  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmct = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance();

  lmcn.insert(1, cnl);
  lmct.insert(2, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  zbe::Collisioner<R> *collisioner = new zbe::CollisionerCommon<R, A>(new zbe::AvatarEntityContainer<A>(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(aner), 1);
  setAvatar(dconer, aner);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  zbe::Collisionator<R> *collisionator = new  zbe::CollisionatorCommon<R, A>(new zbe::AvatarEntityContainer<A>(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(ator), 1, 1);
  setAvatar(dcator, ator);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector<R>* cs = new zbe::BaseCollisionSelector<R>();

  zbe::InteractionEventGenerator<R, zbe::CollisionSelector<R> , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > ieg(2, 1, cs);

  sysTime.update();
  sysTime.update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  ieg.run();
  es.manageCurrent();
  A* a;
  zbe::assignAvatar(&(*dconer), &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(37, a->vs) << "Coner is must be 37";
  zbe::assignAvatar(&(*dcator), &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(42, a->vs) << "Cator is must be 42";

  delete actwrap;
}

TEST(InstantIntersectionEventGenerator, run_no_collision) {
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime.setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > >());

  std::shared_ptr<zbe::CollisionObject<R> > sbox = std::make_shared<zbe::StaticSolidAABB2D<R> >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject<R> > cc = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >& lma = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, A>* > > act(new std::forward_list<zbe::ActuatorWrapper<R, A>* >());
  lma.insert(1, act);

  zbe::ActuatorWrapper<R, A>* actwrap = new  zbe::ActuatorWrapperCommon<R, A, A>(new AActuator());
  act->push_front(actwrap);

  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >& lmcn = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >::getInstance();
  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmct = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance();

  lmcn.insert(1, cnl);
  lmct.insert(2, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  zbe::Collisioner<R> *collisioner = new zbe::CollisionerCommon<R, A>(new zbe::AvatarEntityContainer<A>(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(aner), 1);
  setAvatar(dconer, aner);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  zbe::Collisionator<R> *collisionator = new  zbe::CollisionatorCommon<R, A>(new zbe::AvatarEntityContainer<A>(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(ator), 1, 1);
  setAvatar(dcator, ator);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector<R>* cs = new zbe::IntersectionCollisionSelector<R>();

  zbe::InstantInteractionEventGenerator<R, zbe::CollisionSelector<R> , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > iieg(2, 1, cs);

  sysTime.update();
  sysTime.update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  iieg.run();
  es.manageCurrent();

  A* a;
  zbe::assignAvatar(&(*dconer), &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(0, a->vs) << "Coner is must be 37";
  zbe::assignAvatar(&(*dcator), &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(0, a->vs) << "Cator is must be 42";

  delete actwrap;
}

TEST(InstantIntersectionEventGenerator, run) {
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime.setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > >());

  std::shared_ptr<zbe::CollisionObject<R> > sbox = std::make_shared<zbe::StaticSolidAABB2D<R> >(zbe::AABB2D({{0.0,0.0},{10.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject<R> > cc = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle({{5.0,5.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >& lma = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, A>* > > act(new std::forward_list<zbe::ActuatorWrapper<R, A>* >());
  lma.insert(1, act);

  zbe::ActuatorWrapper<R, A>* actwrap = new  zbe::ActuatorWrapperCommon<R, A, A>(new AActuator());
  act->push_front(actwrap);

  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >& lmcn = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >::getInstance();
  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmct = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance();

  lmcn.insert(1, cnl);
  lmct.insert(2, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  zbe::Collisioner<R> *collisioner = new zbe::CollisionerCommon<R, A>(new zbe::AvatarEntityContainer<A>(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(aner), 1);
  setAvatar(dconer, aner);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  zbe::Collisionator<R> *collisionator = new  zbe::CollisionatorCommon<R, A>(new zbe::AvatarEntityContainer<A>(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(ator), 1, 1);
  setAvatar(dcator, ator);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector<R>* cs = new zbe::IntersectionCollisionSelector<R>();

  zbe::InstantInteractionEventGenerator<R, zbe::CollisionSelector<R> , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > iieg(2, 1, cs);

  sysTime.update();
  sysTime.update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  iieg.run();
  es.manageCurrent();

  A* a;
  zbe::assignAvatar(&(*dconer), &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(37, a->vs) << "Coner is must be 37";
  zbe::assignAvatar(&(*dcator), &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(42, a->vs) << "Cator is must be 42";

  delete actwrap;
}

} //namespace InteractionEventGeneratorTest
