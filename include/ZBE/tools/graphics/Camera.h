/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Camera.h
 * @since 2019-11-04
 * @date 2019-11-04
 * @author Ludo Degryll Batis
 * @brief Tool to manage intrinsics and extrinsics camera parameters.
 */

#ifndef ZBE_TOOLS_GRAPHICS_CAMERA_H_
#define ZBE_TOOLS_GRAPHICS_CAMERA_H_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/hash.hpp>


#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI Camera {
public:
  Camera() : transform(16, 0), projection(16, 0) {
    transform[0] = 1;
    transform[5] = 1;
    transform[10] = 1;
    transform[15] = 1;
  }

  ~Camera() {}

  void setFrustum(float left, float right, float bottom, float top, float near, float far);

  void set_perspective(float fov, float aspect, float znear, float zfar);

  void lookAt(Vector3D eye, Vector3D center, Vector3D up);

  std::vector<float>& getTransformMat() { return transform; }

  std::vector<float>& getProjectionMat() { return projection; }

private:
  std::vector<float> transform;
  std::vector<float> projection;
};

}  // namespace zbe

#endif  // ZBE_TOOLS_GRAPHICS_CAMERA_H_
