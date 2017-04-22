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

#include <math.h>
#include <cstdint>
#include <limits>
#include <utility>
#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

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

/** \brief Used to compare doubles.
 */
static const double PRECISION = 1e-9;

/** \brief This constant represent the minimal value that will keep its value after be rounded.
 */
static const int64_t SECOND = 65536;

/** \brief This constant represent 1 / second.
 */
static const double INVERSE_SECOND = 1.0 / 65536;

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const int64_t TIME_QUANTUM = 256;

/** \brief This constant represent the proportion of time quantum in a second.
 */
static const double TIME_QUANTUM_VALUE = (double)TIME_QUANTUM / SECOND;

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const int64_t ROUND_MASK = -TIME_QUANTUM;


/** \brief This constant is used to transform the time stored in a uint64_t (nanoseconds)to the time in a velocity (in
 *  seconds, because the velocity is in m/s).
 */
inline uint64_t MILITOZBETU(uint64_t time) {
  return ((time << 16) / 1000);
}

/** \brief Used to round time values to its closer quantum.
 * WARNING: does not work with negative times
 */
inline int64_t quantizeTime(int64_t n) {
  return (n & ROUND_MASK);
}

/** \brief Used to round values to its closer integer.
 */
inline double round(double d) {
  return floor(d + 0.5);
}

/** \brief Used to round up values to (negatives values will round down).
 */
inline int64_t roundUp (double n) {
    return ((n > 0) ? ceil(n) : floor(n));
}

template <unsigned dim>
inline double sqrPointDist(Point<dim> a, Point<dim> b) {
    double accum = 0;
    double localDist;
    for(unsigned i = 0; i < dim; i++) {
        localDist = b[i] - a[i];
        accum += localDist * localDist;
    }
    return accum;
};

template <unsigned dim>
inline double pointDist(Point<dim> a, Point<dim> b) {
    return sqrt(sqrPointDist(a,b));
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_MATH_H_
