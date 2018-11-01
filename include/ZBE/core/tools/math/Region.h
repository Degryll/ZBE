/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Region.h
 * @since 2017/06/18
 * @date 26/03/2018
 * @author Degryll Ludo Batis
 * @brief Defines an axis alingned rect area.
 */

#ifndef ZBE_CORE_TOOLS_MATH_REGION_H_
#define ZBE_CORE_TOOLS_MATH_REGION_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A n-dimensional region of the space.
*/
template <unsigned dim>
class _REGION {
public:

  /** \brief Empty constructor
   *  the Point's values are unknown.
   */
  _REGION() : _p(), _v() {}

  /** \brief Parametrized constructor
   *  \param lp Coordinates of the origin point
   *  \param lv Region dimensions
   */
  _REGION(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _p(lp), _v(lv) {}

  /** \brief Parametrized constructor
   *  \param p Origin point
   *  \param v Region dimensions
   */
  _REGION(const Point<dim>& p, const Vector<dim>& v) : _p(p), _v(v) {}

  /** \brief Tells if two given _REGION are considered equal.
   *
   * \param lhs first Region.
   * \param rhs second Region.
   * \return True if both _REGION are equal. False otherwise.
   */
  friend bool operator==(const _REGION& lhs, const _REGION& rhs){
    return ((lhs._p == rhs._p) && (lhs._v == rhs._v));
  }

protected:
  Point<dim> _p;
  Vector<dim> _v;
};

/** \brief A n-dimensional region of the space.
*/
template <unsigned dim>
class Region : public _REGION<dim>{
public:
  Point<dim>& p; //!< N-dimensional point as region origin.
  Vector<dim>& v; //!< N-dimensional vector as region dimensions.

  /** \brief Empty constructor
   *  the Point's values are unknown.
   */
  Region() : _REGION<dim>(), p(_REGION<dim>::_p), v(_REGION<dim>::_v) {}

  /** \brief Copy constructor
   *  \param rhs Region to copy
   */
  Region(const Region<dim>& rhs) : _REGION<dim>(rhs), p(_REGION<dim>::_p), v(_REGION<dim>::_v) {}

  /** \brief Copy constructor
   *  \param rhs _REGION to copy
   */
  Region(const _REGION<dim>& rhs) : _REGION<dim>(rhs), p(_REGION<dim>::_p), v(_REGION<dim>::_v) {}

  /** \brief Parametrized constructor
   *  \param lp Coordinates of the origin point
   *  \param lv Region dimensions
   */
  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<dim>(lp, lv), p(_REGION<dim>::_p), v(_REGION<dim>::_v) {}

  /** \brief Parametrized constructor
   *  \param p Origin point
   *  \param v Region dimensions
   */
  Region(const Point<dim>& p, const Vector<dim>& v) : _REGION<dim>(p, v), p(_REGION<dim>::_p), v(_REGION<dim>::_v) {}

  /** \brief Copy operator
   *  \param rhs Region to copy
   */
  Region& operator=(const Region<dim>& rhs){
    _REGION<dim>::operator=(rhs);
    p = rhs.p;
    v = rhs.v;
    return (*this);
  }

  /** \brief Copy operator that lets to copy a _REGION to REGION
   *  \param rhs _REGION to copy
   */
  Region& operator=(const _REGION<dim>& rhs){
    _REGION<dim>::operator=(rhs);
    p = rhs._p;
    v = rhs._v;
    return (*this);
  }
};

/** \brief A 2-dimensional region of the space.
*/
template <>
class Region<2> : public _REGION<2>{
public:
  Point<2>& p; //!< N-dimensional point as region origin.
  Vector<2>& v; //!< N-dimensional vector as region dimensions.

  /** \brief Empty constructor
   *  the Point's values are unknown.
   */
  Region() :_REGION<2>(), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  /** \brief Copy constructor
   *  \param rhs Region to copy
   */
  Region(const Region<2>& rhs) : _REGION<2>(rhs), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  /** \brief Copy constructor
   *  \param rhs _REGION to copy
   */
  Region(const _REGION<2>& rhs) : _REGION<2>(rhs), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  /** \brief Parametrized constructor
   *  \param lp Coordinates of the origin point
   *  \param lv Region dimensions
   */
  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<2>(lp, lv), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  /** \brief Parametrized constructor
   *  \param p Origin point
   *  \param v Region dimensions
   */
  Region(const Point<2>& p, const Vector<2>& v) : _REGION<2>(p, v), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  /** \brief Copy operator
   *  \param rhs Region to copy
   */
  Region& operator=(const Region<2>& rhs){
    _REGION<2>::operator=(rhs);
    return (*this);
  }

  /** \brief Copy operator that lets to copy a _REGION to REGION
   *  \param rhs _REGION to copy
   */
  Region& operator=(const _REGION<2>& rhs){
    _REGION<2>::operator=(rhs);
    return (*this);
  }
};

using Region2D = Region<2>; //!< An alias to Region<2>.

/** \brief A 3-dimensional region of the space.
*/
template <>
class Region<3> : public _REGION<3>{
public:
  Point3D& p; //!< N-dimensional point as region origin.
  Vector3D& v; //!< N-dimensional vector as region dimensions.

  /** \brief Empty constructor
   *  the Point's values are unknown.
   */
  Region() :_REGION<3>(), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  /** \brief Copy constructor
   *  \param rhs Region to copy
   */
  Region(const Region<3>& rhs) : _REGION<3>(rhs), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  /** \brief Copy constructor
   *  \param rhs _REGION to copy
   */
  Region(const _REGION<3>& rhs) : _REGION<3>(rhs), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  /** \brief Parametrized constructor
   *  \param lp Coordinates of the origin point
   *  \param lv Region dimensions
   */
  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<3>(lp, lv), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  /** \brief Parametrized constructor
   *  \param p Origin point
   *  \param v Region dimensions
   */
  Region(const Point<3>& p, const Vector<3>& v) : _REGION<3>(p, v), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  /** \brief Copy operator
   *  \param rhs Region to copy
   */
  Region& operator=(const Region<3>& rhs){
    _REGION<3>::operator=(rhs);
    return (*this);
  }

  /** \brief Copy operator that lets to copy a _REGION to REGION
   *  \param rhs _REGION to copy
   */
  Region& operator=(const _REGION<3>& rhs){
    _REGION<3>::operator=(rhs);
    return (*this);
  }
};

using Region3D = Region<3>; //!< An alias to Region<3>.

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_REGION_H_
