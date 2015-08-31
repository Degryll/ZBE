#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

TEST(Vector, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector<2> u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector<2> v{3.0,4.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector<3> w({3.0,4.0,5.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector<2> s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector<3> t({3.0,4.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector<2> bad({3.0,4.0,5.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector2D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector2D u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector2D v{3.0,4.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector2D w({3.0,4.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector2D s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector2D t({3.0,4.0,5.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector2D bad({3.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector3D, Constructors) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector3D u;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Void constructor.";

  zbe::Vector3D v{3.0,4.0,5.0};
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list constructor.";

  zbe::Vector3D w({3.0,4.0,5.0});
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initializer list(2) constructor.";

  zbe::Vector3D s(v);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Copy constructor.";

  zbe::Vector3D t({3.0,4.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size.";
  zbe::SysError::clear();

  zbe::Vector3D bad({3.0,4.0,5.0,6.0});
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Initializer list with wrong size(2).";

  zbe::SysError::clear();
}

TEST(Vector, DataAccessAssignation) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Vector<s>

  zbe::Vector<3> u{3.0,4.0,5.0};
  EXPECT_EQ(3.0,u[0]) << "[Vector<3>] Access with operator[].";
  EXPECT_EQ(4.0,u[1]) << "[Vector<3>] Access with operator[](2).";
  EXPECT_EQ(5.0,u[2]) << "[Vector<3>] Access with operator[](3).";

  u[0] = 6.0;
  u[1] = 7.0;
  u[2] = 8.0;

  EXPECT_EQ(6.0,u[0]) << "[Vector<3>] Modify data through operator[].";
  EXPECT_EQ(7.0,u[1]) << "[Vector<3>] Modify data through operator[](2).";
  EXPECT_EQ(8.0,u[2]) << "[Vector<3>] Modify data through operator[](3)";

  zbe::Vector<3> v;
  v = u;

  EXPECT_EQ(6.0,v[0]) << "[Vector<3>] Copy assignation.";
  EXPECT_EQ(7.0,v[1]) << "[Vector<3>] Copy assignation(2).";
  EXPECT_EQ(8.0,v[2]) << "[Vector<3>] Copy assignation(3).";

  // Vector2D

  zbe::Vector2D u2{3.0,4.0};
  EXPECT_EQ(3.0,u2[0]) << "[Vector2D] Access with operator[].";
  EXPECT_EQ(4.0,u2[1]) << "[Vector2D] Access with operator[](2).";

  EXPECT_EQ(3.0,u2.x) << "[Vector2D] Access with \".x\".";
  EXPECT_EQ(4.0,u2.y) << "[Vector2D] Access with \".y\".";

  u2[0] = 6.0;
  u2[1] = 7.0;

  EXPECT_EQ(6.0,u2.x) << "[Vector2D] Modify data through operator[].";
  EXPECT_EQ(7.0,u2.y) << "[Vector2D] Modify data through operator[](2).";

  u2.x = 2.0;
  u2.y = 3.0;

  EXPECT_EQ(2.0,u2.x) << "[Vector2D] Modify data through \".x\".";
  EXPECT_EQ(3.0,u2.y) << "[Vector2D] Modify data through \".y\".";

  zbe::Vector<2> v2;
  v2 = u2;

  EXPECT_EQ(2.0,v2[0]) << "[Vector2D] Copy assignation.";
  EXPECT_EQ(3.0,v2[1]) << "[Vector2D] Copy assignation(2).";

  // Vector3D

  zbe::Vector3D u3{3.0,4.0,5.0};
  EXPECT_EQ(3.0,u3[0]) << "[Vector3D] Access with operator[].";
  EXPECT_EQ(4.0,u3[1]) << "[Vector3D] Access with operator[](2).";
  EXPECT_EQ(5.0,u3[2]) << "[Vector3D] Access with operator[](3).";

  EXPECT_EQ(3.0,u3.x) << "[Vector3D] Access with \".x\".";
  EXPECT_EQ(4.0,u3.y) << "[Vector3D] Access with \".y\".";
  EXPECT_EQ(5.0,u3.z) << "[Vector3D] Access with \".z\".";

  u3[0] = 6.0;
  u3[1] = 7.0;
  u3[2] = 8.0;

  EXPECT_EQ(6.0,u3.x) << "[Vector3D] Modify data through operator[].";
  EXPECT_EQ(7.0,u3.y) << "[Vector3D] Modify data through operator[](2).";
  EXPECT_EQ(8.0,u3.z) << "[Vector3D] Modify data through operator[](3)";

  u3.x = 2.0;
  u3.y = 3.0;
  u3.z = 4.0;

  EXPECT_EQ(2.0,u3.x) << "[Vector3D] Modify data through \".x\".";
  EXPECT_EQ(3.0,u3.y) << "[Vector3D] Modify data through \".y\".";
  EXPECT_EQ(4.0,u3.z) << "[Vector3D] Modify data through \".z\".";

  zbe::Vector<3> v3;
  v3 = u3;

  EXPECT_EQ(2.0,v3[0]) << "[Vector3D] Copy assignation.";
  EXPECT_EQ(3.0,v3[1]) << "[Vector3D] Copy assignation(2).";
  EXPECT_EQ(4.0,v3[2]) << "[Vector3D] Copy assignation(3).";

  zbe::SysError::clear();
}

TEST(Vector, Operations) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Vector3D u{3.0,4.0,5.0};
  zbe::Vector3D v{0.0,0.0,0.0};

  v += u;

  EXPECT_EQ(3.0,v.x) << "Operator += \".x\".";
  EXPECT_EQ(4.0,v.y) << "Operator += \".y\".";
  EXPECT_EQ(5.0,v.z) << "Operator += \".z\".";

  zbe::Vector3D w;

  w = u + v;

  EXPECT_EQ( 6.0,w.x) << "Operator + \".x\".";
  EXPECT_EQ( 8.0,w.y) << "Operator + \".y\".";
  EXPECT_EQ(10.0,w.z) << "Operator + \".z\".";

  u = -w;

  EXPECT_EQ(- 6.0,u.x) << "Operator -(unitary) \".x\".";
  EXPECT_EQ(- 8.0,u.y) << "Operator -(unitary) \".y\".";
  EXPECT_EQ(-10.0,u.z) << "Operator -(unitary) \".z\".";

  v *= 5;

  EXPECT_EQ(15.0,v.x) << "Operator *= \".x\".";
  EXPECT_EQ(20.0,v.y) << "Operator *= \".y\".";
  EXPECT_EQ(25.0,v.z) << "Operator *= \".z\".";

  w = v - u;

  EXPECT_EQ(21.0,w.x) << "Operator - \".x\".";
  EXPECT_EQ(28.0,w.y) << "Operator - \".y\".";
  EXPECT_EQ(35.0,w.z) << "Operator - \".z\".";

  w -= v;

  EXPECT_EQ( 6.0,w.x) << "Operator -= \".x\".";
  EXPECT_EQ( 8.0,w.y) << "Operator -= \".y\".";
  EXPECT_EQ(10.0,w.z) << "Operator -= \".z\".";

  zbe::Vector2D v2{3.0,4.0};
  EXPECT_EQ(25.0,v2.getSqrModule()) << "Squared module.";
  EXPECT_EQ( 5.0,v2.getModule()) << "Module.";

  zbe::Point2D p{3.0,5.0};
  zbe::Point2D q{7.0,2.0};

  v2 = p - q;

  EXPECT_EQ(-4.0,v2.x) << "Operator -= \".x\".";
  EXPECT_EQ( 3.0,v2.y) << "Operator -= \".y\".";

  zbe::SysError::clear();
}

// TODO operaciones tipicas de Vector2D (polares) y Vector3D(producto vectorial)