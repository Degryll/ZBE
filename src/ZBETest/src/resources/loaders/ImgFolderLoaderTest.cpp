#include "gtest/gtest.h"

#include <memory>
#include <filesystem>

#include "ZBE/core/system/SysError.h"

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

namespace RsrcFolderLoaderTest {

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

TEST(RsrcFolderLoader, usage) {
EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

std::shared_ptr<DummyRsrcLoader> rsrcl = std::make_shared<DummyRsrcLoader>();
zbe::RsrcFolderLoader rsrcfl(rsrcl);
rsrcfl.load("data/test/img");

EXPECT_EQ(2,rsrcl->calls) << "Must load one image";
EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
zbe::SysError::clear();
}

}  // namespace RsrcFolderLoaderTest
