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

#include "ZBE/behaviors/StateSetter.h"

#include "ZBE/factories/implementations/behaviors/StateSetterBhvFtry.h"

namespace StateSetterBhvFtryTest {

TEST(StateSetterBhvFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &stateSetterRsrc = RsrcStore<StateSetter>::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<int64_t> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["state"] = "StateSetterState";
  intStore.insert("StateSetterState", 42);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  StateSetterBhvFtry ssbf;
  ssbf.create("StateSetterBhvFtryTestName", cfgId);
  ssbf.setup("StateSetterBhvFtryTestName", cfgId);

  std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();
  std::shared_ptr<zbe::Value<int64_t> > state = std::make_shared<zbe::SimpleValue<int64_t> >(15);

  ent->setInt(1, state);

  std::shared_ptr<zbe::SAvatar<int64_t> > avatar = std::make_shared<zbe::SBaseAvatar<int64_t> >(ent, 1);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Behavior.StateSetterBhvFtryTestName");
  std::shared_ptr<Behavior<int64_t> > outBhv = behaviorRsrc.get(outId);

  uint64_t ssbId = dict.get("StateSetter.StateSetterBhvFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Behavior with given name";
  ASSERT_NE(0, ssbId) << "Must create a StateSetter with given name";

  EXPECT_EQ(15, state->get()) << "Initially state.";

  outBhv->apply(avatar);

  EXPECT_EQ(42, state->get()) << "After apply the behavior, the state has changed.";

  configRsrc.clear();
  dict.clear();
  stateSetterRsrc.clear();
  behaviorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateSetterBhvFtryTest
