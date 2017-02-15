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

  static const int ITERATIONS = 1000000;

TEST(Intersections, DISABLED_RaySphere) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::Ray<2> ray{{20,30},{50,100}};
  zbe::NSphere<2> nsphere{{80,90},30};
  bool result;
  zbe::Point<2> p;
  int64_t t = 1 << zbe::PRECISION_DIGITS;

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

TEST(Intersections, DISABLED_NormalRaySphere) {
  double m = sqrt(125);
  zbe::Ray<2> ray{{20,30},{int64_t(50/m),int64_t(100/m)}};
  zbe::NSphere<2> nsphere{{80,90},30};
  bool result;
  zbe::Point<2> p;
  int64_t t = 100 << zbe::PRECISION_DIGITS;

  int64_t time = (int64_t)(6 * m) << zbe::PRECISION_DIGITS;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "First Normal Ray vs Nsphere collision.";
  EXPECT_EQ(time,t) << "Time of collision.";
  EXPECT_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 50;
  nsphere.c[1] = 120;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(1,result) << "Second Ray vs Nsphere collision.";
  EXPECT_EQ(time,t) << "Time of collision.";
  EXPECT_EQ(50,p[0]) << "Point of collision (x).";
  EXPECT_EQ(90,p[1]) << "Point of collision (y).";

  t = 100 << zbe::PRECISION_DIGITS;
  nsphere.c[0] = 80;
  nsphere.c[1] = 90;
  nsphere.r = 10;

  result = intersectionNormalRayNSphere(ray, nsphere, t, p);
  EXPECT_EQ(0,result) << "Third Ray vs Nsphere collision.";
}

inline void testRayInsideAABBWith(zbe::Ray<2> ray, zbe::AABB<2> aabb, int64_t tMax, int64_t time, zbe::Point<2> point, bool expected =  true){
  zbe::Point<2> p;
  int64_t t = tMax;
  bool result = zbe::intersectionRayInsideAABB(ray, aabb, tMax, t, p);
  EXPECT_EQ(expected, result) << "First Ray vs AABB collision.";
  if (expected) {
    EXPECT_EQ(time, t) << "Time of collision.";
    EXPECT_EQ(point[0] ,p[0]) << "Point of collision (x).";
    EXPECT_EQ(point[1] ,p[1]) << "Point of collision (y).";
  }
}

TEST(Intersections, RayInsideAABB_Base) {
  zbe::Ray<2> ray{{  20 << zbe::PRECISION_DIGITS, 30 << zbe::PRECISION_DIGITS},
                  {  50 << zbe::PRECISION_DIGITS,100 << zbe::PRECISION_DIGITS}};
  zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                    {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};
	int64_t tMax = 10 << zbe::PRECISION_DIGITS;
  int64_t t = zbe::roundPrecision((97 << zbe::PRECISION_DIGITS) / 10);
  zbe::Point<2> p({ray.o[0]+(ray.d[0]*t >> zbe::PRECISION_DIGITS), ray.o[1]+(ray.d[1]*t >> zbe::PRECISION_DIGITS)});
  testRayInsideAABBWith(ray, aabb, tMax, t, p);
}

TEST(Intersections, RayInsideAABB_Horizontal) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t hvel = ((((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  hvel, 0}};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t diff;
    int64_t t;
    if(hvel > 0) {
      diff = aabb.maximum[0] - ray.o[0];
      t = (diff << zbe::PRECISION_DIGITS) / ray.d[0];
    } else {
      diff = aabb.minimum[0] - ray.o[0];
      t = (diff << zbe::PRECISION_DIGITS) / ray.d[0];
    }
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({ray.o[0]+(ray.d[0]*t >> zbe::PRECISION_DIGITS), ray.o[1]});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p, t > 0);
  }
}

