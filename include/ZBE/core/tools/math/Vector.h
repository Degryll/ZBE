/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector.h
 * @since 2010/07/22
 * @date 2016/01/07
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

/** \brief A class that represent Vectors of any dimension.
 *
 *  Not use this class, use Vector<s>.
 *
 *  \sa Vector
 */
template<unsigned s>
class _VECTOR {
  public:

    /** \brief Void constructor, the vector's values are unknown.
     */
    _VECTOR() {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Vector of N dimension with a list of N values:
     *
     *        Vector<N> p({v1, v2, ... , vN})
     *
     *  or
     *
     *        Vector<N> p = {v1, v2, ... , vN}
     *
     */
    _VECTOR(std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("Vector ERROR: Initializer list size is incorrect.");
        return;
      }
      int i = 0;
      for(auto it = l.begin(); it != l.end(); it++, i++) {
        data[i] = *it;
      }
    }

    /** \brief Virtual destructor (this class is a base class).
     */
    virtual ~_VECTOR() {}

//    _VECTOR& operator=(_VECTOR rhs) {
//      std::swap(this->data, rhs.data);
//      return (*this);
//    }

    /** \brief Implements direct access to Vector values with operator[].
     *
     *  No bound checking is performed, the behavior accessing an out of bound
     *  index is undefined.
     *
     * \param idx Index of the dimension that you want to get the value.
     * \return The value of the idx dimension.
     */
    double& operator[](std::size_t idx)       {return (data[idx]);}

    /** \brief Implements direct access to Vector values with operator[].
     *
     *  No bound checking is performed, the behavior accessing an out of bound
     *  index is undefined.
     *
     * \param idx Index of the dimension that you want to get the value.
     * \return The constant value of the idx dimension.
     */
    const double& operator[](std::size_t idx) const {return (data[idx]);}

    /** \brief Add a vector to this one.
     *
     * \param rhs Second Summand.
     * \return A reference to this Vector, resultant of the addition.
     * \sa operator-=(), operator-() and operator*=().
     */
    _VECTOR<s>& operator+=(_VECTOR<s> rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] += rhs.data[i];
      }

      return (*this);
    }

    /** \brief subtract a vector to this one.
     *
     * \param rhs Subtrahend.
     * \return A reference to this Vector, resultant of the subtraction.
     * \sa operator+=(), operator-() and operator*=().
     */
    _VECTOR<s>& operator-=(_VECTOR<s> rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] -= rhs.data[i];
      }

      return (*this);
    }

    /** \brief Changes the orientation of the vector changing the sign of its dimensions.
     *
     * \return A reference to the this Vector.
     * \sa operator+=(), operator-=() and operator*=().
     */
    _VECTOR<s>& operator-() {
      for(unsigned i = 0; i < s; i++) {
        data[i] = -data[i];
      }

      return (*this);
    }

    /** \brief Multiply this Vector by a scalar.
     *
     * \param rhs The scalar.
     * \return A reference to this Vector after the multiplication.
     * \sa operator+=(), operator-=() and operator-().
     */
    _VECTOR<s>& operator*=(double rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] *= rhs;
      }

      return (*this);
    }

    /** \brief Compute the Vector Module.
     *
     * \return The Vector module.
     * \sa getSqrModule().
     */
    double getModule() {
      double r = 0;
      for(unsigned i = 0; i < s; i++) {
        r += data[i] * data[i];
      }

      return (std::sqrt(r));
    }

    /** \brief Compute the squared Vector Module to avoid the square root.
     *
     * \return The squared Vector module.
     * \sa getModule().
     */
    double getSqrModule() {  // to avoid square root
      double r2 = 0;
      for(unsigned i = 0; i < s; i++) {
        r2 += data[i] * data[i];
      }

      return (r2);
    }

    /** \brief Modifies this vector setting module to 1.0.
     *
     * \return Normalized vector.
     */
    _VECTOR<s>&  normalize() {
      double m = getModule();

      for(unsigned i = 0; i < s; i++) {
        data[i] /= m;
      }

      return (*this);
    }

    /**
     * \fn _VECTOR::reflect
     * \param normal Vector normal to the collision plane.
     * \return Vector with the ray or object path reflected.
     * \brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
     */
    _VECTOR<s>& reflect(const _VECTOR<s> normal) {
      _VECTOR<s>& d = *this;
  		d = d - 2 * (d * normal) * normal;
      return (*this);
    }

    //double getAngle(const Vector& rhs);  // TODO espero a necesitarlo

