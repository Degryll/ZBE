#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/behaviors/StateSetter.h"

#include "ZBE/factories/implementations/behaviors/StateSetterBhvFtry.h"

namespace StateSetterBhvFtryTest {

TEST(StateSetterBhvFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &stateSetterRsrc = RsrcStore<StateSetter>::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<Stated> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["behavior"] = "dummyss";
  (*cfg)["limit"] = 42;

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  StateSetterBhvFtry ssbf;
  ssbf.create("StateSetterBhvFtryTestName", cfgId);
  ssbf.setup("StateSetterBhvFtryTestName", cfgId);

  auto *ss = new zbe::SimpleState(15);
  auto *bs = new zbe::BaseStated(ss);
  auto aefs = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(bs);
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated> > aec  = std::make_shared<zbe::AvatarEntityContainer<zbe::Stated> >(aefs);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Behavior.StateSetterBhvFtryTestName");
  std::shared_ptr<Behavior<Stated> > outBhv = behaviorRsrc.get(outId);

  uint64_t ssbId = dict.get("StateSetter.StateSetterBhvFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Behavior with given name";
  ASSERT_NE(0, ssbId) << "Must create a StateSetter with given name";

  EXPECT_EQ(15, ss->getState()) << "Initially state.";

  outBhv->apply(aec);

  EXPECT_EQ(42, ss->getState()) << "After apply the behavior, the state has changed.";

  configRsrc.clear();
  dict.clear();
  stateSetterRsrc.clear();
  behaviorRsrc.clear();

  delete ss;
  delete bs;


  zbe::SysError::clear();
}

}  // namespace StateSetterBhvFtryTest
