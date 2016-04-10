#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"

TEST(EventStore, EventStore) {
  zbe::Event e0(0,104);
  zbe::Event e1(1,100);
  zbe::Event e2(2,100);
  zbe::Event e3(3,101);
  zbe::Event e4(4,104);

  zbe::EventStore &store = zbe::EventStore::getInstance();
  std::forward_list<zbe::Event> eventlist = store.getEvents();

  EXPECT_EQ(true, eventlist.empty()) << "Must be empty at init";

  store.storeEvent(e0);
  store.storeEvent(e1);
  store.storeEvent(e2);
  store.storeEvent(e3);

  eventlist = store.getEvents();

  auto it = eventlist.begin();

  EXPECT_EQ(2u,(*it++).getId()) << "Must find e2 first";
  EXPECT_EQ(1u,(*it++).getId()) << "Must find e1 next";
  EXPECT_EQ(eventlist.end(),it) << "Must found no more";
}
