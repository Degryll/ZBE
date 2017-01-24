/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ReactObjectAdaptor.h
 * @since 2016-12-14
 * @date 2016-12-14
 * @author Batis
 * @brief Template that adapts an entity to a reactObject.
 */

#ifndef CORE_ENTITIES_ADAPTORS_REACTOBJECTADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_REACTOBJECTADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/collisions/ReactObject.h"

namespace zbe {

/** \brief Template that adapts an entity to a reactObject.
 */
template <typename T, typename R>
class ReactObjectAdaptor {
  public:
    virtual std::shared_ptr<ReactObject<R> > getReactObject(T* entity) = 0;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_REACTOBJECTADAPTOR_H_
