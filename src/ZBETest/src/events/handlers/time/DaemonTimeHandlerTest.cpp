#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/events/handlers/time/DaemonTimeHandler.h"

namespace DaemonTimeHandlerTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false){}

  void run() override {
    executed = true;
  }
  bool executed;
};

TEST(DaemonTimeHandler, run) {
  std::shared_ptr<DummyDaemon> d = std::make_shared<DummyDaemon>();

  zbe::DaemonTimeHandler dth(d);

  EXPECT_FALSE(d->executed) << "Initially the daemon is not executed.";

  dth.run(1);

  EXPECT_TRUE(d->executed) << "The daemon is executed.";
}

}  // namespace DaemonTimeHandlerTest
