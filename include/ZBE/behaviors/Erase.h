/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Erase.h
 * @since 2017-11-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Erase given avatar.
 */

#ifndef ZBE_BEHAVIORS_ERASE_H_
#define ZBE_BEHAVIORS_ERASE_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Erase given avatar.
 */
class Erase : virtual public Behavior<void> {
  public:

    /** \brief Virtual destructor.
     */
    virtual ~Erase() {}

    /** \brief Erase given avatar.
     */
    void apply(std::shared_ptr<Avatar> avatar) {
      avatar->setERASED();
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_ERASE_H_
