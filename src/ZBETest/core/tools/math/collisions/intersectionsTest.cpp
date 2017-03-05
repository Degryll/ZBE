#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <time.h>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"

namespace IntersectionsTest {

static const int ITERATIONS = 40000000;//40000000;

inline bool compareQuantizedMovement(double point, double p, double maxDiff){
  if(maxDiff >= 0.0) {
  	return ((point - p) <= (maxDiff + zbe::PRECISION));
  } else {
    return ((point - p) >= (maxDiff - zbe::PRECISION));
  }
}

/******************************************************************************/
/** RAY AGAINST NSPHERE *******************************************************/
/******************************************************************************/

TEST(Intersections, RaySphere) {
  zbe::Ray<2> ray{{2.0,3.0},{5.0,10.0}};
  zbe::NSphere<2> nsphere{{8.0,9.0},3.0};
  bool result;
  zbe::Point<2> p;
  int64_t t = zbe::SECOND;

  int64_t texpected = zbe::quantizeTime(39168);
  zbe::Point<2> q = ray.o + (ray.d * texpected) * zbe::INVERSE_SECOND;
  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_TRUE(result) << "First Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(texpected, t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(q[0], p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(q[1], p[1]) << "Point of collision (y).";

  t = zbe::SECOND;
  nsphere.c[0] = 5.0;
  nsphere.c[1] = 12.0;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_TRUE(result) << "Second Ray vs Nsphere collision.";
  EXPECT_DOUBLE_EQ(texpected, t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(q[0], p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(q[1], p[1]) << "Point of collision (y).";

  t = zbe::SECOND;
  nsphere.c[0] = 8.0;
  nsphere.c[1] = 9.0;
  nsphere.r = 10;

  result = intersectionRayNSphere(ray, nsphere, t, p);
  EXPECT_FALSE(result) << "Third Ray vs Nsphere collision.";
}

/******************************************************************************/
/** NORMAL RAY AGAINST NSPHERE ************************************************/
/******************************************************************************/

TEST(Intersections, DISABLED_NormalRaySphere) {
  double m = sqrt(125);
  zbe::Ray<2> ray{{20,30},{50/m,100/m}};
  zbe::NSphere<2> nsphere{{80,90},30};
  bool result;
  zbe::Point<2> p;
  int64_t t = 100;

  int64_t time = (int64_t)(6 * m) * zbe::SECOND;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_TRUE(result) << "First Normal Ray vs Nsphere collision.";
  EXPECT_EQ(time,t) << "Time of collision.";
  EXPECT_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 * zbe::SECOND;
  nsphere.c[0] = 50;
  nsphere.c[1] = 120;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_TRUE(result) << "Second Ray vs Nsphere collision.";
  EXPECT_EQ(time,t) << "Time of collision.";
  EXPECT_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 * zbe::SECOND;
  nsphere.c[0] = 80;
  nsphere.c[1] = 90;
  nsphere.r = 10;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
}

/******************************************************************************/
/** RAY INSIDE AABB ***********************************************************/
/******************************************************************************/

inline void testRayInsideAABB(zbe::Ray<2> ray, zbe::AABB<2> aabb, int64_t tMax, int64_t time, zbe::Point<2> point, int64_t maxTimeDiff = 0, double maxXDiff = 0.0, double maxYDiff = 0.0, bool expected = true){
  zbe::Point<2> p;
  int64_t t = tMax;
  bool correctP = false;
  bool result = zbe::intersectionBeamInsideAABB(ray, aabb, t, p);
  EXPECT_EQ(expected, result) << "First Ray vs AABB collision.";
  if (expected) {
    int64_t diff = time - t;
    EXPECT_LE(0, diff) << "Collision too late: time(" << time << "), t(" << t << ").";
    EXPECT_GE(maxTimeDiff, diff) << "Time of collision.";
    correctP = compareQuantizedMovement(point[0], p[0], maxXDiff);
    EXPECT_TRUE(correctP) << "Point of collision (x).";
    correctP = compareQuantizedMovement(point[1], p[1], maxYDiff);
    EXPECT_TRUE(correctP) << "Point of collision (y).";
  }
}

TEST(Intersections, RayInsideAABB_Base) {
  zbe::Ray<2> ray{{  20, 30},
                  {  50, 100}};
  zbe::AABB<2> aabb{{0, 0},
                    {1000, 1000}};
	int64_t tMax = 10 * zbe::SECOND;
  int64_t t = zbe::quantizeTime(9.7 * zbe::SECOND);
  zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);
  testRayInsideAABB(ray, aabb, tMax, t, p);
}

TEST(Intersections, RayInsideAABB_Horizontal) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDist = zbe::TIME_QUANTUM_VALUE * hvel;
    double xpos = ((rand() % (10000 - zbe::roundUp(minDist*2))) + minDist) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  hvel, 0}};
    zbe::AABB<2> aabb{{0, 0},
                      {1000, 1000}};

    double diff;
    int64_t t;
    if(hvel > 0) {
      diff = aabb.maximum[0] - ray.o[0];
    } else {
      diff = aabb.minimum[0] - ray.o[0];
    }
    int64_t tRaw = (diff * zbe::SECOND)/ ray.d[0];
    tRaw += (tRaw !=255);  // Precision issue
    t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDist, 0, t > 0);
  }
}

