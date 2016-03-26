#include "gtest/gtest.h"

#include "ZBE/core/entities/CollisionerEntity.h"

//Dummy Entity implementation. Just for test purposes.
class CollisionerEntityTest : public zbe::CollisionerEntity {
};

TEST(CollisionerEntity, Usage) {
  CollisionerEntityTest e;

  e.setCollisionerType(42);

  EXPECT_EQ((uint64_t) 42,e.getCollisionerType()) << "Get Collisioner.";

  e.setCollisionerType(314);

  EXPECT_EQ((uint64_t) 314,e.getCollisionerType()) << "Get Collisioner.";
}
