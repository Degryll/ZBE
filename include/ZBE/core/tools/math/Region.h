/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Region.h
 * @since 2017/06/18
 * @date 2017/06/18
 * @author Degryll Ludo Batis
 * @brief Defines an axis alingned rect area.
 */

#ifndef ZBE_CORE_TOOLS_MATH_REGION_H_
#define ZBE_CORE_TOOLS_MATH_REGION_H_

#include <initializer_list>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

template <unsigned s>
class _REGION {
public:

  _REGION() : _p(), _v() {}

  _REGION(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _p(lp), _v(lv) {}

  _REGION(const Point<s>& p, const Vector<s>& v) : _p(p), _v(v) {}

  Point<s> _p;
  Vector<s> _v;
};

template <unsigned s>
class Region : public _REGION<s>{
public:

  Region() : _REGION<s>(), p(_REGION<s>::_p), v(_REGION<s>::_v) {}

  Region(const Region<s>& rhs) : _REGION<s>(rhs), p(_REGION<s>::_p), v(_REGION<s>::_v) {}

  Region(const _REGION<s>& rhs) : _REGION<s>(rhs), p(_REGION<s>::_p), v(_REGION<s>::_v) {}

  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<s>(lp, lv), p(_REGION<s>::_p), v(_REGION<s>::_v) {}

  Region(const Point<s>& p, const Vector<s>& v) : _REGION<s>(p, v), p(_REGION<s>::_p), v(_REGION<s>::_v) {}

  Region& operator=(const Region<s>& rhs){
    _REGION<s>::operator=(rhs);
    p = rhs.p;
    v = rhs.v;
    return (*this);
  }

  Region& operator=(const _REGION<s>& rhs){
    _REGION<s>::operator=(rhs);
    p = rhs._p;
    v = rhs._v;
    return (*this);
  }

  Point<s>& p;
  Vector<s>& v;
};

template <>
class Region<2> : public _REGION<2>{
public:

  Region() :_REGION<2>(), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  Region(const Region<2>& rhs) : _REGION<2>(rhs), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  Region(const _REGION<2>& rhs) : _REGION<2>(rhs), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<2>(lp, lv), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  Region(const Point<2>& p, const Vector<2>& v) : _REGION<2>(p, v), p(_REGION<2>::_p), v(_REGION<2>::_v) {}

  Region& operator=(const Region<2>& rhs){
    _REGION<2>::operator=(rhs);
    p = rhs.p;
    v = rhs.v;
    return (*this);
  }

  Region& operator=(const _REGION<2>& rhs){
    _REGION<2>::operator=(rhs);
    p = rhs._p;
    v = rhs._v;
    return (*this);
  }

  Point<2>& p;
  Vector<2>& v;
};

using Region2D = Region<2>; //!< An alias to Region<2>.

template <>
class Region<3> : public _REGION<3>{
public:

  Region() :_REGION<3>(), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  Region(const Region<3>& rhs) : _REGION<3>(rhs), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  Region(const _REGION<3>& rhs) : _REGION<3>(rhs), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  Region(const std::initializer_list<double> lp, const std::initializer_list<double> lv) : _REGION<3>(lp, lv), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  Region(const Point<3>& p, const Vector<3>& v) : _REGION<3>(p, v), p(_REGION<3>::_p), v(_REGION<3>::_v) {}

  Region& operator=(const Region<3>& rhs){
    _REGION<3>::operator=(rhs);
    p = rhs.p;
    v = rhs.v;
    return (*this);
  }

  Region& operator=(const _REGION<3>& rhs){
    _REGION<3>::operator=(rhs);
    p = rhs._p;
    v = rhs._v;
    return (*this);
  }

  Point3D& p;
  Vector3D& v;
};

using Region3D = Region<3>; //!< An alias to Region<3>.

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_REGION_H_
