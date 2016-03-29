#include "gtest/gtest.h"

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/archetypes/Movable.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/core/behaviors/Behavior.h"
//#include "ZBE/core/behaviors/PerFrameLinearMotion.h"

using namespace zbe;

class DummyMovable : public Movable<2> {
public:
  DummyMovable():vel({1.0,1.0}),pos({1.0,1.0}){}

  void setVelocity(Vector<2> velocity) {}

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

template<unsigned s>
class PerFrameLinearMotion : public Behavior<Movable<s> > {
  public:
    PerFrameLinearMotion() {}

    ~PerFrameLinearMotion() {}

    void apply(Movable<s> * entity){
      Point<s> endPos = entity->getPosition() + entity->getVelocity();
      entity->setPosition(endPos);
    }
};


TEST(Punishers, BehaviorDaemon) {
  Behavior<Movable<2> > * behav = new PerFrameLinearMotion<2>();
  std::vector<Movable<2>*> * entities = new std::vector<Movable<2>*>();
  DummyMovable * mov1 = new DummyMovable();
  DummyMovable * mov2 = new DummyMovable();
  DummyMovable * mov3 = new DummyMovable();
  entities->push_back(mov1);
  entities->push_back(mov2);
  entities->push_back(mov3);
  // Expect all position to be 1.0, 1.0
  Point<2> finalPos{1.0,1.0};
  Daemon * master = new BehaviorDaemon<std::vector<Movable<2>*>, Movable<2> >(behav, entities);
  EXPECT_EQ(mov1->getPosition().x,finalPos.x);
  EXPECT_EQ(mov2->getPosition().x,finalPos.x);
  EXPECT_EQ(mov3->getPosition().x,finalPos.x);
  EXPECT_EQ(mov1->getPosition().y,finalPos.y);
  EXPECT_EQ(mov2->getPosition().y,finalPos.y);
  EXPECT_EQ(mov3->getPosition().y,finalPos.y);
  // Expect all position to be increased to 2.0, 2.0
  finalPos.x=2.0;finalPos.y=2.0;
  master->run();
  EXPECT_EQ(mov1->getPosition().x,finalPos.x);
  EXPECT_EQ(mov2->getPosition().x,finalPos.x);
  EXPECT_EQ(mov3->getPosition().x,finalPos.x);
  EXPECT_EQ(mov1->getPosition().y,finalPos.y);
  EXPECT_EQ(mov2->getPosition().y,finalPos.y);
  EXPECT_EQ(mov3->getPosition().y,finalPos.y);
  // Expect all position to be increased to 3.0, 3.0
  finalPos.x=3.0;finalPos.y=3.0;
  master->run();
  EXPECT_EQ(mov1->getPosition().x,finalPos.x);
  EXPECT_EQ(mov2->getPosition().x,finalPos.x);
  EXPECT_EQ(mov3->getPosition().x,finalPos.x);
  EXPECT_EQ(mov1->getPosition().y,finalPos.y);
  EXPECT_EQ(mov2->getPosition().y,finalPos.y);
  EXPECT_EQ(mov3->getPosition().y,finalPos.y);
}
