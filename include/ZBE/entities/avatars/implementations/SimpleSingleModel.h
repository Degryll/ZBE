/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleModel.h
 * @since 2018-06-10
 * @date 2018-06-10
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in 3D.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SimpleSINGLEMODEL_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SimpleSINGLEMODEL_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/SingleModel.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in 3D.
 */
class ZBEAPI SimpleSingleModel : public SingleModel {

public:

  SimpleSingleModel(Point3D position, Vector3D orientation, float angle, float scale, uint64_t graphicsID)
    : position(position), orientation(orientation), angle(angle), scale(scale), graphicsID(graphicsID) {}

  /** \brief Virtual Destructor.
   */
  virtual ~SimpleSingleModel() {};

  /** \brief Returns the position.
   *  \return x.
   */
  Point3D getPosition() {
    return position;
  }

  /** \brief Returns the model scale.
   *  \return scale.
   */
  float getScale() {
    return scale;
  }

  /** \brief Returns the model orientation.
   *  \return scale.
   */
  Vector3D getOrientation() {
    return orientation;
  }

  /** \brief Returns the model scale.
   *  \return scale.
   */
  float getAngle() {
    return angle;
  }

  /** \brief Returns graphics.
   *  \return graphics.
   */
  uint64_t getGraphics() {
    return graphicsID;
  }


  /** \brief Sets position value.
   *  \param position value.
   */
  void setPosition(Point3D position) {
    this->position = position;
  }

  /** \brief Sets scale value.
   *  \return scale value.
   */
  void setScale(float scale) {
    this->scale = scale;
  }

  /** \brief Sets orientation value.
   *  \return Orientation value.
   */
  void setOrientation(Vector3D orientation) {
    this->orientation = orientation;
  }

  /** \brief Sets angle value.
   *  \return Angle value.
   */
  void setAngle(float angle) {
    this->angle = angle;
  }

  /** \brief Returns graphics.
   *  \return graphics.
   */
  void setGraphics(uint64_t graphicsID) {
    this->graphicsID = graphicsID;
  }

private:
  Point3D position;
  Vector3D orientation;
  float angle;
  float scale;
  uint64_t graphicsID;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SimpleSINGLEMODEL_H_
