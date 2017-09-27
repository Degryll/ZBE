#include "gtest/gtest.h"

#include "ZBE/core/tools/tools.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

namespace EventsTest {

struct A{
    using Base = void;
};

class DummyInputHandler : public zbe::InputHandler{
    void run(float) {};
};

class R { // Reactor mock
public:
  virtual ~R() {}
};

class C : public zbe::CollisionerCommon<R, A> {
  public:
    C(zbe::AvatarEntityContainer<A>* aeca) : zbe::CollisionerCommon<R, A>(aeca, nullptr, nullptr, 1){};
};

class RO : public zbe::ReactObject<R> {
  public:
    void act(R*) {}
};

class DummyTHandler : public zbe::TimeHandler{
  void run(uint64_t) {}
};

TEST(Event, TimeEvent) {
  std::shared_ptr<zbe::TimeHandler> t(new DummyTHandler());
  zbe::TimeEvent e(1,100, t);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ(t, e.getHandler()) << "Must store the time handler";
}

TEST(Event, InputEvent) {
  DummyInputHandler * dih = new DummyInputHandler();
  zbe::InputEvent e(1,100, 7, 1.0, dih);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ((uint64_t)7, e.getKey()) << "Must store the key id";
  EXPECT_EQ(1.0, e.getState()) << "Must store the key state";
  delete dih;
}

TEST(Event, CollisionEvent) {
  std::shared_ptr<zbe::AvatarEntityFixed<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(new A());
  zbe::AvatarEntityContainer<A> aeca(aea);
  C* c = new C(&aeca);
  RO * ro = new RO();
  zbe::Point2D p{400000, 2};
  zbe::CollisionEvent2D<R> e(1,100, c, p, std::shared_ptr<zbe::ReactObject<R> >(ro));
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  //EXPECT_EQ(c, e.getCollisioner()) << "Must store EntityA";
  EXPECT_EQ(p.x, e.getCollisionData().getPoint().x) << "Must store Point x coordinate";
  EXPECT_EQ(p.y, e.getCollisionData().getPoint().y) << "Must store Point y coordinate";
}

}
