#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/behaviors/Erase.h"

namespace EraseTest {

class EntityMock : public zbe::Entity {
public:
  EntityMock(bool& check) : check(check) {}

  void setERASED() {
    check = true;
    Entity::setERASED();
  }
  bool& check;
};

TEST(Erase, apply) {
    bool check = false;
//    auto *e = new EntityMock(check);
    std::shared_ptr<EntityMock> e = std::make_shared<EntityMock>(check);
    auto *ba = new zbe::BaseAvatar(e);
    auto aefa = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ba);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > aec  = std::make_shared<zbe::AvatarEntityContainer<zbe::Avatar> >(aefa);

    zbe::Erase eraser;

    EXPECT_FALSE(check) << "Initially setERASED is not called.";

    eraser.apply(aec);

    EXPECT_TRUE(check) << "setERASED should be called.";

//    delete e;
    //delete ba;  // AvatarEntityFixed deletes it
}

}  // namespace EraseTest
