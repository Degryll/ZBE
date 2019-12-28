#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/behaviors/StateLTEraser.h"

#include "ZBE/factories/implementations/behaviors/StateLTEraserBhvFtry.h"

namespace StateLTEraserBhvFtryTest {

class EntityMock : public zbe::Entity {
public:
  EntityMock(bool& check) : check(check) {}

  void setERASED() {
    check = true;
    Entity::setERASED();
  }
  bool& check;
};

TEST(StateLTEraserBhvFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &stateLTEraserRsrc = RsrcStore<StateLTEraser>::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<Avatar, Stated> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["limit"] = "StateLTEraserLimit";
  intStore.insert("StateLTEraserLimit", 10);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  StateLTEraserBhvFtry ssbf;
  ssbf.create("StateLTEraserBhvFtryTestName", cfgId);
  ssbf.setup("StateLTEraserBhvFtryTestName", cfgId);

  bool check = false;
//  auto *e = new EntityMock(check);
  std::shared_ptr<EntityMock> e = std::make_shared<EntityMock>(check);
  auto *ba = new zbe::BaseAvatar(e);
  auto *ss = new zbe::SimpleState(15);
  auto *bs = new zbe::BaseStated(ss);
  auto aefa = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ba);
  auto aefs = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(bs);
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar, zbe::Stated> > aec  = std::make_shared<zbe::AvatarEntityContainer<zbe::Avatar, zbe::Stated> >(aefa, aefs);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Behavior.StateLTEraserBhvFtryTestName");
  std::shared_ptr<Behavior<Avatar, Stated> > outBhv = behaviorRsrc.get(outId);

  uint64_t ssbId = dict.get("StateLTEraser.StateLTEraserBhvFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Behavior with given name";
  ASSERT_NE(0, ssbId) << "Must create a StateLTEraser with given name";

  EXPECT_FALSE(check) << "Initially setERASED is not called.";

  outBhv->apply(aec);

  EXPECT_FALSE(check) << "setERASED should'n be called.";

  ss->setState(5);
  outBhv->apply(aec);

  EXPECT_TRUE(check) << "setERASED should be called.";

  configRsrc.clear();
  dict.clear();
  stateLTEraserRsrc.clear();
  behaviorRsrc.clear();

//  delete e;
  //delete ba;  // AvatarEntityFixed deletes it
  delete ss;
  //delete bs;  // AvatarEntityFixed deletes it

  zbe::SysError::clear();
}

}  // namespace StateLTEraserBhvFtryTest
