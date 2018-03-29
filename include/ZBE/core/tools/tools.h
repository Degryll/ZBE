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

namespace zbe {

/** \brief Used when a template need to know the bases classes of "T".
 *
 * In case you have:
 * class A { ... };
 * class B : public A { ... };
 * template <typename T> class Mytemplate { ... };
 *
 * Then:
 * MyTemplate<B>* is an invalid covariance of Mytemplate<A>*.
 * The following avoid this.
 *
 * Usage:
 *
 * class A { ... };
 * class B : public A {using Base = A; ... };
 *
 * template<typename T>
 * class MyTemplateClass : virtual public Covariance_Traits<MyTemplateClass<typename T::Base>, typename T::Base>::Type
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

/** \brief A gimmick class used to specialize a member function without the need to specialized the main class
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

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TOOLS_H_
