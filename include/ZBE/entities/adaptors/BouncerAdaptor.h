/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerAdaptor.h
 * @since 2017-03-09
 * @date 2017-03-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a bouncer.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BOUNCERADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BOUNCERADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Bouncer.h"

namespace zbe {

/** \brief Template that adapts an entity to a bouncer.
 */
template <typename T, unsigned s>
class BouncerAdaptor {
  public:
  ~BouncerAdaptor(){}
    virtual std::shared_ptr<Bouncer<s> > getBouncer(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BOUNCERADAPTOR_H_
