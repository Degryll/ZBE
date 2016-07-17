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

  zbe::Ray<2> ray{{2.0,3.0},{5.0,10.0}};
  zbe::NSphere<2> nsphere{{8.0,9.0},3.0};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 1 * zbe::VELOCITYTOTIME;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "First Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(0.6 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";

  t = 1 * zbe::VELOCITYTOTIME;
  nsphere.c[0] = 5.0;
  nsphere.c[1] = 12.0;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(0.6 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";

  t = 1 * zbe::VELOCITYTOTIME;
  nsphere.c[0] = 8.0;
  nsphere.c[1] = 9.0;
  nsphere.r = 1.0;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";

  zbe::SysError::clear();
}

TEST(Intersections, NormalRaySphere) {
  double m = sqrt(125);
  zbe::Ray<2> ray{{2.0,3.0},{5.0/m,10.0/m}};
  zbe::NSphere<2> nsphere{{8.0,9.0},3.0};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 100 * zbe::VELOCITYTOTIME;

  uint64_t time = 0.6 * m * zbe::VELOCITYTOTIME;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "First Normal Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";

  t = 100 * zbe::VELOCITYTOTIME;
  nsphere.c[0] = 5.0;
  nsphere.c[1] = 12.0;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";

  t = 100 * zbe::VELOCITYTOTIME;
  nsphere.c[0] = 8.0;
  nsphere.c[1] = 9.0;
  nsphere.r = 1.0;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
}

TEST(Intersections, RayAABB) {
  zbe::Ray<2> ray{{2.0,3.0},{5.0,10.0}};
  zbe::AABB<2> aabb{{1.0,9.0},{6.0,10.0}};
  bool result;
  zbe::Point<2> p;
  uint64_t t = 1 * zbe::VELOCITYTOTIME;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(1,result) << "First Ray vs AABB collision.";
  EXPECT_DOUBLE_EQ(0.6 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";

  t = 1 * zbe::VELOCITYTOTIME;
  aabb.minimum[0] = 5.1;
  aabb.minimum[1] = 8.0;
  aabb.maximum[0] = 10.0;
  aabb.maximum[1] = 9.0;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(0,result) << "Second Ray vs AABB collision.";
}

TEST(Intersections, MovingCircleAABB) {
  zbe::Circle ball{{2.0,3.0},1.0};
  zbe::Vector2D velocity{3.0,4.0};
  zbe::AABB2D block{{1.0,5.0},{6.0,10.0}};
  bool result;
  zbe::Point2D p;
  uint64_t t = 1 * zbe::VELOCITYTOTIME;

  result = IntersectionMovingCircleAABB2D(ball, velocity, block, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(0.25 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(2.75,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(5.0,p[1]) << "Point of collision (y).";

  // TODO mas test de colisiones y mas robustos
}
