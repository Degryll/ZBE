#include "gtest/gtest.h"

#include <cstdio>

#include <filesystem>
#include <memory>
#include <string>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Vector.h"

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
  using namespace zbe;

  EXPECT_EQ(0, SysError::getNErrors()) << "Initially no errors.";

  RsrcStore<ImgDef>& rsrc = RsrcStore<ImgDef>::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();

  std::shared_ptr<SDLWindow> window = std::make_shared<SDLWindow>("ImgAndDefTest", 1000, 1000);

  std::shared_ptr<RsrcDefLoader> idl = std::make_shared<JSONImgDefLoader>();
  std::shared_ptr<RsrcLoader> rsrcl = std::make_shared<SDLImgLoader>(window->getImgStore(), idl);
  RsrcFolderLoader rsrcfl(rsrcl);
  rsrcfl.load("data/test/img");

  EXPECT_EQ(0, SysError::getNErrors()) << "No errors after folder load.";

  uint64_t houseStay = nrd.get(cn::IMGDEF + cn::SEPARATOR + std::string("house.stay"));
  uint64_t houseStill = nrd.get(cn::IMGDEF + cn::SEPARATOR + std::string("house.still"));
  uint64_t nosenseFoo = nrd.get(cn::IMGDEF + cn::SEPARATOR + std::string("nosense.foo"));

  EXPECT_EQ(0, SysError::getNErrors()) << "No errors in name dictionary.";

  std::shared_ptr<ImgDef> stayDef = rsrc.get(houseStay);
  std::shared_ptr<ImgDef> stillDef = rsrc.get(houseStill);
  std::shared_ptr<ImgDef> fooDef = rsrc.get(nosenseFoo);

  EXPECT_EQ(0, SysError::getNErrors()) << "No errors in resource manager.";

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

  EXPECT_EQ(0, SysError::getNErrors()) << "Finally no errors.";
  SysError::clear();
  rsrc.clear();
  nrd.clear();
}

