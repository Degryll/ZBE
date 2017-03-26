  /**
 * Copyright 2012 Batis Degryll Ludo
 * @file Adaptor.h
 * @since 2017-03-15
 * @date 2017-03-15
 * @author Batis Degryll Ludo
 * @brief Class that adapts an entity to an avatar.
 */

#include <memory>

#include "ZBE/core/tools/tools.h"

#ifndef ZBE_CORE_ENTITIES_ADAPTOR_H_
#define ZBE_CORE_ENTITIES_ADAPTOR_H_

namespace zbe{

template<typename T>
class Adaptor : virtual public Covariance_Traits<Adaptor<typename T::Base>,  typename T::Base>::Type {
public:
  virtual ~Adaptor() {}
  virtual T* getAvatar() = 0;
};
}

#endif  // ZBE_CORE_ENTITIES_ADAPTOR_H_
