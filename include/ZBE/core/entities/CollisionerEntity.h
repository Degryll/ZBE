/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollsionerEntity.h
 * @since 2016-03-26
 * @date 2016-03-26
 * @author Degryll
 * @brief Every Collisioner (an entity involved in a collision) has a type.
 */

#ifndef CORE_ENTITIES_COLLISIONERENTITY_H_
#define CORE_ENTITIES_COLLISIONERENTITY_H_

#include "ZBE/core/entities/Entity.h"

namespace zbe {

/** \brief Every Collisioner (an entity involved in a collision) has a type.
 */
class CollisionerEntity : public Entity {
  public:
    /** \brief Empty destructor.
      */
    virtual ~CollisionerEntity() {}

    /** \brief Set the type of collisioner this entity is.
     *  \param type Type of the collisioner.
     */
    inline void setCollisionerType(uint64_t type) {t = type;}

    /** \brief Return the type of collisioner.
     *  \return Type of the collsioner.
     */
    inline uint64_t getCollisionerType() {return (t);}

  private:
    uint64_t t;  //!< Collisioner type
};

}  // namespace zbe

#endif  // CORE_ENTITIES_COLLISIONERENTITY_H_
