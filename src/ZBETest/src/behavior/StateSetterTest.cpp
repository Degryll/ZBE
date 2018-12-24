#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/behaviors/StateSetter.h"

namespace StateSetterTest {

TEST(StateSetter, apply) {
    auto *ss = new zbe::SimpleState(15);
    auto *bs = new zbe::BaseStated(ss);
    auto aefs = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(bs);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated> > aec  = std::make_shared<zbe::AvatarEntityContainer<zbe::Stated> >(aefs);

    zbe::StateSetter s(10);

    EXPECT_EQ(15, ss->getState()) << "Initially state.";

    s.apply(aec);

    EXPECT_EQ(10, ss->getState()) << "After apply the behavior, the state has changed.";

    delete ss;
    //delete bs;  // AvatarEntityFixed deletes it
}

}  // namespace StateSetterTest
