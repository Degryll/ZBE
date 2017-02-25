#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

TEST(Vector, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector<2> u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector<2> v{30,40};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector<3> w({30,40,50});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector<2> s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector<3> t({30,40});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector<2> bad({30,40,50});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector2D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector2D u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector2D v{30,40};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector2D w({30,40});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector2D s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector2D t({30,40,50});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector2D bad({30});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector3D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector3D u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector3D v{30,40,50};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector3D w({30,40,50});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector3D s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector3D t({30,40});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector3D bad({30,40,50,60});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Vector<s>

  zbe::Vector<3> u{30,40,50};
  EXPECT_EQ(30,u[0]) << "[Vector<3>] Access with operator[].";
  EXPECT_EQ(40,u[1]) << "[Vector<3>] Access with operator[](2).";
  EXPECT_EQ(50,u[2]) << "[Vector<3>] Access with operator[](3).";

  u[0] = 60;
  u[1] = 70;
  u[2] = 80;

  EXPECT_EQ(60,u[0]) << "[Vector<3>] Modify data through operator[].";
  EXPECT_EQ(70,u[1]) << "[Vector<3>] Modify data through operator[](2).";
  EXPECT_EQ(80,u[2]) << "[Vector<3>] Modify data through operator[](3)";

  zbe::Vector<3> v;
  v = u;

  EXPECT_EQ(60,v[0]) << "[Vector<3>] Copy assignation.";
  EXPECT_EQ(70,v[1]) << "[Vector<3>] Copy assignation(2).";
  EXPECT_EQ(80,v[2]) << "[Vector<3>] Copy assignation(3).";

  // Vector2D

  zbe::Vector2D u2{30,40};
  EXPECT_EQ(30,u2[0]) << "[Vector2D] Access with operator[].";
  EXPECT_EQ(40,u2[1]) << "[Vector2D] Access with operator[](2).";

  EXPECT_EQ(30,u2.x) << "[Vector2D] Access with \".x\".";
  EXPECT_EQ(40,u2.y) << "[Vector2D] Access with \".y\".";

  u2[0] = 60;
  u2[1] = 70;

  EXPECT_EQ(60,u2.x) << "[Vector2D] Modify data through operator[].";
  EXPECT_EQ(70,u2.y) << "[Vector2D] Modify data through operator[](2).";

  u2.x = 20;
  u2.y = 30;

  EXPECT_EQ(20,u2.x) << "[Vector2D] Modify data through \".x\".";
  EXPECT_EQ(30,u2.y) << "[Vector2D] Modify data through \".y\".";

  zbe::Vector<2> v2;
  v2 = u2;

  EXPECT_EQ(20,v2[0]) << "[Vector2D] Copy assignation.";
  EXPECT_EQ(30,v2[1]) << "[Vector2D] Copy assignation(2).";

  // Vector3D

  zbe::Vector3D u3{30,40,50};
  EXPECT_EQ(30,u3[0]) << "[Vector3D] Access with operator[].";
  EXPECT_EQ(40,u3[1]) << "[Vector3D] Access with operator[](2).";
  EXPECT_EQ(50,u3[2]) << "[Vector3D] Access with operator[](3).";

  EXPECT_EQ(30,u3.x) << "[Vector3D] Access with \".x\".";
  EXPECT_EQ(40,u3.y) << "[Vector3D] Access with \".y\".";
  EXPECT_EQ(50,u3.z) << "[Vector3D] Access with \".z\".";

  u3[0] = 60;
  u3[1] = 70;
  u3[2] = 80;

  EXPECT_EQ(60,u3.x) << "[Vector3D] Modify data through operator[].";
  EXPECT_EQ(70,u3.y) << "[Vector3D] Modify data through operator[](2).";
  EXPECT_EQ(80,u3.z) << "[Vector3D] Modify data through operator[](3)";

  u3.x = 20;
  u3.y = 30;
  u3.z = 40;

  EXPECT_EQ(20,u3.x) << "[Vector3D] Modify data through \".x\".";
  EXPECT_EQ(30,u3.y) << "[Vector3D] Modify data through \".y\".";
  EXPECT_EQ(40,u3.z) << "[Vector3D] Modify data through \".z\".";

  zbe::Vector<3> v3;
  v3 = u3;

  EXPECT_EQ(20,v3[0]) << "[Vector3D] Copy assignation.";
  EXPECT_EQ(30,v3[1]) << "[Vector3D] Copy assignation(2).";
  EXPECT_EQ(40,v3[2]) << "[Vector3D] Copy assignation(3).";

  zbe::SysError::clear();
}

