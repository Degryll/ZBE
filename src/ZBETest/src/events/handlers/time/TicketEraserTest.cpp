#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/events/handlers/time/TicketEraser.h"

namespace TicketEraserTest {

class DummyTicket : public zbe::Ticket {
public:
  inline void setACTIVE()   {s = ACTIVE;}
  inline void setINACTIVE() {s = INACTIVE;}
  inline void setERASED()   {s = ERASED;}

  inline bool isACTIVE()    {return (s == ACTIVE);}
  inline bool isNotACTIVE() {return (s != ACTIVE);}
  inline bool isINACTIVE()  {return (s == INACTIVE);}
  inline bool isERASED()    {return (s == ERASED);}

private:
  State s = ACTIVE;
};

TEST(TicketEraser, run) {
  std::shared_ptr<zbe::Ticket> ticket = std::make_shared<DummyTicket>();

  zbe::TicketEraser te(ticket);

  EXPECT_TRUE(ticket->isACTIVE()) << "Initially ticket is active.";

  te.run(1);

  EXPECT_FALSE(ticket->isACTIVE()) << "Ticket is no longer active.";
  EXPECT_TRUE(ticket->isERASED()) << "Ticket is ERASED.";
}

}  // namespace TicketEraserTest
