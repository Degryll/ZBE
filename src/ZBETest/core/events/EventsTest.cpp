#include "gtest/gtest.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/InputEvent.h"

TEST(Event, Event) {
  zbe::Event e(1,100);
  ASSERT_EQ((uint64_t)1, e.getId()) << "Must store id";
  ASSERT_EQ((uint64_t)100, e.getTime()) << "Must store time";
}

TEST(Event, TimeEvent) {
  zbe::TimeEvent e(1,100, 2);
  ASSERT_EQ((uint64_t)1, e.getId()) << "Must store id";
  ASSERT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  ASSERT_EQ((uint64_t)2, e.getTimerId()) << "Must store the timer id";
}

TEST(Event, InputEvent) {
  zbe::InputEvent e(1,100, 7, 1.0);
  ASSERT_EQ((uint64_t)1, e.getId()) << "Must store id";
  ASSERT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  ASSERT_EQ((uint64_t)7, e.getKey()) << "Must store the key id";
  ASSERT_EQ(1.0, e.getState()) << "Must store the key state";
}
