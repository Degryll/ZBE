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

  void Camera::setPerspective(float fov, float aspect, float znear, float zfar) {
    float tangent = static_cast<float>(tan(TORADIANS * (static_cast<double>(fov) / 2.0)));
    float height = znear * tangent;
    float width = height * aspect;
    setFrustum(-width, width, -height, height, znear, zfar);
  }


  void Camera::update()  {
    setPerspective(fov->get(), aspect->get(), znear->get(), zfar->get());
    lookAt(eye->get(),target->get(), up->get());
  }

  void Camera::lookAt(Vector3D eye, Vector3D target, Vector3D up)  {
    Vector3D  f = (target - eye).normalize();
    Vector3D  u = up.normalize();
    Vector3D  s = cross(f, u).normalize();
    u = cross(s, f);

    transform[0u] = static_cast<float>(s.x);
    transform[1u] = static_cast<float>(u.x);
    transform[2u] =-static_cast<float>(f.x);
    transform[3u] = .0f;

    transform[4u] = static_cast<float>(s.y);
    transform[5u] = static_cast<float>(u.y);
    transform[6u] =-static_cast<float>(f.y);
    transform[7u] = .0f;

    transform[8u]  = static_cast<float>(s.z);
    transform[9u]  = static_cast<float>(u.z);
    transform[10u] =-static_cast<float>(f.z);
    transform[11u] = .0f;

    transform[12u] = -static_cast<float>(s * eye);
    transform[13u] = -static_cast<float>(u * eye);
    transform[14u] =  static_cast<float>(f * eye);
    transform[15u] = 1.0f;
  }

}  // namespace zbe
