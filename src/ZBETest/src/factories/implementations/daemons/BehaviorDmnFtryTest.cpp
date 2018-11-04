#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"

namespace BehaviorDmnFtryTest {

struct DummyAvatar {
  using Base = void;
  int val = 0;
};

class DummyBehavior : public zbe::Behavior<DummyAvatar> {
public:
  void apply(std::shared_ptr<zbe::AvatarEntityContainer<DummyAvatar> > aec) {
    DummyAvatar* da;
    assignAvatar(aec, &da);
    //aec->get()->setAvatar(&da);
    da->val = 1;
  }
};

TEST(StateMachineDmnFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &listRsrc = RsrcTicketedFAEC<DummyAvatar>::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<DummyAvatar> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["behavior"] = "dummyb";
  (*cfg)["list"] = "dummyl";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto db = std::make_shared<DummyBehavior>();

  uint64_t dbId = SysIdGenerator::getId();
  behaviorRsrc.insert(dbId, db);
  dict.insert("Behavior.dummyb"s, dbId);

  auto list = std::make_shared<TicketedFAEC<DummyAvatar> >();

  DummyAvatar* da1 = new DummyAvatar();
  DummyAvatar* da2 = new DummyAvatar();
  DummyAvatar* da3 = new DummyAvatar();

  auto aeFixed1 = std::make_shared<AvatarEntityFixed<DummyAvatar> >(da1);
  auto aeContainer1 = std::make_shared<AvatarEntityContainer<DummyAvatar> >(aeFixed1);

  auto aeFixed2 = std::make_shared<AvatarEntityFixed<DummyAvatar> >(da2);
  auto aeContainer2 = std::make_shared<AvatarEntityContainer<DummyAvatar> >(aeFixed2);

  // auto aeFixed3 = std::make_shared<AvatarEntityFixed<DummyAvatar> >(da3)
  // auto aeContainer3 = std::make_shared<AvatarEntityContainer<DummyAvatar> >(aeFixed3)

  list->push_front(aeContainer1);
  list->push_front(aeContainer2);

  uint64_t listId = SysIdGenerator::getId();
  listRsrc.insert(listId, list);
  dict.insert("List.dummyl"s, listId);

  BehaviorDmnFtry<TicketedFAEC<DummyAvatar>, DummyAvatar> bdf;
  bdf.create("BehaviorDmnFtryTestName", cfgId);
  bdf.setup("BehaviorDmnFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Daemon.BehaviorDmnFtryTestName");
  std::shared_ptr<zbe::Daemon> outDmn = daemonRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  EXPECT_EQ(0, da1->val) << "da1 val is initially 0.";
  EXPECT_EQ(0, da2->val) << "da2 val is initially 0.";
  EXPECT_EQ(0, da3->val) << "da3 val is initially 0.";

  outDmn->run();

  EXPECT_EQ(1, da1->val) << "Behavior must modfy da1";
  EXPECT_EQ(1, da2->val) << "Behavior must modfy da2";
  EXPECT_EQ(0, da3->val) << "Behavior must NOT modfy da3";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  listRsrc.clear();
  behaviorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
