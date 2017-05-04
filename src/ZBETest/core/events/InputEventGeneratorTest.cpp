#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace InputEventGeneratorTest {

class DummyTimer : public zbe::Timer {
  public:
    void start() {}
    int64_t stop() {return (0);}
    void reset() {}
    int64_t lapTime() {return (0);}
    int64_t totalTime() {return ((i++*2));}
    bool isRunning() {return (true);}

  private:
    int i = 0;
};

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
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setMaxFrameTime(zbe::SECOND*2);

  DummyTimer* sysTimer = new DummyTimer;
  sysTime.setSystemTimer(sysTimer);

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

  sysTime.update();
  sysTime.update();
  sysTime.setEventTime(2);

  sysTime.update();
  sysTime.setEventTime(4);

  ieg.run();
  zbe::EventStore::getInstance().manageCurrent();

  EXPECT_FALSE(ha.b) << "a must be false";
  EXPECT_FALSE(hb.b) << "b must be false";
  EXPECT_FALSE(hc.b) << "c must be false";
  EXPECT_TRUE(hd.b)  << "d must be true";
  EXPECT_FALSE(he.b) << "e must be false";
  EXPECT_FALSE(hf.b) << "f must be false";

}

}  // namespace InputEventGeneratorTest
