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
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/daemons/RsrcFolderLoaderDmn.h"

#include "ZBE/factories/implementations/daemons/RsrcFolderLoaderDmnFtry.h"

namespace RsrcFolderLoaderDmnTest {

class DummyRsrcLoader : public zbe::RsrcLoader {
public:
DummyRsrcLoader() : calls(0) {}
void load(std::filesystem::path) override {
  calls++;
}

bool isLoadable(std::filesystem::path extension) {
  static std::filesystem::path ext = ".png";
  return (ext.compare(extension) == 0);
}

int calls;
};

TEST(RsrcFolderLoaderDmn, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto& rsrcRsrcLoader = RsrcStore<RsrcLoader>::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();
  (*cfg)["loader"] = "DummyRsrcLoader"s;
  (*cfg)["url"] = "data/test/img"s;
  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dummyRsrcLoader = std::make_shared<DummyRsrcLoader>();

  rsrcRsrcLoader.insert("RsrcLoader.DummyRsrcLoader"s, dummyRsrcLoader);

  RsrcFolderLoaderDmnFtry rfldf;
  rfldf.create("RsrcFolderLoaderDmnTestName", cfgId);
  rfldf.setup("RsrcFolderLoaderDmnTestName", cfgId);

  auto dmn = daemonRsrc.get("Daemon.RsrcFolderLoaderDmnTestName");
  dmn->run();


  EXPECT_EQ(2, dummyRsrcLoader->calls) << "Must load two images";
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace MainLoopFtryTest
