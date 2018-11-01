/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleModel.h
 * @since 2018-06-10
 * @date 2018-06-10
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in 3D.
 */

#ifndef ZBE_ENTITIES_AVATARS_SINGLEMODEL_H_
#define ZBE_ENTITIES_AVATARS_SINGLEMODEL_H_

#include <cstdint>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in 3D.
 */
class SingleModel {

public:

  using Base = void; //!< Inheritance info.

  /** \brief Virtual Destructor.
   */
  virtual ~SingleModel() {};

  /** \brief Returns the position.
   *  \return x.
   */
  virtual Point3D getPosition() = 0;

  /** \brief Returns the model scale.
   *  \return scale.
   */
  virtual float getScale() = 0;

  /** \brief Returns the model orientation.
   *  \return scale.
   */
  virtual Vector3D getOrientation() = 0;

  /** \brief Returns the model angle in rads.
   *  \return angle in rads.
   */
  virtual float getAngle() = 0;

  /** \brief Returns graphics.
   *  \return graphics.
   */
  virtual uint64_t getGraphics() = 0;

};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_SINGLEMODEL_H_