///////////////////////////////////////////////////////////////////////////////
// Friend Functions
///////////////////////////////////////////////////////////////////////////////

    /** \brief Implements Vector addition.
     *
     * \param lhs First Summand.
     * \param rhs Second Summand.
     * \return A reference to the Vector resultant of the addition.
     * \sa operator-=(), operator-() and operator*=().
     */
    friend _VECTOR operator+(_VECTOR lhs, const _VECTOR& rhs) {
//      for(unsigned i = 0; i < s; i++) {
//        lhs.data[i] += rhs.data[i];
//      }

      return (lhs+=rhs);
    }

    /** \brief Implements Vector addition.
     *
     * \param lhs First Summand.
     * \param rhs Second Summand.
     * \return A reference to the Vector resultant of the addition.
     * \sa operator-=(), operator-() and operator*=().
     */
    friend _VECTOR operator+(_VECTOR& lhs, _VECTOR&& rhs) {
//      for(unsigned i = 0; i < s; i++) {
//        rhs.data[i] += lhs.data[i];
//      }

      return (rhs+=lhs);
    }

    /** \brief Implements Vector subtraction.
     *
     * \param lhs Minuend.
     * \param rhs Subtrahend.
     * \return A reference to the Vector resultant of the subtraction.
     * \sa operator+=(), operator-() and operator*=().
     */
    friend _VECTOR operator-(_VECTOR lhs, const _VECTOR& rhs) {
      return (lhs-=rhs);
    }

    /** \brief Implements Vector subtraction.
     *
     * \param lhs Minuend.
     * \param rhs Subtrahend.
     * \return A reference to the Vector resultant of the subtraction.
     * \sa operator+=(), operator-() and operator*=().
     */
    friend _VECTOR operator-(const _VECTOR& lhs, _VECTOR&& rhs) {
      return (rhs-=lhs);
    }

//    /** \brief Changes the orientation of a vector changing the sign of its dimensions.
//     *
//     * \param lhs The original Vector.
//     * \return A reference to the resulting Vector.
//     * \sa operator+(), operator-() and operator*=().
//     */
//    friend Vector<s>& operator-(Vector lhs) {
//      return (-lhs);
//    }

    /** \brief Implements Vector multiplication by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator*(_VECTOR lhs, double rhs) {
//      for(unsigned i = 0; i < s; i++) {
//        lhs.data[i] *= rhs;
//      }

      return (lhs*=rhs);
    }

    /** \brief Implements dot product.
     *
     * \param lhs First vector.
     * \param rhs Second vector.
     * \return Doct product.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend double operator*(const _VECTOR& lhs, const _VECTOR& rhs) {
      double v = 0;
      for(unsigned i = 0; i < s; i++) {
        v += lhs.data[i] * rhs.data[i];
      }

      return (v);
    }

    //friend double getAngle(Vector2D lhs, const Vector2D& rhs);  // TODO espero a necesitarlo
    friend _VECTOR reflect(_VECTOR ray, const _VECTOR &normal){
        return ray.reflect(normal);
    };

///////////////////////////////////////////////////////////////////////////////
// END Friend Functions
///////////////////////////////////////////////////////////////////////////////

  protected:
    double data[s];  //!< Vector data.
};

/** \brief A class that represent Vectors of any dimension.
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Vectors belongs to.
 */
template<unsigned s>
class Vector : public _VECTOR<s> {
  public:
    /** \brief Void constructor, the Vector's values are unknown.
     */
    Vector() : _VECTOR<s>() {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Vector of N dimension with a list of N values:
     *
     *        Vector<N> p({v1, v2, ... , vN})
     *
     *  or
     *
     *        Vector<N> p = {v1, v2, ... , vN}
     *
     */
    Vector(std::initializer_list<double> l) : _VECTOR<s>(l) {}
};

/** \brief A class that represent 2D Vectors.
 *
 *  Vector2D is an alias of Vector<2>.
 *
 *  This specialization let you access with the alias .x or .y to the first and second dimension of the 2D Vectors.
 */
template<>
class Vector<2> : public _VECTOR<2> {
  public:
    double &x;  //!< An alias to access the first dimension as v.x.
    double &y;  //!< An alias to access the first dimension as v.y.

