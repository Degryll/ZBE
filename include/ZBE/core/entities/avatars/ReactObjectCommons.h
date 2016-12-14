/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ReactObjectCommons.h
 * @since 2016-12-12
 * @date 2016-12-12
 * @author Batis
 * @brief
 */

#ifndef CORE_ENTITIES_AVATARS_REACTOBJECTCOMMONS_H
#define CORE_ENTITIES_AVATARS_REACTOBJECTCOMMONS_H

#include "ZBE/core/entities/avatars/ReactObject.h"

namespace zbe {

template <typename T>
class ReactObjectCommons : public ReactObject {
  public:
    ReactObjectCommons(const ReactObjectCommons&) = delete;
    void operator=(const ReactObjectCommons&) = delete;

  	ReactObjectCommons(T* rObject) : rObject(rObject) {}

    void act(Reactor* reactor) {
      reactor->act(rObject);
    }

  private:
    T* rObject;
};

}  // namespace

#endif //CORE_ENTITIES_AVATARS_REACTOBJECTCOMMONS_H
