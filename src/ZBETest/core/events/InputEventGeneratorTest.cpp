#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEventGenerator.h"

TEST(InputEventGenerator, Event) {
  // Build tools
  zbe::InputBuffer * ib = new zbe::InputBuffer();
  zbe::InputEventGenerator ieg(ib, 1);
  // Setup test
  zbe::InputStatus isa(0,0.0,0);
  zbe::InputStatus isb(1,1.0,1);
  zbe::InputStatus isc(2,2.0,2);
  zbe::InputStatus isd(3,3.0,3);
  zbe::InputStatus ise(4,4.0,4);
  zbe::InputStatus isf(5,5.0,5);
  ib->insert(isa);
  ib->insert(isb);
  ib->insert(isc);
  ib->insert(isd);
  ib->insert(ise);
  ib->insert(isf);

  // Actual test
  ieg.generate(2,4);
  zbe::EventStore &es = zbe::EventStore::getInstance();
  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  zbe::Event* e = es.getEvents().front();
  EXPECT_EQ((uint64_t)1, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)3, e->getTime()) << "the event in time 3 must be stored";
  delete e;
}