    /** \brief Void constructor, the Vector2D's values are unknown.
     */
    Vector() : _VECTOR<2>(), x(data[0]), y(data[1]) {}

    /** \brief A copy constructor.
     */
    Vector(const Vector<2>& v) : _VECTOR<2>(v), x(data[0]), y(data[1]) {}

    /** \brief A copy constructor with _VECTOR<2>.
     */
    Vector(const _VECTOR<2>& v) : _VECTOR<2>(v), x(data[0]), y(data[1]) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Vector2D with a list of 2 values:
     *
     *        Vector2D v({v1, v2})
     *
     *  or
     *
     *        Vector2D v = {v1, v2}
     *
     */
    Vector(std::initializer_list<double> l) : _VECTOR<2>(l), x(data[0]), y(data[1]) {}

    /** \brief Assign operator.
     */
    Vector& operator=(Vector<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<2> classes to Vector<2>.
     */
    Vector& operator=(_VECTOR<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief Set values of the vector as Cartesian coordinates (default).
     */
    void setCartesian(double x, double y) {data[0] = x; data[1] = y;}

    /** \brief Set values of the vector as Polar coordinates in radians (transformed to Cartesian).
     */
    void setPolars(double r, double rads) {data[0] = r*cos(rads); data[1] = r*sin(rads);}

    /** \brief Set values of the vector as Polar coordinates in degrees (transformed to Cartesian).
     */
    void setPolarsDegrees(double r, double degree) {data[0] = r*cos(degree*TORADIANS); data[1] = r*sin(degree*TORADIANS);}

    /** \brief Get values of the Polar angles in radians (transformed from Cartesian).
     */
    double getRads()    {return (atan2(data[0],data[1]));}

    /** \brief Get values of the Polar angles in degrees (transformed from Cartesian).
     */
    double getDegrees() {return (atan2(data[0],data[1])*TODEGREE);}

    // reflect es comun a todos los vectores pero en 2D se puede hacer más eficiente usando polares
    //Vector2D& reflect(const Vector2D& rhs);  // TODO espero a necesitarlo
    //friend Vector2D reflect(Vector2D lhs, const Vector2D &rhs);  // TODO espero a necesitarlo
    //friend Vector2D getNormalA(Vector2D v)const;  // TODO espero a necesitarlo
    //friend Vector2D getNormalB(Vector2D v)const;  // TODO espero a necesitarlo
};

using Vector2D = Vector<2>;  //!< An alias to Vector<2>.

/** \brief A class that represent 3D Vectors.
 *
 *  Vector3D is an alias of Vector<3>.
 *
 *  This specialization let you access with the alias .x, .y or .z to the first, second or third dimension of the 3D Vector.
 */
template<>
class Vector<3> : public _VECTOR<3> {
  public:
    double &x;  //!< An alias to access the first dimension as v.x.
    double &y;  //!< An alias to access the first dimension as v.y.
    double &z;  //!< An alias to access the first dimension as v.z.

    /** \brief Void constructor, the Vector3D's values are unknown.
     */
    Vector() : _VECTOR<3>(), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A copy constructor.
     */
    Vector(const Vector<3>& v) : _VECTOR<3>(v), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A copy constructor with _VECTOR<3>.
     */
    Vector(const _VECTOR<3>& v) : _VECTOR<3>(v), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A list initializer constructor.
     *
     *  You can create a Vector3D with a list of 3 values:
     *
     *        Vector3D v({v1, v2, v3})
     *
     *  or
     *
     *        Vector3D v = {v1, v2, v3}
     *
     */
    Vector(std::initializer_list<double> l) : _VECTOR<3>(l), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief Assign operator.
     */
    Vector& operator=(Vector<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<3> classes to Vector<3>.
     */
    Vector& operator=(_VECTOR<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    //vectorial multiplication
};

using Vector3D = Vector<3>; //!< An alias to Vector<3>.

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


///******************************************/
//
//
///** \brief An aliases of a Vector<2>.
// *
// *  Used to implement some functionality of a 2 dimensional Vector.
// */
//class Vector2D : public Vector<2> {
//  public:
//    double &x = data[0];  //!< An alias to access the first dimension as v.x.
//    double &y = data[1];  //!< An alias to access the first dimension as v.y.
//
//    /** \brief Void constructor, the Vector2D's values are unknown.
//     */
//    Vector2D() : Vector<2>() {}
//
//    /** \brief A copy constructor with Vector<2>.
//     */
//    Vector2D(const Vector<2>& v) : Vector<2>(v) {}
//
//    /** \brief A list initializer constructor.
//     *
//     *  You can create a Vector2D with a list of 2 values:
//     *
//     *        Vector2D v(v1, v2)
//     *
//     *  or
//     *
//     *        Vector2D v = {v1, v2}
//     *
//     */
//    Vector2D(std::initializer_list<double> l) : Vector(l) {}
//
//    /** \brief This class let you compare Vector<2> with Vector2D classes.
//     */
//    Vector2D& operator=(Vector<2> rhs) {Vector<2>::operator=(rhs); return (*this);}
//
//    /** \brief Set values of the vector as Cartesian coordinates (default).
//     */
//    void setCartesian(double x, double y) {data[0] = x; data[1] = y;}
//
//    /** \brief Set values of the vector as Polar coordinates in radians (transformed to Cartesian).
//     */
//    void setPolars(double r, double rads) {data[0] = r*cos(rads); data[1] = r*sin(rads);}
//
//    /** \brief Set values of the vector as Polar coordinates in degrees (transformed to Cartesian).
//     */
//    void setPolarsDegrees(double r, double degree) {data[0] = r*cos(degree*TORADIANS); data[1] = r*sin(degree*TORADIANS);}
//
//    /** \brief Get values of the Polar angles in radians (transformed from Cartesian).
//     */
//    double getRads()    {return (atan2(data[0],data[1]));}
//
//    /** \brief Get values of the Polar angles in degrees (transformed from Cartesian).
//     */
//    double getDegrees() {return (atan2(data[0],data[1])*TODEGREE);}
//
//    // reflect es comun a todos los vectores pero en 2D se puede hacer más eficiente usando polares
//    //Vector2D& reflect(const Vector2D& rhs);  // TODO espero a necesitarlo
//    //friend Vector2D reflect(Vector2D lhs, const Vector2D &rhs);  // TODO espero a necesitarlo
//    //friend Vector2D getNormalA(Vector2D v)const;  // TODO espero a necesitarlo
//    //friend Vector2D getNormalB(Vector2D v)const;  // TODO espero a necesitarlo
//};
//
//class Vector3D : public Vector<3> {
//  public:
//    double &x = data[0];  //!< An alias to access the first dimension as v.x.
//    double &y = data[1];  //!< An alias to access the first dimension as v.y.
//    double &z = data[2];  //!< An alias to access the first dimension as v.z.
//
//    /** \brief Void constructor, the Vector3D's values are unknown.
//     */
//    Vector3D() : Vector() {}
//
//    /** \brief A copy constructor with Vector<3>.
//     */
//    Vector3D(const Vector<3>& v) : Vector<3>(v) {}
//
//    /** \brief A list initializer constructor.
//     *
//     *  You can create a Vector3D with a list of 3 values:
//     *
//     *        Vector3D v(v1, v2, v3)
//     *
//     *  or
//     *
//     *        Vector3D v = {v1, v2, v3}
//     *
//     */
//    Vector3D(std::initializer_list<double> l) : Vector(l) {}
//
//    /** \brief This class let you compare Vector<3> with Vector3D classes.
//     */
//    Vector3D& operator=(Vector<3> rhs) {Vector<3>::operator=(rhs); return (*this);}
//
//    //vectorial multiplication
//};
//
///****************************************/




}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_VECTOR_H_
