#include "gtest/gtest.h"

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/archetypes/Movable.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/BehaviorMaster.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/behaviors/PerFrameLinearMotion.h"

using namespace zbe;

class DummyMovable : public Movable<2> {
public:
  DummyMovable():vel({1.0,1.0}),pos({1.0,1.0}){
  }

  void setVelocity(Vector<2> velocity) {
    //I said dummy
  }

  Vector<2> getVelocity() const {
      return vel;
  }

  Point<2> getPosition() const {
    return pos;
  }

  void setPosition(Point<2> position) {
    pos = position;
  }
private:
  Vector2D vel;
  Point2D pos;
};

TEST(BehaviorMaster, DaemonMaster) {
  /*Behavior<Movable<2> > * behav = new PerFrameLinearMotion<2>();
  std::vector<Movable<2> > * entities = new std::vector<Movable<2> >();
  //entities->
  Daemon * master = new BehaviorMaster<Movable<2> >(behav, entities);
  master->run();
  ASSERT_TRUE(true);
  ASSERT_TRUE(true) << "All daemons called";*/
}
