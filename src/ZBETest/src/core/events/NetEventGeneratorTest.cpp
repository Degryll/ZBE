#include "gtest/gtest.h"
#include <vector>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/io/NetMessage.h"
#include "ZBE/core/io/NetBuffer.h"
#include "ZBE/core/events/NetEvent.h"
#include "ZBE/core/events/handlers/NetHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/NetEventGenerator.h"

namespace NetEventGeneratorTest {

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

class DummyNetHandler : public zbe::NetHandler {
public:
  DummyNetHandler() :msgCall() {}
  void run(uint32_t sequence, zbe::SDLSocket, std::vector<char> msg) override {
    sequenceCall = sequence;
    msgCall = msg;
  }

  uint32_t sequenceCall = 0;
  std::vector<char> msgCall;
};

TEST(NetEventGenerator, run) {
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setMaxFrameTime(zbe::SECOND*2);

  auto sysTimer = std::make_shared<DummyTimer>();
  sysTime->setSystemTimer(sysTimer);

  // Build tools
  std::shared_ptr<zbe::NetBuffer> nb = std::make_shared<zbe::NetBuffer>();
  zbe::NetEventGenerator neg(0,nb);

  //NetMessage(Uint32 sequence, SDLSocket socket, std::vector<char> msg, uint64_t time)
  zbe::SDLSocket socket;
  DummyNetHandler* hndlr = new DummyNetHandler();
  socket.setHandler(hndlr);
  // Setup test
  zbe::NetMessage nma(0, socket, {'a','b','c'},0);
  zbe::NetMessage nmb(1, socket, {'d','e','f'},1);
  zbe::NetMessage nmc(2, socket, {'g','h','i'},2);
  zbe::NetMessage nmd(3, socket, {'j','k','l'},3);
  zbe::NetMessage nme(4, socket, {'m','n','o'},4);
  zbe::NetMessage nmf(5, socket, {'p','q','r'},5);
  nb->insert(nma);
  nb->insert(nmb);
  nb->insert(nmc);
  nb->insert(nmd);
  nb->insert(nme);
  nb->insert(nmf);

  sysTime->update();
  sysTime->update();
  sysTime->setEventTime(2);

  sysTime->update();
  sysTime->setEventTime(4);

  neg.run();
  zbe::EventStore::getInstance().manageCurrent();

  EXPECT_EQ(hndlr->sequenceCall, 3)  << "must execute right sequence";
  EXPECT_EQ(hndlr->msgCall, (std::vector<char>{'j','k','l'}))  << "must execute right handler";

  delete hndlr;
}

}  // namespace NetEventGeneratorTest