TEST(Intersections, RayInsideAABB_Vertical) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t vvel = ((((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) << zbe::PRECISION_DIGITS)/10;;
    int64_t xpos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    zbe::Ray<2> ray{{  xpos , ypos},
                    {  0, vvel }};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t diff;
    int64_t t;
    if(vvel > 0) {
      diff = aabb.maximum[1] - ray.o[1];
      t = (diff << zbe::PRECISION_DIGITS) / ray.d[1];
    } else {
      diff = aabb.minimum[1] - ray.o[1];
      t = (diff << zbe::PRECISION_DIGITS) / ray.d[1];
    }
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({ray.o[0], ray.o[1]+(ray.d[1]*t >> zbe::PRECISION_DIGITS)});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p, t > 0);
  }
}

TEST(Intersections, RayInsideAABB_TopLeftCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t xpos = (((rand() % 9980) + 10)<< zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10)<< zbe::PRECISION_DIGITS)/10;
    zbe::Ray<2> ray{{  xpos, ypos},
                    { -xpos, -ypos}};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t t = 1 << zbe::PRECISION_DIGITS;

    t = zbe::roundPrecision(t);
    zbe::Point<2> p({0, 0});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p);
  }
}

TEST(Intersections, RayInsideAABB_TopRightCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t xpos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    zbe::Ray<2> ray{{ xpos, ypos},
                    { -xpos , (1000 << zbe::PRECISION_DIGITS) - ypos }};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t t = 1 << zbe::PRECISION_DIGITS;

    t = zbe::roundPrecision(t);
    zbe::Point<2> p({0, aabb.maximum[1]});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p);
  }
}

TEST(Intersections, RayInsideAABB_BottomLeftCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t xpos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10) << zbe::PRECISION_DIGITS)/10;
    zbe::Ray<2> ray{{ xpos ,  ypos },
                    { (1000<< zbe::PRECISION_DIGITS) -xpos, -ypos}};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t t = 1 << zbe::PRECISION_DIGITS;

    t = zbe::roundPrecision(t);
    zbe::Point<2> p({aabb.maximum[0], 0});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p);
  }
}

TEST(Intersections, RayInsideAABB_BottomRightCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t xpos = (((rand() % 9980) + 10)<< zbe::PRECISION_DIGITS)/10;
    int64_t ypos = (((rand() % 9980) + 10)<< zbe::PRECISION_DIGITS)/10 ;
    zbe::Ray<2> ray{{ xpos ,  ypos },
                    { (1000 << zbe::PRECISION_DIGITS) - xpos, (1000<< zbe::PRECISION_DIGITS) - ypos}};
    zbe::AABB<2> aabb{{0 << zbe::PRECISION_DIGITS, 0 << zbe::PRECISION_DIGITS},
                      {1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS}};

    int64_t t = 1 << zbe::PRECISION_DIGITS;

    t = zbe::roundPrecision(t);
    zbe::Point<2> p({aabb.maximum[0], aabb.maximum[1]});

    int64_t tMax = 10 << zbe::PRECISION_DIGITS;
    testRayInsideAABBWith(ray, aabb, tMax, t, p);
  }
}

TEST(Intersections, DISABLED_RayAABB) {
  zbe::Ray<2> ray{{  20 << zbe::PRECISION_DIGITS, 30 << zbe::PRECISION_DIGITS},
  								{  50 << zbe::PRECISION_DIGITS,100 << zbe::PRECISION_DIGITS}};
  zbe::AABB<2> aabb{{10 << zbe::PRECISION_DIGITS, 90 << zbe::PRECISION_DIGITS},
  									{60 << zbe::PRECISION_DIGITS,100 << zbe::PRECISION_DIGITS}};
  bool result;
  zbe::Point<2> p;
  int64_t t = 1 << zbe::PRECISION_DIGITS;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(1, result) << "First Ray vs AABB collision.";
  int64_t six = (6 << zbe::PRECISION_DIGITS) / 10;
  EXPECT_EQ(six,t) << "Time of collision.";
  EXPECT_EQ(50 << zbe::PRECISION_DIGITS,p[0]) << "Point of collision (x).";
  EXPECT_EQ(90 << zbe::PRECISION_DIGITS,p[1]) << "Point of collision (y).";

  t = 1 << zbe::PRECISION_DIGITS;
  aabb.minimum[0] = 51  << zbe::PRECISION_DIGITS;
  aabb.minimum[1] = 80  << zbe::PRECISION_DIGITS;
  aabb.maximum[0] = 100 << zbe::PRECISION_DIGITS;
  aabb.maximum[1] = 90  << zbe::PRECISION_DIGITS;

  result = intersectionRayAABB(ray, aabb, t, p);
  EXPECT_EQ(0,result) << "Second Ray vs AABB collision.";
}