TEST(Intersections, RayInsideAABB_Vertical) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double vvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDist = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % (10000 - zbe::roundUp(minDist*2))) + minDist) / 10.0;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  0, vvel}};
    zbe::AABB<2> aabb{{0, 0},
                      {1000, 1000}};

    double diff;
    int64_t t;
    if(vvel > 0) {
      diff = aabb.maximum[1] - ray.o[1];
    } else {
      diff = aabb.minimum[1] - ray.o[1];
    }
    int64_t tRaw = (diff * zbe::SECOND)/ ray.d[1];
    tRaw += (tRaw !=255);  // Precision issue
    t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, 0, minDist, t > 0);
  }
}

TEST(Intersections, RayInsideAABB_TopLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double xpos = ((rand() % 9980) + 10)/10.0;
    double ypos = ((rand() % 9980) + 10)/10.0;
    zbe::Ray<2> ray{{  xpos, ypos},
                   { -xpos, -ypos}};
    zbe::AABB<2> aabb{{0, 0},
                      {1000,1000}};

    int64_t t = zbe::SECOND;

    t = zbe::quantizeTime(t);
    zbe::Point<2> p({0, 0});

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * ray.d[0], zbe::TIME_QUANTUM_VALUE * ray.d[1]);
  }
}

TEST(Intersections, RayInsideAABB_TopRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double xpos = ((rand() % 9980) + 10)/10.0;
    double ypos = ((rand() % 9980) + 10)/10.0;
    zbe::Ray<2> ray{{ xpos, ypos},
                    {-xpos , 1000 - ypos }};
    zbe::AABB<2> aabb{{0, 0 },
                      {1000, 1000}};

    int64_t t = zbe::SECOND;

    t = zbe::quantizeTime(t);
    zbe::Point<2> p({0, aabb.maximum[1]});

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * ray.d[0], zbe::TIME_QUANTUM_VALUE * ray.d[1]);
  }
}

TEST(Intersections, RayInsideAABB_BottomLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double xpos = ((rand() % 9980) + 10)/10.0;
    double ypos = ((rand() % 9980) + 10)/10.0;
    zbe::Ray<2> ray{{ xpos ,  ypos },
                    {1000 - xpos, -ypos}};
    zbe::AABB<2> aabb{{0, 0},
                      {1000, 1000}};

    int64_t t = zbe::SECOND;

    t = zbe::quantizeTime(t);
    zbe::Point<2> p({aabb.maximum[0], 0});

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * ray.d[0], zbe::TIME_QUANTUM_VALUE * ray.d[1]);
  }
}

