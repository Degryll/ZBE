#include "gtest/gtest.h"

#include <string>
#include <cstdint>
#include <vector>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "testutils/MockedContextTime.h"

#include "ZBE/factories/implementations/entities/avatars/SimpleAnimSprtFtry.h"

namespace SimpleAnimatedSpriteFtryTest {

const char LIST_NAMESPACE[] = "Tedefresas";

TEST(SimpleAnimatedSpriteFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;

  using TFSAS = TicketedForwardList<SimpleAnimatedSprite>;

  auto& dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& sasStore = RsrcStore<SimpleAnimatedSprite>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto& ticketStore = RsrcStore<Ticket>::getInstance();
  auto& doubleStore = RsrcDictionary<double>::getInstance();
  auto& listStore = RsrcStore<TFSAS>::getInstance();
  auto& timeRsrc = RsrcStore<ContextTime>::getInstance();

  auto list = std::make_shared<TFSAS>();
  listStore.insert("Tedefresas.sasftrytest.list",list);

  std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();

  timeRsrc.insert("ContextTime.sasftrytest.cTime", contextTime);

  auto cfg = std::make_shared<json>();
  (*cfg)["list"] = "sasftrytest.list";
  (*cfg)["contexttime"] = "sasftrytest.cTime";
  (*cfg)["time"] = "sasftrytest.time";
  (*cfg)["state"] = "sasftrytest.state";
  (*cfg)["degrees"] = "sasftrytest.degrees";
  (*cfg)["x"] = "sasftrytest.x";
  (*cfg)["y"] = "sasftrytest.y";
  (*cfg)["w"] = "sasftrytest.w";
  (*cfg)["h"] = "sasftrytest.h";
  (*cfg)["graphics"] = "sasftrytest.graphics";

  intStore.insert("sasftrytest.time", 1);
  intStore.insert("sasftrytest.state", 2);
  doubleStore.insert("sasftrytest.degrees", 15.0);
  intStore.insert("sasftrytest.x", 10);
  intStore.insert("sasftrytest.y", 20);
  intStore.insert("sasftrytest.w", 30);
  intStore.insert("sasftrytest.h", 40);
  intStore.insert("sasftrytest.graphics", 5);

  uint64_t cfgId = configRsrc.insert(cfg);

  SimpleAnimSprtFtry<TFSAS, LIST_NAMESPACE> sasFtry;
  sasFtry.create("SimpleAnimatedSpriteFtryTestName", cfgId);
  sasFtry.setup("SimpleAnimatedSpriteFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("SimpleAnimatedSprite.SimpleAnimatedSpriteFtryTestName");

  ASSERT_NE(0, outId) << "Must create an entity with given name";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors 1.";

  auto outEntity = sasStore.get(outId);
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors 2.";

  EXPECT_EQ(1, outEntity->getTime()) << "Must load correct time.";
  EXPECT_EQ(2, outEntity->getState()) << "Must load correct state.";
  EXPECT_EQ(15.0, outEntity->getDegrees()) << "Must load correct degrees.";
  EXPECT_EQ(10, outEntity->getX()) << "Must load correct x.";
  EXPECT_EQ(20, outEntity->getY()) << "Must load correct y.";
  EXPECT_EQ(30, outEntity->getW()) << "Must load correct w.";
  EXPECT_EQ(40, outEntity->getH()) << "Must load correct h.";
  EXPECT_EQ(5, outEntity->getGraphics()) << "Must load correct .";

  dict.clear();
  configRsrc.clear();
  sasStore.clear();
  intStore.clear();
  ticketStore.clear();
  doubleStore.clear();
  listStore.clear();

  zbe::SysError::clear();
}
}  // namespace SimpleAnimatedSpriteFtryTest
