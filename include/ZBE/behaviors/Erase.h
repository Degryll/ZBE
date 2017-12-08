/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Erase.h
 * @since 2017-11-05
 * @date 2017-11-05
 * @author Degryll Ludo Batis
 * @brief Erase given avatar.
 */

#ifndef ZBE_BEHAVIORS_ERASE_H_
#define ZBE_BEHAVIORS_ERASE_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Avatar.h"


namespace zbe {

/** \brief Erase given avatar.
 */
class Erase : virtual public Behavior<Avatar> {
  public:

    /** \brief Virtual destructor.
     */
    virtual ~Erase() {}

    /** \brief Changes the entity velocity with the accumulated normals.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<Avatar> > aec) {
      Avatar* avatar;
      assignAvatar(aec, &avatar);
      avatar->setERASED();
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_ERASE_H_