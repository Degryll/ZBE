/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheet.h
 * @since 2018-06-09
 * @date 2018-06-09
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZBE_OGL_GRAPHICS_OGLMODELSHEET_H_
#define ZBE_OGL_GRAPHICS_OGLMODELSHEET_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/system/system.h"

#include "ZBE/OGL/graphics/OGLModel.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
template<typename T, typename ...Ts>
class OGLModelSheet {
public:

  /** \brief Virtual destructor
  */
  virtual ~OGLModelSheet() {} //!< Virtual destrutor.

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  virtual OGLModel generateModel(std::shared_ptr<MAvatar<T, Ts...> > avatar) = 0;

};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_OGLMODELSHEET_H_