TEST(Intersections, RayInsideAABB_BottomRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double xpos = ((rand() % 9980) + 10)/10.0;
    double ypos = ((rand() % 9980) + 10)/10.0;
    zbe::Ray<2> ray{{xpos, ypos},
                    {1000 - xpos, 1000 - ypos}};
    zbe::AABB<2> aabb{{0, 0},
                      {1000, 1000}};

    int64_t t = zbe::SECOND;

    t = zbe::quantizeTime(t);
    zbe::Point<2> p({aabb.maximum[0], aabb.maximum[1]});

    int64_t tMax = 10 * zbe::SECOND;
    testRayInsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * ray.d[0], zbe::TIME_QUANTUM_VALUE * ray.d[1]);
  }
}

/******************************************************************************/
/** BEAM OUTSIDE AABB *********************************************************/
/******************************************************************************/

inline void testBeamOutsideAABB(zbe::Ray<2> ray, zbe::AABB<2> aabb, int64_t tMax, int64_t time, zbe::Point<2> point, int64_t maxTimeDiff = 0, double maxXDiff = 0.0, double maxYDiff = 0.0, bool expected =  true){
  zbe::Point<2> p;
  int64_t t = tMax;
  bool correctP = false;
  bool result = zbe::intersectionBeamOutsideAABB(ray, aabb, t, p);
  EXPECT_EQ(expected, result) << "First Ray vs AABB collision.";
  if (expected) {
    int64_t diff = time - t;
    EXPECT_LE(0, diff) << "Collision too late: time(" << time << "), t(" << t << ").";
    EXPECT_GE(maxTimeDiff, diff) << "Time of collision.";
    correctP = compareQuantizedMovement(point[0], p[0], maxXDiff);
    EXPECT_TRUE(correctP) << "Point of collision (x).";
    correctP = compareQuantizedMovement(point[1], p[1], maxYDiff);
    EXPECT_TRUE(correctP) << "Point of collision (y).";
  }
}

TEST(Intersections, BeamOutsideAABB_Base) {
  zbe::Ray<2> ray{{  50, 150 },
                  {  100, 10 }};
  zbe::AABB<2> aabb{{100, 100},
                    {200, 200}};
	int64_t tMax = 10 * zbe::SECOND;
  int64_t t = zbe::quantizeTime(zbe::SECOND / 2);
  zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);
  testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * ray.d[0], zbe::TIME_QUANTUM_VALUE * ray.d[1]);
}

TEST(Intersections, BeamOutsideAABB_Horizontal) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDist = zbe::TIME_QUANTUM_VALUE * hvel;
    double xpos = ((rand() % (10000 - zbe::roundUp(minDist*2))) + minDist) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    double dist = ((rand() % 5000) + 2000) / 10.0;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  hvel, 0}};

    double minx, maxx;
    if (hvel > 0) {
      minx = xpos + dist;
      maxx = minx + 100;
    } else {
      dist = -dist;
      maxx = xpos + dist;
      minx = maxx - 100;
    }
    zbe::AABB<2> aabb{{minx, ypos-50},
                      {maxx, ypos+50}};


    int64_t tRaw = (dist * zbe::SECOND)/ ray.d[0];
    tRaw += (tRaw !=255);  // Precision issue
    int64_t t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDist, 0, t > 0);
  }
}

TEST(Intersections, BeamOutsideAABB_Vertical) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double vvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDist = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % (10000 - zbe::roundUp(minDist*2))) + minDist) / 10.0;
    double dist = ((rand() % 5000) + 2000) / 10.0;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  0, vvel}};

    double miny, maxy;
    if (vvel > 0) {
      miny = ypos + dist;
      maxy = miny + 100;
    } else {
      dist = -dist;
      maxy = ypos + dist;
      miny = maxy - 100;
    }
    zbe::AABB<2> aabb{{xpos-50, miny},
                      {xpos+50, maxy}};


    int64_t tRaw = (dist * zbe::SECOND)/ ray.d[1];
    tRaw += (tRaw !=255);  // Precision issue
    int64_t t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, 0, minDist, t > 0);
  }
}

