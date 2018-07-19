#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/events/handlers/actuators/DaemonSelectorAtor.h"

namespace DaemonSelectorAtor {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false){}

  void run(){
    executed = true;
  }
  bool executed;
};

class A {
public:
    using Base = void;
};

class DummyReactor {
public:
  virtual ~DummyReactor(){}
  virtual void act() {};
  virtual void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<A> >) {};
  virtual void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<zbe::Stated> >) {};
};

class DummyStated : public zbe::Stated {
public:
  DummyStated(int64_t state) : value(state) {}
  ~DummyStated() {}
  void setState(int64_t state) {value = state;}
  void add(int64_t state) {value += state;}
  int64_t getState()  {return value;}
private:
  int64_t value;
};

TEST(DaemonSelectorSelfAtor, act) {
  // Daemons & Actuator
  std::shared_ptr<DummyDaemon> d1 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> d2 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dd = std::make_shared<DummyDaemon>();
  zbe::DaemonSelectorSelfAtor<A, DummyReactor> dssa(dd);
  dssa.setDaemon(0,d1);
  dssa.setDaemon(1,d2);
  // react object
  A *a = new A();
  std::shared_ptr<zbe::AvatarEntity<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(a);
  auto waeca = std::make_shared<zbe::WeakAvatarEntityContainer<A> >(aea);
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, A> > (waeca);
  // Collisioner
  zbe::Stated *s = new DummyStated(0);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto coner = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  // cd
  zbe::CollisionData* cData = new zbe::CollisionData(zbe::Point2D(), zbe::Vector2D());

  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";

  dssa.run(coner, ro,  cData);
  EXPECT_TRUE(d1->executed) << "d1 must be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d1->executed = false;

  s->setState(1);
  dssa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_TRUE(d2->executed) << "d2 must be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d2->executed = false;

  s->setState(102); // Use default
  dssa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_TRUE(dd->executed) << "dd must be executed";
  dd->executed = false;

  // empty ro.
  std::shared_ptr<zbe::ReactObject<DummyReactor> > emptyRo = std::make_shared<zbe::ReactObjectCommon<DummyReactor> > ();
  s->setState(0); // Use default
  dssa.run(coner, emptyRo,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d1->executed = false;

  s->setState(1);
  dssa.run(coner, emptyRo,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d2->executed = false;

  s->setState(102); // Use default
  dssa.run(coner, emptyRo,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  dd->executed = false;
}

TEST(DaemonSelectorSelfAnyAtor, act) {
  // Daemons & Actuator
  std::shared_ptr<DummyDaemon> d1 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> d2 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dd = std::make_shared<DummyDaemon>();
  zbe::DaemonSelectorSelfAnyAtor<DummyReactor> dssaa(dd);
  dssaa.setDaemon(0,d1);
  dssaa.setDaemon(1,d2);
  // Collisioner
  A *a = new A();
  std::shared_ptr<zbe::AvatarEntity<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(a);
  auto waeca = std::make_shared<zbe::WeakAvatarEntityContainer<A> >(aea);
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, A> > (waeca);
  // react object
  zbe::Stated *s = new DummyStated(0);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto coner = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  // cd
  zbe::CollisionData* cData = new zbe::CollisionData(zbe::Point2D(), zbe::Vector2D());

  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";

  dssaa.run(coner, ro,  cData);
  EXPECT_TRUE(d1->executed) << "d1 must be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d1->executed = false;

  s->setState(1);
  dssaa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_TRUE(d2->executed) << "d2 must be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d2->executed = false;

  s->setState(102); // Use default
  dssaa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_TRUE(dd->executed) << "dd must be executed";
  dd->executed = false;

  // empty ro.
  std::shared_ptr<zbe::ReactObject<DummyReactor> > emptyRo = std::make_shared<zbe::ReactObjectCommon<DummyReactor> > ();
  s->setState(0); // Use default
  dssaa.run(coner, emptyRo,  cData);
  EXPECT_TRUE(d1->executed) << "d1 must be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d1->executed = false;

  s->setState(1);
  dssaa.run(coner, emptyRo,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_TRUE(d2->executed) << "d2 must be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d2->executed = false;

  s->setState(102); // Use default
  dssaa.run(coner, emptyRo,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_TRUE(dd->executed) << "dd must be executed";
  dd->executed = false;
}

TEST(DaemonSelectorAlienAtor, act) {
  // Daemons & Actuator
  std::shared_ptr<DummyDaemon> d1 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> d2 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dd = std::make_shared<DummyDaemon>();
  zbe::DaemonSelectorAlienAtor<zbe::WeakAvatarEntityContainer<>, DummyReactor > dsaa(dd);
  dsaa.setDaemon(0,d1);
  dsaa.setDaemon(1,d2);
  // react object
  zbe::Stated *s = new DummyStated(0);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto waecs = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, zbe::Stated> > (waecs);
  // Collisioner
  auto coner = std::make_shared<zbe::WeakAvatarEntityContainer<> >();
  // cd
  zbe::CollisionData* cData = new zbe::CollisionData(zbe::Point2D(), zbe::Vector2D());

  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";

  dsaa.run(coner, ro,  cData);
  EXPECT_TRUE(d1->executed) << "d1 must be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d1->executed = false;

  s->setState(1);
  dsaa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_TRUE(d2->executed) << "d2 must be executed";
  EXPECT_FALSE(dd->executed) << "dd must not be executed";
  d2->executed = false;

  s->setState(102); // Use default
  dsaa.run(coner, ro,  cData);
  EXPECT_FALSE(d1->executed) << "d1 must not be executed";
  EXPECT_FALSE(d2->executed) << "d2 must not be executed";
  EXPECT_TRUE(dd->executed) << "dd must be executed";
  dd->executed = false;
}

}  // namespace DaemonSelectorAtor
