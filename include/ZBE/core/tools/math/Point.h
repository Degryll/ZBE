/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Point.h
 * @since 2015/05/16
 * @date 2015/12/01
 * @author Degryll
 * @brief Math Point definitions
 */

#ifndef ZBE_CORE_TOOLS_MATH_POINT_H_
#define ZBE_CORE_TOOLS_MATH_POINT_H_

#include <initializer_list>

#include "ZBE/core/system/SysError.h"

namespace zbe {

template <unsigned s>
class Vector;

/** \brief A class that represent Points of any dimension.
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Point belongs.
 */
template<unsigned s>
class Point {
  public:

    /** \brief Void constructor, the Point's values are unknown.
     */
    Point() {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point of N dimension with a list of N values:
     *
     *        Point<N> p(v1, v2, ... , vN)
     *
     *  or
     *
     *        Point<N> p = {v1, v2, ... , vN}
     *
     */
    Point(const std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("Point ERROR: Initializer list size is incorrect.");
        return;
      }

      int i = 0;
      for(auto it = l.begin(); it != l.end(); it++) {
        data[i++] = *it;
      }
    }

    /** \brief Implements direct access to Point values with operator[].
     *
     *  No bound checking is performed, the behavior accessing an out of bound
     *  index is undefined.
     *
     * \param idx Index of the dimension that you want to get the value.
     * \return The value of the idx dimension.
     */
          double& operator[](std::size_t idx)       {return (data[idx]);};

    /** \brief Implements direct access to Point values with operator[].
     *
     *  No bound checking is performed, the behavior accessing an out of bound
     *  index is undefined.
     *
     * \param idx Index of the dimension that you want to get the value.
     * \return The constant value of the idx dimension.
     */
    const double& operator[](std::size_t idx) const {return (data[idx]);};

    /** \brief Translate a Point in the direction of a Vector.
     *
     * \param rhs Vector in which you want to move the Point.
     * \return A reference to this Point.
     * \sa operator*=()
     */
    Point& operator+=(Vector<s> rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] += rhs[i];
      }

      return (*this);
    }

    /** \brief Multiply a Point by a scalar.
     *
     *  The resulting Point is as follows:
     *
     *        Point<2> p(1,2);
     *        p *= 3;
     *
     *  p values are (3,6).
     *
     * \param rhs The scalar.
     * \return A reference to this Point.
     * \sa operator+=()
     */
    Point& operator*=(double rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] *= rhs;
      }

      return (*this);
    }

    /** \brief Translate a Point in the direction of a Vector.
     *
     * \param lhs The initial Point.
     * \param rhs Vector in which you want to move the Point.
     * \return A new Point with the result of the translation.
     */
    friend Point operator+(Point lhs, const Vector<s>& rhs) {
      return (lhs+=rhs);
    }

    /** \brief Calculate the Vector that connects two Points.
     *
     * \param lhs The initial Point.
     * \param rhs The destiny Point.
     * \return A Vector that translate the initial Point to the destination
     *         Point.
     */
    friend Vector<s> operator-(const Point& lhs, const Point& rhs) {
      Vector<s> v;
      for(unsigned i = 0; i < s; i++) {
        v[i] = lhs.data[i] - rhs.data[i];
      }

      return (v);
    }

    /** \brief Multiply a Point by a scalar.
     *
     *  The resulting Point is as follows:
     *
     *        Point<2> p(1,2);
     *        Point<2> q = p * 3;
     *
     *  q values are (3,6).
     *
     * \param lhs The initial Point.
     * \param rhs The scalar.
     * \return The resulting Point of multiplying the initial point by the
     *         scalar.
     */
    friend Point operator*(Point lhs, double rhs) {
      for(unsigned i = 0; i < s; i++) {
        lhs.data[i] *= rhs;
      }

      return (lhs);
    }

  protected:
    double data[s];  //!< Point data.
};

/** \brief An aliases of a Point<2>.
 *
 *  Used to implement some functionality of a 2 dimensional Point.
 */
class Point2D : public Point<2> {
  public:
    double &x = data[0];  //!< An alias to access the first dimension as p.x.
    double &y = data[1];  //!< An alias to access the second dimension as p.y.

    /** \brief Void constructor, the Point2D's values are unknown.
     */
    Point2D() {}

    /** \brief A copy constructor with Point<2>.
     */
    Point2D(const Point<2>& p) : Point<2>(p) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point2D with a list of 2 values:
     *
     *        Point2D p(v1, v2)
     *
     *  or
     *
     *        Point2D p = {v1, v2}
     *
     */
    Point2D(std::initializer_list<double> l) : Point(l) {}

    /** \brief This class let you compare Point<2> with Point2D classes.
     */
    Point2D& operator=(Point<2> rhs) {Point<2>::operator=(rhs); return (*this);}
};

/** \brief An aliases of a Point<3>.
 *
 *  Used to implement some functionality of a 3 dimensional Point.
 */
class Point3D : public Point<3> {
  public:
    double &x = data[0];  //!< An alias to access the first dimension as p.x.
    double &y = data[1];  //!< An alias to access the second dimension as p.y.
    double &z = data[2];  //!< An alias to access the third dimension as p.z.

    /** \brief Void constructor, the Point3D's values are unknown.
     */
    Point3D() {}

    /** \brief A copy constructor with Point<3>.
     */
    Point3D(const Point<3>& p) : Point<3>(p) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point3D with a list of 3 values:
     *
     *        Point3D p(v1, v2, v3)
     *
     *  or
     *
     *        Point3D p = {v1, v2, v3}
     *
     */
    Point3D(std::initializer_list<double> l) : Point(l) {}

    /** \brief This class let you compare Point<3> with Point3D classes.
     */
    Point3D& operator=(Point<3> rhs) {Point<3>::operator=(rhs); return (*this);}
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_POINT_H_
