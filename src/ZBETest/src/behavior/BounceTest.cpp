#include "gtest/gtest.h"

#include <memory>
#include <array>

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace BounceTest {

TEST(Bounce, apply) {

    std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();
    std::shared_ptr<zbe::Value<bool> > hasNormals = std::make_shared<zbe::SimpleValue<bool> >(true);
    std::shared_ptr<zbe::Value<zbe::Vector<2> > > normals = std::make_shared<zbe::SimpleValue<zbe::Vector<2> > >(zbe::Vector<2>{0.0, 0.0});
    std::shared_ptr<zbe::Value<zbe::Vector<2> > > vel = std::make_shared<zbe::SimpleValue<zbe::Vector<2> > >(zbe::Vector<2>{1.0, 0.0});

    ent->setBool(1, hasNormals);
    ent->setVector2D(35, normals);
    ent->setVector2D(82, vel);

    std::array<uint64_t, 3> a1{ {1, 35, 82} };
    std::shared_ptr<zbe::MAvatar<bool, zbe::Vector<2>, zbe::Vector<2> > > avatar = std::make_shared<zbe::MBaseAvatar<bool, zbe::Vector<2>, zbe::Vector<2> > >(ent, a1);

    zbe::Bounce<2> bounce;

    normals->set(normals->get()+zbe::Vector<2>{1.0,1.0});
    normals->set(normals->get()+zbe::Vector<2>{1.0,-1.0});

    bounce.apply(avatar);

    EXPECT_FALSE(hasNormals->get()) << "Normals should be cleaned.";

    EXPECT_EQ(-1, vel->get()[0]) << "Velocity should be inverted";
    EXPECT_EQ( 0, vel->get()[1]) << "Velocity should be inverted";
}

}  // namespace BounceTest
