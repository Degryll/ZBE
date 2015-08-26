/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Point.h
 * @since 2015/05/16
 * @date 2015/05/21
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

template<unsigned s>
class Point {
  public:

    Point() {}
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

          double& operator[](std::size_t idx)       {return (data[idx]);};
    const double& operator[](std::size_t idx) const {return (data[idx]);};

    Point& operator+=(Vector<s> rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] += rhs[i];
      }

      return (*this);
    }

    Point& operator*=(double rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] *= rhs;
      }

      return (*this);
    }

    friend Point operator+(Point lhs, const Vector<s>& rhs) {
      return (lhs+=rhs);
    }

    friend Vector<s> operator-(const Point& lhs, const Point& rhs) {
      Vector<s> v;
      for(unsigned i = 0; i < s; i++) {
        v[i] = lhs.data[i] - rhs.data[i];
      }

      return (v);
    }

    friend Point operator*(Point lhs, double rhs) {
      for(unsigned i = 0; i < s; i++) {
        lhs.data[i] *= rhs;
      }

      return (lhs);
    }

  protected:
    double data[s];
};

class Point2D : public Point<2> {
  public:
    double &x = data[0];
    double &y = data[1];

    Point2D() {}
    Point2D(std::initializer_list<double> l) : Point(l) {}

    Point2D& operator=(Point<2> rhs) {Point<2>::operator=(rhs); return (*this);}
};

class Point3D : public Point<3> {
  public:
    double &x = data[0];
    double &y = data[1];
    double &z = data[2];

    Point3D() {}
    Point3D(std::initializer_list<double> l) : Point(l) {}

    Point3D& operator=(Point<3> rhs) {Point<3>::operator=(rhs); return (*this);}
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_POINT_H_