TEST(Intersections, BeamOutsideAABB_TopLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = ((rand() % 9000) + 1000) / 10.0;
    double vvel = ((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    zbe::Ray<2> ray{{xpos, ypos},
                    {hvel, vvel}};

    zbe::AABB<2> aabb{{xpos+hvel, ypos+vvel},
                      {xpos+hvel+50, ypos+vvel+50}};


    int64_t t = zbe::SECOND;
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, BeamOutsideAABB_TopRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = -((rand() % 9000) + 1000) / 10.0;
    double vvel = ((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    zbe::Ray<2> ray{{xpos, ypos},
                    {hvel, vvel}};

    zbe::AABB<2> aabb{{xpos+hvel-50, ypos+vvel},
                      {xpos+hvel, ypos+vvel+50}};


    int64_t t = zbe::SECOND;
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, BeamOutsideAABB_BottomLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = ((rand() % 9000) + 1000) / 10.0;
    double vvel = -((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    zbe::Ray<2> ray{{xpos, ypos},
                    {hvel, vvel}};

    zbe::AABB<2> aabb{{xpos+hvel, ypos+vvel-50},
                      {xpos+hvel+50, ypos+vvel}};

    int64_t t = zbe::SECOND;
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, BeamOutsideAABB_BottomRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double hvel = -((rand() % 9000) + 1000) / 10.0;
    double vvel = -((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    zbe::Ray<2> ray{{xpos, ypos},
                    {hvel, vvel}};

    zbe::AABB<2> aabb{{xpos+hvel-50, ypos+vvel-50},
                      {xpos+hvel, ypos+vvel}};

    int64_t t = zbe::SECOND;
    zbe::Point<2> p = ray.o + ((ray.d * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testBeamOutsideAABB(ray, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

/******************************************************************************/
/** MOVING CIRCLE INSIDE AABB *************************************************/
/******************************************************************************/

void testMovingCircleInsideABB(zbe::Circle ball, zbe::Vector2D velocity, zbe::AABB<2> block, int64_t tMax, int64_t time, zbe::Point<2> point, int64_t maxTimeDiff = 0, double maxXDiff = 0.0, double maxYDiff = 0.0, bool expected =  true){
  zbe::Point<2> p;
  int64_t t = tMax;
  bool correctP = false;
  bool result = IntersectionMovingCircleInsideAABB2D(ball, velocity, block, t, p);
  EXPECT_EQ(expected,result) << "First Moving Circle vs AABB collision.";
  if (expected) {
    int64_t diff = time - t;
    EXPECT_LE(0, diff) << "Collision too late: time(" << time << "), t(" << t << ").";
    EXPECT_GE(maxTimeDiff, diff) << "Time of collision: " << t;
    correctP = compareQuantizedMovement(point[0], p[0], maxXDiff);
    EXPECT_TRUE(correctP) << "Point of collision (x): " << p[0] << " instead of " << point[0];
    correctP = compareQuantizedMovement(point[1], p[1], maxYDiff);
    EXPECT_TRUE(correctP) << "Point of collision (y): " << p[1] << " instead of " << point[1];
  }
}

TEST(Intersections, MovingCircleInsideAABB_Base) {
  zbe::Circle ball{{42, 513}, 7};
  zbe::Vector2D velocity{-999.65, -999.65};
  zbe::AABB2D block{{0,0},{1000, 1000}};
  int64_t tMax = zbe::SECOND;
  zbe::Point<2> p({3.7609375, 474.7609375});
  testMovingCircleInsideABB(ball, velocity, block, tMax, 2048, p);
}

TEST(Intersections, MovingCircleInsideAABB_Horizontal) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1))/10.0;
    double minDiff = hvel * zbe::TIME_QUANTUM_VALUE;
    double minDist = abs(minDiff) + (radius+1);
    double xpos = (rand() % (9980 -zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    xpos = std::min(1000 - minDist , xpos);
    xpos = std::max(minDist, xpos);
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
		radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, 0});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    double diff;
    int64_t t;
    double offset;
    if(hvel > 0) {
      diff = block.maximum[0] - (ball.c[0] + ball.r);
      offset = ball.r;
    } else {
      diff = block.minimum[0] - (ball.c[0] - ball.r);
      offset = -ball.r;
    }
    int64_t tRaw = (diff * zbe::SECOND)/ velocity[0];
    tRaw += (tRaw !=255);  // Precision issue
    t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ball.c + (velocity * t * zbe::INVERSE_SECOND);
    p[0] += offset;

    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, minDiff);
  }
}

TEST(Intersections, MovingCircleInsideAABB_Vertical) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double vvel = ((rand() % 9000) + 1000) * ((rand() % 2)*2-1)/10.0;
    double minDiff = vvel * zbe::TIME_QUANTUM_VALUE;
    double minDist = abs(minDiff) + (radius+1);
    double xpos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    ypos = std::min(1000 - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({0, vvel});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    double diff;
    int64_t t;
    double offset;
    if(vvel > 0) {
      diff = block.maximum[1] - (ball.c[1] + ball.r);
      offset = ball.r;
    } else {
      diff = block.minimum[1] - (ball.c[1] - ball.r);
      offset = -ball.r;
    }
    int64_t tRaw = (diff * zbe::SECOND)/ velocity[1];
    tRaw += (tRaw !=255);  // Precision issue
    t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ball.c + (velocity * t * zbe::INVERSE_SECOND);
    p[1] += offset;

    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, 0.0, minDiff);
  }
}

TEST(Intersections, MovingCircleInsideAABB_TopLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double minDist = abs(((1000) * zbe::TIME_QUANTUM_VALUE)) + (radius+1)/10.0;
    double xpos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    xpos = std::min( (1000) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    ypos = std::min(1000 - minDist, ypos);
    ypos = std::max(minDist, ypos);
    radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({-(xpos-radius), -(ypos-radius)});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p({0, 0});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, -(xpos-radius)*zbe::TIME_QUANTUM_VALUE, -(ypos-radius)*zbe::TIME_QUANTUM_VALUE);
  }
}

TEST(Intersections, MovingCircleInsideAABB_TopRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double minDist = abs(1000 * zbe::TIME_QUANTUM_VALUE) + (radius+1)/10.0;
    double xpos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    xpos = std::min(1000 - minDist , xpos);
    xpos = std::max(minDist, xpos);
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    ypos = std::min(1000 - minDist, ypos);
    ypos = std::max(minDist, ypos);
    radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({1000 - (xpos+radius), -(ypos - radius)});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p({block.maximum[0], 0});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, -(xpos-radius)*zbe::TIME_QUANTUM_VALUE, -(ypos-radius)*zbe::TIME_QUANTUM_VALUE);
  }
}
TEST(Intersections, MovingCircleInsideAABB_BottomLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double minDist = abs(1000 * zbe::TIME_QUANTUM_VALUE) + (radius+1)/10.0;
    double xpos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    xpos = std::min(1000 - minDist, xpos);
    xpos = std::max(minDist, xpos);
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    ypos = std::min(1000 - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({ -(xpos-radius), 1000 - (ypos+radius)});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p({0, block.maximum[1]});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, -(xpos-radius)*zbe::TIME_QUANTUM_VALUE, -(ypos-radius)*zbe::TIME_QUANTUM_VALUE);
  }
}

TEST(Intersections, MovingCircleInsideAABB_BottomRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double minDist = abs(((1000) * zbe::TIME_QUANTUM_VALUE)) + (radius+1)/10.0;
    double xpos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    xpos = std::min(1000 - minDist , xpos);
    xpos = std::max(minDist, xpos);
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    ypos = std::min( 1000 - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({1000 -(xpos+radius), 1000 - (ypos+radius)});
  	zbe::AABB2D block({0,0},{1000, 1000});
  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p({block.maximum[0], block.maximum[1]});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, -(xpos-radius)*zbe::TIME_QUANTUM_VALUE, -(ypos-radius)*zbe::TIME_QUANTUM_VALUE);
  }
}

