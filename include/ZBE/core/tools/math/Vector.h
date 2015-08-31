/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector2d.h
 * @since 2010/07/22
 * @date 2015/05/21
 * @author Ludo and Degryll
 * @brief Math Vector definition
 */

#ifndef ZBE_CORE_TOOLS_MATH_VECTOR_H_
#define ZBE_CORE_TOOLS_MATH_VECTOR_H_

#include <utility>
#include <initializer_list>

#include <cmath>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template<unsigned s>
class Vector {
  public:

    Vector() {}
    Vector(std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("Vector ERROR: Initializer list size is incorrect.");
        return;
      }
      int i = 0;
      for(auto it = l.begin(); it != l.end(); it++, i++) {
        data[i] = *it;
      }
    }

          double& operator[](std::size_t idx)       {return (data[idx]);}
    const double& operator[](std::size_t idx) const {return (data[idx]);}

    Vector<s>& operator+=(Vector<s> rhs);
    Vector<s>& operator-=(Vector<s> rhs);
    Vector<s>& operator-();
    Vector<s>& operator*=(double rhs);
    //double getAngle(const Vector& rhs);  // TODO espero a necesitarlo
    //Vector& reflect(const Vector& rhs);  // TODO espero a necesitarlo

    double getModule();
    double getSqrModule();  // to avoid square root

///////////////////////////////////////////////////////////////////////////////
// Friend Functions
///////////////////////////////////////////////////////////////////////////////

    // Degryll usar operador += que pa eso esta
    friend Vector operator+(Vector lhs, const Vector& rhs) {
      for(unsigned i = 0; i < s; i++) {
        lhs.data[i] += rhs.data[i];
      }

      return (lhs);
    }

    friend Vector operator+(Vector& lhs, Vector&& rhs) {
      for(unsigned i = 0; i < s; i++) {
        rhs.data[i] += lhs.data[i];
      }

      return (rhs);
    }

    friend Vector operator-(Vector lhs, const Vector& rhs) {
      return (lhs-=rhs);
    }

    friend Vector operator-(const Vector& lhs, Vector&& rhs) {
      return (rhs-=lhs);
    }

    friend Vector operator*(Vector lhs, double rhs) {
      for(unsigned i = 0; i < s; i++) {
        lhs.data[i] *= rhs;
      }

      return (lhs);
    }

    friend double operator*(const Vector& lhs, const Vector& rhs) {
      double v = 0;
      for(unsigned i = 0; i < s; i++) {
        v += lhs.data[i] * rhs.data[i];
      }

      return (v);
    }

    //friend double getAngle(Vector2D lhs, const Vector2D& rhs);  // TODO espero a necesitarlo
    //friend Vector2D reflect(Vector2D lhs, const Vector2D &rhs);  // TODO espero a necesitarlo

///////////////////////////////////////////////////////////////////////////////
// END Friend Functions
///////////////////////////////////////////////////////////////////////////////

  protected:
    double data[s];
};

class Vector2D : public Vector<2> {
  public:
    double &x = data[0];
    double &y = data[1];

    Vector2D() : Vector<2>() {}
    Vector2D(const Vector<2>& v) : Vector<2>(v) {}
    Vector2D(std::initializer_list<double> l) : Vector(l) {}

    Vector2D& operator=(Vector<2> rhs) {Vector<2>::operator=(rhs); return (*this);}

    void setCartesian(double x, double y) {data[0] = x; data[1] = y;}

    void setPolars(double r, double rads) {data[0] = r*cos(rads); data[1] = r*sin(rads);}
    void setPolarsDegrees(double r, double degree) {data[0] = r*cos(degree*TORADIANS); data[1] = r*sin(degree*TORADIANS);}

    double getRads()    {return (atan2(data[0],data[1]));}
    double getDegrees() {return (atan2(data[0],data[1])*TODEGREE);}

    // reflect es comun a todos los vectores pero en 2D se puede hacer más eficiente usando polares
    //Vector2D& reflect(const Vector2D& rhs);  // TODO espero a necesitarlo
    //friend Vector2D reflect(Vector2D lhs, const Vector2D &rhs);  // TODO espero a necesitarlo
    //friend Vector2D getNormalA(Vector2D v)const;  // TODO espero a necesitarlo
    //friend Vector2D getNormalB(Vector2D v)const;  // TODO espero a necesitarlo
};

