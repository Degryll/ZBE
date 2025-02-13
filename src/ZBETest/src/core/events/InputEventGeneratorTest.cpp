#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/util/InputStatusManager.h"
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

// class MockInputHandler : public zbe::InputHandler {
// 	public:
// 	  MockInputHandler(const MockInputHandler&) = delete;
// 	  void operator=(const MockInputHandler&) = delete;
//
//   	MockInputHandler() : b(false) {}
//
//   	void run(uint32_t, float) override {
//       b = true;
//   	}
//
//     bool b;
// };

class DummyInputStatusManager : public zbe::InputStatusManager {
public:
  DummyInputStatusManager() : iss() {}
  void generate(const zbe::InputStatus& is) {
    iss.push_back(is);
  }
  std::vector<zbe::InputStatus> iss;
};

TEST(InputEventGenerator, run) {
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setMaxFrameTime(zbe::SECOND*2);

  auto sysTimer = std::make_shared<DummyTimer>();
  sysTime->setSystemTimer(sysTimer);

  // Build tools
  std::shared_ptr<zbe::InputBuffer> ib = std::make_shared<zbe::InputBuffer>();
  std::shared_ptr<DummyInputStatusManager> dism =  std::make_shared<DummyInputStatusManager>();
  zbe::InputEventGenerator ieg(ib);
  ieg.addManager(dism);

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

  sysTime->update();
  sysTime->update();
  sysTime->setEventTime(2);

  sysTime->update();
  sysTime->setEventTime(4);

  ieg.run();

  EXPECT_EQ(dism->iss[0].getId(), 3)  << "d must be true";

}

}  // namespace InputEventGeneratorTest
