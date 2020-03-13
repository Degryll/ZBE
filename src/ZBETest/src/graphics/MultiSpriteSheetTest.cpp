#include "gtest/gtest.h"

#include "ZBE/core/system/SysTime.h"


#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/graphics/MultiSpriteSheet.h"

#include "testutils/MockedContextTime.h"

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

    std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
    zbe::ContextTime::setMaxFrameTime(5000000);

    //int64_t x, int64_t y, int64_t w, int64_t h, uint64_t graphics, double degrees, uint64_t state, uint64_t time, std::shared_ptr<ContextTime> contextTime
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();
    ent->setContextTime(contextTime);
    std::shared_ptr<Value<uint64_t> > graphics = std::make_shared<SimpleValue<uint64_t> >(1);
    std::shared_ptr<Value<int64_t> > state = std::make_shared<SimpleValue<int64_t> >(0);
    std::shared_ptr<Value<double> > rotation = std::make_shared<SimpleValue<double> >(0.0);
    std::shared_ptr<Value<Vector2D> > position = std::make_shared<SimpleValue<Vector2D> >(Vector2D({0, 0}));
    std::shared_ptr<Value<Vector2D> > size = std::make_shared<SimpleValue<Vector2D> >(Vector2D({100, 100}));

    ent->setUint(1, graphics);
    ent->setInt(1, state);
    ent->setDouble(1, rotation);
    ent->setVector2D(1, size);
    ent->setVector2D(2, position);

    std::array<uint64_t, 5> a{ {1, 1, 1, 1, 2} };
    std::shared_ptr<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> > avatar = std::make_shared<MBaseAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> >(ent, a);

    state->set(0);
    Sprite s = mss.generateSprite(avatar);
    EXPECT_EQ(0, s.src.p.x);
    EXPECT_EQ(0, s.src.p.y);
    EXPECT_EQ(1, s.src.v.x);
    EXPECT_EQ(1, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    state->set(1);
    s = mss.generateSprite(avatar);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0.0, s.dst.p.x);
    EXPECT_EQ(0.0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    state->set(2);
    s = mss.generateSprite(avatar);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    state->set(7);
    s = mss.generateSprite(avatar);
    EXPECT_EQ(0.5, s.src.p.x);
    EXPECT_EQ(0.5, s.src.p.y);
    EXPECT_EQ(0.5, s.src.v.x);
    EXPECT_EQ(0.5, s.src.v.y);
    EXPECT_EQ(0, s.dst.p.x);
    EXPECT_EQ(0, s.dst.p.y);
    EXPECT_EQ(100, s.dst.v.x);
    EXPECT_EQ(100, s.dst.v.y);

    state->set(1);
    contextTime->setFixedTime(SECOND*1.5);
    contextTime->update();
    s = mss.generateSprite(avatar);
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
