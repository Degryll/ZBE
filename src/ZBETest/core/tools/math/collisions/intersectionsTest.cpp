//#include "gtest/gtest.h"
//
//#include <cstdint>
//
//#include "ZBE/core/tools/math/math.h"
//
//#include "ZBE/core/system/SysError.h"
//
//#include "ZBE/core/tools/math/Point.h"
//#include "ZBE/core/tools/math/Vector.h"
//#include "ZBE/core/tools/math/objects.h"
//#include "ZBE/core/tools/math/collisions/intersections.h"
//
//TEST(Intersections, RaySphere) {
//  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
//
//  zbe::Ray<2> ray{{2.0,3.0},{5.0,10.0}};
//  zbe::NSphere<2> nsphere{{8.0,9.0},3.0};
//  bool result;
//  zbe::Point<2> p;
//  uint64_t t = 1 * VELOCITYTOTIME;
//
//  result = intersectionRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(1,result) << "First Ray vs Nsphere collision.";
//  EXPECT_DOUBLE_EQ(0.6,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";
//
//  t = 1.0;
//  nsphere.c[0] = 5.0;
//  nsphere.c[1] = 12.0;
//
//  result = intersectionRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
//  EXPECT_DOUBLE_EQ(0.6,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";
//
//  t = 1.0;
//  nsphere.c[0] = 8.0;
//  nsphere.c[1] = 9.0;
//  nsphere.r = 1.0;
//
//  result = intersectionRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
//
//  inline bool intersectionRayCircle(Ray2D ray, Circle circle, double &time, Point2D& point) {return (intersectionRayNSphere<2>(ray,circle,time,point));}
//  inline bool intersectionRaySphere(Ray3D ray, Sphere sphere, double &time, Point3D& point) {return (intersectionRayNSphere<3>(ray,sphere,time,point));}
//
//  zbe::SysError::clear();
//}
//
//TEST(Intersections, NormalRaySphere) {
//  double m = sqrt(125);
//  zbe::Ray<2> ray{{2.0,3.0},{5.0/m,10.0/m}};
//  zbe::NSphere<2> nsphere{{8.0,9.0},3.0};
//  bool result;
//  zbe::Point<2> p;
//  uint64_t t = 100 * VELOCITYTOTIME;
//
//  uint64_t time = 0.6 * m;
//
//  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(1,result) << "First Normal Ray vs Nsphere collision.";
//  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";
//
//  t = 100.0;
//  nsphere.c[0] = 5.0;
//  nsphere.c[1] = 12.0;
//
//  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
//  EXPECT_DOUBLE_EQ(time,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";
//
//  t = 100.0;
//  nsphere.c[0] = 8.0;
//  nsphere.c[1] = 9.0;
//  nsphere.r = 1.0;
//
//  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
//  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
//
//  inline bool intersectionNormalRayCircle(Ray2D ray, Circle circle, double &time, Point2D& point) {return (intersectionNormalRayNSphere<2>(ray,circle,time,point));}
//  inline bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, double &time, Point3D& point) {return (intersectionNormalRayNSphere<3>(ray,sphere,time,point));}
//}
//
//TEST(Intersections, RayAABB) {
//  zbe::Ray<2> ray{{2.0,3.0},{5.0,10.0}};
//  zbe::AABB<2> aabb{{1.0,9.0},{6.0,10.0}};
//  bool result;
//  zbe::Point<2> p;
//  double t = 1.0;
//
//  result = intersectionRayAABB(ray, aabb, t, p);
//  EXPECT_EQ(1,result) << "First Ray vs AABB collision.";
//  EXPECT_DOUBLE_EQ(0.6,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(5.0,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(9.0,p[1]) << "Point of collision (y).";
//
//  t = 1.0;
//  aabb.minimum[0] = 5.1;
//  aabb.minimum[1] = 8.0;
//  aabb.maximum[0] = 10.0;
//  aabb.maximum[1] = 9.0;
//
//  result = intersectionRayAABB(ray, aabb, t, p);
//  EXPECT_EQ(0,result) << "Second Ray vs AABB collision.";
//
//  inline bool intersectionRayAABB2D(Ray2D ray, AABB2D box, double &time, Point2D& point) {return (intersectionRayAABB<2>(ray,box,time,point));}
//  inline bool intersectionRayAABB3D(Ray3D ray, AABB3D box, double &time, Point3D& point) {return (intersectionRayAABB<3>(ray,box,time,point));}
//}
//
//TEST(Intersections, MovingCircleAABB) {
//  zbe::Circle ball{{2.0,3.0},1.0};
//  zbe::Vector2D velocity{3.0,4.0};
//  zbe::AABB2D block{{1.0,5.0},{6.0,10.0}};
//  bool result;
//  zbe::Point2D p;
//  double t = 1.0;
//
//  result = IntersectionMovingCircleAABB2D(ball, velocity, block, t, p);
//  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
//  EXPECT_DOUBLE_EQ(0.25,t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(2.75,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(5.0,p[1]) << "Point of collision (y).";
//
//  TODO mas test de colisiones y mas robustos
//}
