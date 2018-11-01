/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bouncer.h
 * @since 2017-03-07
 * @date 2017-05-09
 * @author Batis Degryll Ludo
 * @brief This define an avatar of an entity that can bounce with multiple normals.
 */

#ifndef ZBE_ENTITIES_AVATARS_BOUNCER_H_
#define ZBE_ENTITIES_AVATARS_BOUNCER_H_

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/entities/avatars/Movable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar of an entity that can bounce with multiple normals.
 */
template <unsigned s>
class Bouncer : virtual public Movable<s> {
  public:
    using Base = Movable<s>;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Bouncer() {}

    /** \brief Adds a normal to current bounce measurement
     * \param normal Normal value to add
     */
  	virtual void addNormal(const Vector<s>& normal) = 0;

    /** \brief Return the current normal sum.
     * \return The current normal sum.
     */
  	virtual Vector<s> getNormalSum() = 0;

    /** \brief Tells if there is normals added.
     * \return True if there is normals added.
     */
  	virtual bool hasNormals() = 0;

    /** \brief Clean the current normal measurement.
     */
  	virtual void clearNormals() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_BOUNCER_H_
