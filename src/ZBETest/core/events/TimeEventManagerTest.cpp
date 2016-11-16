#include "gtest/gtest.h"

#include "ZBE/core/events/managers/TimeEventManager.h"

#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/handlers/TimeHandler.h"

class DUMMYTimeHandler : public zbe::TimeHandler {
public:
  DUMMYTimeHandler(uint64_t timerId) : timerId(timerId), success(false), called(false) {}

  void run(zbe::TimeEvent* event) {
    success = event->getTimerId() == timerId;
    called = true;
    delete event;
  }

  bool check() {return (success);}

  bool isCalled() {return (called);}

  void reset(uint64_t timerId) {
    this->timerId = timerId;
    success = false;
    called = false;
  }

private:
  uint64_t timerId;
  bool success;
  bool called;
};

TEST(TimeEventManager, Run) {
  DUMMYTimeHandler t1(1);
  DUMMYTimeHandler t2(2);
  DUMMYTimeHandler t3(3);
  DUMMYTimeHandler t4(4);

  zbe::TimeEventManager& tem = zbe::TimeEventManager::getInstance();

  tem.addHandler(1, &t1);
  tem.addHandler(2, &t2);
  tem.addHandler(3, &t3);
  tem.addHandler(4, &t4);

  zbe::TimeEvent *te1 = new zbe::TimeEvent(1, 1, 1);
  zbe::TimeEvent *te3 = new zbe::TimeEvent(1, 1, 3);
  zbe::TimeEvent *te4 = new zbe::TimeEvent(1, 1, 4);

  EXPECT_FALSE(t1.check()) << "Initially t1 is not true.";
  EXPECT_FALSE(t2.check()) << "Initially t2 is not true.";
  EXPECT_FALSE(t3.check()) << "Initially t3 is not true.";
  EXPECT_FALSE(t4.check()) << "Initially t4 is not true.";

  tem.run(te1);

  EXPECT_TRUE(t1.check()) << "t1 now is true.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_FALSE(t3.check()) << "t3 is not true.";
  EXPECT_FALSE(t4.check()) << "t4 is not true.";

  t1.reset(1);
  tem.run(te3);

  EXPECT_FALSE(t1.check()) << "t1 is not true, anymore.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_TRUE(t3.check()) << "t3 now is true.";
  EXPECT_FALSE(t4.check()) << "t4 is not true.";

  t3.reset(3);
  tem.run(te4);

  EXPECT_FALSE(t1.check()) << "t1 is not true, anymore.";
  EXPECT_FALSE(t2.check()) << "t2 is not true and never will be.";
  EXPECT_FALSE(t3.check()) << "t3 is not true, anymore.";
  EXPECT_TRUE(t4.check()) << "t4 now is true.";
}
