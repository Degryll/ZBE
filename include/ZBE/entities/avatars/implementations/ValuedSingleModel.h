/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleModel.h
 * @since 2018-06-10
 * @date 2018-06-10
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in 3D.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_VALUEDSINGLEMODEL_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_VALUEDSINGLEMODEL_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/SingleModel.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in 3D.
 */
class ValuedSingleModel : public SingleModel {

public:

  ValuedSingleModel(
    std::shared_ptr<Value<float> > px, std::shared_ptr<Value<float> > py,
    std::shared_ptr<Value<float> > pz, std::shared_ptr<Value<float> > ox,
    std::shared_ptr<Value<float> > oy, std::shared_ptr<Value<float> > oz,
    std::shared_ptr<Value<float> > scale, std::shared_ptr<Value<float> > angle, std::shared_ptr<Value<uint64_t> > graphicsID)
    : px(px), py(py), pz(pz), ox(ox), oy(oy), oz(oz), scale(scale), angle(angle), graphicsID(graphicsID) {}

  /** \brief Virtual Destructor.
   */
  virtual ~ValuedSingleModel() {};

  /** \brief Returns the position.
   *  \return x.
   */
  Point3D getPosition() {
    return Point3D(px.getValue(), py.getValue(), pz.getValue());
  }

  /** \brief Returns the model scale.
   *  \return scale.
   */
  float getScale() {
    return scale.getValue();
  }

  /** \brief Returns the model orientation.
   *  \return scale.
   */
  Vector3D getOrientation() {
    return Vector3D(ox.getValue(), oy.getValue(), oz.getValue());
  }

  /** \brief Returns the model scale.
   *  \return scale.
   */
  float getAngle() {
    return angle.getValue();
  }

  /** \brief Returns graphics.
   *  \return graphics.
   */
  uint64_t getGraphics() {
    return (graphicsID.getValue());
  }

private:
  std::shared_ptr<Value<float> > px, py, pz;
  std::shared_ptr<Value<float> > ox, oy, oz;
  std::shared_ptr<Value<float> > angle;
  std::shared_ptr<Value<float> > scale;
  std::shared_ptr<Value<uint64_t> > graphicsID;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_VALUEDSINGLEMODEL_H_