/******************************************************************************/
/** MOVING CIRCLE OUTSIDE AABB *************************************************/
/******************************************************************************/

void testMovingCircleOutsideABB(zbe::Circle ball, zbe::Vector2D velocity, zbe::AABB<2> block, int64_t tMax, int64_t time, zbe::Point<2> point, int64_t maxTimeDiff = 0, double maxXDiff = 0.0, double maxYDiff = 0.0, bool expected =  true){
  zbe::Point<2> p;
  int64_t t = tMax;
  bool correctP = false;
  bool result = IntersectionMovingCircleOutsideAABB2D(ball, velocity, block, t, p);
  EXPECT_EQ(expected,result) << "First Moving Circle vs AABB collision.";
  if (expected) {
    int64_t diff = time - t;
    EXPECT_LE(0, diff) << "Collision too late: time(" << time << "), t(" << t << ").\nball: (" << ball.c[0] << ", " << ball.c[1] << ") r(" << ball.r << "), velocity: (" << velocity[0] << ", " << velocity[1] << "), block: min(" << block.minimum[0] << ", " << block.minimum[1] << ") max(" << block.maximum[0] << ", " << block.maximum[1] << ").";
    EXPECT_GE(maxTimeDiff, diff) << "Time of collision: " << t;
    correctP = compareQuantizedMovement(point[0], p[0], maxXDiff);
    EXPECT_TRUE(correctP) << "Point of collision (x): " << p[0] << " instead of " << point[0];
    correctP = compareQuantizedMovement(point[1], p[1], maxYDiff);
    EXPECT_TRUE(correctP) << "Point of collision (y): " << p[1] << " instead of " << point[1];
  }
}

