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

#include <cstdint>
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
    _VECTOR(std::initializer_list<int64_t> l) {
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
    int64_t& operator[](std::size_t idx)       {return (data[idx]);}

    /** \brief Implements direct access to Vector values with operator[].
     *
     *  No bound checking is performed, the behavior accessing an out of bound
     *  index is undefined.
     *
     * \param idx Index of the dimension that you want to get the value.
     * \return The constant value of the idx dimension.
     */
    const int64_t& operator[](std::size_t idx) const {return (data[idx]);}

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
    _VECTOR<s>& operator*=(int64_t rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] *= rhs;
      }

      return (*this);
    }

    /** \brief Multiply this Vector by a scalar.
     *
     * \param rhs The scalar.
     * \return A reference to this Vector after the multiplication.
     * \sa operator+=(), operator-=() and operator-().
     */
    _VECTOR<s>& operator*=(uint64_t rhs) {
      for(unsigned i = 0; i < s; i++) {
        data[i] *= rhs;
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
    int64_t getModule() {
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
    int64_t getSqrModule() {  // to avoid square root
      int64_t r2 = 0;
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
      int64_t m = getModule();

      for(unsigned i = 0; i < s; i++) {
        data[i] = (data[i] << PRECISION_DIGITS) / m;
      }

      return (*this);
    }

    /**
     * \fn _VECTOR::reflect
     * \param normal Vector normal to the collision plane.
     * \return Vector with the ray or object path reflected.
     * \brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
     */
    _VECTOR<s>& reflect(_VECTOR<s> normal) {
      _VECTOR<s>& d = *this;
      if(normal[0] == 1048576 && normal[1] == -1048576 && d[0] == 65536000 && d[1] == 65536000){
        printf("Aqui esta el mal!\n");fflush(stdout);
      }
      normal.normalize();
      int64_t dn = ((d * normal) >> PRECISION_DIGITS) >> PRECISION_DIGITS;
      _VECTOR<s> dnn = dn * normal;
      _VECTOR<s> dnn2 = int64_t(2) * dnn;
      _VECTOR<s> out = d - dnn2;
      d = out;
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

//    /** \brief Implements Vector subtraction.
//     *
//     * \param lhs Minuend.
//     * \param rhs Subtrahend.
//     * \return A reference to the Vector resultant of the subtraction.
//     * \sa operator+=(), operator-() and operator*=().
//     */
//    friend _VECTOR operator-(const _VECTOR& lhs, _VECTOR&& rhs) {
//      return _VECTOR(rhs-=lhs);
//    }

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
    friend _VECTOR operator*(_VECTOR lhs, int64_t rhs) {
      return (lhs*=rhs);
    }

    /** \brief Implements Vector multiplication by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator*(_VECTOR lhs, uint64_t rhs) {
      return (lhs*=rhs);
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
    friend _VECTOR operator*(int64_t lhs, _VECTOR rhs) {
      return (rhs*=lhs);
    }

    /** \brief Implements Vector multiplication by a scalar.
     *
     * \param lhs The original Vector.
     * \param rhs The scalar.
     * \return A reference to the resulting Vector.
     * \sa operator+=(), operator-=() and operator-().
     */
    friend _VECTOR operator*(uint64_t lhs, _VECTOR rhs) {
      return (rhs*=lhs);
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
    friend int64_t operator*(const _VECTOR& lhs, const _VECTOR& rhs) {
      int64_t v = 0;
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
    int64_t data[s];  //!< Vector data.
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
    Vector(std::initializer_list<int64_t> l) : _VECTOR<s>(l) {}
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
    int64_t &x;  //!< An alias to access the first dimension as v.x.
    int64_t &y;  //!< An alias to access the first dimension as v.y.

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
    Vector(std::initializer_list<int64_t> l) : _VECTOR<2>(l), x(data[0]), y(data[1]) {}

    /** \brief Assign operator.
     */
    Vector& operator=(Vector<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<2> classes to Vector<2>.
     */
    Vector& operator=(_VECTOR<2> rhs) {_VECTOR<2>::operator=(rhs); return (*this);}

    /** \brief Set values of the vector as Cartesian coordinates (default).
     */
    void setCartesian(int64_t x, int64_t y) {data[0] = x; data[1] = y;}

    /** \brief Set values of the vector as Polar coordinates in radians (transformed to Cartesian).
     */
    void setPolars(int64_t r, double rads) {data[0] = r*cos(rads); data[1] = r*sin(rads);}

    /** \brief Set values of the vector as Polar coordinates in degrees (transformed to Cartesian).
     */
    void setPolarsDegrees(int64_t r, double degree) {data[0] = r*cos(degree*TORADIANS); data[1] = r*sin(degree*TORADIANS);}

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
    int64_t &x;  //!< An alias to access the first dimension as v.x.
    int64_t &y;  //!< An alias to access the first dimension as v.y.
    int64_t &z;  //!< An alias to access the first dimension as v.z.

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
    Vector(std::initializer_list<int64_t> l) : _VECTOR<3>(l), x(data[0]), y(data[1]), z(data[2]) {}

    /** \brief Assign operator.
     */
    Vector& operator=(Vector<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    /** \brief This class let you assign _VECTOR<3> classes to Vector<3>.
     */
    Vector& operator=(_VECTOR<3> rhs) {_VECTOR<3>::operator=(rhs); return (*this);}

    //vectorial multiplication
};

using Vector3D = Vector<3>; //!< An alias to Vector<3>.

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_VECTOR_H_
