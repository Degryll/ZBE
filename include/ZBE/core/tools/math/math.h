/**
 * Copyright 2011 Batis Degryll Ludo
 * @file math.h
 * @since 2015/05/16
 * @date 2015/05/19
 * @author Degryll
 * @brief Math constant
 */

#ifndef ZBE_CORE_TOOLS_MATH_MATH_H_
#define ZBE_CORE_TOOLS_MATH_MATH_H_

#include <utility>
#include <initializer_list>
#include <cstdio>

namespace zbe {

/** \brief The value of PI as 3.14159265358979323846.
 */
static const double PI = 3.14159265358979323846;
/** \brief Multiply an angle in degrees by TORADIANS to get the angle in radians.
    \sa TODEGREE
 */
static const double TORADIANS = PI/180.0;
/** \brief Multiply an angle in radians by TODEGREES to get the angle in degrees.
    \sa TORADIANS
 */
static const double TODEGREE = 180.0/PI;
/** \brief This constant is used to transform the time from a velocity (in
 *  seconds, because the velocity is in m/s) to the time stored in a uint64_t (nanoseconds).
 */
static const double VELOCITYTOTIME = 1.0e9;

/** \brief This constant is used to transform the time stored in a uint64_t (nanoseconds)to the time in a velocity (in
 *  seconds, because the velocity is in m/s).
 */
static const double TIMETOVELOCITY = 1.0e-9;
}
#endif  // ZBE_CORE_TOOLS_MATH_MATH_H_
