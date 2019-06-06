#include "gtest/gtest.h"

#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/graphics/MultiSpriteSheet.h"

namespace MultiSpriteSheetTest {

TEST(MultiSpriteSheet, generateSprite) {
    using namespace zbe;
    ImgDef id1(0);
    ImgDef id2(1, 10000, 2, Region2D({0.5,0.5},{0.5,0.5}), Vector2D({0.5,0.0}));
    ImgDef idd(2, 10000, 2, Region2D({0.0,0.5},{0.5,0.5}), Vector2D({0.0,0.5}));
    SprtDef sd1(id1);
    SprtDef sd2(id2);
    SprtDef sdd(idd);
    MultiSpriteSheet mss(2,sdd);
    mss.setSprite(0, id1);
    mss.setSprite(1, id2);
    SimpleAnimatedSprite sas(0, 0, 100, 100, 1, 0.0, 0, 0, SysTime::getInstance());

    sas.setState(0);
    Sprite s = mss.generateSprite(&sas);
    EXPECT_EQ(0, s.src.p.x);
    EXPECT_EQ(0, s.src.p.y);
    EXPECT_EQ(1, s.src.v.x);
    EXPECT_EQ(1, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    sas.setState(1);
    s = mss.generateSprite(&sas);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0.0, s.dst.p.x);
    EXPECT_EQ(0.0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    sas.setState(2);
    s = mss.generateSprite(&sas);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    sas.setState(7);
    s = mss.generateSprite(&sas);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    sas.setState(1);
    sas.setTime(SECOND*1.5);
    s = mss.generateSprite(&sas);
    EXPECT_EQ(1.0, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);
}

}  // namespace MultiSpriteSheetTest
