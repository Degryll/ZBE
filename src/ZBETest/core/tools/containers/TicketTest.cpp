#include "gtest/gtest.h"

#include "ZBE/core/tools/containers/Ticket.h"

TEST(Ticket, Usage) {
  zbe::TicketedElement<int> te(std::make_shared<int>(42));
  EXPECT_EQ(zbe::Ticket::ACTIVE,te.getState()) << "Create TicketedElement, ACTIVE by default. - getState";
  EXPECT_TRUE(te.isACTIVE()) << "Create TicketedElement, ACTIVE by default. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE()) << "Create TicketedElement, ACTIVE by default. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE()) << "Create TicketedElement, ACTIVE by default. - isINACTIVE";
  EXPECT_FALSE(te.isERASED()) << "Create TicketedElement, ACTIVE by default. - isERASED";

  te.setState(zbe::Ticket::ACTIVE);
  EXPECT_EQ(zbe::Ticket::ACTIVE,te.getState()) << "Set state to ACTIVE. - getState";
  EXPECT_TRUE(te.isACTIVE())                << "Set state to ACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "Set state to ACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "Set state to ACTIVE. - isERASED";

  te.setState(zbe::Ticket::INACTIVE);
  EXPECT_EQ(zbe::Ticket::INACTIVE,te.getState()) << "Set state to INACTIVE. - getState";
  EXPECT_FALSE(te.isACTIVE())                 << "Set state to INACTIVE. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())               << "Set state to INACTIVE. - isNotACTIVE";
  EXPECT_TRUE(te.isINACTIVE())                << "Set state to INACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())                 << "Set state to INACTIVE. - isERASED";

  te.setState(zbe::Ticket::ERASED);
  EXPECT_EQ(zbe::Ticket::ERASED,te.getState()) << "Set state to ERASED. - getState";
  EXPECT_FALSE(te.isACTIVE())               << "Set state to ERASED. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())             << "Set state to ERASED. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ERASED. - isINACTIVE";
  EXPECT_TRUE(te.isERASED())                << "Set state to ERASED. - isERASED";

  te.setState(zbe::Ticket::ACTIVE);
  EXPECT_EQ(zbe::Ticket::ACTIVE,te.getState()) << "Set state to ACTIVE. - getState";
  EXPECT_TRUE(te.isACTIVE())                << "Set state to ACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "Set state to ACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "Set state to ACTIVE. - isERASED";

  te.setACTIVE();
  EXPECT_EQ(zbe::Ticket::ACTIVE,te.getState()) << "SetACTIVE. - getState";
  EXPECT_TRUE(te.isACTIVE())                << "SetACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "SetACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "SetACTIVE. - isERASED";

  te.setINACTIVE();
  EXPECT_EQ(zbe::Ticket::INACTIVE,te.getState()) << "SetINACTIVE. - getState";
  EXPECT_FALSE(te.isACTIVE())                 << "SetINACTIVE. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())               << "SetINACTIVE. - isNotACTIVE";
  EXPECT_TRUE(te.isINACTIVE())                << "SetINACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())                 << "SetINACTIVE. - isERASED";

  te.setERASED();
  EXPECT_EQ(zbe::Ticket::ERASED,te.getState()) << "SetERASED. - getState";
  EXPECT_FALSE(te.isACTIVE())               << "SetERASED. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())             << "SetERASED. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetERASED. - isINACTIVE";
  EXPECT_TRUE(te.isERASED())                << "SetERASED. - isERASED";

  te.setACTIVE();
  EXPECT_EQ(zbe::Ticket::ACTIVE,te.getState()) << "SetACTIVE. - getState";
  EXPECT_TRUE(te.isACTIVE())                << "SetACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "SetACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "SetACTIVE. - isERASED";
}
