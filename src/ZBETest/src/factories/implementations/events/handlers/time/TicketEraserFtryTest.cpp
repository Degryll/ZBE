#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/events/handlers/time/TicketEraser.h"

#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"

namespace TicketEraserFtryTest {

class DummyTicket : public zbe::Ticket {
public:
  inline void setACTIVE()   {s = ACTIVE;}
  inline void setINACTIVE() {s = INACTIVE;}
  inline void setERASED()   {s = ERASED;}

  inline void setState(State state) {s = state;}

  inline bool isACTIVE()    {return (s == ACTIVE);}
  inline bool isNotACTIVE() {return (s != ACTIVE);}
  inline bool isINACTIVE()  {return (s == INACTIVE);}
  inline bool isERASED()    {return (s == ERASED);}

  inline State getState() {return (s);}

private:
  State s = ACTIVE;
};

TEST(TicketEraserFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &ticketRsrc = RsrcStore<Ticket>::getInstance();
  auto &timeRsrc = RsrcStore<TimeHandler>::getInstance();
  auto &ticketEraserRsrc = RsrcStore<TicketEraser>::getInstance();

  auto cfg = std::make_shared<json>();
//  (*cfg)["behavior"] = "dummyss";
  (*cfg)["ticket"] = "dummyticket";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  std::shared_ptr<zbe::Ticket> ticket = std::make_shared<DummyTicket>();
  ticketRsrc.insert("Ticket.dummyticket"s, ticket);

  TicketEraserFtry tef;
  tef.create("TicketEraserFtryTestName", cfgId);
  tef.setup("TicketEraserFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("TimeHandler.TicketEraserFtryTestName");
  std::shared_ptr<TimeHandler> outTH = timeRsrc.get(outId);

  uint64_t tefId = dict.get("TicketEraser.TicketEraserFtryTestName");

  ASSERT_NE(0, outId) << "Must create a time handler with given name";
  ASSERT_NE(0, tefId) << "Must create a Ticket Eraser with given name";

  EXPECT_TRUE(ticket->isACTIVE()) << "Initially ticket is active.";

  outTH->run(1);

  EXPECT_FALSE(ticket->isACTIVE()) << "Ticket is no longer active.";
  EXPECT_TRUE(ticket->isERASED()) << "Ticket is ERASED.";

  configRsrc.clear();
  dict.clear();
  ticketRsrc.clear();
  timeRsrc.clear();
  ticketEraserRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace TicketEraserFtryTest
