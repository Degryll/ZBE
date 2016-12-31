#include "gtest/gtest.h"

#include "ZBE/core/events/managers/TimeEventManager.h"

#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

class DUMMYTimeHandler : public zbe::TimeHandler {
public:
  DUMMYTimeHandler() : called(false) {}

  void run() {
    called = true;
  }

  bool check() {return (called);}

  void reset() {
    called = false;
  }

private:
  bool called;
};

TEST(TimeEventManager, Run) {
  DUMMYTimeHandler t1;
  DUMMYTimeHandler t2;
  DUMMYTimeHandler t3;
  DUMMYTimeHandler t4;

  zbe::TimeEventManager& tem = zbe::TimeEventManager::getInstance();

  zbe::TimeEvent *te1 = new zbe::TimeEvent(1, 1, &t1);
  zbe::TimeEvent *te3 = new zbe::TimeEvent(1, 1, &t3);
  zbe::TimeEvent *te4 = new zbe::TimeEvent(1, 1, &t4);

  EXPECT_FALSE(t1.check()) << "Initially t1 is not true.";
  EXPECT_FALSE(t2.check()) << "Initially t2 is not true.";
  EXPECT_FALSE(t3.check()) << "Initially t3 is not true.";
  EXPECT_FALSE(t4.check()) << "Initially t4 is not true.";

  tem.run(te1);

  EXPECT_TRUE(t1.check()) << "t1 now is true.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_FALSE(t3.check()) << "t3 is not true.";
  EXPECT_FALSE(t4.check()) << "t4 is not true.";

  t1.reset();
  tem.run(te3);

  EXPECT_FALSE(t1.check()) << "t1 is not true, anymore.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_TRUE(t3.check()) << "t3 now is true.";
  EXPECT_FALSE(t4.check()) << "t4 is not true.";

  t3.reset();
  tem.run(te4);

  EXPECT_FALSE(t1.check()) << "t1 is not true, anymore.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_FALSE(t3.check()) << "t3 is not true, anymore.";
  EXPECT_TRUE(t4.check()) << "t4 now is true.";
}
