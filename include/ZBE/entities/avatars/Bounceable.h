/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bounceable.h
 * @since 2016-12-17
 * @date 2018-02-25
 * @author Batis
 * @brief This define an avatar in which others can bounce.
 */

#ifndef ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_
#define ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar in which others can bounce.
 */
class ZBEAPI Bounceable {
  public:
    using Base = void; //!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Bounceable() {};

    /** \brief Return the bounce factor.
     * \return The bounce factor.
     */
    virtual double getFactor() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_
