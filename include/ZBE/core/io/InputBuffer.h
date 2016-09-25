/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputBuffer.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Ludo
 * @brief Stores a ordered collection of InputStatus.
 * Its in charge of keet them ordered and discard those that have expired.
 */

#ifndef CORE_IO_INPUTBUFFER_H
#define CORE_IO_INPUTBUFFER_H

#include <cstdint>
#include <set>
#include <vector>
#include "InputStatus.h"

namespace zbe {

class InputBuffer {
  public:
    InputBuffer():buffer(){};

    /** \brief inserts an InputStatus into the buffer ordered.
     *  \return void
     */
    inline void insert(InputStatus const& status){buffer.insert(status);};

    /** \brief Will insert in the given store all InputStatus occurred
     *    in the given time range. All InputStatus occurred before initT
     *    will be drop from the buffer.
     *  \return void
     */
    void getRange(uint64_t initT, uint64_t endT, std::vector<InputStatus>& store);

  private:
    std::multiset<InputStatus> buffer;
};
}

#endif //CORE_IO_INPUTBUFFER_H
