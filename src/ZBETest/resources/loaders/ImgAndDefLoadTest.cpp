#include "gtest/gtest.h"

#include <filesystem>
#include <memory>
#include <string>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/resources/loaders/ImgDefLoader.h"
#include "ZBE/resources/loaders/ImgLoader.h"
#include "ZBE/resources/loaders/ImgFolderLoader.h"

#include "ZBE/SDL/resources/SDLImgLoader.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/JSON/resources/JSONImgDefLoader.h"

#include "ZBE/graphics/MultiSpriteSheet.h"

namespace ImgAndDefTest {

TEST(ImgAndDefTest, Load_folder) {
 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
 std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("ImgAndDefTest", 1000, 1000);

 std::shared_ptr<zbe::ImgDefLoader> idl = std::make_shared<zbe::JSONImgDefLoader>();
 std::shared_ptr<zbe::ImgLoader> il = std::make_shared<zbe::SDLImgLoader>(window->getImgStore());
 zbe::ImgFolderLoader ifl(il, idl);
 ifl.load("data/test/img");

 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors after folder load.";

 zbe::RsrcStore<zbe::ImgDef>& rsrc = zbe::RsrcStore<zbe::ImgDef>::getInstance();
 zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

 uint64_t houseStay = nrd.get(std::string("house.stay"));
 uint64_t houseStill = nrd.get(std::string("house.still"));
 uint64_t nosenseFoo = nrd.get(std::string("nosense.foo"));

 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors in name dictionary.";

 std::shared_ptr<zbe::ImgDef> stayDef = rsrc.get(houseStay);
 std::shared_ptr<zbe::ImgDef> stillDef = rsrc.get(houseStill);
 std::shared_ptr<zbe::ImgDef> fooDef = rsrc.get(nosenseFoo);

 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors in resource manager.";

 EXPECT_EQ(1000, stayDef->frameTime) << "Must match frameTime.";
 EXPECT_EQ(500, stillDef->frameTime) << "Must match frameTime.";
 EXPECT_EQ(333, fooDef->frameTime) << "Must match frameTime.";

 EXPECT_EQ(6, stayDef->frameAmount) << "Must match frameAmount.";
 EXPECT_EQ(2, stillDef->frameAmount) << "Must match frameAmount.";
 EXPECT_EQ(42, fooDef->frameAmount) << "Must match frameAmount.";

 EXPECT_NEAR(0.0, stayDef->region.p.x, 0.01) << "Must match region.x";
 EXPECT_NEAR(0.0, stayDef->region.p.y, 0.01) << "Must match region.y";
 EXPECT_NEAR(0.5, stayDef->region.v.x, 0.01) << "Must match region.w";
 EXPECT_NEAR(0.5, stayDef->region.v.y, 0.01) << "Must match region.h";

 EXPECT_NEAR(0.5, stillDef->region.p.x, 0.01) << "Must match region.x";
 EXPECT_NEAR(0.5, stillDef->region.p.y, 0.01) << "Must match region.y";
 EXPECT_NEAR(1.0, stillDef->region.v.x, 0.01) << "Must match region.w";
 EXPECT_NEAR(1.0, stillDef->region.v.y, 0.01) << "Must match region.h";

 EXPECT_NEAR(1.0, fooDef->region.p.x, 0.01) << "Must match region.x";
 EXPECT_NEAR(2.0, fooDef->region.p.y, 0.01) << "Must match region.y";
 EXPECT_NEAR(3.0, fooDef->region.v.x, 0.01) << "Must match region.w";
 EXPECT_NEAR(4.0, fooDef->region.v.y, 0.01) << "Must match region.h";

 EXPECT_NEAR(0.0, stayDef->regionOffset.x, 0.01) << "Must match regionOffset.x";
 EXPECT_NEAR(0.0, stayDef->regionOffset.y, 0.01) << "Must match regionOffset.y";

 EXPECT_NEAR(1.0, stillDef->regionOffset.x, 0.01) << "Must match regionOffset.x";
 EXPECT_NEAR(0.0, stillDef->regionOffset.y, 0.01) << "Must match regionOffset.y";

 EXPECT_NEAR(5.0, fooDef->regionOffset.x, 0.01) << "Must match regionOffset.x";
 EXPECT_NEAR(6.0, fooDef->regionOffset.y, 0.01) << "Must match regionOffset.y";

 EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
 zbe::SysError::clear();
}

}  // namespace ImgAndDefTest