TEST(RsrcLoadTest, Load_folder) {
  using namespace zbe;

  EXPECT_EQ(0, SysError::getNErrors()) << "Initially no errors.";

  RsrcStore<ImgDef>& rsrc = RsrcStore<ImgDef>::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
  RsrcStore<SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& ssrsrc = RsrcStore<SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >::getInstance();

  nrd.insert(cn::STATE + cn::SEPARATOR + "stay",1);
  nrd.insert(cn::STATE + cn::SEPARATOR + "jump",2);
  nrd.insert(cn::STATE + cn::SEPARATOR + "run",3);

  std::shared_ptr<SDLWindow> window = std::make_shared<SDLWindow>("ImgAndDefTest", 1000, 1000);
  std::shared_ptr<RsrcDefLoader> idl = std::make_shared<JSONImgDefLoader>();
  std::shared_ptr<RsrcLoader> prerl = std::make_shared<SDLImgLoader>(window->getImgStore(), idl);
  RsrcFolderLoader prerfl(prerl);

  EXPECT_EQ(0, SysError::getNErrors()) << "No errors after test config."+SysError::getFirstErrorString();

  prerfl.load("data/test/img");
  EXPECT_EQ(0, SysError::getNErrors()) << "No errors after pre folder load:"+SysError::getFirstErrorString();

  std::shared_ptr<RsrcLoader> rl = std::make_shared<JSONMultiSpriteSheetLoader>();
  RsrcFolderLoader rfl(rl);
  rfl.load("data/test/sprtsheet");

  EXPECT_EQ(2, SysError::getNErrors()) << "Two errors expected: \"Resource id not found\" and \"Json failed to build MultiSpriteSheet\".";
  SysError::clear();

  std::shared_ptr<SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> > player001 = ssrsrc.get(nrd.get(/*cn::SPRTSHEET + cn::SEPARATOR + */"player_001"));
  std::shared_ptr<SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> > player002 = ssrsrc.get(nrd.get(/*cn::SPRTSHEET + cn::SEPARATOR + */"player_002"));

  std::shared_ptr<Entity> ent1 = std::make_shared<Entity>();
  std::shared_ptr<Value<uint64_t> > graphics1 = std::make_shared<SimpleValue<uint64_t> >(1);
  std::shared_ptr<Value<int64_t> > state1 = std::make_shared<SimpleValue<int64_t> >(1);
  std::shared_ptr<Value<double> > rotation1 = std::make_shared<SimpleValue<double> >(0.0);
  std::shared_ptr<Value<Vector2D> > position1 = std::make_shared<SimpleValue<Vector2D> >(Vector2D({0, 0}));
  std::shared_ptr<Value<Vector2D> > size1 = std::make_shared<SimpleValue<Vector2D> >(Vector2D({100, 100}));

  ent1->setUint(1, graphics1);
  ent1->setInt(1, state1);
  ent1->setDouble(1, rotation1);
  ent1->setVector2D(1, size1);
  ent1->setVector2D(2, position1);

  std::array<uint64_t, 5> a1{ {1, 1, 1, 1, 2} };
  std::shared_ptr<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> > avatar1 = std::make_shared<MBaseAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> >(ent1, a1);

  std::shared_ptr<Entity> ent2 = std::make_shared<Entity>();
  std::shared_ptr<Value<uint64_t> > graphics2 = std::make_shared<SimpleValue<uint64_t> >(2);
  std::shared_ptr<Value<int64_t> > state2 = std::make_shared<SimpleValue<int64_t> >(2);
  std::shared_ptr<Value<double> > rotation2 = std::make_shared<SimpleValue<double> >(0.0);
  std::shared_ptr<Value<Vector2D> > position2 = std::make_shared<SimpleValue<Vector2D> >(Vector2D({10, 10}));
  std::shared_ptr<Value<Vector2D> > size2 = std::make_shared<SimpleValue<Vector2D> >(Vector2D({110, 110}));

  ent2->setUint(1, graphics2);
  ent2->setInt(1, state2);
  ent2->setDouble(1, rotation2);
  ent2->setVector2D(1, size2);
  ent2->setVector2D(2, position2);

  std::array<uint64_t, 5> a2{ {1, 1, 1, 1, 2} };
  std::shared_ptr<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> > avatar2 = std::make_shared<MBaseAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> >(ent2, a2);

  //SimpleAnimatedSprite(x, y, w, h, graphics, degrees, uint64_t state, uint64_t time, std::shared_ptr<ContextTime> contextTime)
  // SimpleAnimatedSprite sas1(0, 0, 100, 100, 1, 0.0f, 1, 100, SysTime::getInstance());
  //
  // SimpleAnimatedSprite sas2(10, 10, 110, 110, 2, 0.0f, 2, 600, SysTime::getInstance());

  Sprite s1 = player001->generateSprite(avatar1);
  Sprite s2 = player002->generateSprite(avatar2);

  EXPECT_NEAR(0.0, s1.src.p.x, 0.00001) << "Must match src x";
  EXPECT_NEAR(0.0, s1.src.p.y, 0.00001) << "Must match src y";
  EXPECT_NEAR(0.5, s1.src.v.x, 0.00001) << "Must match src width";
  EXPECT_NEAR(0.5, s1.src.v.y, 0.00001) << "Must match src height";

  EXPECT_NEAR(-0.1, s1.dst.p.x, 0.00001) << "Must match dst x";
  EXPECT_NEAR(-0.1, s1.dst.p.y, 0.00001) << "Must match dst y";
  EXPECT_NEAR(70.0, s1.dst.v.x, 0.00001) << "Must match dst width";
  EXPECT_NEAR(70.0, s1.dst.v.y, 0.00001) << "Must match dst height";

  EXPECT_EQ(rsrc.get(nrd.get(cn::IMGDEF + cn::SEPARATOR + "house.stay"))->imgSrcId, s1.g) << "Must match graphics id.";

  EXPECT_NEAR(0.5, s2.src.p.x, 0.00001) << "Must match src x";
  EXPECT_NEAR(0.5, s2.src.p.y, 0.00001) << "Must match src y";
  EXPECT_NEAR(1.0, s2.src.v.x, 0.00001) << "Must match src width";
  EXPECT_NEAR(1.0, s2.src.v.y, 0.00001) << "Must match src height";

  EXPECT_NEAR(9.9, s2.dst.p.x, 0.00001) << "Must match dst x";
  EXPECT_NEAR(9.9, s2.dst.p.y, 0.00001) << "Must match dst y";
  EXPECT_NEAR(77.0, s2.dst.v.x, 0.00001) << "Must match dst width";
  EXPECT_NEAR(77.0, s2.dst.v.y, 0.00001) << "Must match dst height";

  EXPECT_EQ(rsrc.get(nrd.get(cn::IMGDEF + cn::SEPARATOR + "house.still"))->imgSrcId, s2.g) << "Must match graphics id.";

  EXPECT_EQ(0, SysError::getNErrors()) << "Finally no errors.";
  rsrc.clear();
  nrd.clear();
  ssrsrc.clear();
  SysError::clear();
}
}  // namespace ImgAndDefTest
