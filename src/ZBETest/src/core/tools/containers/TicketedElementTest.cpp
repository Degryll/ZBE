#include "gtest/gtest.h"

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/TicketedElement.h"

namespace TicketedElementTest {

TEST(Ticket, Usage) {
  zbe::TicketedElement<int> te(std::make_shared<int>(42));
  EXPECT_TRUE(te.isACTIVE()) << "Create TicketedElement, ACTIVE by default. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE()) << "Create TicketedElement, ACTIVE by default. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE()) << "Create TicketedElement, ACTIVE by default. - isINACTIVE";
  EXPECT_FALSE(te.isERASED()) << "Create TicketedElement, ACTIVE by default. - isERASED";

  te.setACTIVE();
  EXPECT_TRUE(te.isACTIVE())                << "Set state to ACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "Set state to ACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "Set state to ACTIVE. - isERASED";

  te.setINACTIVE();
  EXPECT_FALSE(te.isACTIVE())                 << "Set state to INACTIVE. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())               << "Set state to INACTIVE. - isNotACTIVE";
  EXPECT_TRUE(te.isINACTIVE())                << "Set state to INACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())                 << "Set state to INACTIVE. - isERASED";

  te.setERASED();
  EXPECT_FALSE(te.isACTIVE())               << "Set state to ERASED. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())             << "Set state to ERASED. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ERASED. - isINACTIVE";
  EXPECT_TRUE(te.isERASED())                << "Set state to ERASED. - isERASED";

  te.setACTIVE();
  EXPECT_TRUE(te.isACTIVE())                << "Set state to ACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "Set state to ACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "Set state to ACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "Set state to ACTIVE. - isERASED";

  te.setACTIVE();
  EXPECT_TRUE(te.isACTIVE())                << "SetACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "SetACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "SetACTIVE. - isERASED";

  te.setINACTIVE();
  EXPECT_FALSE(te.isACTIVE())                 << "SetINACTIVE. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())               << "SetINACTIVE. - isNotACTIVE";
  EXPECT_TRUE(te.isINACTIVE())                << "SetINACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())                 << "SetINACTIVE. - isERASED";

  te.setERASED();
  EXPECT_FALSE(te.isACTIVE())               << "SetERASED. - isACTIVE";
  EXPECT_TRUE(te.isNotACTIVE())             << "SetERASED. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetERASED. - isINACTIVE";
  EXPECT_TRUE(te.isERASED())                << "SetERASED. - isERASED";

  te.setACTIVE();
  EXPECT_TRUE(te.isACTIVE())                << "SetACTIVE. - isACTIVE";
  EXPECT_FALSE(te.isNotACTIVE())            << "SetACTIVE. - isNotACTIVE";
  EXPECT_FALSE(te.isINACTIVE())             << "SetACTIVE. - isINACTIVE";
  EXPECT_FALSE(te.isERASED())               << "SetACTIVE. - isERASED";
}

}  // namespace TicketedElementTest
