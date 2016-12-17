/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ReactObject.h
 * @since 2016-12-12
 * @date 2016-12-12
 * @author Batis
 * @brief
 */

#ifndef CORE_ENTITIES_AVATARS_REACTOBJECT_H
#define CORE_ENTITIES_AVATARS_REACTOBJECT_H

namespace zbe {

template <typename R>
class ReactObject {
  public:
		virtual void act(R* reactor) = 0;
};

}  // namespace

#endif //CORE_ENTITIES_AVATARS_REACTOBJECT_H
