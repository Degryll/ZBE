/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeStamp.h
 * @since 2017-06-07
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Archetype for an entity with a time stamp.
 */

#ifndef ZBE_ARCHETYPES_TIMESTAMP_H
#define ZBE_ARCHETYPES_TIMESTAMP_H

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Archetype for an entity with a time stamp.
 */
class ZBEAPI TimeStamp {
public:
  /** \brief Virtual destructor.
   */
  virtual ~TimeStamp() {}

  /** \brief Returns a time stamp.
   *  \return The time stamp.
   */
  virtual int64_t getTimeStamp() = 0;

  /** \brief Set the time stamp.
   *  \param timeStamp The value of the time stamp.
   */
  virtual void setTimeStamp(int64_t timeStamp) = 0;

};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_TIMESTAMP_H
