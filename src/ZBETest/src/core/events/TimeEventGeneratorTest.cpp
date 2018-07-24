#include "gtest/gtest.h"
#include <vector>
#include <memory>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/time/ContextTime.h"

#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

#include "testutils/MockedContextTime.h"

namespace TimeEventGeneratorTest {

struct DummyTimeHandler : public zbe::TimeHandler {
public:
  DummyTimeHandler() : callTime(0) {}
  void run(uint64_t time) {
    callTime = time;
  }

  uint64_t callTime;
};

TEST(TimeEventGenerator, Event) {
  std::shared_ptr<DummyTimeHandler> a = std::make_shared<DummyTimeHandler>();
  std::shared_ptr<DummyTimeHandler> b = std::make_shared<DummyTimeHandler>();
  std::shared_ptr<DummyTimeHandler> c = std::make_shared<DummyTimeHandler>();

  std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
  zbe::ContextTime::setMaxFrameTime(5000000);

  contextTime->setFixedTime(0);
  contextTime->update();

  zbe::TimeEventGenerator teg(3, contextTime);
  teg.addTimer(a, 1000000);
  teg.addTimer(b, 1500000);
  teg.addTimer(c, 2500000);
  zbe::EventStore &es = zbe::EventStore::getInstance();

  EXPECT_EQ(0, a->callTime) << "a must not be called";
  EXPECT_EQ(0, b->callTime) << "b must not be called";
  EXPECT_EQ(0, c->callTime) << "c must not be called";

  contextTime->setFixedTime(2000000);
  contextTime->update();

  teg.run();
  es.manageCurrent();

  EXPECT_EQ(zbe::quantizeTime(1000000), a->callTime) << "a must be called with time 1000000";
  EXPECT_EQ(0, b->callTime) << "b must not be called";
  EXPECT_EQ(0, c->callTime) << "c must not be called";

  es.clearStore();
  a->callTime = 0;

  contextTime->setEventTime(zbe::quantizeTime(1000000));
  contextTime->updateInitTime();
  teg.run();
  es.manageCurrent();

  EXPECT_EQ(0, a->callTime) << "a must not be called";
  EXPECT_EQ(zbe::quantizeTime(1500000), b->callTime) << "b must be called with time 1500000";
  EXPECT_EQ(0, c->callTime) << "c must not be called";
}

TEST(TimeEventGenerator, TimerTicket) {
  std::shared_ptr<DummyTimeHandler> a = std::make_shared<DummyTimeHandler>();
  std::shared_ptr<DummyTimeHandler> b = std::make_shared<DummyTimeHandler>();
  std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
  contextTime->setMaxFrameTime(1000000);
  zbe::TimeEventGenerator teg(3, contextTime);
  zbe::EventStore &es = zbe::EventStore::getInstance();

  std::shared_ptr<zbe::TimerTicket> ticketA = teg.addTimer(a, 1500000);
  std::shared_ptr<zbe::TimerTicket> ticketB = teg.addTimer(b, 1500000);

  contextTime->setFixedTime(0);
  contextTime->update();

  contextTime->setFixedTime(1000000);
  contextTime->update();

  teg.run();
  es.manageCurrent();

  EXPECT_EQ(0, a->callTime) << "a must not be called";
  EXPECT_EQ(0, b->callTime) << "b must not be called";

  ticketB->increaseTime(700000);

  ticketA->increaseTime(-700000);
  ticketB->increaseTime(-700000);

  teg.run();
  es.manageCurrent();

  EXPECT_EQ(zbe::quantizeTime(1500000) + zbe::quantizeTime(-700000), a->callTime) << "a must be called with time 1000000 (now)";
  EXPECT_EQ(0, b->callTime) << "b must not be called";

  contextTime->setFixedTime(2000000);
  contextTime->update();

  teg.run();
  es.manageCurrent();

  EXPECT_EQ(zbe::quantizeTime(1500000) + zbe::quantizeTime(700000) + zbe::quantizeTime(-700000), b->callTime) << "b must be called with time 1500000 (now)";
}

}  // namespace TimeEventGeneratorTest