class Vector3D : public Vector<3> {
  public:
    double &x = data[0];
    double &y = data[1];
    double &z = data[2];

    Vector3D() : Vector() {}
    Vector3D(const Vector<3>& v) : Vector(v) {}
    Vector3D(std::initializer_list<double> l) : Vector(l) {}

    Vector& operator=(Vector<3> rhs) {Vector<3>::operator=(rhs); return (*this);}

    //vectorial multiplication
};

template <unsigned s>
Vector<s>& Vector<s>::operator+=(Vector<s> rhs) {
  for(unsigned i = 0; i < s; i++) {
    data[i] += rhs.data[i];
  }

  return (*this);
}

template <unsigned s>
Vector<s>& Vector<s>::operator-=(Vector<s> rhs) {
  for(unsigned i = 0; i < s; i++) {
    data[i] -= rhs.data[i];
  }

  return (*this);
}

template <unsigned s>
Vector<s>& Vector<s>::operator-() {
  for(unsigned i = 0; i < s; i++) {
    data[i] = -data[i];
  }

  return (*this);
}

template <unsigned s>
Vector<s>& Vector<s>::operator*=(double rhs) {
  for(unsigned i = 0; i < s; i++) {
    data[i] *= rhs;
  }

  return (*this);
}

template <unsigned s>
double Vector<s>::getModule() {
  double r = 0;
  for(unsigned i = 0; i < s; i++) {
    r += data[i] * data[i];
  }

  return (std::sqrt(r));
}

template <unsigned s>
double Vector<s>::getSqrModule() {
  double r2 = 0;
    for(unsigned i = 0; i < s; i++) {
    r2 += data[i] * data[i];
  }

  return (r2);
}

//Vector2D Vector2D::getNormalA()const {
//  Vector2D aux;
//  aux.setXY(y,-x);
//  return (aux);
//}
//
//Vector2D Vector2D::getNormalB()const {
//  Vector2D aux;
//  aux.setXY(-y,x);
//  return (aux);
//}
//
///**
// * @fn Vector2D::reflect
// * @param normal Vector normal to the collision plane.
// * @brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
// */
//void Vector2D::reflect(const Vector2D& normal) {
//  (*this) =  reflect((*this),normal);
//}
//
///**
// * @fn Vector2D::getRadsAB
// * @param v1 first operand
// * @param v2 second operand
// * @return angle diference between vectors in rads
// * @brief calculate angle diference between vectors in rads
// */
//double Vector2D::getRadsAB(Vector2D v1, Vector2D v2) {
//  return (fabs(v1.getRads() - v2.getRads()));
//}
//
///**
// * @fn Vector2D::reflect
// * @param ray Vector with the ray or object path.
// * @param normal Vector normal to the collision plane.
// * @return Vector with the ray or object path reflected.
// * @brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
// */
////
////                      1 - 2(normal.x^2)
////  ray.x = ray.x * -------------------------
////                   normal.x^2 + normal.y^2
////
////                    2(normal.x * normal.y)
////        - ray.y * -------------------------
////                   normal.x^2 + normal.y^2
////
////
////                    -2(normal.x * normal.y)
////  ray.y = ray.x * -------------------------
////                   normal.x^2 + normal.y^2
////
////                      1 - 2(normal.y^2)
////        + ray.y * -------------------------
////                   normal.x^2 + normal.y^2
////
//Vector2D Vector2D::reflect(const Vector2D &ray, const Vector2D &normal) {
//  Vector2D v;
//  Vector2D normalAux = normal;
//  normalAux.setModule(1.0);
//
//  double nx = normalAux.getX();
//  double ny = normalAux.getY();
//  double nx2 = nx*nx;
//  double ny2 = ny*ny;
//  double nxy = nx*ny;
//  double nx2ny2 = nx2+ny2;
//
//  double rx = ray.getX();
//  double ry = ray.getY();
//
//  v.setX(rx * (1-(2*nx2))/(nx2ny2)-
//         ry * (2*nxy)/(nx2ny2));
//
//  v.setY(rx * (-(2*nxy))/(nx2ny2)+
//         ry * (1-(2*ny2))/(nx2ny2));
//
//  return (v);
//}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_VECTOR_H_
