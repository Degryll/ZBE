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

#include <limits>
#include <utility>
#include <initializer_list>

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

/** \brief This constant represent the amount of bits that will be used as precision digits.
 * I.E. :
 *  uint64_t v1;  // velocity in pixel / sec.
 *  uint64_t v2;  // velocity in pixel / nanosec for collision purpouses.
 *  ...
 *  v2 = v1 << PRECISION_DIGITS;
 *  ...
 *  v1 = v2 >> PRECISION_DIGITS;
 */
static const int PRECISION_DIGITS = 16;

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const int64_t TIME_QUANTUM = 256;

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const int64_t ROUND_MASK = std::numeric_limits<int64_t>::max() - 255;

  /** \brief This constant is used to transform the time stored in a uint64_t (nanoseconds)to the time in a velocity (in
 *  seconds, because the velocity is in m/s).
 */
inline uint64_t MILITOZBETU(uint32_t time) {
  return ((time << 16) / 1000);
}

inline int64_t roundPrecision(int64_t n) {
  return (n & ROUND_MASK);
}

inline void roundPrecision(int64_t *n) {
  (*n) = ((*n) & ROUND_MASK);
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_MATH_H_
