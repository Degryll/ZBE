/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionatorAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-23
 * @author Degryll
 * @brief Template that adapts an entity to a collisionator.
 */

#ifndef CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_

#include <memory>

#include "ZBE/core/entities/avatarentities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/adaptors/Adaptor.h"

namespace zbe {

/** \brief Template that adapts an entity to a collisionator.
 */
template <typename T, typename R>
class BaseCollisionerAdaptor : public Adator<Collisioner<R> >{
public:
  	BaseCollisionerAdaptor(AvatarEntity<T>* aet, AvatarEntity<ReactObject<R> >* aero, AvatarEntity<CollisionObject<R> >* aeco) : aet(aet), aero(aero), aeco(aeco) {}
    virtual ~BaseCollisionerAdaptor() {}

    void getCollisionator(Collisioner<R>** entity) {
      //CollisionerCommon(T * collisioner, std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList);
      T* t;
      T* t;
      Collisioner<R>* coner = new CollsionerCommon<T,R>
    };
private:
  AvatarEntity<T>* aet;
  AvatarEntity<ReactObject<R> >* aero;
  AvatarEntity<CollisionObject<R> >* aeco;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