void testMovingCircleInsideABB(zbe::Circle ball, zbe::Vector2D velocity, zbe::AABB<2> block, int64_t tMax, int64_t time, zbe::Point<2> point, bool expected =  true){
  int64_t t = tMax;
  zbe::Point<2> p;
  bool result = IntersectionMovingCircleInsideAABB2D(ball, velocity, block, tMax, t, p);
  EXPECT_EQ(expected,result) << "First Moving Circle vs AABB collision.";
  if (expected) {
    EXPECT_EQ(time, t) << "Time of collision.";
    EXPECT_EQ(point[0] ,p[0]) << "Point of collision (x).";
    EXPECT_EQ(point[1] ,p[1]) << "Point of collision (y).";
  }
}

TEST(Intersections, MovingCircleInsideAABB_BaseMod) {
  zbe::Circle ball{{19850854,45940736},727449};
  zbe::Vector2D velocity{52553318, 0};
  zbe::AABB2D block{{0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS}};
  int64_t tMax = 1 << zbe::PRECISION_DIGITS;
  zbe::Point<2> p({65330737, 45940736});
  testMovingCircleInsideABB(ball, velocity, block, tMax, 55808, p);
}

TEST(Intersections, MovingCircleInsideAABB_Base) {
  zbe::Circle ball{{42 << zbe::PRECISION_DIGITS,513 << zbe::PRECISION_DIGITS},7 << zbe::PRECISION_DIGITS};
  zbe::Vector2D velocity{-65513520, -65513520};
  zbe::AABB2D block{{0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS}};
  int64_t tMax = 1 << zbe::PRECISION_DIGITS;
  zbe::Point<2> p({246462, 31572670});
  testMovingCircleInsideABB(ball, velocity, block, tMax, 2048, p);
}

