/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Camera.cpp
 * @since 2019-11-04
 * @date 2019-11-04
 * @author Ludo Degryll Batis
 * @brief Tool to manage intrinsics and extrinsics camera parameters.
 */

#include "ZBE/tools/graphics/Camera.h"

namespace zbe {

  void Camera::setFrustum(float left, float right, float bottom, float top, float near, float far) {
    projection[0] = 2 * near / (right - left);
    projection[2] = (right + left) / (right - left);
    projection[5] = 2 * near / (top - bottom);
    projection[6] = (top + bottom) / (top - bottom);
    projection[10] = -(far + near) / (far - near);
    projection[11] = -(2 * far * near) / (far - near);
    projection[14] = -1;
    projection[15] = 0;
  }

  void Camera::set_perspective(float fov, float aspect, float znear, float zfar) {
    float tangent = tan(float(TORADIANS) * (fov / 2.0f));
    float height = znear * tangent;
    float width = height * aspect;
    setFrustum(-width, width, -height, height, znear, zfar);
  }


  void Camera::lookAt(Vector3D eye, Vector3D center, Vector3D up)  {
    Vector3D  f = (center - eye).normalize();
    Vector3D  u = up.normalize();
    Vector3D  s = cross(f, u).normalize();
    u = cross(s, f);

    transform[0] = s.x;
    transform[1] = u.x;
    transform[2] =-f.x;
    transform[3] = 0;

    transform[4] = s.y;
    transform[5] = u.y;
    transform[6] =-f.y;
    transform[7] = 0;

    transform[8]  = s.z;
    transform[9]  = u.z;
    transform[10] =-f.z;
    transform[11] = 0;

    transform[12] = -(s * eye);
    transform[13] = -(u * eye);
    transform[14] =  (f * eye);
    transform[15] = 1;
  }

}  // namespace zbe
