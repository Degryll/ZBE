  /**
 * Copyright 2012 Batis Degryll Ludo
 * @file Adaptor.h
 * @since 2017-03-15
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief class ZBEAPI that adapts an entity to an avatar.
 */
#ifndef ZBE_CORE_ENTITIES_ADAPTOR_H_
#define ZBE_CORE_ENTITIES_ADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/tools.h"

#include "ZBE/core/system/system.h"

namespace zbe{

/** \brief class ZBEAPI that adapts an entity to an avatar.
 */
template<typename T>
class Adaptor : virtual public Covariance_Traits<Adaptor<typename T::Base>,  typename T::Base>::Type {
public:

  /** \brief Virtual destructor.
   */
  virtual ~Adaptor() {}

  /** \brief returns avatar
   *  \return the avatar
   */
  virtual T* getAvatar() = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ADAPTOR_H_
