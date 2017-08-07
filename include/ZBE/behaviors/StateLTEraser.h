/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateLTEraser.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Degryll Ludo Batis
 * @brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

#ifndef ZBE_BEHAVIORS_STATELTERASER_H_
#define ZBE_BEHAVIORS_STATELTERASER_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/core/entities/avatars/Avatar.h"

namespace zbe {

/** \brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */
template<typename T>
  class StateLTEraser {// : public Behavior<Element2D<R> > {
  public:
    /** \brief Parametrized constructor.
        \param limit Limit below which the entity will be killed.
     */
    StateLTEraser(int64_t limit) : limit(limit){}

    /** \brief Changes the entity velocity with the accumulated normals.
     */
    void apply(std::shared_ptr<T> entity) {
      Stated* stated;
      assignAvatar<AvatarEntity<Stated>, Stated>(&(*entity), &stated);
      Avatar* avatar;
      assignAvatar<AvatarEntity<Avatar>, Avatar>(&(*entity), &avatar);
      if(stated->getState() < limit){
      	avatar->setERASED();
      }
    }
  private:
    int64_t limit;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_STATELTERASER_H_
