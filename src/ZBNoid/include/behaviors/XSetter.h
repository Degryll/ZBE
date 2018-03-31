/**
 * Copyright 2012 Batis Degryll Ludo
 * @file XSetter.h
 * @since 2017-10-16
 * @date 2017-10-16
 * @author Degryll Ludo Batis
 * @brief Behavior that sets x position from a given Value.
 */

#ifndef ZOMBIENOID_BEHAVIORS_XSETTER_H_
#define ZOMBIENOID_BEHAVIORS_XSETTER_H_

#include <memory>

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Positionable.h"

namespace zombienoid {

/** \brief Behavior that sets x position from a given Value.
 */
class XSetter : virtual public zbe::Behavior<zbe::Positionable<2> > {// : public Behavior<Element2D<R> > {
public:

  XSetter(std::shared_ptr<zbe::Value<double> > position) : p(position) {}

  ~XSetter(){}

  /**\brief Sets x position of the entity to given Value<double>.
  */
  void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > entity) {
    zbe::Positionable<2>* positionable;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > aecp2 = entity;
    assignAvatar(aecp2 , &positionable);
    positionable->setPosition({p->getValue(), positionable->getPosition().y});
  }

private:

  std::shared_ptr<zbe::Value<double> > p;

};

}  // namespace zombienoid

#endif  // ZOMBIENOID_BEHAVIORS_XSETTER_H_
