#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/core/tools/math/math.h"

TEST(UniformLinearMotion, apply) {
    zbe::SimpleMobile<2> m({30, 50},{70, 110});
    zbe::UniformLinearMotion<2> bulma;

    EXPECT_EQ(30,m.getPosition()[0]) << "Initial Position X.";
    EXPECT_EQ(50,m.getPosition()[1]) << "Initial Position Y.";

    bulma.apply(&m, int64_t(1) * zbe::SECOND );

    EXPECT_EQ(100,m.getPosition()[0]) << "Position X.";
    EXPECT_EQ(160,m.getPosition()[1]) << "Position Y.";

    bulma.apply(&m, (int64_t(1) * zbe::SECOND)/2);

    EXPECT_EQ(130,m.getPosition()[0]) << "Position X.";
    EXPECT_EQ(215,m.getPosition()[1]) << "Position Y.";
}
