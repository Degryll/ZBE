/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Stated.h
 * @since 2017-06-05
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that will have a state.
 */

#ifndef ZBE_ENTITIES_AVATARS_STATED_H_
#define ZBE_ENTITIES_AVATARS_STATED_H_

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This defines an avatar that will have a state.
 */
class ZBEAPI Stated {
  public:
    using Base = void;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Stated() {}

    /** \brief Setter for the state
     *  \param state The integer value for the state.
     */
    virtual void setState(int64_t state) = 0;

    /** \brief Adds a value to the state.
     *  \param value The integer value to add to the state.
     */
    virtual void add(int64_t value) = 0;

    /** \brief Getter for the state.
     *  \return The integer value of the state.
     */
    virtual int64_t getState() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_STATED_H_
