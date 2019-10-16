#include "gtest/gtest.h"

#include <cstdio>

#include <filesystem>
#include <memory>
#include <string>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"

#include "ZBE/resources/loaders/RsrcDefLoader.h"
#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/SDL/resources/SDLImgLoader.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/JSON/resources/JSONImgDefLoader.h"
#include "ZBE/JSON/resources/JSONMultiSpriteSheetLoader.h"

#include "ZBE/graphics/MultiSpriteSheet.h"

namespace RsrcLoadTest {

TEST(ImgAndDefTest, Load_folder) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::RsrcStore<zbe::ImgDef>& rsrc = zbe::RsrcStore<zbe::ImgDef>::getInstance();
  zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

  std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("ImgAndDefTest", 1000, 1000);

  std::shared_ptr<zbe::RsrcDefLoader> idl = std::make_shared<zbe::JSONImgDefLoader>();
  std::shared_ptr<zbe::RsrcLoader> rsrcl = std::make_shared<zbe::SDLImgLoader>(window->getImgStore(), idl);
  zbe::RsrcFolderLoader rsrcfl(rsrcl);
  rsrcfl.load("data/test/img");

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors after folder load.";

  uint64_t houseStay = nrd.get(zbe::cn::IMGDEF + zbe::cn::SEPARATOR + std::string("house.stay"));
  uint64_t houseStill = nrd.get(zbe::cn::IMGDEF + zbe::cn::SEPARATOR + std::string("house.still"));
  uint64_t nosenseFoo = nrd.get(zbe::cn::IMGDEF + zbe::cn::SEPARATOR + std::string("nosense.foo"));

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

  EXPECT_NEAR(0.0, stayDef->region.p.x, 0.00001) << "Must match region.x";
  EXPECT_NEAR(0.0, stayDef->region.p.y, 0.00001) << "Must match region.y";
  EXPECT_NEAR(0.5, stayDef->region.v.x, 0.00001) << "Must match region.w";
  EXPECT_NEAR(0.5, stayDef->region.v.y, 0.00001) << "Must match region.h";

  EXPECT_NEAR(0.5, stillDef->region.p.x, 0.00001) << "Must match region.x";
  EXPECT_NEAR(0.5, stillDef->region.p.y, 0.00001) << "Must match region.y";
  EXPECT_NEAR(1.0, stillDef->region.v.x, 0.00001) << "Must match region.w";
  EXPECT_NEAR(1.0, stillDef->region.v.y, 0.00001) << "Must match region.h";

  EXPECT_NEAR(1.0, fooDef->region.p.x, 0.00001) << "Must match region.x";
  EXPECT_NEAR(2.0, fooDef->region.p.y, 0.00001) << "Must match region.y";
  EXPECT_NEAR(3.0, fooDef->region.v.x, 0.00001) << "Must match region.w";
  EXPECT_NEAR(4.0, fooDef->region.v.y, 0.00001) << "Must match region.h";

  EXPECT_NEAR(0.0, stayDef->regionOffset.x, 0.00001) << "Must match regionOffset.x";
  EXPECT_NEAR(0.0, stayDef->regionOffset.y, 0.00001) << "Must match regionOffset.y";

  EXPECT_NEAR(1.0, stillDef->regionOffset.x, 0.00001) << "Must match regionOffset.x";
  EXPECT_NEAR(0.0, stillDef->regionOffset.y, 0.00001) << "Must match regionOffset.y";

  EXPECT_NEAR(5.0, fooDef->regionOffset.x, 0.00001) << "Must match regionOffset.x";
  EXPECT_NEAR(6.0, fooDef->regionOffset.y, 0.00001) << "Must match regionOffset.y";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
  zbe::SysError::clear();
  rsrc.clear();
  nrd.clear();
}

