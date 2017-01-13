#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/core/tools/math/math.h"

TEST(UniformLinearMotion, apply0) {
    zbe::SimpleMobile<2> m({3.0, 5.0},{7.0, 11.0});
    zbe::UniformLinearMotion<2> bulma;

    EXPECT_EQ(3.0,m.getPosition()[0]) << "Initial Position X.";
    EXPECT_EQ(5.0,m.getPosition()[1]) << "Initial Position Y.";

    bulma.apply(&m, uint64_t(1.0 * zbe::VELOCITYTOTIME));

    EXPECT_EQ(10.0,m.getPosition()[0]) << "Position X.";
    EXPECT_EQ(16.0,m.getPosition()[1]) << "Position Y.";

    bulma.apply(&m, uint64_t(0.5 * zbe::VELOCITYTOTIME));

    EXPECT_EQ(13.5,m.getPosition()[0]) << "Position X.";
    EXPECT_EQ(21.5,m.getPosition()[1]) << "Position Y.";
    //EXPECT_NEAR(-1.0,mb.getVelocity().y,0.00001) << "bounce velocity \".y\".";
}

