#include "gtest/gtest.h"

#include <memory>


#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/behaviors/StateSetter.h"

namespace StateSetterTest {

TEST(StateSetter, apply) {

    std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();
    std::shared_ptr<zbe::Value<int64_t> > state = std::make_shared<zbe::SimpleValue<int64_t> >(15);

    ent->setInt(1, state);

    std::shared_ptr<zbe::SAvatar<int64_t> > avatar = std::make_shared<zbe::SBaseAvatar<int64_t> >(ent, 1);

    zbe::StateSetter s(10);

    EXPECT_EQ(15, state->get()) << "Initially state.";

    s.apply(avatar);

    EXPECT_EQ(10, state->get()) << "After apply the behavior, the state has changed.";
}

}  // namespace StateSetterTest
