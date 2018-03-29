/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputBuffer.h
 * @since 2016-08-21
 * @date 2018-03-20
 * @author Ludo
 * @brief Stores a ordered collection of InputStatus.
 * Its in charge of keep them ordered and discard those that have expired.
 */

#ifndef ZBE_CORE_IO_INPUTBUFFER_H
#define ZBE_CORE_IO_INPUTBUFFER_H

#include <cstdint>
#include <set>
#include <vector>

#include "ZBE/core/io/InputStatus.h"

namespace zbe {

/** \brief Stores a ordered collection of InputStatus.
 * Its in charge of keep them ordered and discard those that have expired.
 */
class InputBuffer {
public:
  /** \brief Construct a new InputBuffer.
   */
  InputBuffer() : buffer() {}

  /** \brief inserts an InputStatus into the buffer ordered.
   *  \param status InputStatus with the info of the input.
   */
  inline void insert(InputStatus const& status) {buffer.insert(status);}

  /** \brief Will insert in the given store all InputStatus occurred
   *    in the given time range. All inputStatus with time less than or equal to initT will be discarded.
   *  \param initT Initial time. All inputStatus with time less than or equal to initT will be discarded.
   *  \param endT End time. All inputStatus with time less than or equal to endT will be returned in the given store.
   *  \param store Store with all the inputStatus in the given range.
   */
  void getRange(uint64_t initT, uint64_t endT, std::vector<InputStatus>& store);

private:
  std::multiset<InputStatus> buffer;
};

}  // namespace zbe

#endif  // ZBE_CORE_IO_INPUTBUFFER_H
