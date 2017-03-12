/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerEntity.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Entity that can be seen as a Bouncer.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERENTITY_H_

#include <memory>

#include "ZBE/entities/adaptors/BouncerAdaptor.h"
#include "ZBE/entities/avatars/Bouncer.h"

namespace zbe {

/** \brief Entity that can be seen as a Bouncer.
 */
template <unsigned s>
class BouncerEntity {
  public:
    virtual ~BouncerEntity(){}

    virtual std::shared_ptr< Bouncer<s> > getBouncer() = 0;

};

/** \brief Entity that can be seen as a Bouncer using an adaptor.
 */
template <typename T, unsigned s>
class BouncerEntityAdapted : public BouncerEntity<s> {
  public:
    BouncerEntityAdapted(const BouncerEntityAdapted&) = delete;
    void operator=(const BouncerEntityAdapted&) = delete;

    BouncerEntityAdapted(T* entity) : entity(entity), a(nullptr) {}

    virtual ~BouncerEntityAdapted(){}

    void setBouncerAdaptor(BouncerAdaptor<T, s> *adaptor) {a = adaptor;}

    std::shared_ptr< Bouncer<s> > getBouncer() {return (a->getBouncer(entity));}

  private:
    T* entity;
    BouncerAdaptor<T, s> *a;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERENTITY_H_
