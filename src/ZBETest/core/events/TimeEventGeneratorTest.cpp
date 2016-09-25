#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEventGenerator.h"

TEST(TimeEventGenerator, Event) {
  zbe::TimeEventGenerator teg(3);
  teg.addTimer(1, 1000000, 0);
  teg.addTimer(2, 1500000, 0);
  teg.addTimer(3, 2500000, 0);
  zbe::EventStore &es = zbe::EventStore::getInstance();

  teg.generate(0, 2000000);

  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  zbe::TimeEvent* e = (zbe::TimeEvent*)(es.getEvents().front());
  es.clearStore();
  EXPECT_EQ((uint64_t)3, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)1000000, e->getTime()) << "the event in time 3 must be stored";
  EXPECT_EQ((uint64_t)1, e->getTimerId()) << "the event in time 3 must be stored";
  ASSERT_TRUE(es.getEvents().empty()) << "List must be empty.";

  teg.generate(1000000, 2000000);

  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  e = (zbe::TimeEvent*)(es.getEvents().front());
  es.clearStore();
  EXPECT_EQ((uint64_t)3, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)1500000, e->getTime()) << "the event in time 3 must be stored";
  EXPECT_EQ((uint64_t)2, e->getTimerId()) << "the event in time 3 must be stored";
  ASSERT_TRUE(es.getEvents().empty()) << "List must be empty.";

  delete e;
}
