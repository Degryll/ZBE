
#include "ZBE/core/io/InputBuffer.h"

namespace zbe {

  void InputBuffer::getRange(uint64_t initT, uint64_t endT, std::vector<InputStatus>& store) {
    InputStatus upper(0,0,initT);
    buffer.erase(buffer.begin(),buffer.upper_bound(upper));
    if(!buffer.empty()){
      auto it = buffer.begin();
      uint64_t first = it->getTime();
      for(; it != buffer.end(); ++it) {
        if(it->getTime()>endT || it->getTime()!=first){
          break;
        }
        store.push_back((*it));
      }
    }
  }

}
