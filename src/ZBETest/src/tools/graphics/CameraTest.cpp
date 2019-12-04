#include "gtest/gtest.h"

#include <memory>
#include <cstdio>

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/tools/graphics/Camera.h"


namespace CameraTest {

void testData(zbe::Vector3D eye, zbe::Vector3D target, zbe::Vector3D up, float fov, float aspect, float znear, float zfar, const std::vector<float>& transform, const std::vector<float>& projection) {
  zbe::Camera cam;
  auto eyeVal = std::make_shared<zbe::SimpleValue<zbe::Vector3D> >(eye);
  auto targetVal = std::make_shared<zbe::SimpleValue<zbe::Vector3D> >(target);
  auto upVal = std::make_shared<zbe::SimpleValue<zbe::Vector3D> >(up);

  cam.set_perspective(fov, aspect, znear, zfar);

  cam.setEyeValue(eyeVal);
  cam.setTargetValue(targetVal);
  cam.setUpValue(upVal);

  cam.update();

  auto& trans = cam.getTransformMat();
  auto& proj = cam.getProjectionMat();
  printf("trans\n");
  printf("%f,%f,%f,%f,", trans[0], trans[1], trans[2], trans[3]);
  printf("%f,%f,%f,%f,", trans[4], trans[5], trans[6], trans[7]);
  printf("%f,%f,%f,%f,", trans[8], trans[9], trans[10], trans[11]);
  printf("%f,%f,%f,%f\n", trans[12], trans[13], trans[14], trans[5]);

  printf("Proj\n");
  printf("%f,%f,%f,%f,", proj[0], proj[1], proj[2], proj[3]);
  printf("%f,%f,%f,%f,", proj[4], proj[5], proj[6], proj[7]);
  printf("%f,%f,%f,%f,", proj[8], proj[9], proj[10], proj[11]);
  printf("%f,%f,%f,%f\n", proj[12], proj[13], proj[14], proj[5]);

  // EXPECT_EQ(transform.size(), 16) << "Input transform is a 4x4 matrix, must have 16 elements";
  // EXPECT_EQ(projection.size(), 16) << "Input projection is a 4x4 matrix, must have 16 elements";;
  // EXPECT_EQ(trans.size(), 16) << "Output trans is a 4x4 matrix, must have 16 elements";;
  // EXPECT_EQ(proj.size(), 16) << "Output proj is a 4x4 matrix, must have 16 elements";;
  //
  // for(int i = 0; i < trans.size(); i++) {
  //   EXPECT_FLOAT_EQ(trans[i], transform[i]) << "Output transform matrix element " << i << " must match input";
  //   EXPECT_FLOAT_EQ(proj[i], projection[i]) << "Output projection matrix element " << i << " must match input";
  // }
}

TEST(Camera, usage) {

  testData(
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    120.0f, 1.0f, 1.0f, 50.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {42.0f, 37.0f, 4.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    120.0f, 1.0f, 1.0f, 50.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {7.0f, 25.0f, 2.0f},
    {8.0f, 3.14f, 1547.0f},
    {45.5f, 13.0f, 87.0f},
    120.0f, 1.0f, 1.0f, 50.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    90.0f, 4.0f/3.0f, 1.0f, 10.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {42.0f, 37.0f, 4.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    90.0f, 4.0f/3.0f, 1.0f, 10.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {7.0f, 25.0f, 2.0f},
    {8.0f, 3.14f, 1547.0f},
    {45.5f, 13.0f, 87.0f},
    90.0f, 4.0f/3.0f, 1.0f, 10.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    70.0f, 16.0f/9.0f, 0.1f, 100.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {42.0f, 37.0f, 4.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    70.0f, 16.0f/9.0f, 0.1f, 100.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );

  testData(
    {7.0f, 25.0f, 2.0f},
    {8.0f, 3.14f, 1547.0f},
    {45.5f, 13.0f, 87.0f},
    70.0f, 16.0f/9.0f, 0.1f, 100.0f,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  );
}

}  // namespace RsrcFolderLoadDmnTest
