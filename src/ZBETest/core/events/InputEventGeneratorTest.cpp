#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/io/InputReader.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEventGenerator.h"

class DummyInputReader : public zbe::InputReader {
  public:
    std::list<uint32_t> _changes;
    std::vector<uint64_t> times;
    std::vector<float> states;

    DummyInputReader(): _changes({0,1,2,3,4,5}),
                        times({0,1,2,3,4,5}),
                        states({0.0,1.0,2.0,3.0,4.0,5.0}){
    }

    ~DummyInputReader() {
    }

    std::list<uint32_t>* changes() {return &_changes;}

    float getStatus(uint32_t keyid) {return states[keyid];}

    uint64_t getTime(uint32_t keyid) {return times[keyid];}
};

TEST(InputEventGenerator, Event) {
  zbe::InputEventGenerator ieg(new DummyInputReader(), 1);
  ieg.generate(2,4);
  zbe::EventStore &es = zbe::EventStore::getInstance();
  ASSERT_FALSE(es.getEvents().empty()) << "List must have items.";
  zbe::Event* e = es.getEvents().front();
  EXPECT_EQ((uint64_t)1, e->getId()) << "must be stored with id 1";
  EXPECT_EQ((uint64_t)3, e->getTime()) << "the event in time 3 must be stored";
  delete e;
}
