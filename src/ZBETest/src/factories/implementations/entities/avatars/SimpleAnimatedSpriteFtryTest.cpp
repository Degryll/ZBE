// #include "gtest/gtest.h"
//
// #include <string>
// #include <cstdint>
// #include <vector>
//
// #include "ZBE/core/tools/containers/RsrcDictionary.h"
// #include "ZBE/core/tools/containers/TicketedForwardList.h"
//
// #include "ZBE/core/tools/shared/Value.h"
// #include "ZBE/core/tools/shared/implementations/SimpleValue.h"
//
// #include "ZBE/core/entities/avatars/Avatar.h"
// #include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
// #include "ZBE/core/entities/Entity.h"
//
// #include "testutils/MockedContextTime.h"
//
// #include "ZBE/factories/implementations/entities/avatars/SimpleAnimSprtFtry.h"
//
// namespace SimpleAnimatedSpriteFtryTest {
//
// const char LIST_NAMESPACE[] = "Tedefresas";
//
// TEST(SimpleAnimatedSpriteFtry, Create) {
//   EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
//
//   using namespace zbe;
//   using namespace nlohmann;
//   using namespace std::string_literals;
//
//   using TFLA = TicketedForwardList<AvatarEntityContainer<AnimatedSprite> >;
//
//   auto& dict = NameRsrcDictionary::getInstance();
//   auto& configRsrc = RsrcStore<json>::getInstance();
//   auto& sasPtrStore = RsrcStore<SimpleAnimatedSprite*>::getInstance();
//   auto& intStore = RsrcDictionary<int64_t>::getInstance();
//   auto& uintStore = RsrcDictionary<uint64_t>::getInstance();
//   auto& ticketStore = RsrcStore<Ticket>::getInstance();
//   auto& doubleStore = RsrcDictionary<double>::getInstance();
//   auto& listStore = RsrcStore<TFLAECAS>::getInstance();
//   auto& timeRsrc = RsrcStore<ContextTime>::getInstance();
//
//   auto list = std::make_shared<TFLAECAS>();
//   listStore.insert("Tedefresas.sasftrytest.list",list);
//
//   std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
//
//   contextTime->setFixedTime(2);
//   contextTime->update();
//
//   timeRsrc.insert("ContextTime.sasftrytest.cTime", contextTime);
//
//   auto cfg = std::make_shared<json>();
//   (*cfg)["lists"] = {"sasftrytest.list"};
//   (*cfg)["contexttime"] = "sasftrytest.cTime";
//   (*cfg)["time"] = "sasftrytest.time";
//   (*cfg)["state"] = "sasftrytest.state";
//   (*cfg)["degrees"] = "sasftrytest.degrees";
//   (*cfg)["x"] = "sasftrytest.x";
//   (*cfg)["y"] = "sasftrytest.y";
//   (*cfg)["w"] = "sasftrytest.w";
//   (*cfg)["h"] = "sasftrytest.h";
//   (*cfg)["graphics"] = "sasftrytest.graphics";
//
//   intStore.insert("sasftrytest.time", 1);
//   intStore.insert("sasftrytest.state", 2);
//   doubleStore.insert("sasftrytest.degrees", 15.0);
//   intStore.insert("sasftrytest.x", 10);
//   intStore.insert("sasftrytest.y", 20);
//   intStore.insert("sasftrytest.w", 30);
//   intStore.insert("sasftrytest.h", 40);
//   uintStore.insert("sasftrytest.graphics", 5);
//
//   uint64_t cfgId = configRsrc.insert(cfg);
//
//   SimpleAnimSprtFtry<TFLAECAS, LIST_NAMESPACE> sasFtry;
//
//   sasFtry.create("SimpleAnimatedSpriteFtryTestName", cfgId);
//
//   uint64_t outId = dict.get("SimpleAnimatedSpritePtr.SimpleAnimatedSpriteFtryTestName");
//   ASSERT_NE(0, outId) << "Must create an entity with given name";
//
//   auto createdEntity = sasPtrStore.get(outId);
//   EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no stored errors 1.";
//
//   sasFtry.setup("SimpleAnimatedSpriteFtryTestName", cfgId);
//
//   auto setupEntity = sasPtrStore.get(outId);
//   EXPECT_EQ(1, zbe::SysError::getNErrors()) << "After setup, there is no entity in the store.";
//   zbe::SysError::clear();
//
//   EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no errors.";
//
//   auto it = list->begin();
//   AnimatedSprite* outEntity;
//   assignAvatar(*it, &outEntity);
//   //auto outEntity = *it;
//
//   EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no stored errors 2.";
//
//   EXPECT_EQ(1, outEntity->getTime()) << "Must load correct time.";
//   EXPECT_EQ(2, outEntity->getState()) << "Must load correct state.";
//   EXPECT_EQ(15.0, outEntity->getDegrees()) << "Must load correct degrees.";
//   EXPECT_EQ(10, outEntity->getX()) << "Must load correct x.";
//   EXPECT_EQ(20, outEntity->getY()) << "Must load correct y.";
//   EXPECT_EQ(30, outEntity->getW()) << "Must load correct w.";
//   EXPECT_EQ(40, outEntity->getH()) << "Must load correct h.";
//   EXPECT_EQ(5, outEntity->getGraphics()) << "Must load correct .";
//   EXPECT_EQ(++it, list->end()) << "Must be the only element";
//
//   dict.clear();
//   configRsrc.clear();
//   sasPtrStore.clear();
//   intStore.clear();
//   ticketStore.clear();
//   doubleStore.clear();
//   listStore.clear();
//
//   zbe::SysError::clear();
// }
// }  // namespace SimpleAnimatedSpriteFtryTest
