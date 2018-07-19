#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Region.h"

namespace regiontest {

TEST(Region, DataAccessAssignation) {
  zbe::Region<3> r({10,20,30},{10,10,10});
  EXPECT_EQ(10,r.p[0]) << "[Region<3>] Access to point[0].";
  EXPECT_EQ(20,r.p[1]) << "[Region<3>] Access to point[1].";
  EXPECT_EQ(30,r.p[2]) << "[Region<3>] Access to point[2].";

  EXPECT_EQ(10,r.v[0]) << "[Region<3>] Access to vector[0].";
  EXPECT_EQ(10,r.v[1]) << "[Region<3>] Access to vector[1].";
  EXPECT_EQ(10,r.v[2]) << "[Region<3>] Access to vector[2].";

  r.p[0] = 60;
  r.p[1] = 70;
  r.p[2] = 80;

  EXPECT_EQ(60,r.p[0]) << "[Region<3>] Modify point[0].";
  EXPECT_EQ(70,r.p[1]) << "[Region<3>] Modify point[1].";
  EXPECT_EQ(80,r.p[2]) << "[Region<3>] Modify point[2].";

  r.v[0] = 5;
  r.v[1] = 15;
  r.v[2] = 20;

  EXPECT_EQ(5,r.v[0]) << "[Region<3>] Modify vector[0].";
  EXPECT_EQ(15,r.v[1]) << "[Region<3>] Modify vector[1].";
  EXPECT_EQ(20,r.v[2]) << "[Region<3>] Modify vector[2].";

  zbe::Region<3> q;
  q = r;

  EXPECT_EQ(60,r.p[0]) << "[Region<3>] Modify point[0].";
  EXPECT_EQ(70,r.p[1]) << "[Region<3>] Modify point[1].";
  EXPECT_EQ(80,r.p[2]) << "[Region<3>] Modify point[2].";

  EXPECT_EQ(5,r.v[0]) << "[Region<3>] Modify vector[0].";
  EXPECT_EQ(15,r.v[1]) << "[Region<3>] Modify vector[1].";
  EXPECT_EQ(20,r.v[2]) << "[Region<3>] Modify vector[2].";
}

TEST(Region, Region2DCompatibility ) {
  zbe::Region2D r2({30,40},{10,20});

  zbe::Point2D p2 = r2.p;
  zbe::Vector2D v2 = r2.v;

  EXPECT_EQ(30,p2.x) << "[Point2D] Access data.";
  EXPECT_EQ(10,v2.x) << "[Vector2D] Access data.";

  zbe::Point<2> pt2 = r2.p;
  zbe::Vector<2> vt2 = r2.v;

  EXPECT_EQ(30,pt2[0]) << "[Point<2>] Access data.";
  EXPECT_EQ(10,vt2[0]) << "[Vector<2>] Access data.";


  zbe::Region<2> t2;
  t2 = r2;

  EXPECT_EQ(30,t2.p[0]) << "[Region<2>] Modify point[0].";
  EXPECT_EQ(40,t2.p[1]) << "[Region<2>] Modify point[1].";

  EXPECT_EQ(10,t2.v[0]) << "[Region<3>] Modify vector[0].";
  EXPECT_EQ(20,t2.v[1]) << "[Region<2>] Modify vector[1].";
}


TEST(Region, Region3DCompatibility ) {
  zbe::Region3D r3({30, 40, 50},{10, 20, 30});

  zbe::Point3D p3 = r3.p;
  zbe::Vector3D v3 = r3.v;

  EXPECT_EQ(30,p3.x) << "[Point3D] Access data.";
  EXPECT_EQ(10,v3.x) << "[Vector3D] Access data.";

  zbe::Point<3> pt3 = r3.p;
  zbe::Vector<3> vt3 = r3.v;

  EXPECT_EQ(30,pt3[0]) << "[Point<3>] Access data.";
  EXPECT_EQ(10,vt3[0]) << "[Vector<3>] Access data.";

  zbe::Region<3> t3;
  t3 = r3;

  EXPECT_EQ(30,t3.p[0]) << "[Region<3>] Modify point[0].";
  EXPECT_EQ(40,t3.p[1]) << "[Region<3>] Modify point[1].";
  EXPECT_EQ(50,t3.p[2]) << "[Region<3>] Modify point[2].";

  EXPECT_EQ(10,t3.v[0]) << "[Region<3>] Modify vector[0].";
  EXPECT_EQ(20,t3.v[1]) << "[Region<3>] Modify vector[1].";
  EXPECT_EQ(30,t3.v[2]) << "[Region<3>] Modify vector[2].";
}

} //namespace regiontest
