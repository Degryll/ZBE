#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"

// Ray

TEST(Ray, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Ray<2> p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Ray<2> q{{3.0,4.0},{2.0,5.3}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Ray<3> r({{3.0,4.0,5.0},{1.0,6.0,8.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Ray<2> s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point<3> o;
  zbe::Vector<3> d;
  zbe::Ray<3> ray(o,d);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::Ray<3> t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Ray<2> u({{3.0,4.0,5.0},{3.0,2.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Ray2D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Ray2D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Ray2D q{{3.0,4.0},{2.0,5.3}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Ray2D r({{3.0,4.0},{1.0,6.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Ray2D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point2D o;
  zbe::Vector2D d;
  zbe::Ray2D ray(o,d);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::Ray2D t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Ray2D u({{3.0,4.0,5.0},{3.0,2.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Ray3D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Ray3D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Ray3D q{{3.0,4.0,5.0},{1.0,2.0,6.0}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Ray3D r({{3.0,4.0,5.0},{1.0,2.0,6.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Ray3D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point3D o;
  zbe::Vector3D d;
  zbe::Ray3D ray(o,d);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::Ray3D t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Ray3D u({{3.0,4.0,5.0,6.0},{3.0,2.0,1.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Ray, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Ray<s>

  zbe::Ray<3> p{{3.0,4.0,5.0},{13.0,11.0,7.0}};
  EXPECT_EQ( 3.0,p.o[0]) << "[Ray<3>] Access with operator[].";
  EXPECT_EQ( 4.0,p.o[1]) << "[Ray<3>] Access with operator[](2).";
  EXPECT_EQ( 5.0,p.o[2]) << "[Ray<3>] Access with operator[](3).";
  EXPECT_EQ(13.0,p.d[0]) << "[Ray<3>] Access with operator[].";
  EXPECT_EQ(11.0,p.d[1]) << "[Ray<3>] Access with operator[](2).";
  EXPECT_EQ( 7.0,p.d[2]) << "[Ray<3>] Access with operator[](3).";

  p.o[0] = 6.0;
  p.o[1] = 7.0;
  p.o[2] = 8.0;
  p.d[0] = 1.0;
  p.d[1] = 3.0;
  p.d[2] = 2.0;

  EXPECT_EQ(6.0,p.o[0]) << "[Ray<3>] Modify data through operator[].";
  EXPECT_EQ(7.0,p.o[1]) << "[Ray<3>] Modify data through operator[](2).";
  EXPECT_EQ(8.0,p.o[2]) << "[Ray<3>] Modify data through operator[](3)";
  EXPECT_EQ(1.0,p.d[0]) << "[Ray<3>] Modify data through operator[](4)";
  EXPECT_EQ(3.0,p.d[1]) << "[Ray<3>] Modify data through operator[](5)";
  EXPECT_EQ(2.0,p.d[2]) << "[Ray<3>] Modify data through operator[](6)";

  zbe::Ray<3> q;
  q = p;

  EXPECT_EQ(6.0,q.o[0]) << "[Ray<3>] Copy assignation.";
  EXPECT_EQ(7.0,q.o[1]) << "[Ray<3>] Copy assignation(2).";
  EXPECT_EQ(8.0,q.o[2]) << "[Ray<3>] Copy assignation(3).";
  EXPECT_EQ(1.0,q.d[0]) << "[Ray<3>] Copy assignation(4).";
  EXPECT_EQ(3.0,q.d[1]) << "[Ray<3>] Copy assignation(5).";
  EXPECT_EQ(2.0,q.d[2]) << "[Ray<3>] Copy assignation(6).";

  // Ray2D

  zbe::Ray2D p2{{3.0,4.0},{13.0,11.0}};
  EXPECT_EQ( 3.0,p2.o[0]) << "[Ray2D] Access with operator[].";
  EXPECT_EQ( 4.0,p2.o[1]) << "[Ray2D] Access with operator[](2).";
  EXPECT_EQ(13.0,p2.d[0]) << "[Ray2D] Access with operator[](3).";
  EXPECT_EQ(11.0,p2.d[1]) << "[Ray2D] Access with operator[](4).";

  EXPECT_EQ( 3.0,p2.o.x) << "[Ray2D] Access with alias \".x\".";
  EXPECT_EQ( 4.0,p2.o.y) << "[Ray2D] Access with alias \".y\".";
  EXPECT_EQ(13.0,p2.d.x) << "[Ray2D] Access with alias \".x\"(2).";
  EXPECT_EQ(11.0,p2.d.y) << "[Ray2D] Access with alias \".y\"(2).";

  p2.o[0] = 6.0;
  p2.o[1] = 7.0;
  p2.d[0] = 1.0;
  p2.d[1] = 3.0;

  EXPECT_EQ(6.0,p2.o[0]) << "[Ray2D] Modify data through operator[].";
  EXPECT_EQ(7.0,p2.o[1]) << "[Ray2D] Modify data through operator[](2).";
  EXPECT_EQ(1.0,p2.d[0]) << "[Ray2D] Modify data through operator[](3).";
  EXPECT_EQ(3.0,p2.d[1]) << "[Ray2D] Modify data through operator[](4).";

  EXPECT_EQ(6.0,p2.o.x) << "[Ray2D] Modify data through alias \".x\".";
  EXPECT_EQ(7.0,p2.o.y) << "[Ray2D] Modify data through alias \".y\".";
  EXPECT_EQ(1.0,p2.d.x) << "[Ray2D] Modify data through alias \".x\"(2).";
  EXPECT_EQ(3.0,p2.d.y) << "[Ray2D] Modify data through alias \".y\"(2).";

  zbe::Ray<2> q2;
  q2 = p2;

  EXPECT_EQ(6.0,q2.o[0]) << "[Ray2D] Copy assignation.";
  EXPECT_EQ(7.0,q2.o[1]) << "[Ray2D] Copy assignation(2).";
  EXPECT_EQ(1.0,q2.d[0]) << "[Ray2D] Copy assignation(3).";
  EXPECT_EQ(3.0,q2.d[1]) << "[Ray2D] Copy assignation(4).";

  // Ray3D

  zbe::Ray3D p3{{3.0,4.0,5.0},{13.0,11.0,7.0}};
  EXPECT_EQ( 3.0,p3.o[0]) << "[Ray3D] Access with operator[].";
  EXPECT_EQ( 4.0,p3.o[1]) << "[Ray3D] Access with operator[](2).";
  EXPECT_EQ( 5.0,p3.o[2]) << "[Ray3D] Access with operator[](3).";
  EXPECT_EQ(13.0,p3.d[0]) << "[Ray3D] Access with operator[](4).";
  EXPECT_EQ(11.0,p3.d[1]) << "[Ray3D] Access with operator[](5).";
  EXPECT_EQ( 7.0,p3.d[2]) << "[Ray3D] Access with operator[](6).";

  EXPECT_EQ( 3.0,p3.o.x) << "[Ray3D] Access with alias \".x\".";
  EXPECT_EQ( 4.0,p3.o.y) << "[Ray3D] Access with alias \".y\".";
  EXPECT_EQ( 5.0,p3.o.z) << "[Ray3D] Access with alias \".z\".";
  EXPECT_EQ(13.0,p3.d.x) << "[Ray3D] Access with alias \".x\"(2).";
  EXPECT_EQ(11.0,p3.d.y) << "[Ray3D] Access with alias \".y\"(2).";
  EXPECT_EQ( 7.0,p3.d.z) << "[Ray3D] Access with alias \".z\"(2).";

  p3.o[0] = 6.0;
  p3.o[1] = 7.0;
  p3.o[2] = 8.0;
  p3.d[0] = 1.0;
  p3.d[1] = 3.0;
  p3.d[2] = 2.0;

  EXPECT_EQ(6.0,p3.o[0]) << "[Ray3D] Modify data through operator[].";
  EXPECT_EQ(7.0,p3.o[1]) << "[Ray3D] Modify data through operator[](2).";
  EXPECT_EQ(8.0,p3.o[2]) << "[Ray3D] Modify data through operator[](3).";
  EXPECT_EQ(1.0,p3.d[0]) << "[Ray3D] Modify data through operator[](4).";
  EXPECT_EQ(3.0,p3.d[1]) << "[Ray3D] Modify data through operator[](5).";
  EXPECT_EQ(2.0,p3.d[2]) << "[Ray3D] Modify data through operator[](6).";

  EXPECT_EQ(6.0,p3.o.x) << "[Ray3D] Modify data through alias \".x\".";
  EXPECT_EQ(7.0,p3.o.y) << "[Ray3D] Modify data through alias \".y\".";
  EXPECT_EQ(8.0,p3.o.z) << "[Ray3D] Modify data through alias \".z\".";
  EXPECT_EQ(1.0,p3.d.x) << "[Ray3D] Modify data through alias \".x\"(2).";
  EXPECT_EQ(3.0,p3.d.y) << "[Ray3D] Modify data through alias \".y\"(2).";
  EXPECT_EQ(2.0,p3.d.z) << "[Ray3D] Modify data through alias \".z\"(2).";

  zbe::Ray<3> q3;
  q3 = p3;

  EXPECT_EQ(6.0,q3.o[0]) << "[Ray3D] Copy assignation.";
  EXPECT_EQ(7.0,q3.o[1]) << "[Ray3D] Copy assignation(2).";
  EXPECT_EQ(8.0,q3.o[2]) << "[Ray3D] Copy assignation(3).";
  EXPECT_EQ(1.0,q3.d[0]) << "[Ray3D] Copy assignation(4).";
  EXPECT_EQ(3.0,q3.d[1]) << "[Ray3D] Copy assignation(5).";
  EXPECT_EQ(2.0,q3.d[2]) << "[Ray3D] Copy assignation(6).";

  zbe::SysError::clear();
}

// NSphere
TEST(NSphere, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::NSphere<2> p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::NSphere<2> q{{3.0,4.0},2.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::NSphere<3> r({{3.0,4.0,5.0},1.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::NSphere<2> s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point<3> c;
  zbe::NSphere<3> nsphere(c,2.5);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::NSphere<3> t({{3.0,4.0},2.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::NSphere<2> u({{3.0,4.0,5.0},3.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Circle, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Circle p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Circle q{{3.0,4.0},2.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Circle r({{3.0,4.0},1.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Circle s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point2D c;
  zbe::Circle circle(c,1.3);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::Circle t({{3.0,4.0,5.9},2.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::SysError::clear();
}

TEST(Sphere, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Sphere p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Sphere q{{3.0,4.0,5.0},1.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Sphere r({{3.0,4.0,5.0},1.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Sphere s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point3D c;
  zbe::Sphere sphere(c,3.2);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::Sphere t({{3.0,4.0},2.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Sphere u({{3.0,4.0,5.0,6.0},3.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(NSphere, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // NSphere<s>

  zbe::NSphere<3> p{{3.0,4.0,5.0},13.0};
  EXPECT_EQ( 3.0,p.c[0]) << "[NSphere<3>] Access with operator[].";
  EXPECT_EQ( 4.0,p.c[1]) << "[NSphere<3>] Access with operator[](2).";
  EXPECT_EQ( 5.0,p.c[2]) << "[NSphere<3>] Access with operator[](3).";
  EXPECT_EQ(13.0,p.r)    << "[NSphere<3>] Access with operator[](4).";

  p.c[0] = 6.0;
  p.c[1] = 7.0;
  p.c[2] = 8.0;
  p.r = 1.0;

  EXPECT_EQ(6.0,p.c[0]) << "[NSphere<3>] Modify data through operator[].";
  EXPECT_EQ(7.0,p.c[1]) << "[NSphere<3>] Modify data through operator[](2).";
  EXPECT_EQ(8.0,p.c[2]) << "[NSphere<3>] Modify data through operator[](3)";
  EXPECT_EQ(1.0,p.r)    << "[NSphere<3>] Modify data through operator[](4)";

  zbe::NSphere<3> q;
  q = p;

  EXPECT_EQ(6.0,q.c[0]) << "[NSphere<3>] Copy assignation.";
  EXPECT_EQ(7.0,q.c[1]) << "[NSphere<3>] Copy assignation(2).";
  EXPECT_EQ(8.0,q.c[2]) << "[NSphere<3>] Copy assignation(3).";
  EXPECT_EQ(1.0,q.r)    << "[NSphere<3>] Copy assignation(4).";

  // Circle

  zbe::Circle p2{{3.0,4.0},13.0};
  EXPECT_EQ( 3.0,p2.c[0]) << "[Circle] Access with operator[].";
  EXPECT_EQ( 4.0,p2.c[1]) << "[Circle] Access with operator[](2).";
  EXPECT_EQ(13.0,p2.r)    << "[Circle] Access with operator[](3).";

  EXPECT_EQ( 3.0,p2.c.x) << "[Circle] Access with alias \".x\".";
  EXPECT_EQ( 4.0,p2.c.y) << "[Circle] Access with alias \".y\".";

  p2.c[0] = 6.0;
  p2.c[1] = 7.0;
  p2.r = 1.0;

  EXPECT_EQ(6.0,p2.c[0]) << "[Circle] Modify data through operator[].";
  EXPECT_EQ(7.0,p2.c[1]) << "[Circle] Modify data through operator[](2).";
  EXPECT_EQ(1.0,p2.r)    << "[Circle] Modify data through operator[](3).";

  EXPECT_EQ(6.0,p2.c.x) << "[Circle] Modify data through alias \".x\".";
  EXPECT_EQ(7.0,p2.c.y) << "[Circle] Modify data through alias \".y\".";

  zbe::NSphere<2> q2;
  q2 = p2;

  EXPECT_EQ(6.0,q2.c[0]) << "[Circle] Copy assignation.";
  EXPECT_EQ(7.0,q2.c[1]) << "[Circle] Copy assignation(2).";
  EXPECT_EQ(1.0,q2.r)    << "[Circle] Copy assignation(3).";

  // Sphere

  zbe::Sphere p3{{3.0,4.0,5.0},13.0};
  EXPECT_EQ( 3.0,p3.c[0]) << "[Sphere] Access with operator[].";
  EXPECT_EQ( 4.0,p3.c[1]) << "[Sphere] Access with operator[](2).";
  EXPECT_EQ( 5.0,p3.c[2]) << "[Sphere] Access with operator[](3).";
  EXPECT_EQ(13.0,p3.r)    << "[Sphere] Access with operator[](4).";

  EXPECT_EQ( 3.0,p3.c.x) << "[Sphere] Access with alias \".x\".";
  EXPECT_EQ( 4.0,p3.c.y) << "[Sphere] Access with alias \".y\".";
  EXPECT_EQ( 5.0,p3.c.z) << "[Sphere] Access with alias \".z\".";

  p3.c[0] = 6.0;
  p3.c[1] = 7.0;
  p3.c[2] = 8.0;
  p3.r = 1.0;

  EXPECT_EQ(6.0,p3.c[0]) << "[Sphere] Modify data through operator[].";
  EXPECT_EQ(7.0,p3.c[1]) << "[Sphere] Modify data through operator[](2).";
  EXPECT_EQ(8.0,p3.c[2]) << "[Sphere] Modify data through operator[](3).";
  EXPECT_EQ(1.0,p3.r)    << "[Sphere] Modify data through operator[](4).";

  EXPECT_EQ(6.0,p3.c.x) << "[Sphere] Modify data through \".x\".";
  EXPECT_EQ(7.0,p3.c.y) << "[Sphere] Modify data through \".y\".";
  EXPECT_EQ(8.0,p3.c.z) << "[Sphere] Modify data through \".z\".";

  zbe::NSphere<3> q3;
  q3 = p3;

  EXPECT_EQ(6.0,q3.c[0]) << "[Sphere] Copy assignation.";
  EXPECT_EQ(7.0,q3.c[1]) << "[Sphere] Copy assignation(2).";
  EXPECT_EQ(8.0,q3.c[2]) << "[Sphere] Copy assignation(3).";
  EXPECT_EQ(1.0,q3.r)    << "[Sphere] Copy assignation(4).";

  zbe::SysError::clear();
}

TEST(AABB, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::AABB<2> p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::AABB<2> q{{3.0,4.0},{2.0,5.3}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::AABB<3> r({{3.0,4.0,5.0},{1.0,6.0,8.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::AABB<2> s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point<3> pmin;
  zbe::Point<3> pmax;
  zbe::AABB<3> aabb(pmin,pmax);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::AABB<3> t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::AABB<2> u({{3.0,4.0,5.0},{3.0,2.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(AABB2D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::AABB2D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::AABB2D q{{3.0,4.0},{2.0,5.3}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::AABB2D r({{3.0,4.0},{1.0,6.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::AABB2D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point2D pmin;
  zbe::Point2D pmax;
  zbe::AABB2D aabb2D(pmin,pmax);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::AABB2D t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::AABB2D u({{3.0,4.0,5.0},{3.0,2.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(AABB3D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::AABB3D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::AABB3D q{{3.0,4.0,5.0},{1.0,2.0,6.0}};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::AABB3D r({{3.0,4.0,5.0},{1.0,2.0,6.0}});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::AABB3D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point3D pmin;
  zbe::Point3D pmax;
  zbe::AABB3D aabb3D(pmin,pmax);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Parametrized constructor.";

  zbe::AABB3D t({{3.0,4.0},{2.0,5.0,9.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::AABB3D u({{3.0,4.0,5.0,6.0},{3.0,2.0,1.0}});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(AABB, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // AABB<s>

  zbe::AABB<3> p{{3.0,4.0,5.0},{13.0,11.0,7.0}};
  EXPECT_EQ( 3.0,p.minimum[0]) << "[AABB<3>] Access minimum with operator[].";
  EXPECT_EQ( 4.0,p.minimum[1]) << "[AABB<3>] Access minimum with operator[](2).";
  EXPECT_EQ( 5.0,p.minimum[2]) << "[AABB<3>] Access minimum with operator[](3).";
  EXPECT_EQ(13.0,p.maximum[0]) << "[AABB<3>] Access maximum with operator[].";
  EXPECT_EQ(11.0,p.maximum[1]) << "[AABB<3>] Access maximum with operator[](2).";
  EXPECT_EQ( 7.0,p.maximum[2]) << "[AABB<3>] Access maximum with operator[](3).";

  p.minimum[0] = 6.0;
  p.minimum[1] = 7.0;
  p.minimum[2] = 8.0;
  p.maximum[0] = 1.0;
  p.maximum[1] = 3.0;
  p.maximum[2] = 2.0;

  EXPECT_EQ(6.0,p.minimum[0]) << "[AABB<3>] Modify minimum data through operator[].";
  EXPECT_EQ(7.0,p.minimum[1]) << "[AABB<3>] Modify minimum data through operator[](2).";
  EXPECT_EQ(8.0,p.minimum[2]) << "[AABB<3>] Modify minimum data through operator[](3).";
  EXPECT_EQ(1.0,p.maximum[0]) << "[AABB<3>] Modify maximum data through operator[](.";
  EXPECT_EQ(3.0,p.maximum[1]) << "[AABB<3>] Modify maximum data through operator[](2).";
  EXPECT_EQ(2.0,p.maximum[2]) << "[AABB<3>] Modify maximum data through operator[](3).";

  zbe::AABB<3> q;
  q = p;

  EXPECT_EQ(6.0,q.minimum[0]) << "[AABB<3>] Copy assignation.";
  EXPECT_EQ(7.0,q.minimum[1]) << "[AABB<3>] Copy assignation(2).";
  EXPECT_EQ(8.0,q.minimum[2]) << "[AABB<3>] Copy assignation(3).";
  EXPECT_EQ(1.0,q.maximum[0]) << "[AABB<3>] Copy assignation(4).";
  EXPECT_EQ(3.0,q.maximum[1]) << "[AABB<3>] Copy assignation(5).";
  EXPECT_EQ(2.0,q.maximum[2]) << "[AABB<3>] Copy assignation(6).";

  // AABB2D

  zbe::AABB2D p2{{3.0,4.0},{13.0,11.0}};
  EXPECT_EQ( 3.0,p2.minimum[0]) << "[AABB2D] Access minimum with operator[].";
  EXPECT_EQ( 4.0,p2.minimum[1]) << "[AABB2D] Access minimum with operator[](2).";
  EXPECT_EQ(13.0,p2.maximum[0]) << "[AABB2D] Access maximum with operator[].";
  EXPECT_EQ(11.0,p2.maximum[1]) << "[AABB2D] Access maximum with operator[](2).";

  EXPECT_EQ( 3.0,p2.minimum.x) << "[AABB2D] Access minimum with alias \".x\".";
  EXPECT_EQ( 4.0,p2.minimum.y) << "[AABB2D] Access minimum with alias \".y\".";
  EXPECT_EQ(13.0,p2.maximum.x) << "[AABB2D] Access maximum with alias \".x\".";
  EXPECT_EQ(11.0,p2.maximum.y) << "[AABB2D] Access maximum with alias \".y\".";

  p2.minimum[0] = 6.0;
  p2.minimum[1] = 7.0;
  p2.maximum[0] = 1.0;
  p2.maximum[1] = 3.0;

  EXPECT_EQ(6.0,p2.minimum[0]) << "[AABB2D] Modify minimum data through operator[].";
  EXPECT_EQ(7.0,p2.minimum[1]) << "[AABB2D] Modify minimum data through operator[](2).";
  EXPECT_EQ(1.0,p2.maximum[0]) << "[AABB2D] Modify maximum data through operator[].";
  EXPECT_EQ(3.0,p2.maximum[1]) << "[AABB2D] Modify maximum data through operator[](2).";

  EXPECT_EQ(6.0,p2.minimum.x) << "[AABB2D] Modify minimum data through alias \".x\".";
  EXPECT_EQ(7.0,p2.minimum.y) << "[AABB2D] Modify minimum data through alias \".y\".";
  EXPECT_EQ(1.0,p2.maximum.x) << "[AABB2D] Modify maximum data through alias \".x\".";
  EXPECT_EQ(3.0,p2.maximum.y) << "[AABB2D] Modify maximum data through alias \".y\".";

  zbe::AABB<2> q2;
  q2 = p2;

  EXPECT_EQ(6.0,q2.minimum[0]) << "[AABB2D] Copy assignation.";
  EXPECT_EQ(7.0,q2.minimum[1]) << "[AABB2D] Copy assignation(2).";
  EXPECT_EQ(1.0,q2.maximum[0]) << "[AABB2D] Copy assignation(3).";
  EXPECT_EQ(3.0,q2.maximum[1]) << "[AABB2D] Copy assignation(4).";

  // AABB3D

  zbe::AABB3D p3{{3.0,4.0,5.0},{13.0,11.0,7.0}};
  EXPECT_EQ( 3.0,p3.minimum[0]) << "[AABB3D] Access with operator[].";
  EXPECT_EQ( 4.0,p3.minimum[1]) << "[AABB3D] Access with operator[](2).";
  EXPECT_EQ( 5.0,p3.minimum[2]) << "[AABB3D] Access with operator[](3).";
  EXPECT_EQ(13.0,p3.maximum[0]) << "[AABB3D] Access with operator[](4).";
  EXPECT_EQ(11.0,p3.maximum[1]) << "[AABB3D] Access with operator[](5).";
  EXPECT_EQ( 7.0,p3.maximum[2]) << "[AABB3D] Access with operator[](6).";

  EXPECT_EQ( 3.0,p3.minimum.x) << "[AABB3D] Access with alias \".x\".";
  EXPECT_EQ( 4.0,p3.minimum.y) << "[AABB3D] Access with alias \".y\".";
  EXPECT_EQ( 5.0,p3.minimum.z) << "[AABB3D] Access with alias \".z\".";
  EXPECT_EQ(13.0,p3.maximum.x) << "[AABB3D] Access with alias \".x\"(2).";
  EXPECT_EQ(11.0,p3.maximum.y) << "[AABB3D] Access with alias \".y\"(2).";
  EXPECT_EQ( 7.0,p3.maximum.z) << "[AABB3D] Access with alias \".z\"(2).";

  p3.minimum[0] = 6.0;
  p3.minimum[1] = 7.0;
  p3.minimum[2] = 8.0;
  p3.maximum[0] = 1.0;
  p3.maximum[1] = 3.0;
  p3.maximum[2] = 2.0;

  EXPECT_EQ(6.0,p3.minimum[0]) << "[AABB3D] Modify data through operator[].";
  EXPECT_EQ(7.0,p3.minimum[1]) << "[AABB3D] Modify data through operator[](2).";
  EXPECT_EQ(8.0,p3.minimum[2]) << "[AABB3D] Modify data through operator[](3).";
  EXPECT_EQ(1.0,p3.maximum[0]) << "[AABB3D] Modify data through operator[](4).";
  EXPECT_EQ(3.0,p3.maximum[1]) << "[AABB3D] Modify data through operator[](5).";
  EXPECT_EQ(2.0,p3.maximum[2]) << "[AABB3D] Modify data through operator[](6).";

  EXPECT_EQ(6.0,p3.minimum.x) << "[AABB3D] Modify data through alias \".x\".";
  EXPECT_EQ(7.0,p3.minimum.y) << "[AABB3D] Modify data through alias \".y\".";
  EXPECT_EQ(8.0,p3.minimum.z) << "[AABB3D] Modify data through alias \".z\".";
  EXPECT_EQ(1.0,p3.maximum.x) << "[AABB3D] Modify data through alias \".x\"(2).";
  EXPECT_EQ(3.0,p3.maximum.y) << "[AABB3D] Modify data through alias \".y\"(2).";
  EXPECT_EQ(2.0,p3.maximum.z) << "[AABB3D] Modify data through alias \".z\"(2).";

  zbe::AABB<3> q3;
  q3 = p3;

  EXPECT_EQ(6.0,q3.minimum[0]) << "[AABB3D] Copy assignation.";
  EXPECT_EQ(7.0,q3.minimum[1]) << "[AABB3D] Copy assignation(2).";
  EXPECT_EQ(8.0,q3.minimum[2]) << "[AABB3D] Copy assignation(3).";
  EXPECT_EQ(1.0,q3.maximum[0]) << "[AABB3D] Copy assignation(4).";
  EXPECT_EQ(3.0,q3.maximum[1]) << "[AABB3D] Copy assignation(5).";
  EXPECT_EQ(2.0,q3.maximum[2]) << "[AABB3D] Copy assignation(6).";

  zbe::SysError::clear();
}