TEST(Intersections, MovingCircleInsideAABB_Horizontal) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t hvel = ((((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) << zbe::PRECISION_DIGITS)/10;
    int64_t minDist = abs((hvel * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    xpos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    radius = (radius << zbe::PRECISION_DIGITS)/10;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({hvel, 0});
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t diff;
    int64_t t;
    int64_t offset;
    if(hvel > 0) {
      diff = block.maximum[0] - (ball.c[0] + ball.r);
      t = (diff << zbe::PRECISION_DIGITS) / velocity[0];
      offset = ball.r;
    } else {
      diff = block.minimum[0] - (ball.c[0] - ball.r);
      t = (diff << zbe::PRECISION_DIGITS) / velocity[0];
      offset = -ball.r;
    }
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({ball.c[0]+((velocity[0]*t) >> zbe::PRECISION_DIGITS) + offset, ball.c[1]});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}

TEST(Intersections, MovingCircleInsideAABB_Vertical) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t vvel = ((((rand() % 9000) + 1000) * ((rand() % 2)*2-1)) << zbe::PRECISION_DIGITS)/10;
    int64_t minDist = abs((vvel * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    ypos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius = (radius << zbe::PRECISION_DIGITS)/10;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({0, vvel});
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t diff;
    int64_t t;
    int64_t offset;
    if(vvel > 0) {
      diff = block.maximum[1] - (ball.c[1] + ball.r);
      t = (diff << zbe::PRECISION_DIGITS) / velocity[1];
      offset = ball.r;
    } else {
      diff = block.minimum[1] - (ball.c[1] - ball.r);
      t = (diff << zbe::PRECISION_DIGITS) / velocity[1];
      offset = -ball.r;
    }
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({ball.c[0], ball.c[1]+((velocity[1]*t) >> zbe::PRECISION_DIGITS) + offset});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}

TEST(Intersections, MovingCircleInsideAABB_TopLeftCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t minDist = abs(((1000 << zbe::PRECISION_DIGITS) * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    xpos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    ypos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius = (radius << zbe::PRECISION_DIGITS)/10;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({-(xpos-radius), -(ypos-radius)});
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t t = 1 << zbe::PRECISION_DIGITS;
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({0, 0});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}

TEST(Intersections, MovingCircleInsideAABB_TopRightCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t minDist = abs(((1000 << zbe::PRECISION_DIGITS) * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    xpos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    ypos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius = (radius << zbe::PRECISION_DIGITS)/10;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({(1000 << zbe::PRECISION_DIGITS) -(xpos+radius), -(ypos-radius)});
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t t = 1 << zbe::PRECISION_DIGITS;
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({block.maximum[0], 0});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}
TEST(Intersections, MovingCircleInsideAABB_BottomLeftCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t minDist = abs(((1000 << zbe::PRECISION_DIGITS) * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    xpos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    ypos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius = (radius << zbe::PRECISION_DIGITS)/10;
    //printf("minDist: %ld\n", minDist );
    //printf("r: %ld hv: %ld x: %ld y: %ld\n",radius, hvel, xpos, ypos);

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({ -(xpos-radius), (1000 << zbe::PRECISION_DIGITS) - (ypos+radius)});//(1000 << zbe::PRECISION_DIGITS) - ypos
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t t = 1 << zbe::PRECISION_DIGITS;
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({0, block.maximum[1]});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}

TEST(Intersections, MovingCircleInsideAABB_BottomRightCorner) {
  srand (time(NULL));
  for(int i = 0; i < ITERATIONS ; i++) {
    int64_t radius = ((rand() % 100) + 100);
    int64_t minDist = abs(((1000 << zbe::PRECISION_DIGITS) * zbe::TIME_QUANTUM) >> zbe::PRECISION_DIGITS) + ((radius+1) << zbe::PRECISION_DIGITS)/10;
    int64_t xpos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    xpos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , xpos);
    xpos = std::max(minDist, xpos);
    int64_t ypos = ((rand() % (9980 -(radius*2)) + 10 + radius) << zbe::PRECISION_DIGITS)/10;
    ypos = std::min( (1000 << zbe::PRECISION_DIGITS) - minDist , ypos);
    ypos = std::max(minDist, ypos);
    radius = (radius << zbe::PRECISION_DIGITS)/10;

    zbe::Circle ball({xpos, ypos}, radius);
  	zbe::Vector2D velocity({(1000 << zbe::PRECISION_DIGITS) -(xpos+radius), (1000 << zbe::PRECISION_DIGITS) -(ypos+radius)});//(1000 << zbe::PRECISION_DIGITS) - ypos
  	zbe::AABB2D block({0,0},{1000 << zbe::PRECISION_DIGITS ,1000 << zbe::PRECISION_DIGITS});
  	int64_t tMax = 10 << zbe::PRECISION_DIGITS;

    int64_t t = 1 << zbe::PRECISION_DIGITS;
    t = zbe::roundPrecision(t);
    zbe::Point<2> p({block.maximum[0], block.maximum[1]});
    testMovingCircleInsideABB(ball, velocity, block, tMax, t, p);
  }
}

TEST(Intersections, DISABLED_MovingCircleOutsideAABB) {
  zbe::Circle ball{{20,30},10};
  zbe::Vector2D velocity{30,40};
  zbe::AABB2D block{{10,50},{60,100}};
  bool result;
  zbe::Point2D p;
  int64_t t = 1 << zbe::PRECISION_DIGITS;

  result = IntersectionMovingCircleOutsideAABB2D(ball, velocity, block, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_EQ(25 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_EQ(275,p[0]) << "Point of collision (x).";
  EXPECT_EQ(500,p[1]) << "Point of collision (y).";
}

}
