/**
 * Copyright 2012 Batis Degryll Ludo
 * @file tools.h
 * @since 2017-03-18
 * @date 2017-03-18
 * @author Batis Degryll Ludo
 * @brief ZBE coding tools
 */

/* \brief Used when a template need to know the bases classes of "T".
 *
 * In the case you have:
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

template<typename T>
struct Covariance_Traits<T, void> {struct Type {};};