TEST(Vector, Operations) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector3D u{30,40,50};
  zbe::Vector3D v{0,0,0};

  v += u;

  EXPECT_EQ(30,v.x) << "Operator += \".x\".";
  EXPECT_EQ(40,v.y) << "Operator += \".y\".";
  EXPECT_EQ(50,v.z) << "Operator += \".z\".";

  zbe::Vector3D w;

  w = u + v;

  EXPECT_EQ( 60,w.x) << "Operator + \".x\".";
  EXPECT_EQ( 80,w.y) << "Operator + \".y\".";
  EXPECT_EQ(100,w.z) << "Operator + \".z\".";

  u = -w;

  EXPECT_EQ(- 60,u.x) << "Operator -(unitary) \".x\".";
  EXPECT_EQ(- 80,u.y) << "Operator -(unitary) \".y\".";
  EXPECT_EQ(-100,u.z) << "Operator -(unitary) \".z\".";

  v *= int64_t(5);

  EXPECT_EQ(150,v.x) << "Operator *= \".x\".";
  EXPECT_EQ(200,v.y) << "Operator *= \".y\".";
  EXPECT_EQ(250,v.z) << "Operator *= \".z\".";

  w = v - u;

  EXPECT_EQ(210,w.x) << "Operator - \".x\".";
  EXPECT_EQ(280,w.y) << "Operator - \".y\".";
  EXPECT_EQ(350,w.z) << "Operator - \".z\".";

  w -= v;

  EXPECT_EQ( 60,w.x) << "Operator -= \".x\".";
  EXPECT_EQ( 80,w.y) << "Operator -= \".y\".";
  EXPECT_EQ(100,w.z) << "Operator -= \".z\".";

  zbe::Vector2D v2{3,4};
  EXPECT_EQ(25,v2.getSqrModule()) << "Squared module.";
  EXPECT_EQ( 5,v2.getModule()) << "Module.";

  zbe::Point2D p{30,50};
  zbe::Point2D q{70,20};

  v2 = p - q;

  EXPECT_EQ(-40,v2.x) << "Operator -= \".x\".";
  EXPECT_EQ( 30,v2.y) << "Operator -= \".y\".";

  zbe::Vector2D vr{0,-10000};
  zbe::Vector2D vn{-65536 * 16,-65536 * 16};
  vr.reflect(vn);
  EXPECT_EQ(10000,vr.x) << "reflect \".x\".";
  EXPECT_EQ(0,vr.y) << "reflect  \".y\".";

  vr.setCartesian(10,0);
  vn.setCartesian(0,10);
  vr.reflect(vn);
  EXPECT_EQ(10,vr.x) << "reflect \".x\".";
  EXPECT_EQ(0,vr.y) << "reflect  \".y\".";

  zbe::Vector2D va{65536,65536};
  va.normalize();
  EXPECT_EQ(65536,va.getModule()) << "normalized module";

  zbe::Vector2D vb{0,20};
  vb.normalize();
  EXPECT_EQ(65536,vb.getModule()) << "normalized module";

  zbe::Vector2D vc{20,0};
  vc.normalize();
  EXPECT_EQ(65536,vc.getModule()) << "normalized module";

  zbe::Vector2D vd{20,500};
  vd.normalize();
  EXPECT_EQ(65536,vd.getModule()) << "normalized module";

  zbe::SysError::clear();
}

// TODO operaciones tipicas de Vector2D (polares) y Vector3D(producto vectorial)
