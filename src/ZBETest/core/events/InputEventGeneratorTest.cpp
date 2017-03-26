#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace InputEventGeneratorTest {

class MockInputHandler : public zbe::InputHandler {
	public:
	  MockInputHandler(const MockInputHandler&) = delete;
	  void operator=(const MockInputHandler&) = delete;

  	MockInputHandler() : b(false) {}

  	void run(float) {
      b = true;
  	}

    bool b;
};

TEST(InputEventGenerator, Event) {
  // Build tools
  zbe::InputBuffer * ib = new zbe::InputBuffer();
  MockInputHandler ha;
  MockInputHandler hb;
  MockInputHandler hc;
  MockInputHandler hd;
  MockInputHandler he;
  MockInputHandler hf;
  zbe::InputEventGenerator ieg(ib, 1);
  ieg.addHandler(0, &ha);
  ieg.addHandler(1, &hb);
  ieg.addHandler(2, &hc);
  ieg.addHandler(3, &hd);
  ieg.addHandler(4, &he);
  ieg.addHandler(5, &hf);
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

  ieg.generate(2,4);
  zbe::EventStore::getInstance().manageCurrent();

  EXPECT_FALSE(ha.b) << "a must be false";
  EXPECT_FALSE(hb.b) << "b must be false";
  EXPECT_FALSE(hc.b) << "c must be false";
  EXPECT_TRUE(hd.b)  << "d must be true";
  EXPECT_FALSE(he.b) << "e must be false";
  EXPECT_FALSE(hf.b) << "f must be false";

}

}  // namespace InputEventGeneratorTest
