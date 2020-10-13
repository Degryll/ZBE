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
#include <memory>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/tools/shared/Value.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI Camera {
public:
  Camera() : eye(), target(), up(), transform(16, 0), projection(16, 0) {
    transform[0] = 1;
    transform[5] = 1;
    transform[10] = 1;
    transform[15] = 1;
  }

  ~Camera() {}

  void setEyeValue(std::shared_ptr<Value<Vector3D> > eye) {
    this->eye = eye;
  }

  void setTargetValue(std::shared_ptr<Value<Vector3D> > target) {
    this->target = target;
  }

  void setUpValue(std::shared_ptr<Value<Vector3D> > up) {
    this->up = up;
  }

  void setPerspectiveValues(
      std::shared_ptr<Value<float> > fov,
      std::shared_ptr<Value<float> > aspect,
      std::shared_ptr<Value<float> > znear,
      std::shared_ptr<Value<float> > zfar) {

    this->fov = fov;
    this->aspect = aspect;
    this->znear = znear;
    this->zfar = zfar;
  }

  void setFrustum(float left, float right, float bottom, float top, float near, float far);

  void setPerspective(float fov, float aspect, float znear, float zfar);

  void lookAt(Vector3D eye, Vector3D target, Vector3D up);

  void update();

  std::vector<float>& getTransformMat() { return transform; }

  std::vector<float>& getProjectionMat() { return projection; }

private:
  std::shared_ptr<Value<Vector3D> > eye;
  std::shared_ptr<Value<Vector3D> > target;
  std::shared_ptr<Value<Vector3D> > up;

  std::shared_ptr<Value<float> > fov;
  std::shared_ptr<Value<float> > aspect;
  std::shared_ptr<Value<float> > znear;
  std::shared_ptr<Value<float> > zfar;

  std::vector<float> transform;
  std::vector<float> projection;
};

}  // namespace zbe

#endif  // ZBE_TOOLS_GRAPHICS_CAMERA_H_
