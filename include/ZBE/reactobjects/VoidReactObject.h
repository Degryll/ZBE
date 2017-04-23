/**
 * Copyright 2012 Batis Degryll Ludo
 * @file VoidReactObject.h
 * @since 2017-01-24
 * @date 2017-01-24
 * @author Degryll
 * @brief Simple implementations of null react objects.
 */

#ifndef ZBE_REACTOBJECTS_VOIDREACTOBJECT
#define ZBE_REACTOBJECTS_VOIDREACTOBJECT

#include "ZBE/core/events/generators/util/ReactObject.h"

namespace zbe {

template <typename R>
class VoidReactObject : public ReactObjectCommon<VoidReactObject<R>, R> {
public:
  VoidReactObject() : zbe::ReactObjectCommon<VoidReactObject<R>, R>(this) {}
  virtual ~VoidReactObject() {}
};

} //namespace zbe

#endif //ZBE_REACTOBJECTS_VOIDREACTOBJECT
