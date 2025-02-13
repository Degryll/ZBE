/**
 * Copyright 2011 Batis Degryll Ludo
 * @file math.h
 * @since 2015-05-16
 * @date 2018-03-25
 * @author Degryll Batis Ludo
 * @brief Math constants and functions
 */

#ifndef ZBE_CORE_TOOLS_MATH_MATH_H_
#define ZBE_CORE_TOOLS_MATH_MATH_H_

#include <cmath>
#include <cstdint>
#include <limits>

namespace zbe {

/** \brief Projection matrix size. 4x4
 */
static const int PROJ_MAT4 = 16;

/** \brief The value of PI as 3.14159265358979323846.
 */
static const double PI = 3.14159265358979323846;

/** \brief The value of TAU as 2 * PI (= 6. 2831853071795864769252867)
 */
static const double TAU = 2.0*PI;

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
static const double INVERSE_SECOND = 1.0 / 65536.0;

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const uint64_t TIME_QUANTUM = 256;

/** \brief This constant represent the proportion of time quantum in a second.
 */
static const double TIME_QUANTUM_VALUE = static_cast<double>(TIME_QUANTUM / SECOND);

/** \brief This constant represent the minimal amount of bits that will be used as precision.
 */
static const uint64_t ROUND_MASK = std::numeric_limits<uint64_t>::max() - (TIME_QUANTUM - 1); //-static_cast<int64_t>(TIME_QUANTUM);

/** \brief Transforms the received time from ZBE time units to miliseconds.
 * \param time Time to convert.
 */
inline uint64_t MILITOZBETU(uint64_t time) {
  return ((time << 16) / 1000);
}

/** \brief Used to round time values to its closer quantum.
 * WARNING: does not work with negative times
 * \param n Time to quantize.
 */
inline uint64_t quantizeTime(uint64_t n) {
  return (n & ROUND_MASK);
}

/** \brief Used to round time values to its closer quantum.
 * WARNING: does not work with negative times
 * \param n Time to quantize.
 */
inline uint64_t quantizeTime(double n) {
  uint64_t time = static_cast<uint64_t>(n * SECOND);
  return quantizeTime(time);
}

/** \brief Used to compare two double values.
 * \param a First number to compare
 * \param b Second number to compare
 * \param epsilon Distance to consider both equals
 */
inline bool isNearlyEqual(double a, double b, double epsilon) {
  return (std::abs(a - b) <= epsilon);
}

/** \brief Used to round values to its closer integer.
 * \param Number to be rounded.
 */
inline double round(double d) {
  return std::floor(d + 0.5);
}

/** \brief Used to round up values to (negatives values will round down).
 * \param n Number to be rounded.
 */
inline int64_t roundUp (double n) {
    return ((n > 0.0) ?  static_cast<int64_t>(ceil(n)) :  static_cast<int64_t>(floor(n)));
}

/** \brief Tells if the given double values are close enough to be cosidered equal.
 * This code is based in an example found here:
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 * ULP is fixed to value 2.
 *  \param a first double
 *  \param b second double
 */
inline bool almost_equal(double a, double b) {
    const int ulp = 2;
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(a-b) <= std::numeric_limits<double>::epsilon() * std::abs(a+b) * ulp
    // unless the result is subnormal
    || std::abs(a-b) < std::numeric_limits<double>::min();
}

/** \brief Tells if the given float values are close enough to be cosidered equal.
 * This code is based in an example found here:
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 * ULP is fixed to value 2.
 *  \param a first float
 *  \param b second float
 */
inline bool almost_equal(float a, float b) {
    const int ulp = 2;
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(a-b) <= std::numeric_limits<float>::epsilon() * std::abs(a+b) * ulp
    // unless the result is subnormal
    || std::abs(a-b) < std::numeric_limits<float>::min();
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_MATH_H_
