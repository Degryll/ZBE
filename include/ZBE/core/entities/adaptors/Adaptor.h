/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Adaptor.h
 * @since 2017-03-15
 * @date 2017-03-15
 * @author Batis Degryll Ludo
 * @brief Class that adapts an entity to an avatar.
 */

#include <memory>

#ifndef ZBE_CORE_ENTITIES_ADAPTOR_H_
#define ZBE_CORE_ENTITIES_ADAPTOR_H_

namespace zbe{

template<typename T>
class Adaptor {
public:
  virtual ~Adaptor() {}
  virtual T* getAvatar() = 0;
};
}

#endif  // ZBE_CORE_ENTITIES_ADAPTOR_H_
