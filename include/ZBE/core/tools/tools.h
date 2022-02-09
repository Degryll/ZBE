/**
 * Copyright 2012 Batis Degryll Ludo
 * @file tools.h
 * @since 2017-03-18
 * @date 2017-03-18
 * @author Batis Degryll Ludo
 * @brief ZBE coding tools
 */

#ifndef ZBE_CORE_TOOLS_TOOLS_H_
#define ZBE_CORE_TOOLS_TOOLS_H_

#include <functional>
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Used when a template need to know the bases classes of "T".
 *
 * In case you have:
 * class ZBEAPI A { ... };
 * class ZBEAPI B : public A { ... };
 * template <typename T> class ZBEAPI Mytemplate { ... };
 *
 * Then:
 * MyTemplate<B>* is an invalid covariance of Mytemplate<A>*.
 * The following avoid this.
 *
 * Usage:
 *
 * class ZBEAPI A { ... };
 * class ZBEAPI B : public A {using Base = A; ... };
 *
 * template<typename T>
 * class ZBEAPI MyTemplateclass ZBEAPI : virtual public Covariance_Traits<MyTemplateClass<typename T::Base>, typename T::Base>::Type
 */
template<typename T, typename U>
struct Covariance_Traits {
  using Type = T;
};

/** \brief Base case of.
 *  \sa Covariance_Traits
 */
template<typename T>
struct Covariance_Traits<T, void> {
  struct Type {
    Type(){}
    template<typename ...Ts>
    Type(Ts...){}
    virtual ~Type(){}
  };
};

/** \brief A gimmick class ZBEAPI used to specialize a member function without the need to specialized the main class
 */
template <typename T>
struct TypeGimmick { typedef T type; };

/** \brief Grouping of an undetermined number of types
 */
template <typename T, typename... Bases>
struct TypeContainer : public TypeContainer<T>, public TypeContainer<Bases...> {
  TypeContainer(T* t, Bases*...bases): TypeContainer<T>(t), TypeContainer<Bases...>(bases...) {}
  ~TypeContainer(){}
};

/** \brief Base case of.
 *  \sa TypeContainer
 */
template <typename T>
struct TypeContainer<T> {
  TypeContainer<T>(const TypeContainer<T>&) = delete;
  void operator=(const TypeContainer<T>&) = delete;

  TypeContainer(T* t): t(t){}
  ~TypeContainer(){}

  /** \brief Return the stored instance.
   *
   */
  T* get() {return t;}

  T* t;
};

template<typename RetVal, typename ...Ts>
class Funct {
public:
  virtual ~Funct() {};
  virtual RetVal operator()(Ts...) = 0;
};

template<typename RetVal, typename ...Ts>
class WrapperFunct : public Funct<RetVal, Ts...> {
public:
  WrapperFunct(std::function<RetVal(Ts...)> callable) : callable(callable) {}
  RetVal operator()(Ts... something) { return callable(something...);};
private:
  std::function<RetVal(Ts...)> callable;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TOOLS_H_
