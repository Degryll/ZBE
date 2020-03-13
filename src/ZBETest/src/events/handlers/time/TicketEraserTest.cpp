#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/events/handlers/time/TicketEraser.h"

#include "testutils/DummyTicket.h"

namespace TicketEraserTest {

TEST(TicketEraser, run) {
  std::shared_ptr<zbe::Ticket> ticket = std::make_shared<zbetest::DummyTicket>();

  zbe::TicketEraser te(ticket);

  EXPECT_TRUE(ticket->isACTIVE()) << "Initially ticket is active.";

  te.run(1);

  EXPECT_FALSE(ticket->isACTIVE()) << "Ticket is no longer active.";
  EXPECT_TRUE(ticket->isERASED()) << "Ticket is ERASED.";
}

}  // namespace TicketEraserTest
