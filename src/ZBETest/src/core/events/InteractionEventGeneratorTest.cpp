#include "gtest/gtest.h"
#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/Reactor.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/IntersectionCollisionSelector.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/Interactionator.h"

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

typedef zbe::Reactor<zbe::CollisionData, zbe::CollisionObject, A> R;

class Coner : public zbe::AvatarEntityFixed<A>, public zbe::AvatarEntityFixed<zbe::Interactioner<R> > {
  public:
    Coner() {}
    ~Coner(){}
};

class Cator :  public zbe::AvatarEntityFixed<A>, public zbe::AvatarEntityFixed<zbe::Interactionator<R> > {
  public:
    Cator() {}
    ~Cator(){}
};

class AActuator: public zbe::Actuator<zbe::WeakAvatarEntityContainer<A> , R> {
  public:
    void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<A> > a) {
      A* avatar;
      a->get()->assignAvatar(&avatar);
      A* vs;
      collisioner->get()->assignAvatar(&vs);
      vs->vs = avatar->id;
    }
};

TEST(IntersectionEventGenerator, run) {
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime->setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > >());

  std::shared_ptr<zbe::CollisionObject> sbox = std::make_shared<zbe::StaticSolidAABB2D >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject> cc = std::make_shared<zbe::ConstantMovingCircle >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >& lma = zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > > act(new std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* >());
  lma.insert(10, act);

  zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* actwrap = new  zbe::ActuatorWrapperCommon<R, zbe::WeakAvatarEntityContainer<A>, zbe::WeakAvatarEntityContainer<A> >(new AActuator());
  act->push_front(actwrap);

  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >& lmcn = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >::getInstance();
  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >::getInstance();

  lmcn.insert(10, cnl);
  lmct.insert(20, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  setAvatar(dconer, aner);
  zbe::Interactioner<R> *collisioner = new zbe::InteractionerCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer)), 10);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  setAvatar(dcator, ator);
  zbe::Interactionator<R> *collisionator = new  zbe::InteractionatorCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator)), 10, 10);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector* cs = new zbe::BaseCollisionSelector();

  zbe::InteractionEventGenerator<R, zbe::CollisionSelector , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > ieg(20, 10, cs);

  sysTime->update();
  sysTime->update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  ieg.run();
  es.manageCurrent();
  A* a;
  zbe::assignAvatar(dconer, &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(37, a->vs) << "Coner vs must be 37";
  zbe::assignAvatar(dcator, &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(42, a->vs) << "Cator vs must be 42";

  delete actwrap;
}

TEST(InstantIntersectionEventGenerator, run_no_collision) {
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime->setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > >());

  std::shared_ptr<zbe::CollisionObject> sbox = std::make_shared<zbe::StaticSolidAABB2D >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject> cc = std::make_shared<zbe::ConstantMovingCircle >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >& lma = zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > > act(new std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* >());
  lma.insert(100, act);

  zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* actwrap = new  zbe::ActuatorWrapperCommon<R, zbe::WeakAvatarEntityContainer<A>, zbe::WeakAvatarEntityContainer<A> >(new AActuator());
  act->push_front(actwrap);

  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >& lmcn = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >::getInstance();
  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >::getInstance();

  lmcn.insert(100, cnl);
  lmct.insert(200, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  setAvatar(dconer, aner);
  zbe::Interactioner<R> *collisioner = new zbe::InteractionerCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer)), 100);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  setAvatar(dcator, ator);
  zbe::Interactionator<R> *collisionator = new  zbe::InteractionatorCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator)), 100, 100);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector* cs = new zbe::IntersectionCollisionSelector();

  zbe::InstantInteractionEventGenerator<R, zbe::CollisionSelector , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > iieg(200, 100, cs);

  sysTime->update();
  sysTime->update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  iieg.run();
  es.manageCurrent();

  A* a;
  zbe::assignAvatar(dconer, &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(0, a->vs) << "Coner vs must be 37";
  zbe::assignAvatar(dcator, &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(0, a->vs) << "Cator vs must be 42";

  delete actwrap;
}

TEST(InstantIntersectionEventGenerator, run) {
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime->setSystemTimer(sysTimer);

  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > > cnl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >());
  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > >());

  std::shared_ptr<zbe::CollisionObject> sbox = std::make_shared<zbe::StaticSolidAABB2D >(zbe::AABB2D({{0.0,0.0},{10.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject> cc = std::make_shared<zbe::ConstantMovingCircle >(zbe::Circle({{5.0,5.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >& lma = zbe::RsrcStore<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > >::getInstance();

  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* > > act(new std::forward_list<zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* >());
  lma.insert(1, act);

  zbe::ActuatorWrapper<R, zbe::WeakAvatarEntityContainer<A> >* actwrap = new  zbe::ActuatorWrapperCommon<R, zbe::WeakAvatarEntityContainer<A> , zbe::WeakAvatarEntityContainer<A> >(new AActuator());
  act->push_front(actwrap);

  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >& lmcn = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > > >::getInstance();
  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > >::getInstance();

  lmcn.insert(1, cnl);
  lmct.insert(2, ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>();
  A* aner = new A(42);
  setAvatar(dconer, aner);
  zbe::Interactioner<R> *collisioner = new zbe::InteractionerCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer), sbox, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dconer)), 1);
  setAvatar(dconer, collisioner);

  std::shared_ptr<Cator> dcator= std::make_shared<Cator>();
  A* ator = new A(37);
  setAvatar(dcator, ator);
  zbe::Interactionator<R> *collisionator = new  zbe::InteractionatorCommon<R, A>(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator), cc, std::make_shared<zbe::ReactObjectCommon<R, A> >(std::make_shared<zbe::WeakAvatarEntityContainer<A> >(dcator)), 1, 1);
  setAvatar(dcator, collisionator);

  cnl->push_front(dconer);
  ctl->push_front(dcator);
  zbe::CollisionSelector* cs = new zbe::IntersectionCollisionSelector();

  zbe::InstantInteractionEventGenerator<R, zbe::CollisionSelector , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<R> > > > iieg(2, 1, cs);

  sysTime->update();
  sysTime->update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  iieg.run();
  es.manageCurrent();

  A* a;
  zbe::assignAvatar(dconer, &a);
  EXPECT_EQ(42, a->id) << "Coner id must be 42";
  EXPECT_EQ(37, a->vs) << "Coner vs must be 37";
  zbe::assignAvatar(dcator, &a);
  EXPECT_EQ(37, a->id) << "Cator id must be 37";
  EXPECT_EQ(42, a->vs) << "Cator vs must be 42";

  delete actwrap;
}

} //namespace InteractionEventGeneratorTest
