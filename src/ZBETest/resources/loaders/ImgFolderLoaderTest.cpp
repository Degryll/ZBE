#include "gtest/gtest.h"

#include <memory>
#include <filesystem>

#include "ZBE/core/system/SysError.h"

#include "ZBE/resources/loaders/ImgDefLoader.h"
#include "ZBE/resources/loaders/ImgLoader.h"
#include "ZBE/resources/loaders/ImgFolderLoader.h"

namespace ImgFolderLoaderTest {

class DummyImgDefLoader : public zbe::ImgDefLoader {
public:
 DummyImgDefLoader() : calls(0) {}

 void loadImgDef(const std::filesystem::path&, uint64_t) {
   calls++;
 }

 const std::filesystem::path getExtension() {
   return std::filesystem::path(".json");
 }

 int calls;
};

class DummyImgLoader : public zbe::ImgLoader {
public:
 DummyImgLoader() : calls(0) {}
 uint64_t loadImg(std::filesystem::path) {
   calls++;
   return calls;
 }

 bool isLoadable(std::filesystem::path extension) {
   static std::filesystem::path ext = ".png";
   return (ext.compare(extension) == 0);
 }

 int calls;
};

TEST(ImgFolderLoader, usage) {
 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

 std::shared_ptr<DummyImgDefLoader> idl = std::make_shared<DummyImgDefLoader>();
 std::shared_ptr<DummyImgLoader> il = std::make_shared<DummyImgLoader>();
 zbe::ImgFolderLoader ifl(il, idl);
 ifl.load("data/test/img");

 EXPECT_EQ(2,idl->calls) << "Must load one definition";
 EXPECT_EQ(2,il->calls) << "Must load one image";
 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
 zbe::SysError::clear();
}

}  // namespace ImgFolderLoaderTest
