#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "testutils/DummyTicket.h"

#include "ZBE/behaviors/StateLTEraser.h"

namespace StateLTEraserTest {

TEST(StateLTEraser, apply) {

  auto ent = std::make_shared<zbe::Entity>();
  auto ticket1 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(1, ticket1);
  auto ticket2 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(2, ticket2);
  std::shared_ptr<zbe::Value<int64_t> > state = std::make_shared<zbe::SimpleValue<int64_t> >(15);

  ent->setInt(1, state);

  std::shared_ptr<zbe::SAvatar<int64_t> > avatar = std::make_shared<zbe::SBaseAvatar<int64_t> >(ent, 1);


  zbe::StateLTEraser slteraser(10);

  EXPECT_TRUE(ticket1->isACTIVE()) << "Initially ticket1 must be active.";
  EXPECT_TRUE(ticket2->isACTIVE()) << "Initially ticket2 must be active.";

  slteraser.apply(avatar);

  EXPECT_TRUE(ticket1->isACTIVE()) << "Still, the ticket1 must be active.";
  EXPECT_TRUE(ticket2->isACTIVE()) << "Still, the ticket2 must be active.";

  state->set(5);
  slteraser.apply(avatar);

  EXPECT_TRUE(ticket1->isERASED()) << "Finaly ticket1 must be erased.";
  EXPECT_TRUE(ticket2->isERASED()) << "Finaly ticket2 must be erased.";
}

}  // namespace StateLTEraserTest
