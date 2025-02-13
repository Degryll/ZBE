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

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"

namespace BehaviorDmnFtryTest {

class DummyBehavior : public zbe::Behavior<uint64_t> {
public:
  void apply(std::shared_ptr<zbe::SAvatar<uint64_t> > avatar) override {
    //void zbe::Behavior<T>::apply(std::shared_ptr<zbe::_Avatar<1, T> >) [with T = zbe::_Avatar<1, long unsigned int>]’|
    avatar->get<1, uint64_t>()->set(1);
  }
};

TEST(BehaviorDmnFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  //auto &listRsrc = RsrcTicketedFAEC<DummyAvatar>::getInstance();
  auto &listRsrc = RsrcStore<TicketedForwardList<SAvatar<uint64_t> > >::getInstance();
  auto &behaviorRsrc = RsrcStore<Behavior<uint64_t> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["behavior"] = "dummyb";
  (*cfg)["list"] = "dummyl";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto db = std::make_shared<DummyBehavior>();
  behaviorRsrc.insert("Behavior.dummyb"s, db);

  auto list = std::make_shared<TicketedForwardList<SAvatar<uint64_t> > >();

  std::shared_ptr<zbe::Entity> ent1 = std::make_shared<zbe::Entity>();
  std::shared_ptr<zbe::Value<uint64_t> > state1 = std::make_shared<zbe::SimpleValue<uint64_t> >(15);

  ent1->setUint(1, state1);

  std::shared_ptr<zbe::Entity> ent2 = std::make_shared<zbe::Entity>();
  std::shared_ptr<zbe::Value<uint64_t> > state2 = std::make_shared<zbe::SimpleValue<uint64_t> >(25);

  ent2->setUint(1, state2);

  std::shared_ptr<zbe::SAvatar<uint64_t> > avatar1 = std::make_shared<zbe::SBaseAvatar<uint64_t> >(ent1, 1);
  std::shared_ptr<zbe::SAvatar<uint64_t> > avatar2 = std::make_shared<zbe::SBaseAvatar<uint64_t> >(ent2, 1);

  list->push_front(avatar1);
  list->push_front(avatar2);

  listRsrc.insert("List.dummyl"s, list);

  BehaviorDmnFtry<TicketedForwardList<SAvatar<uint64_t> >, uint64_t> bdf;
  bdf.create("BehaviorDmnFtryTestName", cfgId);
  bdf.setup("BehaviorDmnFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Daemon.BehaviorDmnFtryTestName");
  std::shared_ptr<zbe::Daemon> outDmn = daemonRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  EXPECT_EQ(15, state1->get()) << "First value is initially 15.";
  EXPECT_EQ(25, state2->get()) << "Second value is initially 25.";

  outDmn->run();

  EXPECT_EQ(1, state1->get()) << "Behavior must modfy value to 1.";
  EXPECT_EQ(1, state2->get()) << "Behavior must modfy value to 1.";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  listRsrc.clear();
  behaviorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace BehaviorDmnFtryTest
