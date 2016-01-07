#include "gtest/gtest.h"

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/archetypes/Movable.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/BehaviorMaster.h"

#include "ZBE/core/behaviors/PerFrameLinearMotion.h"

class DummyMovable : public zbe::Movable<2> {
public:
  DummyMovable():vel(),pos(){
      vel.setCartesian(1,1);
      pos.setCartesian(1,1);
  }

  void setVelocity(zbe::Vector<2> velocity) {
    //I said dummy
  }

  zbe::Vector<2> getVelocity() const {
      return vel;
  }

  Point<s> getPosition() const {
    return pos;
  }

  void setPosition(Point<s> position) {
    pos = position;
  }
private:
  zbe::Vector2D vel;
  zbe::Point<2> pos;
};

TEST(BehaviorMaster, DaemonMaster) {
  Behavior<Movable<2> > * behav = new PerFrameLinearMotion();
  std::vector<Movable<2> > * entities = new std::vector<Movable<2> >();
  entities->
  BehaviorMaster<Movable<2> > master(Behavior<T> * behavior, std::vector<T> * entities);
  master.run();
  ASSERT_TRUE(true);
  ASSERT_TRUE(true) << "All daemons called";
}
