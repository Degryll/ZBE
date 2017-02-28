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

///** \brief This constant represent the amount of bits that will be used as precision digits.
// * I.E. :
// *  uint64_t v1;  // velocity in pixel / sec.
// *  uint64_t v2;  // velocity in pixel / nanosec for collision purpouses.
// *  ...
// *  v2 = v1 << PRECISION_DIGITS;
// *  ...
// *  v1 = v2 >> PRECISION_DIGITS;
// */
//static const int PRECISION_DIGITS = 16;
//
///** \brief This constant represent the minimal value that will keep its value after be rounded.
// */
//static const int64_t PRECISION_VALUE = (1 << zbe::PRECISION_DIGITS);
//
///** \brief This constant represent half the minimal value that will keep its value after be rounded.
// * Used to test if a value must be rounded up or down.
// */
//static const int64_t HALF_PRECISION_VALUE = PRECISION_VALUE/2;
//
///** \brief This constant represent the amount of bits that will be used as precision digits
// * before (and after) make a division.
// * I.E. :
// * instead of : v1 / v2 do ((v1 << DIV_PRECISION_DIGITS)/v2) >> DIV_PRECISION_DIGITS)
//*/
//static const int DIV_PRECISION_DIGITS = PRECISION_DIGITS+1;

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
inline uint64_t MILITOZBETU(uint32_t time) {
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

/*inline int64_t div(int64_t lhs, int64_t rhs){
  int64_t result = (lhs << DIV_PRECISION_DIGITS) / rhs;
  int64_t absResult =  llabs(result);
  int round = absResult & 1;
  return ((absResult+round) >> 1) * ((result>=0)*2-1);
}

inline int64_t mult(int64_t lhs, int64_t rhs){
  int64_t result = lhs * rhs;
  int64_t absResult = llabs(result);
  int round = (absResult >> (PRECISION_DIGITS-1)) & 1;
  absResult = (absResult >> PRECISION_DIGITS);
  return (absResult + round) * ((result>=0)*2-1);
}*/

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_MATH_H_
