#include "gtest/gtest.h"

#include <string>
#include <cstdint>
#include <vector>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"


#include "ZBE/factories/implementations/entities/avatars/BaseAvatarFtry.h"

namespace BaseAvatarFtryTest {

TEST(BaseAvatarFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;

  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();

  auto& baseAvatarStoreD = RsrcStore<SBaseAvatar<double> >::getInstance();
  auto& baseAvatarStoreDUU = RsrcStore<MBaseAvatar<double, uint64_t, uint64_t> >::getInstance();

  using TFLD = TicketedForwardList<zbe::SAvatar<double> >;
  using TFLDUU = TicketedForwardList<zbe::MAvatar<double, uint64_t, uint64_t> >;

  auto& listStoreD = RsrcStore<TFLD>::getInstance();
  auto& listStoreDUU = RsrcStore<TFLDUU>::getInstance();

  auto& configRsrc = RsrcStore<json>::getInstance();

  auto listD1 = std::make_shared<TFLD>();
  auto listD2 = std::make_shared<TFLD>();
  auto listDUU1 = std::make_shared<TFLDUU>();
  auto listDUU2 = std::make_shared<TFLDUU>();

  listStoreD.insert("List.testlistd1", listD1);
  listStoreD.insert("List.testlistd2", listD2);

  listStoreDUU.insert("List.testlistDUU1", listDUU1);
  listStoreDUU.insert("List.testlistDUU2", listDUU2);

  EXPECT_TRUE(listD1->empty()) << "Initialy must be no elements in list testlistd1";
  EXPECT_TRUE(listD2->empty()) << "Initialy must be no elements in list testlistd2";
  EXPECT_TRUE(listDUU1->empty()) << "Initialy must be no elements in list testlistDUU1";
  EXPECT_TRUE(listDUU2->empty()) << "Initialy must be no elements in list testlistDUU1";

  dict.insert("Attribs.D1",0);
  dict.insert("Attribs.D2",1);
  dict.insert("Attribs.U1",0);
  dict.insert("Attribs.U2",1);
  dict.insert("Attribs.I1",0);
  dict.insert("Attribs.I2",1);

  dict.insert("Tickets.A",0);
  dict.insert("Tickets.B",1);
  dict.insert("Tickets.C",2);
  dict.insert("Tickets.D",3);

  RsrcStore<Entity>& entStore = RsrcStore<Entity>::getInstance();

  std::shared_ptr<zbe::Entity> e = std::make_shared<zbe::Entity>();

  entStore.insert("Entity.testEnt", e);

  std::shared_ptr<zbe::Value<double> >  vald1 = std::make_shared<zbe::SimpleValue<double> >(0.0);
  std::shared_ptr<zbe::Value<double> >  vald2 = std::make_shared<zbe::SimpleValue<double> >(1.0);
  std::shared_ptr<zbe::Value<uint64_t> >  valu1 = std::make_shared<zbe::SimpleValue<uint64_t> >(42);
  std::shared_ptr<zbe::Value<uint64_t> >  valu2 = std::make_shared<zbe::SimpleValue<uint64_t> >(37);
  std::shared_ptr<zbe::Value<int64_t> >  vali1 = std::make_shared<zbe::SimpleValue<int64_t> >(-1);
  std::shared_ptr<zbe::Value<int64_t> >  vali2 = std::make_shared<zbe::SimpleValue<int64_t> >(3);

  e->setDouble(dict.get("Attribs.D1"), vald1);
  e->setDouble(dict.get("Attribs.D2"), vald2);

  e->setUint(dict.get("Attribs.U1"), valu1);
  e->setUint(dict.get("Attribs.U2"), valu2);

  e->setInt(dict.get("Attribs.I1"), vali1);
  e->setInt(dict.get("Attribs.I2"), vali2);

  EXPECT_DOUBLE_EQ(0.0,  e->getDouble(0)->get()) << "First double value is 0.0.";
  EXPECT_DOUBLE_EQ(1.0,  e->getDouble(1)->get()) << "Second double value is 1.0";
  EXPECT_EQ(42, e->getUint(0)->get()) << "First uint value is 42.";
  EXPECT_EQ(37, e->getUint(1)->get()) << "Second uint value is 37";
  EXPECT_EQ(-1, e->getInt(0)->get()) << "First int value is -1.";
  EXPECT_EQ(3, e->getInt(1)->get()) << "Second int value is 3";

  std::string jsonStrD = "{\"entity\": \"testEnt\","s+
    "\"attribIndexes\": [\"Attribs.D1\"],"s+
    "\"lists\" : {\"testlistd1\":\"Tickets.A\",\"testlistd2\":\"Tickets.B\"}"s+
  "}"s;

  json jD = json::parse(jsonStrD);

  std::string jsonStrDUU = "{\"entity\": \"testEnt\","s+
    "\"attribIndexes\": [\"Attribs.D1\",\"Attribs.U1\",\"Attribs.U2\"],"s+
    "\"lists\" : {\"testlistDUU1\":\"Tickets.C\",\"testlistDUU2\":\"Tickets.D\"}"s+
  "}"s;

  json jDUU = json::parse(jsonStrDUU);

  uint64_t cfgIdD = configRsrc.insert(std::make_shared<json>(jD));
  uint64_t cfgIdDUU = configRsrc.insert(std::make_shared<json>(jDUU));

  BaseAvatarFtry<double> bafD;
  BaseAvatarFtry<double, uint64_t, uint64_t> bafDUU;

  bafD.create("BaseAvatarFtryTestAVTD", cfgIdD);
  bafD.setup("BaseAvatarFtryTestAVTD", cfgIdD);

  bafDUU.create("BaseAvatarFtryTestAVTDUU", cfgIdDUU);
  bafDUU.setup("BaseAvatarFtryTestAVTDUU", cfgIdDUU);

  std::shared_ptr<zbe::SBaseAvatar<double> > ba1 = std::make_shared<zbe::SBaseAvatar<double> >();
  ba1->setupEntity(e, 1);

  auto d1 = ba1->get<1, double>();
  d1->set(0.1);

  EXPECT_DOUBLE_EQ(0.1,  e->getDouble(1)->get()) << "Second double value now is 0.1.";
  std::shared_ptr<zbe::MBaseAvatar<double, uint64_t, uint64_t> > ba3 = std::make_shared<zbe::MBaseAvatar<double, uint64_t, uint64_t> >();
  ba3->setupEntity(e, std::array<uint64_t, 3>({1, 1, 0}));


  auto d3 = ba3->get<3, double>();
  d3->set(4.2);
  auto u1 = ba3->get<2, uint64_t>();
  u1->set(73);
  auto u0 = ba3->get<1, uint64_t>();
  u0->set(24);

  EXPECT_DOUBLE_EQ(4.2,  e->getDouble(1)->get()) << "Second double value now is 4.2.";
  EXPECT_EQ(24, e->getUint(0)->get()) << "First uint value now is 24.";
  EXPECT_EQ(73, e->getUint(1)->get()) << "Second uint value now is 73";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Must be no errors but:" + zbe::SysError::getFirstErrorString();

  baseAvatarStoreD.get("BaseAvatar.BaseAvatarFtryTestAVTD");
  baseAvatarStoreDUU.get("BaseAvatar.BaseAvatarFtryTestAVTDUU");

  EXPECT_FALSE(listD1->empty()) << "Must be elements in list testlistd1";
  EXPECT_FALSE(listD2->empty()) << "Must be elements in list testlistd2";
  EXPECT_FALSE(listDUU1->empty()) << "Must be elements in list testlistDUU1";
  EXPECT_FALSE(listDUU2->empty()) << "Must be elements in list testlistDUU1";

  // Must generate two errors: Tow for dictionary and two for the RsrcStores
  EXPECT_EQ(4,zbe::SysError::getNErrors()) << "Must be no leftovers. Just 4 errors";

  zbe::SysError::clear();

}
}  // namespace SimpleAnimatedSpriteFtryTest
