/**
 * Copyright 2016 Batis Degryll Ludo
 * @file TimedElement.h
 * @since 2018-08-12
 * @date 2018-08-12
 * @author Degryll
 * @brief Element with temporary validity.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TIMEDELEMENT_H
#define ZBE_CORE_TOOLS_CONTAINERS_TIMEDELEMENT_H

#include <cstdint>

namespace zbe {

/** \brief Element with temporary validity.
 */
template <typename T>
class TimedElement {
public:
  /** \brief Construct a dummy Timed Element for comparison purpose.
   *  \param time When this element was created.
   */
  TimedElement(uint64_t time) : e(), time(time) {}

  /** \brief Construct an Timed Element.
   *  \param element The element.
   *  \param time When this element was created.
   */
  TimedElement(T element, uint64_t time) : e(element), time(time) {}

  /** \brief Returns the element.
   *  \return The element.
   */
  T getElement() const { return e;}

  /** \brief Returns the timestamp in which this state is reached.
   *  \return Timestamp in which this state is reached.
   */
  uint64_t getTime() const { return time;}

  /** \brief "Less than" operator overloading.
   *  \return true if left hand element is less than right hand one.
   */
  bool operator<(const TimedElement<T>& rhs) const {return time<rhs.getTime();}

private:
  T e;
  uint64_t time;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TIMEDELEMENT_H
