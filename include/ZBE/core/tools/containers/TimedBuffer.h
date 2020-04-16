/**
 * Copyright 2016 Batis Degryll Ludo
 * @file TimedBuffer.h
 * @since 2018-08-12
 * @date 2018-08-12
 * @author Degryll
 * @brief Stores a ordered collection of Elements.
 * Its in charge of keep them ordered and discard those that have expired.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TIMEDBUFFER_H
#define ZBE_CORE_TOOLS_CONTAINERS_TIMEDBUFFER_H

#include <cstdint>
#include <set>
#include <vector>

#include "ZBE/core/tools/containers/TimedElement.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Stores a ordered collection of Elements.
 * Its in charge of keep them ordered and discard those that have expired.
 */
template <typename T>
class TimedBuffer {
public:
  /** \brief Construct a new InputBuffer.
   */
  TimedBuffer() : buffer() {}

  /** \brief inserts a timedElement into the buffer in order.
   *  \param element timedElement with the info.
   */
  inline void insert(T const& element) {buffer.insert(TimedElement<T>(element, element.getTime()));}

  uint64_t size() {return buffer.size();}

  /** \brief Will insert in the given store all TimedElements created
   *    in the given time range. All elements with time less than or equal to initT will be discarded.
   *  \param initT Initial time. All elements with time less than or equal to initT will be discarded.
   *  \param endT End time. All elements with time less than or equal to endT will be returned in the given store.
   *  \param store Store with all the elements in the given range.
   */
  void getRange(uint64_t initT, uint64_t endT, std::vector<T>& store);

private:
  std::multiset< TimedElement<T> > buffer;
};

template <typename T>
void TimedBuffer<T>::getRange(uint64_t initT, uint64_t endT, std::vector<T>& store) {
  TimedElement<T> upper(initT);
  buffer.erase(buffer.begin(),buffer.upper_bound(upper));
  if(!buffer.empty()){
    auto it = buffer.begin();
    uint64_t first = it->getTime();
    for(; it != buffer.end(); ++it) {
      if((it->getTime() > endT) || (it->getTime() != first)) {
        break;
      }
      store.push_back(it->getElement());
    }
  }  // if buffer not empty
}


}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TIMEDBUFFER_H
