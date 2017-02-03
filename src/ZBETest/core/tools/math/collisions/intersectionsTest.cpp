#include "gtest/gtest.h"

#include <cstdint>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"

TEST(Intersections, RaySphere) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Ray<2> ray{{20,30},{50,100}};
  zbe::NSphere<2> nsphere{{80,90},30};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 1 << zbe::PRECISION_DIGITS;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "First Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(6 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(90,p[1]) << "Point of collision (y).";

  t = 1 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 50;
  nsphere.c[1] = 120;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(6 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(90,p[1]) << "Point of collision (y).";

  t = 1 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 80;
  nsphere.c[1] = 90;
  nsphere.r = 10;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";

  zbe::SysError::clear();
}

TEST(Intersections, NormalRaySphere) {
  double m = sqrt(125);
  zbe::Ray<2> ray{{20,30},{50/m,100/m}};
  zbe::NSphere<2> nsphere{{80,90},30};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 100 << zbe::PRECISION_DIGITS;

  uint64_t time = (uint64_t)(6 * m) << zbe::PRECISION_DIGITS;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "First Normal Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 50;
  nsphere.c[1] = 120;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 80;
  nsphere.c[1] = 90;
  nsphere.r = 10;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
}

TEST(Intersections, RayAABB) {
  zbe::Ray<2> ray{{20,30},{50,100}};
  zbe::AABB<2> aabb{{10,90},{60,100}};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 1 << zbe::PRECISION_DIGITS;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(1,result) << "First Ray vs AABB collision.";
  EXPECT_DOUBLE_EQ(6 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(90,p[1]) << "Point of collision (y).";

  t = 1 << zbe::PRECISION_DIGITS;
  aabb.minimum[0] = 51;
  aabb.minimum[1] = 80;
  aabb.maximum[0] = 100;
  aabb.maximum[1] = 90;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(0,result) << "Second Ray vs AABB collision.";
}

TEST(Intersections, MovingCircleOutsideAABB) {
  zbe::Circle ball{{20,30},10};
  zbe::Vector2D velocity{30,40};
  zbe::AABB2D block{{10,50},{60,100}};
  bool result;
  zbe::Point2D p;
  uint64_t t = 1 << zbe::PRECISION_DIGITS;

  result = IntersectionMovingCircleOutsideAABB2D(ball, velocity, block, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(25 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(275,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(500,p[1]) << "Point of collision (y).";
}

TEST(Intersections, DISABLED_MovingCircleInsideAABB) {
  // TODO mas test de colisiones y mas robustos
}
