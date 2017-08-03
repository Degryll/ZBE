/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Stated.h
 * @since 2017-06-05
 * @date 2017-06-06
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that will have a state.
 */

#ifndef ZBE_ENTITIES_AVATARS_STATED_H_
#define ZBE_ENTITIES_AVATARS_STATED_H_

#include <cstdint>

namespace zbe {

/** \brief This defines an avatar that will have a state.
 */
class Stated {
  public:
    using Base = void;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Stated() {}

    virtual void setState(uint64_t state) = 0;

    virtual uint64_t getState() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_STATED_H_
