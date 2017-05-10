/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovableCollisionator.h
 * @since 2017-03-09
 * @date 2017-03-09
 * @author Degryll Ludo Batis
 * @brief This implements a base 1:1 avatar that can bounce.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEBOUNCER_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEBOUNCER_H_

#include "ZBE/archetypes/Bouncing.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can bounce.
 */
template <unsigned s>
class BaseBouncer : virtual public Bouncer<s>, public BaseMovable<s> {
  public:
    BaseBouncer(const BaseBouncer<s>&) = delete;
    void operator=(const BaseBouncer<s>&) = delete;

    /** \brief Builds this BaseBouncer with a Bouncing.
     */
    BaseBouncer(Bouncing<s>* bouncing): BaseMovable<s>(bouncing), b(bouncing) {}

    /** \brief Adds a normal to current bounce measurement
     * \param normal Normal value to add
     */
    void addNormal(const Vector<s>& normal) {b->addNormal(normal);}

    /** \brief Return the current normal sum.
     * \return The current normal sum.
     */
  	Vector<s> getNormalSum() {return b->getNormalSum();}

    /** \brief Tells if there is normals added.
     * \return True if there is normals added.
     */
  	bool hasNormals() {return b->hasNormals();}

    /** \brief Clean the current normal measurement.
     */
  	void clearNormals() {b->clearNormals();}

  private:
  	Bouncing<s>* b;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEBOUNCER_H_
