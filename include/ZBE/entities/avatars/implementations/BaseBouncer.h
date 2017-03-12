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

namespace zbe {

/** \brief This implements a base 1:1 avatar that can bounce.
 */
template <unsigned s>
class BaseBouncer : virtual public Bouncer<s> {
  public:
    BaseBouncer(const BaseBouncer<s>&) = delete;
    void operator=(const BaseBouncer<s>&) = delete;

    BaseBouncer(Bouncing<s>* bouncing) : b(bouncing) {}

    void addNormal(const Vector<s>& normal) {b->addNormal(normal);}
  	Vector<s> getNormalSum() {return b->getNormalSum();}
  	bool hasNormals() {return b->hasNormals();}
  	void clearNormals() {b->clearNormals();}

  private:
  	Bouncing<s>* b;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEBOUNCER_H_
