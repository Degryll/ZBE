/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector.h
 * @since 2010/07/22
 * @date 26/03/2018
 * @author Ludo Degryll Batis
 * @brief Math Vector definition
 */

#ifndef ZBE_CORE_TOOLS_MATH_VECTOR_H_
#define ZBE_CORE_TOOLS_MATH_VECTOR_H_

#include <cmath>
#include <initializer_list>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A class that represent Vectors of any dimension.
 *
 *  Not use this class, use Vector<dim>.
 *
 *  \sa Vector
 */
template<unsigned dim>
class _VECTOR {
  public:

    /** \brief Void constructor, the vector's values are set to 0.
     */
    _VECTOR() {
      for(unsigned i = 0; i < dim; i++) {
        data[i] = 0;
      }
    }

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
     *  \param l Initializer list with the vector coordinates
     */
    _VECTOR(std::initializer_list<double> l) {
      if (l.size() != dim) {
        SysError::setError("Vector ERROR: Initializer list size is incorrect.");
        return;
      }

      int i = 0;
      for(auto it : l) {
        data[i++] = it;
      }
    }

    /** \brief Virtual destructor (this class is a base class).
     */
    virtual ~_VECTOR() {}

    /** \brief This class let you assign initializer lists to _VECTOR.
     *  \param l Initializer list with the vector coordinates
     */
    _VECTOR& operator=(std::initializer_list<double> l) {
      if (l.size() != dim) {
        SysError::setError("Vector ERROR: Initializer list size is incorrect.");
        return (*this);
      }

      int i = 0;
      for(auto it : l) {
        data[i++] = it;
      }

      return (*this);
    }

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
    _VECTOR<dim>& operator+=(_VECTOR<dim> rhs) {
      for(unsigned i = 0; i < dim; i++) {
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
    _VECTOR<dim>& operator-=(_VECTOR<dim> rhs) {
      for(unsigned i = 0; i < dim; i++) {
        data[i] -= rhs.data[i];
      }

      return (*this);
    }

    /** \brief Changes the orientation of the vector changing the sign of its dimensions.
     *
     * \return A reference to the this Vector.
     * \sa operator+=(), operator-=() and operator*=().
     */
    _VECTOR<dim>& operator-() {
      for(unsigned i = 0; i < dim; i++) {
        data[i] = -data[i];
      }

      return (*this);
    }

    /** \brief Multiply this Vector by a scalar.
     *
     * \param rhs The scalar.
     * \return A reference to this Vector after the multiplication.
     * \sa operator+=(), operator-=(), operator-(), operator+(), operator/=().
     */
    _VECTOR<dim>& operator*=(double rhs) {
      for(unsigned i = 0; i < dim; i++) {
        data[i] *= rhs;
      }

      return (*this);
    }

    /** \brief Divide this Vector by a scalar.
     *
     * \param rhs The scalar.
     * \return A reference to this Vector after the multiplication.
     * \sa operator+=(), operator-=(), operator-(), operator+(), operator*=().
     */
    _VECTOR<dim>& operator/=(double rhs) {
      for(unsigned i = 0; i < dim; i++) {
        data[i] /= rhs;
      }

      return (*this);
    }

    /** \brief Creates an all-zero vector
     * \return An all-zero vector
     */
    _VECTOR<dim>& setZeros() {
      for(unsigned i = 0; i < dim; i++) {
        data[i] = 0.0;
      }

      return (*this);
    }

    /** \brief Creates an all-zero vector
     * \return An all-zero vector
     */
    static _VECTOR<dim> zeros() {
      _VECTOR<dim> out;
      out.setZeros();

      return (out);
    }

    /** \brief Returns this vector as a Point.
     * \return this vector as a Point.
     */
    _POINT<dim> toPoint() {
      _POINT<dim> p;
      return p + (*this);
    }


    /** \brief Compute the Vector Module.
     *
     * \return The Vector module.
     * \sa getSqrModule().
     */
    double getModule() {
      double r = 0;
      for(unsigned i = 0; i < dim; i++) {
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
      for(unsigned i = 0; i < dim; i++) {
        r2 += data[i] * data[i];
      }

      return (r2);
    }

    /** \brief Modifies this vector setting module to 1.0.
     *
     * \return Normalized vector.
     */
    _VECTOR<dim>&  normalize() {
      double m = getModule();
      if(isNearlyEqual(m, 0.0, 0.0)) {return (*this);}
      *this /= m;

      return (*this);
    }

    /** \brief Modifies this vector setting module to given value
     *
     * \return Normalized vector.
     */
    _VECTOR<dim>&  setModule(double module) {
      return this->normalize() *= module;
    }

    /** \brief Modifies this vector setting module to 1.0.
     *
     * \return Normalized vector.
     */
    friend _VECTOR normalize(_VECTOR rhs)  {
      return rhs.normalize();
    }

    /** \brief Modifies this vector setting module to given value
     *
     * \return Normalized vector.
     */
    friend _VECTOR setModule(_VECTOR rhs, double module)  {
      return rhs.setModule(module);
    }


    /**
     * \fn _VECTOtypename R::reflect
     * \param normal Vector normal to the collision plane.
     * \return Vector with the ray or object path reflected.
     * \brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
     */
    _VECTOR<dim>& reflect(_VECTOR<dim> normal) {
      _VECTOR<dim>& d = *this;
      normal.normalize();
      double dn = (d * normal);
      _VECTOR<dim> dnn = dn * normal;
      _VECTOR<dim> dnn2 = dnn * 2;
      _VECTOR<dim> out = d - dnn2;
      d = out;
      //*this = d - (((d * normal) * normal) * 2);
      return (*this);
    }

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

    /** \brief Implements Vector multiplication by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator*(_VECTOR lhs, double rhs) {
      return (lhs*=rhs);
    }

    /** \brief Implements Vector multiplication by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator*(double lhs, _VECTOR rhs) {
      return (rhs*=lhs);
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
      for(unsigned i = 0; i < dim; i++) {
        v += lhs.data[i] * rhs.data[i];
      }

      return (v);
    }

    /** \brief Implements Vector divsion by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator/(_VECTOR lhs, double rhs) {
      return (lhs/=rhs);
    }

    /** \brief Implements dot product.
     *
     * \param lhs First vector.
     * \param rhs Second vector.
     * \return Doct product.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend inline double dot(const _VECTOR& lhs, const _VECTOR& rhs) {
      return (lhs * rhs);
    }

    /** \brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
     * \param normal Vector normal to the collision plane.
     * \return Vector with the ray or object path reflected.
     */
    friend _VECTOR reflect(_VECTOR ray, const _VECTOR &normal){
        return ray.reflect(normal);
    };

    /** \brief Tells if two given _VECTOR are considered equal.
     *
     * \param lhs first Vector.
     * \param rhs second Vector.
     * \return True if both _VECTOR are equal. False otherwise.
     */
    friend bool operator==(const _VECTOR& lhs, const _VECTOR& rhs){
      bool equal = true;
      for(unsigned i = 0; i < dim; i++ ) {
        equal &= almost_equal(lhs.data[i], rhs.data[i]);
      }
      return equal;
    }

    /** \brief Tells if given _VECTOR is all zeroes
     *
     * \param v the Vector.
     * \return True if _VECTOR is all zeroes
     */
    friend bool isZero(const _VECTOR& v){
      bool iszero = true;
      for(unsigned i = 0; i < dim; i++ ) {
        iszero &= almost_equal(v.data[i], 0.0);
      }
      return iszero;
    }

///////////////////////////////////////////////////////////////////////////////
// END Friend Functions
///////////////////////////////////////////////////////////////////////////////

  protected:
    double data[dim];  //!< Vector data.
};

/** \brief A class that represent Vectors of any dimension.
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Vectors belongs to.
 */
template<unsigned dim>
class Vector : public _VECTOR<dim> {
  public:
    /** \brief Void constructor, the Vector's values are unknown.
     */
    Vector() : _VECTOR<dim>() {}

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
     *  \param l Initializer list with the vector coordinates
     */
    Vector(std::initializer_list<double> l) : _VECTOR<dim>(l) {}
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
     *  \param v Vector to copy
     */
    Vector(const Vector<2>& v) : _VECTOR<2>(v), x(data[0]), y(data[1]) {}

    /** \brief A copy constructor with _VECTOR<2>.
     *  \param v _VECTOR to copy
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
     *  \param l Initializer list with the vector coordinates
     */
    Vector(std::initializer_list<double> l) : _VECTOR<2>(l), x(data[0]), y(data[1]) {}

    /** \brief Assign operator.
     *  \param rhs Vector to copy
     */
    Vector& operator=(Vector<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<2> classes to Vector<2>.
     *  \param rhs _VECTOR to copy
     */
    Vector& operator=(_VECTOR<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign initializer lists to Vector<2>.
     *  \param l Initializer list with the vector coordinates
     */
    Vector& operator=(std::initializer_list<double> l) {_VECTOR<2>::operator=(l); return (*this);}

    /** \brief Set values of the vector as Cartesian coordinates (default).
     *  \param x X coordinate
     *  \param y Y coordinate
     */
    void setCartesian(double x, double y) {data[0] = x; data[1] = y;}

    /** \brief Set values of the vector as Polar coordinates in radians (transformed to Cartesian).
     *  \param r Radial coordinate
     *  \param rads Angular coordinate (in radians)
     */
    void setPolars(double r, double rads) {data[0] = r*cos(rads); data[1] = r*sin(rads);}

    /** \brief Set values of the vector as Polar coordinates in degrees (transformed to Cartesian).
    *  \param r Radial coordinate
    *  \param degree Angular coordinate (in degrees)
     */
    void setPolarsDegrees(double r, double degree) {data[0] = r*cos(degree*TORADIANS); data[1] = r*sin(degree*TORADIANS);}

    /** \brief Get values of the Polar angles in radians (transformed from Cartesian).
     */
    double getRads()    {return (atan2(data[0],data[1]));}

    /** \brief Get values of the Polar angles in degrees (transformed from Cartesian).
     */
    double getDegrees() {return (atan2(data[0],data[1])*TODEGREE);}

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
     *  \param Vector to copy
     */
    Vector(const Vector<3>& v) : _VECTOR<3>(v), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief A copy constructor with _VECTOR<3>.
     *  \param _VECTOR to copy
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
     *  \param l Initializer list with the vector coordinates
     */
    Vector(std::initializer_list<double> l) : _VECTOR<3>(l), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief Assign operator.
     *  \param Vector to copy
     */
    Vector& operator=(Vector<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<3> classes to Vector<3>.
     *  \param _VECTOR to copy
     */
    Vector& operator=(_VECTOR<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<3> classes to Vector<3>.
     *  \param l Initializer list with the vector coordinates
     */
    Vector& operator=(std::initializer_list<double> l) {_VECTOR<3>::operator=(l); return (*this);}

    /** \brief Modifies this vector setting module to 1.0.
     *
     * \return Normalized vector.
     */
    Vector&  cross(Vector<3> rhs) {
      double v0 = data[1] * rhs[2] - data[2] * rhs[1];
      double v1 = data[2] * rhs[0] - data[0] * rhs[2];
      double v2 = data[0] * rhs[1] - data[1] * rhs[0];

      data[0] = v0;
      data[1] = v1;
      data[2] = v2;
      return (*this);
    }

    /** \brief Implements Vector addition.
     *
     * \param lhs First vector.
     * \param rhs Second vector.
     * \return A vector with the cross product.
     * \sa cross().
     */
    friend Vector<3> cross(Vector<3> lhs, const Vector<3>& rhs);

    /** \brief Implements vector between two angles.
     *
     * \param lhs First vector.
     * \param rhs Second vector.
     * \return The angle between given vectors
     */
    double angle(Vector<3> lhs, Vector<3> rhs);

};

Vector<3> cross(Vector<3> lhs, const Vector<3>& rhs);

double angle(Vector<3> lhs, Vector<3> rhs);

using Vector3D = Vector<3>; //!< An alias to Vector<3>.

ZBEAPI Vector<2> reflect(Vector<2> ray, const Vector<2> &normal);
ZBEAPI Vector<3> reflect(Vector<3> ray, const Vector<3> &normal);

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_VECTOR_H_