TEST(RsrcLoadTest, Load_folder) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::RsrcStore<zbe::ImgDef>& rsrc = zbe::RsrcStore<zbe::ImgDef>::getInstance();
  zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();
  zbe::RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >& ssrsrc = zbe::RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >::getInstance();

  nrd.insert(zbe::cn::STATE + zbe::cn::SEPARATOR + "stay",1);
  nrd.insert(zbe::cn::STATE + zbe::cn::SEPARATOR + "jump",2);
  nrd.insert(zbe::cn::STATE + zbe::cn::SEPARATOR + "run",3);

  std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("ImgAndDefTest", 1000, 1000);
  std::shared_ptr<zbe::RsrcDefLoader> idl = std::make_shared<zbe::JSONImgDefLoader>();
  std::shared_ptr<zbe::RsrcLoader> prerl = std::make_shared<zbe::SDLImgLoader>(window->getImgStore(), idl);
  zbe::RsrcFolderLoader prerfl(prerl);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors after test config."+zbe::SysError::getFirstErrorString();

  prerfl.load("data/test/img");
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors after pre folder load:"+zbe::SysError::getFirstErrorString();

  std::shared_ptr<zbe::RsrcLoader> rl = std::make_shared<zbe::JSONMultiSpriteSheetLoader>();
  zbe::RsrcFolderLoader rfl(rl);
  rfl.load("data/test/sprtsheet");

  EXPECT_EQ(2, zbe::SysError::getNErrors()) << "Two errors expected: \"Resource id not found\" and \"Json failed to build MultiSpriteSheet\".";
  zbe::SysError::clear();

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > player001 = ssrsrc.get(nrd.get(/*zbe::cn::SPRTSHEET + zbe::cn::SEPARATOR + */"player_001"));
  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > player002 = ssrsrc.get(nrd.get(/*zbe::cn::SPRTSHEET + zbe::cn::SEPARATOR + */"player_002"));

  zbe::SimpleAnimatedSprite sas1(0, 0, 100, 100, 1, 0.0f, 1, 100, zbe::SysTime::getInstance());
  zbe::Sprite s1 = player001->generateSprite(&sas1);

  zbe::SimpleAnimatedSprite sas2(10, 10, 110, 110, 2, 0.0f, 2, 600, zbe::SysTime::getInstance());
  zbe::Sprite s2 = player002->generateSprite(&sas2);

  EXPECT_NEAR(0.0, s1.src.p.x, 0.00001) << "Must match src x";
  EXPECT_NEAR(0.0, s1.src.p.y, 0.00001) << "Must match src y";
  EXPECT_NEAR(0.5, s1.src.v.x, 0.00001) << "Must match src width";
  EXPECT_NEAR(0.5, s1.src.v.y, 0.00001) << "Must match src height";

  EXPECT_NEAR(-0.1, s1.dst.p.x, 0.00001) << "Must match dst x";
  EXPECT_NEAR(-0.1, s1.dst.p.y, 0.00001) << "Must match dst y";
  EXPECT_NEAR(70.0, s1.dst.v.x, 0.00001) << "Must match dst width";
  EXPECT_NEAR(70.0, s1.dst.v.y, 0.00001) << "Must match dst height";

  EXPECT_EQ(rsrc.get(nrd.get(zbe::cn::IMGDEF + zbe::cn::SEPARATOR + "house.stay"))->imgSrcId, s1.g) << "Must match graphics id.";

  EXPECT_NEAR(0.5, s2.src.p.x, 0.00001) << "Must match src x";
  EXPECT_NEAR(0.5, s2.src.p.y, 0.00001) << "Must match src y";
  EXPECT_NEAR(1.0, s2.src.v.x, 0.00001) << "Must match src width";
  EXPECT_NEAR(1.0, s2.src.v.y, 0.00001) << "Must match src height";

  EXPECT_NEAR(9.9, s2.dst.p.x, 0.00001) << "Must match dst x";
  EXPECT_NEAR(9.9, s2.dst.p.y, 0.00001) << "Must match dst y";
  EXPECT_NEAR(77.0, s2.dst.v.x, 0.00001) << "Must match dst width";
  EXPECT_NEAR(77.0, s2.dst.v.y, 0.00001) << "Must match dst height";

  EXPECT_EQ(rsrc.get(nrd.get(zbe::cn::IMGDEF + zbe::cn::SEPARATOR + "house.still"))->imgSrcId, s2.g) << "Must match graphics id.";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
  rsrc.clear();
  nrd.clear();
  ssrsrc.clear();
  zbe::SysError::clear();
}
}  // namespace ImgAndDefTest
