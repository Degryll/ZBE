#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "testutils/DummyTicket.h"

#include "ZBE/behaviors/Erase.h"

namespace EraseTest {

TEST(Erase, apply) {

  auto ent = std::make_shared<zbe::Entity>();
  auto ticket1 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(1, ticket1);
  auto ticket2 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(2, ticket2);
  std::shared_ptr<zbe::Avatar> avatar = std::make_shared<zbe::BaseAvatar>(ent);

  zbe::Erase eraser;

  EXPECT_TRUE(ticket1->isACTIVE()) << "Initially ticket1 must be active.";
  EXPECT_TRUE(ticket2->isACTIVE()) << "Initially ticket2 must be active.";

  eraser.apply(avatar);

  EXPECT_TRUE(ticket1->isERASED()) << "Finaly ticket1 must be erased.";
  EXPECT_TRUE(ticket2->isERASED()) << "Finaly ticket2 must be erased.";
}

}  // namespace EraseTest
