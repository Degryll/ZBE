#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/MainLoop.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"

#include "ZBE/factories/implementations/daemons/MainLoopFtry.h"

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

class DummyMainLoopExit : virtual public zbe::Daemon {
public:
  DummyMainLoopExit(std::shared_ptr<zbe::MainLoop> mainLoop) : ml(mainLoop), executed(false) {}
  DummyMainLoopExit() : ml(0), executed(false) {}

  void setML(std::shared_ptr<zbe::MainLoop> mainLoop) {
    ml = mainLoop;
  }

  void run() {
    ml->stop();
    executed = true;
  }

  std::shared_ptr<zbe::MainLoop> ml;
  bool executed = false;
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

TEST(MainLoopFtryTest, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto& timeRsrc = RsrcStore<ContextTime>::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();
  (*cfg)["preDaemon"] = "preD"s;
  (*cfg)["eventDaemon"] = "eventD"s;
  (*cfg)["commonDaemon"] = "commonD"s;
  (*cfg)["reactDaemon"] = "reactD"s;
  (*cfg)["drawDaemon"] = "drawD"s;
  (*cfg)["postDaemon"] = "postD"s;
  (*cfg)["contextTime"] = "contextT"s;
  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto preD = std::make_shared<DummyDaemon>();
  auto eventD = std::make_shared<DummyEventDaemon>();
  auto commonD = std::make_shared<DummyDaemon>();
  auto reactD = std::make_shared<DummyDaemon>();
  auto drawD = std::make_shared<DummyDaemon>();
  auto postD = std::make_shared<DummyMainLoopExit>();

  auto contextT = std::make_shared<zbetest::MockedContextTime>();
  zbe::ContextTime::setMaxFrameTime(5000000);

  daemonRsrc.insert("Daemon.preD"s, preD);
  daemonRsrc.insert("Daemon.eventD"s, eventD);
  daemonRsrc.insert("Daemon.commonD"s, commonD);
  daemonRsrc.insert("Daemon.reactD"s, reactD);
  daemonRsrc.insert("Daemon.drawD"s, drawD);
  daemonRsrc.insert("Daemon.postD"s, postD);
  timeRsrc.insert("Time.contextT"s, contextT);
  MainLoopFtry mlf;
  mlf.create("MainLoopFtryTestName", cfgId);
  mlf.setup("MainLoopFtryTestName", cfgId);

  auto mlDmn = daemonRsrc.get("Daemon.MainLoopFtryTestName");
  std::shared_ptr<MainLoop> aux = std::dynamic_pointer_cast<MainLoop> (mlDmn);
  postD->setML(aux);

  contextT->setFixedTime(0);
  contextT->update();

  contextT->setFixedTime(10000);

  mlDmn->run();

  EXPECT_TRUE(preD->executed) << "Must call preD";
  EXPECT_TRUE(eventD->executed) << "Must call eventD";
  EXPECT_TRUE(commonD->executed) << "Must call commonD";
  EXPECT_TRUE(reactD->executed) << "Must call reactD";
  EXPECT_TRUE(drawD->executed) << "Must not call drawD";
  EXPECT_TRUE(postD->executed) << "Must not call postD";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace MainLoopFtryTest
