/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputBuffer.h
 * @since 2016-08-21
 * @date 2017-05-13
 * @author Ludo
 * @brief Stores a ordered collection of InputStatus.
 * Its in charge of keep them ordered and discard those that have expired.
 */

#include "ZBE/core/io/InputBuffer.h"

namespace zbe {

  void InputBuffer::getRange(uint64_t initT, uint64_t endT, std::vector<InputStatus>& store) {
    InputStatus upper(0,0,initT);
    buffer.erase(buffer.begin(),buffer.upper_bound(upper));
    if(!buffer.empty()){
      auto it = buffer.begin();
      uint64_t first = it->getTime();
      for(; it != buffer.end(); ++it) {
        if((it->getTime() > endT) || (it->getTime() != first)) {
          break;
        }
        store.push_back(*it);
      }
    }
  }

}  // namespace zbe
