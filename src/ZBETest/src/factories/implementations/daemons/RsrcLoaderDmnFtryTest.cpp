#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/daemons/RsrcLoaderDmn.h"

#include "ZBE/factories/implementations/daemons/RsrcLoaderDmnFtry.h"

namespace RsrcLoaderDmnTest {

class DummyRsrcLoader : public zbe::RsrcLoader {
public:
DummyRsrcLoader() : calls(0) {}
void load(std::filesystem::path) {
  calls++;
}

bool isLoadable(std::filesystem::path extension) {
  static std::filesystem::path ext = ".png";
  return (ext.compare(extension) == 0);
}

int calls;
};

TEST(RsrcLoaderDmn, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto& rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();
  (*cfg)["rsrcLoader"] = "DummyRsrcLoader"s;
  (*cfg)["url"] = "data/test/img/testing_001.png"s;
  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dummyRsrcLoader = std::make_shared<DummyRsrcLoader>();

  rsrcLoaderRsrc.insert("RsrcLoader.DummyRsrcLoader"s, dummyRsrcLoader);

  RsrcLoaderDmnFtry rfldf;
  rfldf.create("RsrcLoaderDmnTestName", cfgId);
  rfldf.setup("RsrcLoaderDmnTestName", cfgId);

  auto dmn = daemonRsrc.get("Daemon.RsrcLoaderDmnTestName");
  dmn->run();


  EXPECT_EQ(1, dummyRsrcLoader->calls) << "RsrcLoader must be called once";
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace MainLoopFtryTest
