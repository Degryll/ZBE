#include "gtest/gtest.h"

#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <fstream>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/factories/implementations/entities/EntityFtry.h"

#include "ZBE/core/entities/Entity.h"

namespace EntityFtryTest {
TEST (EntityFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;

  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();

  auto &entityRsrc = RsrcStore<Entity>::getInstance();
  auto &valueDRsrc = RsrcStore<Value<double> >::getInstance();
  auto &valueFRsrc = RsrcStore<Value<float> >::getInstance();
  auto &valueURsrc = RsrcStore<Value<uint64_t> >::getInstance();
  auto &valueBRsrc = RsrcStore<Value<bool> >::getInstance();
  auto &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  auto &valueV2Rsrc = RsrcStore<Value<Vector2D> >::getInstance();
  auto &valueV3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
  auto &valueSRsrc = RsrcStore<Value<std::string> >::getInstance();
  auto &valueVSRsrc = RsrcStore<Value<std::vector<std::string> > >::getInstance();

  //auto &intStore = RsrcDictionary<int64_t>::getInstance();
  //auto &uintStore = RsrcDictionary<uint64_t>::getInstance();
  auto &doubleStore = RsrcDictionary<double>::getInstance();
  //auto &floatStore = RsrcDictionary<float>::getInstance();
  //auto &boolStore = RsrcDictionary<bool>::getInstance();
  auto &stringStore = RsrcDictionary<std::string>::getInstance();

  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();

  valueDRsrc.insert("nameOfDouble1", std::make_shared<SimpleValue<double> >(SimpleValue<double>(1.2345)));
  valueFRsrc.insert("nameOfFloat1", std::make_shared<SimpleValue<float> >(SimpleValue<float>(2.3456f)));
  valueURsrc.insert("nameOfUint1", std::make_shared<SimpleValue<uint64_t> >(SimpleValue<uint64_t>(45678)));
  valueIRsrc.insert("nameOfInt1", std::make_shared<SimpleValue<int64_t> >(SimpleValue<int64_t>(-56789)));
  valueBRsrc.insert("nameOfBool1", std::make_shared<SimpleValue<bool> >(SimpleValue<bool>(true)));
  valueV2Rsrc.insert("nameOfV2D1", std::make_shared<SimpleValue<Vector2D> >(SimpleValue<Vector2D>(Vector2D({6.0, 789.0}))));
  valueV3Rsrc.insert("nameOfV3D1", std::make_shared<SimpleValue<Vector3D> >(SimpleValue<Vector3D>(Vector3D({6.0, 789.0, 0.123}))));
  valueSRsrc.insert("nameOfString1", std::make_shared<SimpleValue<std::string> >(SimpleValue<std::string>("This is another string")));
  valueVSRsrc.insert("nameOfVString1", std::make_shared<SimpleValue<std::vector<std::string> > >(SimpleValue<std::vector<std::string> >(std::vector<std::string>{"The first string for vector", "The second"})));

  doubleStore.insert("literalOfDouble3", 3.4567);
  doubleStore.insert("nameOfDouble2", 1.23456);
  doubleStore.insert("nameOfDouble3", 1.234567);
  stringStore.insert("nameOfString2", "This is a third string");

  dict.insert("double1", 1);
  dict.insert("double2", 2);
  dict.insert("double3", 19);
  dict.insert("float1", 3);
  dict.insert("float2", 4);
  dict.insert("uint1", 5);
  dict.insert("uint2", 6);
  dict.insert("int1", 7);
  dict.insert("int2", 8);
  dict.insert("bool1", 9);
  dict.insert("bool2", 10);
  dict.insert("V2D1", 11);
  dict.insert("V2D2", 12);
  dict.insert("V3D1", 13);
  dict.insert("V3D2", 14);
  dict.insert("string1", 15);
  dict.insert("string2", 16);
  dict.insert("VString1", 17);
  dict.insert("VString2", 18);

  std::ifstream ifs("data/test/json/EntityFtryTest.json");
  json appCfg;
  ifs >> appCfg;
  uint64_t cfgId = configRsrc.insert(std::make_shared<json>(appCfg));

  zbe::EntityFtry ef;
  ef.create("DummyEntity", cfgId);
  ef.setup("DummyEntity", cfgId);

  uint64_t eId = dict.get("Entity.DummyEntity");
  ASSERT_NE(0, eId) << "Must create an Entity with given name";

  auto e = entityRsrc.get(eId);

  EXPECT_EQ(1.2345,e->getDouble(1)->get()) << "First double loaded";
  EXPECT_EQ(0.987654321,e->getDouble(2)->get()) << "Second double loaded";
  EXPECT_EQ(3.4567,e->getDouble(19)->get()) << "third double loaded";

  EXPECT_EQ(2.3456f,e->getFloat(3)->get()) << "First float loaded";
  EXPECT_EQ(0.987654321f,e->getFloat(4)->get()) << "Second float loaded";

  EXPECT_EQ(45678,e->getUint(5)->get()) << "First uint loaded";
  EXPECT_EQ(987654321,e->getUint(6)->get()) << "Second uint loaded";

  EXPECT_EQ(-56789,e->getInt(7)->get()) << "First int loaded";
  EXPECT_EQ(-987654321,e->getInt(8)->get()) << "Second int loaded";

  EXPECT_TRUE(e->getBool(9)->get()) << "First bool loaded";
  EXPECT_FALSE(e->getBool(10)->get()) << "Second bool loaded";

  EXPECT_EQ(6, e->getVector2D(11)->get()[0]) << "First value of first V2d loaded";
  EXPECT_EQ(789, e->getVector2D(11)->get()[1]) << "Second value of first V2d loaded";
  EXPECT_EQ(1.234567, e->getVector2D(12)->get()[0]) << "First value of second V2d loaded";
  EXPECT_EQ(1.23456, e->getVector2D(12)->get()[1]) << "Second value of second V2d loaded";

  EXPECT_EQ(6, e->getVector3D(13)->get()[0]) << "First value of first V3d loaded";
  EXPECT_EQ(789, e->getVector3D(13)->get()[1]) << "Second value of first V3d loaded";
  EXPECT_EQ(0.123, e->getVector3D(13)->get()[2]) << "Third value of first V3d loaded";
  EXPECT_EQ(1.234567, e->getVector3D(14)->get()[0]) << "First value of second V3d loaded";
  EXPECT_EQ(1.234567, e->getVector3D(14)->get()[1]) << "Second value of second V3d loaded";
  EXPECT_EQ(-7.1, e->getVector3D(14)->get()[2]) << "Third value of second V3d loaded";

  EXPECT_STREQ("This is another string",e->getString(15)->get().c_str()) << "First string loaded";
  EXPECT_STREQ("This is a string",e->getString(16)->get().c_str()) << "Second string loaded";

  EXPECT_STREQ("The first string for vector",e->getStringVector(17)->get()[0].c_str()) << "First string of first vString loaded";
  EXPECT_STREQ("The second",e->getStringVector(17)->get()[1].c_str()) << "Second string of first vString loaded";
  EXPECT_STREQ("This is a third string",e->getStringVector(18)->get()[0].c_str()) << "First string of second vString loaded";
  EXPECT_STREQ("I do not have free will",e->getStringVector(18)->get()[1].c_str()) << "Second string of second vString loaded";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors at the end.";

  valueDRsrc.clear();
  valueFRsrc.clear();
  valueURsrc.clear();
  valueBRsrc.clear();
  valueIRsrc.clear();
  valueV2Rsrc.clear();
  valueV3Rsrc.clear();
  valueSRsrc.clear();
  valueVSRsrc.clear();
  configRsrc.clear();
  entityRsrc.clear();
  dict.clear();
  zbe::SysError::clear();
}

} //namespace EntityFtryTest