TEST(Intersections, MovingCircleOutsideAABB_Base) {
  zbe::Circle ball{{50.0, 150.0}, 16.0};
  zbe::Vector2D velocity{100.0, 10.0};
  zbe::AABB2D block{{116.0, 100.0},{200.0, 200.0}};
  int64_t tMax = 10 * zbe::SECOND;
  int64_t t = zbe::quantizeTime(zbe::SECOND / 2);
  zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);
  testMovingCircleOutsideABB(ball, velocity, block, tMax, t, p, zbe::TIME_QUANTUM, zbe::TIME_QUANTUM_VALUE * velocity[0], zbe::TIME_QUANTUM_VALUE * velocity[1]);
}

TEST(Intersections, MovingCircleOutsideAABB_Horizontal) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDiff = hvel * zbe::TIME_QUANTUM_VALUE;
    double minDist = abs(minDiff) + (radius+1);
    double xpos = (rand() % (9980 -zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    double dist = ((rand() % 5000) + 2000) / 10.0;
 		radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, 0});

    double minx, maxx;
    if (hvel > 0) {
      minx = xpos + dist + radius;
      maxx = minx + 100;
    } else {
      dist = -dist;
      maxx = xpos + dist - radius;
      minx = maxx - 100;
    }
    zbe::AABB<2> aabb{{minx, ypos-50},
                      {maxx, ypos+50}};

    int64_t tRaw = (dist * zbe::SECOND)/ velocity[0];
    tRaw += (tRaw !=255);  // Precision issue
    int64_t t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDist, 0, t > 0);
  }
}

