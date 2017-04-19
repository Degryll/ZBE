/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Generator.h
 * @since 2016-06-05
 * @date 2017-03-26
 * @author Batis Degryll Ludo
 * @brief Generate events.
 */

#ifndef CORE_EVENTS_GENERATOR_H
#define CORE_EVENTS_GENERATOR_H

#include <cstdint>

namespace zbe {

/** \brief Generate events.
 */
class Generator {
  public:

    /** \brief Empty destructor.
    */
    virtual ~Generator() {};

    virtual void generate() = 0;
};


}  // namespace zbe

#endif // CORE_EVENTS_GENERATOR_H
