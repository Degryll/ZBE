#include "gtest/gtest.h"

#include <memory>
#include <filesystem>

#include "ZBE/core/system/SysError.h"

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/daemons/RsrcFolderLoaderDmn.h"

namespace RsrcFolderLoadDmnTest {

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

TEST(RsrcFolderLoadDmn, usage) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  std::shared_ptr<DummyRsrcLoader> rsrcl = std::make_shared<DummyRsrcLoader>();
  std::shared_ptr<zbe::RsrcFolderLoader> rsrcfl = std::make_shared<zbe::RsrcFolderLoader>(rsrcl);

  zbe::RsrcFolderLoaderDmn dmn;
  dmn.setRsrcFolderLoader(rsrcfl);
  dmn.setUrl("data/test/img");
  dmn.run();

  EXPECT_EQ(2,rsrcl->calls) << "Must load one image";
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
  zbe::SysError::clear();
}

}  // namespace RsrcFolderLoadDmnTest
