#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

namespace TimeEventGeneratorTest {

class DummyTimer : public zbe::Timer {
  public:
    void start() {}
    int64_t stop() {return (0);}
    void reset() {}
    int64_t lapTime() {return (0);}
    int64_t totalTime() {return ((i++)*1000000);}
    bool isRunning() {return (true);}

  private:
    int i = 0;
};

TEST(TimeEventGenerator, Event) {
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setMaxFrameTime(1000000);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime.setSystemTimer(sysTimer);

  zbe::TimeEventGenerator teg(3);
  teg.addTimer(nullptr, 1000000);
  teg.addTimer(nullptr, 1500000);
  teg.addTimer(nullptr, 2500000);
  zbe::EventStore &es = zbe::EventStore::getInstance();

  sysTime.update();
  sysTime.update();
  sysTime.setPartialFrameTime(1000000);

  teg.generate();

  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  zbe::TimeEvent* e = (zbe::TimeEvent*)(es.getEvents().front());
  es.clearStore();
  EXPECT_EQ((uint64_t)3, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)zbe::quantizeTime(1000000), e->getTime()) << "the event in time 3 must be stored";
  EXPECT_EQ(nullptr, e->getHandler()) << "the event in time 3 must be stored";
  ASSERT_TRUE(es.getEvents().empty()) << "List must be empty.";

  sysTime.update();
  sysTime.setPartialFrameTime(2000000);

  teg.generate();

  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  e = (zbe::TimeEvent*)(es.getEvents().front());
  es.clearStore();
  EXPECT_EQ((uint64_t)3, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)zbe::quantizeTime(1500000), e->getTime()) << "the event in time 3 must be stored";
  EXPECT_EQ(nullptr, e->getHandler()) << "the event in time 3 must be stored";
  ASSERT_TRUE(es.getEvents().empty()) << "List must be empty.";
}

}  // namespace TimeEventGeneratorTest
