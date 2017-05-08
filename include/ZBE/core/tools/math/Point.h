/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Point.h
 * @since 2015/05/16
 * @date 2017/02/26
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

/** \brief A base class that represent Points of any dimension.
 *
 *  Not use this class, use Point<s>.
 *
 *  \sa Point
 */
template<unsigned s>
class _POINT {
  public:

    /** \brief Void constructor, the point's values are unknown.
     */
    _POINT() {}

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
    _POINT(const std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("Point ERROR: Initializer list size is incorrect.");
        return;
      }

      int i = 0;
      for(auto it : l) {
        data[i++] = it;
      }
    }

    /** \brief Virtual destructor (this class is a base class).
     */
    virtual ~_POINT() {}

//    _POINT& operator=(_POINT rhs) {
//      std::swap(this->data, rhs.data);
//      return (*this);
//    }

    _POINT& operator=(const std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("Point ERROR: Initializer list size is incorrect.");
        return (*this);
      }

      int i = 0;
      for(auto it : l) {
        data[i++] = it;
      }

      return (*this);
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

    /** \brief Translate this point in the direction of a Vector.
     *
     * \param rhs Vector in which you want to move the Point.
     * \return A reference to this point.
     * \sa operator*=()
     */
    _POINT& operator+=(Vector<s> rhs) {
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
    _POINT& operator*=(double rhs) {
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
    friend _POINT operator+(_POINT lhs, const Vector<s>& rhs) {
      return (lhs+=rhs);
    }

    /** \brief Calculate the Vector that connects two Points.
     *
     * \param lhs The initial Point.
     * \param rhs The destiny Point.
     * \return A Vector that translate the initial Point to the destination
     *         Point.
     */
    friend Vector<s> operator-(const _POINT& lhs, const _POINT& rhs) {
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
    friend _POINT operator*(_POINT lhs, double rhs) {
      return (lhs *= rhs);
    }

  protected:
    double data[s];  //!< Point data.
};

/** \brief A class that represent Points of any dimension.
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Point belongs.
 */
template <unsigned s>
class Point : public _POINT<s> {
  public:
    /** \brief Void constructor, the Point's values are unknown.
     */
    Point() : _POINT<s>() {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point of N dimension with a list of N values:
     *
     *        Point<N> p({v1, v2, ... , vN})
     *
     *  or
     *
     *        Point<N> p = {v1, v2, ... , vN}
     *
     */
    Point(std::initializer_list<double> l) : _POINT<s>(l) {}
};

/** \brief A class that represent 2D points.
 *
 *  Point2D is an alias of Point<2>.
 *
 *  This specialization let you access with the alias .x or .y to the first and second dimension of the 2D point.
 */
template <>
class Point<2> : public _POINT<2> {
  public:
    double &x;  //!< An alias to access the first dimension as p.x.
    double &y;  //!< An alias to access the second dimension as p.y.

    /** \brief Void constructor, the Point's values are unknown.
     */
    Point() : _POINT<2>(), x(data[0]), y(data[1]) {}

    /** \brief A copy constructor.
     */
    Point(const Point<2>& p) : _POINT<2>(p), x(data[0]), y(data[1]) {}

    /** \brief A copy constructor with _POINT<2>.
     */
    Point(const _POINT<2>& p) : _POINT<2>(p), x(data[0]), y(data[1]) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point2D with a list of 2 values:
     *
     *        Point2D p({v1, v2})
     *
     *  or
     *
     *        Point2D p = {v1, v2}
     *
     */
    Point(std::initializer_list<double> l) : _POINT(l), x(data[0]), y(data[1]) {}

    /** \brief Assign operator.
     */
    Point& operator=(Point<2> rhs) {_POINT<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _POINT<2> classes to Point<2>.
     */
    Point& operator=(_POINT<2> rhs) {_POINT<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign initializer lists to Point<2>.
     */
    Point& operator=(std::initializer_list<double> l) {_POINT<2>::operator=(l); return (*this);}
};

using Point2D = Point<2>;  //!< An alias to Point<2>.

/** \brief A class that represent 3D points.
 *
 *  Point3D is an alias of Point<3>.
 *
 *  This specialization let you access with the alias .x, .y or .z to the first, second or third dimension of the 3D point.
 */
template <>
class Point<3> : public _POINT<3> {
  public:
    double &x;  //!< An alias to access the first dimension as p.x.
    double &y;  //!< An alias to access the second dimension as p.y.
    double &z;  //!< An alias to access the third dimension as p.z.

    /** \brief Void constructor, the Point's values are unknown.
     */
    Point() : _POINT<3>(), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A copy constructor.
     */
    Point(const Point<3>& p) : _POINT<3>(p), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A copy constructor with _POINT<3>.
     */
    Point(const _POINT<3>& p) : _POINT<3>(p), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Point3D with a list of 3 values:
     *
     *        Point2D p({v1, v2, v3})
     *
     *  or
     *
     *        Point2D p = {v1, v2, v3}
     *
     */
    Point(std::initializer_list<double> l) : _POINT(l), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief Assign operator.
     */
    Point& operator=(Point<3> rhs) {_POINT<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _POINT<3> classes to Point<3>.
     */
    Point& operator=(_POINT<3> rhs) {_POINT<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign initializer lists to Point<3>.
     */
    Point& operator=(std::initializer_list<double> l) {_POINT<3>::operator=(l); return (*this);}
};

using Point3D = Point<3>;  //!< An alias to Point<3>.

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_POINT_H_
