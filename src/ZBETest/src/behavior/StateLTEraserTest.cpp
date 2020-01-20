#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/behaviors/StateLTEraser.h"

namespace StateLTEraserTest {

class EntityMock : public zbe::_Entity2 {
public:
  EntityMock(bool& check) : _Entity2(this), check(check) {}

  void setERASED() {
    check = true;
    _Entity2::setERASED();
  }
  bool& check;
};

TEST(StateLTEraser, apply) {
    bool check = false;
//    auto *e = new EntityMock(check);
    std::shared_ptr<EntityMock> e = std::make_shared<EntityMock>(check);
    auto *ba = new zbe::BaseAvatar(e);
    auto *ss = new zbe::SimpleState(15);
    auto *bs = new zbe::BaseStated(ss);
    auto aefa = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ba);
    auto aefs = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(bs);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar, zbe::Stated> > aec  = std::make_shared<zbe::AvatarEntityContainer<zbe::Avatar, zbe::Stated> >(aefa, aefs);

    zbe::StateLTEraser slteraser(10);

    EXPECT_FALSE(check) << "Initially setERASED is not called.";

    slteraser.apply(aec);

    EXPECT_FALSE(check) << "setERASED should'n be called.";

    ss->setState(5);
    slteraser.apply(aec);

    EXPECT_TRUE(check) << "setERASED should be called.";

//    delete e;
    //delete ba;  // AvatarEntityFixed deletes it
    delete ss;
    //delete bs;  // AvatarEntityFixed deletes it
}

}  // namespace StateLTEraserTest