TEST(Intersections, MovingCircleOutsideAABB_Vertical) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = (((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) / 10.0;
    double minDiff = hvel * zbe::TIME_QUANTUM_VALUE;
    double minDist = abs(minDiff) + (radius+1);
    double xpos = (rand() % (9980 -zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    double ypos = (rand() % (9980 - zbe::roundUp(radius*2)) + 10 + zbe::roundUp(radius))/10.0;
    double dist = ((rand() % 5000) + 2000) / 10.0;
 		radius /= 10.0;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, 0});

    double miny, maxy;
    if (hvel > 0) {
      miny = xpos + dist + radius;
      maxy = miny + 100;
    } else {
      dist = -dist;
      maxy = xpos + dist - radius;
      miny = maxy - 100;
    }
    zbe::AABB<2> aabb{{xpos-50, miny},
                      {xpos+50, maxy}};

    int64_t tRaw = (dist * zbe::SECOND)/ velocity[1];
    tRaw += (tRaw !=255);  // Precision issue
    int64_t t = zbe::quantizeTime(tRaw);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);

    int64_t tMax = 10 * zbe::SECOND;
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDist, 0, t > 0);
  }
}

TEST(Intersections, MovingCircleOutsideAABB_TopLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = ((rand() % 9000) + 1000) / 10.0;
    double vvel = ((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    radius /= 10.0;

    double h = sqrt(hvel*hvel+vvel*vvel);
    double cos = hvel / h;
    double sin = vvel / h;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, vvel});
    zbe::AABB<2> aabb{{xpos+hvel+cos*radius, ypos+vvel+sin*radius},
                      {xpos+hvel+cos*radius+50, ypos+vvel+sin*radius+50}};

  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, MovingCircleOutsideAABB_TopRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = -((rand() % 9000) + 1000) / 10.0;
    double vvel = ((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    radius /= 10.0;

    double h = sqrt(hvel*hvel+vvel*vvel);
    double cos = hvel / h;
    double sin = vvel / h;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, vvel});
    zbe::AABB<2> aabb{{xpos+hvel+cos*radius-50, ypos+vvel+sin*radius},
                      {xpos+hvel+cos*radius, ypos+vvel+sin*radius+50}};

  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, MovingCircleOutsideAABB_BottomLeftCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = ((rand() % 9000) + 1000) / 10.0;
    double vvel = -((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    radius /= 10.0;

    double h = sqrt(hvel*hvel+vvel*vvel);
    double cos = hvel / h;
    double sin = vvel / h;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, vvel});
    zbe::AABB<2> aabb{{xpos+hvel+cos*radius, ypos+vvel+sin*radius-50},
                      {xpos+hvel+cos*radius+50, ypos+vvel+sin*radius}};

  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

TEST(Intersections, MovingCircleOutsideAABB_BottomRightCorner) {
  srand(time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    double radius = ((rand() % 100) + 100);
    double hvel = -((rand() % 9000) + 1000) / 10.0;
    double vvel = -((rand() % 9000) + 1000) / 10.0;
    double minDistX = zbe::TIME_QUANTUM_VALUE * hvel;
    double minDistY = zbe::TIME_QUANTUM_VALUE * vvel;
    double xpos = ((rand() % 9980) + 10) / 10.0;
    double ypos = ((rand() % 9980) + 10) / 10.0;
    radius /= 10.0;

    double h = sqrt(hvel*hvel+vvel*vvel);
    double cos = hvel / h;
    double sin = vvel / h;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, vvel});
    zbe::AABB<2> aabb{{xpos+hvel+cos*radius-50, ypos+vvel+sin*radius-50},
                      {xpos+hvel+cos*radius, ypos+vvel+sin*radius}};

  	int64_t tMax = 10 * zbe::SECOND;

    int64_t t = zbe::SECOND;
    t = zbe::quantizeTime(t);
    zbe::Point<2> p = ball.c + ((velocity * t) * zbe::INVERSE_SECOND);
    testMovingCircleOutsideABB(ball, velocity, aabb, tMax, t, p, zbe::TIME_QUANTUM, minDistX, minDistY, t > 0);
  }
}

}
