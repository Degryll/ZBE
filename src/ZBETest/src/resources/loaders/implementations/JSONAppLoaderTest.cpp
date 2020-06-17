#include "gtest/gtest.h"

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/implementations/JSONAppLoader.h"

namespace JSONAppLoaderTest {
using json = nlohmann::json;

class DummyFtry : public zbe::Factory {
public:

  DummyFtry() : createSet(), setupSet(), createCfgId() {}

  void create(std::string name, uint64_t cfgId) {
    EXPECT_EQ(setupSet.find(name), setupSet.end()) << "Must call create first and only once per cfg";
    createCfgId[name] = cfgId;
    createSet.insert(name);
  };

  void setup(std::string name, uint64_t cfgId) {
    EXPECT_NE(createSet.find(name), createSet.end()) << "Must call create first.";
    EXPECT_EQ(createCfgId[name], cfgId) << "Must recieve the same cfgId as create.";
    setupSet.insert(name);
  }

  void check(int expected) {
    EXPECT_EQ(expected, createSet.size()) << "Must have created all factories";
    EXPECT_EQ(expected, setupSet.size()) << "Must have setup all factories";
  }

  std::unordered_set<std::string> createSet;
  std::unordered_set<std::string> setupSet;
  std::unordered_map<std::string, uint64_t>  createCfgId;

};

TEST(JSONAppLoader, load) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  auto& intStore    = zbe::RsrcDictionary<int64_t>::getInstance();
  auto& uintStore    = zbe::RsrcDictionary<uint64_t>::getInstance();
  auto& doubleStore  = zbe::RsrcDictionary<double>::getInstance();
  auto& flaotStore  = zbe::RsrcDictionary<float>::getInstance();
  auto& stringStore = zbe::RsrcDictionary<std::string>::getInstance();

  auto& rsrcFtry = zbe::RsrcStore<zbe::Factory>::getInstance();
  auto& rsrcJson = zbe::RsrcStore<json>::getInstance();

  auto dmyFtry1 = std::make_shared<DummyFtry>();
  auto dmyFtry2 = std::make_shared<DummyFtry>();
  auto dmyFtry3 = std::make_shared<DummyFtry>();

  rsrcFtry.insert("test.dmyFtry1", dmyFtry1);
  rsrcFtry.insert("test.dmyFtry2", dmyFtry2);
  rsrcFtry.insert("test.dmyFtry3", dmyFtry3);

  zbe::JSONAppLoader appLoader;
  appLoader.load("data/test/app/test_app_001.json");

  dmyFtry1->check(1);
  dmyFtry2->check(2);
  dmyFtry3->check(3);

  json aux;
  aux["key"] = "dmy1_1";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry1->createCfgId["dmy1_1"]))) << "Must have received the proper json.";
  aux["key"] = "dmy2_1";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry2->createCfgId["dmy2_1"]))) << "Must have received the proper json.";
  aux["key"] = "dmy2_2";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry2->createCfgId["dmy2_2"]))) << "Must have received the proper json.";
  aux["key"] = "dmy3_1";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry3->createCfgId["dmy3_1"]))) << "Must have received the proper json.";
  aux["key"] = "dmy3_2";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry3->createCfgId["dmy3_2"]))) << "Must have received the proper json.";
  aux["key"] = "dmy3_3";
  EXPECT_EQ(aux, *(rsrcJson.get(dmyFtry3->createCfgId["dmy3_3"]))) << "Must have received the proper json.";
  EXPECT_EQ(42, intStore.get("cagando")) << "Must load first int";
  EXPECT_EQ(0, intStore.get("ojete")) << "Must load second int";

  EXPECT_EQ(0, intStore.get("ZERAPIO")) << "Must load ZERAPIO as int";
  EXPECT_EQ(0, uintStore.get("ZERAPIO")) << "Must load ZERAPIO as uint";
  EXPECT_FLOAT_EQ(0.0, doubleStore.get("ZERAPIO")) << "Must load ZERAPIO as double";
  EXPECT_FLOAT_EQ(0.0, flaotStore.get("ZERAPIO")) << "Must load ZERAPIO as float";
  //EXPECT_EQ("0", stringStore.get("ZERAPIO")) << "Must load ZERAPIO as string";

  EXPECT_FLOAT_EQ(2.71828,doubleStore.get("math.e")) << "Must load first float";
  EXPECT_FLOAT_EQ(3.14159,doubleStore.get("math.pi")) << "Must load second float";

  EXPECT_EQ("y Blas",stringStore.get("era.necesario")) << "Must load first string";
  EXPECT_EQ("sacabo",stringStore.get("san")) << "Must load second string";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
  zbe::SysError::clear();
}

}  // namespace JSONAppLoaderTest
