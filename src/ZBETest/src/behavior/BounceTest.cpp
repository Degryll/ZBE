#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/archetypes/implementations/SimpleBouncing.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/time/Timer.h"

namespace BounceTest {

TEST(Bounce, apply) {

    zbe::SimpleBouncing<2> b({0.0, 0.0},{1.0, 0.0});
    zbe::BaseBouncer<2> * bm = new zbe::BaseBouncer<2>(&b);
    std::shared_ptr<zbe::AvatarEntityFixed<zbe::Bouncer<2> > > bemock = std::make_shared<zbe::AvatarEntityFixed<zbe::Bouncer<2> > >();
    bemock->setAvatar(bm);
    zbe::Bounce<2> bounce;


    EXPECT_FALSE(b.hasNormals()) << "Initially should not have normals.";
    bm->addNormal({1.0,1.0});
    bm->addNormal({1.0,-1.0});
    EXPECT_TRUE(b.hasNormals()) << "Then it should have normals.";

    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > aec;
    wrapAEC(&aec,bemock);
    bounce.apply(aec);

    EXPECT_FALSE(b.hasNormals()) << "Normals should be cleaned.";

    EXPECT_EQ(-1,b.getVelocity()[0]) << "Velocity should be inverted";
    EXPECT_EQ(0,b.getVelocity()[1]) << "Velocity should be inverted";
}

}  // namespace BounceTest
