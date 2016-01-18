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
  Behavior<Movable<2> > * behav = new PerFrameLinearMotion<2>();
  std::vector<Movable<2>*> * entities = new std::vector<Movable<2>*>();
  DummyMovable * mov1 = new DummyMovable();
  DummyMovable * mov2 = new DummyMovable();
  DummyMovable * mov3 = new DummyMovable();
  entities->push_back(mov1);
  entities->push_back(mov2);
  entities->push_back(mov3);
  Daemon * master = new BehaviorMaster<Movable<2> >(behav, entities);
  // Expect all position to be increased to 2.0, 2.0
  Point<2> finalPos{2.0,2.0};
  master->run();
  EXPECT_EQ(mov1->getPosition().x,finalPos.x);
  EXPECT_EQ(mov2->getPosition().x,finalPos.x);
  EXPECT_EQ(mov3->getPosition().x,finalPos.x);
  EXPECT_EQ(mov1->getPosition().y,finalPos.y);
  EXPECT_EQ(mov2->getPosition().y,finalPos.y);
  EXPECT_EQ(mov3->getPosition().y,finalPos.y);
  // Expect all position to be increased by 2.0, 2.0
  finalPos.x=3.0;finalPos.y=3.0;
  master->run();
  EXPECT_EQ(mov1->getPosition().x,finalPos.x);
  EXPECT_EQ(mov2->getPosition().x,finalPos.x);
  EXPECT_EQ(mov3->getPosition().x,finalPos.x);
  EXPECT_EQ(mov1->getPosition().y,finalPos.y);
  EXPECT_EQ(mov2->getPosition().y,finalPos.y);
  EXPECT_EQ(mov3->getPosition().y,finalPos.y);
}
