#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/behaviors/StateLTEraser.h"

#include "testutils/DummyTicket.h"

#include "ZBE/factories/implementations/behaviors/StateLTEraserBhvFtry.h"

namespace StateLTEraserBhvFtryTest {

TEST(StateLTEraserBhvFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &stateLTEraserRsrc = RsrcStore<StateLTEraser>::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<int64_t> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["limit"] = "StateLTEraserLimit";
  intStore.insert("StateLTEraserLimit", 10);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  StateLTEraserBhvFtry ssbf;
  ssbf.create("StateLTEraserBhvFtryTestName", cfgId);
  ssbf.setup("StateLTEraserBhvFtryTestName", cfgId);


  auto ent = std::make_shared<zbe::Entity>();
  auto ticket1 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(1, ticket1);
  auto ticket2 = std::make_shared<zbetest::DummyTicket>();
  ent->addTicket(2, ticket2);
  std::shared_ptr<zbe::Value<int64_t> > state = std::make_shared<zbe::SimpleValue<int64_t> >(15);

  ent->setInt(1, state);

  std::shared_ptr<zbe::SAvatar<int64_t> > avatar = std::make_shared<zbe::SBaseAvatar<int64_t> >(ent, 1);


  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Behavior.StateLTEraserBhvFtryTestName");
  std::shared_ptr<Behavior<int64_t> > outBhv = behaviorRsrc.get(outId);

  uint64_t ssbId = dict.get("StateLTEraser.StateLTEraserBhvFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Behavior with given name";
  ASSERT_NE(0, ssbId) << "Must create a StateLTEraser with given name";


  EXPECT_TRUE(ticket1->isACTIVE()) << "Initially ticket1 must be active.";
  EXPECT_TRUE(ticket2->isACTIVE()) << "Initially ticket2 must be active.";

  outBhv->apply(avatar);

  EXPECT_TRUE(ticket1->isACTIVE()) << "Still, the ticket1 must be active.";
  EXPECT_TRUE(ticket2->isACTIVE()) << "Still, the ticket2 must be active.";

  state->set(5);
  outBhv->apply(avatar);

  EXPECT_TRUE(ticket1->isERASED()) << "Finaly ticket1 must be erased.";
  EXPECT_TRUE(ticket2->isERASED()) << "Finaly ticket2 must be erased.";

  configRsrc.clear();
  dict.clear();
  stateLTEraserRsrc.clear();
  behaviorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateLTEraserBhvFtryTest
