#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"

namespace eventtest {
class EventMock : public zbe::Event{
public:
  EventMock(uint64_t id, int64_t time, bool& b) : Event(id,time), b(b) {b=false;}
  void manage() {b=true;};
	bool& b;
};


TEST(EventStore, EventStore) {
  bool a,b,c,d;
  EventMock* e0 = new EventMock(0,104, a);
  EventMock* e1 = new EventMock(1,100, b);
  EventMock* e2 = new EventMock(2,100, c);
  EventMock* e3 = new EventMock(3,101, d);

  zbe::EventStore &store = zbe::EventStore::getInstance();

  store.storeEvent(e0);
  store.storeEvent(e1);
  store.storeEvent(e2);
  store.storeEvent(e3);

  store.manageCurrent();

  EXPECT_FALSE(a) << "a must be false";
  EXPECT_TRUE(b)  << "b must be true";
  EXPECT_TRUE(c)  << "c must be true";
  EXPECT_FALSE(d) << "d must be false";
}

} //namespace eventtest
