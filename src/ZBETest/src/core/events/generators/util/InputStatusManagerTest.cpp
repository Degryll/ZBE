#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/util/InputStatusManager.h"

namespace InputStatusManagerTest {

class MockInputHandler : public zbe::InputHandler {
	public:
	  MockInputHandler(const MockInputHandler&) = delete;
	  void operator=(const MockInputHandler&) = delete;

  	MockInputHandler() : b(false) {}

  	void run(uint32_t, float) override {
      b = true;
  	}

    bool b;
};

TEST(InputStatusManager, generate) {
  using namespace zbe;
  MappedInputStatusManager mism(1);
  MockInputHandler mih;
  mism.addHandler(2, &mih);

  ASSERT_FALSE(mih.b) << "Intially handler not called.";

  // Setup test
  zbe::InputStatus isa(1,1.0,0);
  zbe::InputStatus isb(2,1.0,0);

  mism.generate(isa);
  zbe::EventStore::getInstance().manageCurrent();

  ASSERT_FALSE(mih.b) << "No hander for first input.";

  mism.generate(isb);
  zbe::EventStore::getInstance().manageCurrent();

  ASSERT_TRUE(mih.b) << "Hander must be called.";
}

}  // namespace InputEventGeneratorTest
