#include "gtest/gtest.h"
#include <vector>
#include <cstdio>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
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
    Coner(std::shared_ptr<zbe::CollisionObject<R> > co, uint64_t actuators, int id)
        : a(id) {
          zbe::AvatarEntityFixed<A >::setAvatar(&a);
          zbe::AvatarEntityFixed<zbe::Collisioner<R> >::setAvatar(new zbe::CollisionerCommon<R, A>(new zbe::AvatarEntityContainer<A>(this), co, std::make_shared<zbe::ReactObjectCommon<A, R> >(&a), actuators));
        }
    ~Coner(){}
    A a;
};

class Cator :  public zbe::AvatarEntityFixed<A>, public zbe::AvatarEntityFixed<zbe::Collisionator<R> > {
  public:
    Cator(std::shared_ptr<zbe::CollisionObject<R> > co, uint64_t actuators, uint64_t listId, int id)
      : a(id) {
        zbe::AvatarEntityFixed<A >::setAvatar(&a);
        zbe::AvatarEntityFixed<zbe::Collisionator<R> >::setAvatar(new  zbe::CollisionatorCommon<R, A>(new zbe::AvatarEntityContainer<A>(this), co, std::make_shared<zbe::ReactObjectCommon<A, R> >(&a), actuators, listId));
      }
    ~Cator(){}
    A a;
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

  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > cnl;
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > ctl;

  std::shared_ptr<zbe::CollisionObject<R> > sbox = std::make_shared<zbe::StaticSolidAABB2D<R> >(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::CollisionObject<R> > cc = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));

  zbe::ListManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >& lma = zbe::ListManager<std::forward_list<zbe::ActuatorWrapper<R, A>* > >::getInstance();

  std::forward_list<zbe::ActuatorWrapper<R, A>* > act;
  lma.insert(1, &act);

  zbe::ActuatorWrapper<R, A>* actwrap = new  zbe::ActuatorWrapperCommon<R, A, A>(new AActuator());
  act.push_front(actwrap);

  zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >& lmcn = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > > >::getInstance();
  zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance();

  lmcn.insert(1, &cnl);
  lmct.insert(2, &ctl);

  std::shared_ptr<Coner> dconer= std::make_shared<Coner>(sbox, 1, 42);
  std::shared_ptr<Cator> dcator= std::make_shared<Cator>(cc, 1, 1, 37);

  cnl.push_front(dconer);
  ctl.push_front(dcator);
  zbe::CollisionSelector<R>* cs = new zbe::BaseCollisionSelector<R>();

  zbe::InteractionEventGenerator<R, zbe::CollisionSelector<R> , zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<R> > >,  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > > ceg(2, 1, cs);

  sysTime.update();
  sysTime.update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  ceg.run();
  es.manageCurrent();

  EXPECT_EQ(42, dconer->a.id) << "Coner id must be 42";
  EXPECT_EQ(37, dconer->a.vs) << "Coner is must be 37";
  EXPECT_EQ(37, dcator->a.id) << "Cator id must be 37";
  EXPECT_EQ(42, dcator->a.vs) << "Cator is must be 42";

  delete actwrap;
}

} //namespace CollisionEventGeneratorTest
