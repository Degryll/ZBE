#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

TEST(Point, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Point<2> p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Point<2> q{30,40};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Point<3> r({30,40,50});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Point<2> s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point<3> t({30,40});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Point<2> u({30,40,50});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Point2D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Point2D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Point2D q{30,40};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Point2D r({30,40});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Point2D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point2D t({30,40,50});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Point2D u({30});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Point3D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Point3D p;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Point3D q{30,40,50};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Point3D r({30,40,50});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Point3D s(q);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Point3D t({30,40});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Point3D u({30,40,50,60});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Point, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Point<s>

  zbe::Point<3> p{30,40,50};
  EXPECT_EQ(30,p[0]) << "[Point<3>] Access with operator[].";
  EXPECT_EQ(40,p[1]) << "[Point<3>] Access with operator[](2).";
  EXPECT_EQ(50,p[2]) << "[Point<3>] Access with operator[](3).";

  p[0] = 60;
  p[1] = 70;
  p[2] = 80;

  EXPECT_EQ(60,p[0]) << "[Point<3>] Modify data through operator[].";
  EXPECT_EQ(70,p[1]) << "[Point<3>] Modify data through operator[](2).";
  EXPECT_EQ(80,p[2]) << "[Point<3>] Modify data through operator[](3)";

  zbe::Point<3> q;
  q = p;

  EXPECT_EQ(60,q[0]) << "[Point<3>] Copy assignation.";
  EXPECT_EQ(70,q[1]) << "[Point<3>] Copy assignation(2).";
  EXPECT_EQ(80,q[2]) << "[Point<3>] Copy assignation(3).";

  // Point2D

  zbe::Point2D p2{30,40};
  EXPECT_EQ(30,p2[0]) << "[Point2D] Access with operator[].";
  EXPECT_EQ(40,p2[1]) << "[Point2D] Access with operator[](2).";

  EXPECT_EQ(30,p2.x) << "[Point2D] Access with \".x\".";
  EXPECT_EQ(40,p2.y) << "[Point2D] Access with \".y\".";

  p2[0] = 60;
  p2[1] = 70;

  EXPECT_EQ(60,p2.x) << "[Point2D] Modify data through operator[].";
  EXPECT_EQ(70,p2.y) << "[Point2D] Modify data through operator[](2).";

  p2.x = 20;
  p2.y = 30;

  EXPECT_EQ(20,p2.x) << "[Point2D] Modify data through \".x\".";
  EXPECT_EQ(30,p2.y) << "[Point2D] Modify data through \".y\".";

  zbe::Point<2> q2;
  q2 = p2;

  EXPECT_EQ(20,q2[0]) << "[Point2D] Copy assignation.";
  EXPECT_EQ(30,q2[1]) << "[Point2D] Copy assignation(2).";

  // Point3D

  zbe::Point3D p3{30,40,50};
  EXPECT_EQ(30,p3[0]) << "[Point3D] Access with operator[].";
  EXPECT_EQ(40,p3[1]) << "[Point3D] Access with operator[](2).";
  EXPECT_EQ(50,p3[2]) << "[Point3D] Access with operator[](3).";

  EXPECT_EQ(30,p3.x) << "[Point3D] Access with \".x\".";
  EXPECT_EQ(40,p3.y) << "[Point3D] Access with \".y\".";
  EXPECT_EQ(50,p3.z) << "[Point3D] Access with \".z\".";

  p3[0] = 60;
  p3[1] = 70;
  p3[2] = 80;

  EXPECT_EQ(60,p3.x) << "[Point3D] Modify data through operator[].";
  EXPECT_EQ(70,p3.y) << "[Point3D] Modify data through operator[](2).";
  EXPECT_EQ(80,p3.z) << "[Point3D] Modify data through operator[](3)";

  p3.x = 20;
  p3.y = 30;
  p3.z = 40;

  EXPECT_EQ(20,p3.x) << "[Point3D] Modify data through \".x\".";
  EXPECT_EQ(30,p3.y) << "[Point3D] Modify data through \".y\".";
  EXPECT_EQ(40,p3.z) << "[Point3D] Modify data through \".z\".";

  zbe::Point<3> q3;
  q3 = p3;

  EXPECT_EQ(20,q3[0]) << "[Point3D] Copy assignation.";
  EXPECT_EQ(30,q3[1]) << "[Point3D] Copy assignation(2).";
  EXPECT_EQ(40,q3[2]) << "[Point3D] Copy assignation(3).";

  zbe::SysError::clear();
}

TEST(Point, Operations) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Point3D p{30,40,50};

  p *= int64_t(2);
  EXPECT_EQ( 60,p.x) << "Operator *= \".x\".";
  EXPECT_EQ( 80,p.y) << "Operator *= \".y\".";
  EXPECT_EQ(100,p.z) << "Operator *= \".z\".";

  zbe::Vector3D v{20,50,10};

  zbe::Point3D q;

  q = p + v;

  EXPECT_EQ( 80,q.x) << "Operator + \".x\".";
  EXPECT_EQ(130,q.y) << "Operator + \".y\".";
  EXPECT_EQ(110,q.z) << "Operator + \".z\".";

  q += v;

  EXPECT_EQ(100,q.x) << "Operator += \".x\".";
  EXPECT_EQ(180,q.y) << "Operator += \".y\".";
  EXPECT_EQ(120,q.z) << "Operator += \".z\".";

  p = q * int64_t(-1);

  EXPECT_EQ(-100,p.x) << "Operator * \".x\".";
  EXPECT_EQ(-180,p.y) << "Operator * \".y\".";
  EXPECT_EQ(-120,p.z) << "Operator * \".z\".";

  zbe::SysError::clear();
}
