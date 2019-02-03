#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/MainLoop.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"

#include "ZBE/factories/implementations/daemons/MainLoopExitFtry.h"

#include "testutils/MockedContextTime.h"

namespace MainLoopFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon() : executed(false){}

  void run(){
    executed = true;
  }
  bool executed;
};

class DummyEvent : public zbe::Event {
public:
  DummyEvent(): Event(42, 9500){};
  void manage() {}
};

class DummyEventDaemon : public zbe::Daemon {
public:
  DummyEventDaemon(): executed(false) {}

  void run() {
    if(executed) return;
    auto e = new DummyEvent();
    es.storeEvent(e);
    executed = true;
  }
  zbe::EventStore& es = zbe::EventStore::getInstance();
  bool executed;
};

TEST(MainLoopExitFtryTest, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto& mlRsrc = RsrcStore<MainLoop>::getInstance();
  auto& valIRsrc = RsrcStore<Value<int64_t> >::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();
  (*cfg)["mainloop"] = "ml1"s;
  (*cfg)["valueHolder"] = "val1"s;
  (*cfg)["outValue"] = 1;
  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto preD = std::make_shared<DummyDaemon>();
  auto eventD = std::make_shared<DummyEventDaemon>();
  auto commonD = std::make_shared<DummyDaemon>();
  auto reactD = std::make_shared<DummyDaemon>();
  auto drawD = std::make_shared<DummyDaemon>();
  auto postD = std::make_shared<DaemonMaster>();

  auto contextT = std::make_shared<zbetest::MockedContextTime>();
  zbe::ContextTime::setMaxFrameTime(5000000);
  auto ml = std::make_shared<MainLoop>(preD, eventD, commonD, reactD, drawD, postD, contextT);
  mlRsrc.insert("MainLoop.ml1", ml);
  daemonRsrc.insert("Daemon.ml1", ml);
  valIRsrc.insert("ValueI.val1", std::make_shared<SimpleValue<int64_t> >());

  MainLoopExitFtry mlef;
  mlef.create("MainLoopExitFtryTestName", cfgId);
  mlef.setup("MainLoopExitFtryTestName", cfgId);

  auto mleDmn = daemonRsrc.get("Daemon.MainLoopExitFtryTestName");
  postD->addDaemon(mleDmn);

  contextT->setFixedTime(0);
  contextT->update();

  contextT->setFixedTime(10000);

  ml->run();

  EXPECT_TRUE(preD->executed) << "Must call preD";
  EXPECT_TRUE(eventD->executed) << "Must call eventD";
  EXPECT_TRUE(commonD->executed) << "Must call commonD";
  EXPECT_TRUE(reactD->executed) << "Must call reactD";

  configRsrc.clear();
  daemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace MainLoopFtryTest
