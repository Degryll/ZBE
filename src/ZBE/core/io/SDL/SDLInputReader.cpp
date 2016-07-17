/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.cpp
 * @since 2016-04-27
 * @date 2016-04-27
 * @author Ludo
 * @brief Imput reader using sdl. Implementation file.
 */

#include "ZBE/core/io/SDL/SDLInputReader.h"

namespace zbe {

  float SDLInputReader::getStatus(uint32_t keyid) {
    auto search = states->find(keyid);
    if(search != states->end()) {
      return search->second;
    } else {
      SysError::setError("Asking for a non changed input.");
      return 0.0f;
    }
  }

  uint64_t SDLInputReader::getTime(uint32_t keyid) {
    auto search = times->find(keyid);
    if(search != times->end()) {
      return search->second;
    } else {
      SysError::setError("Asking for a non changed input.");
      return 0.0f;
    }
  }

  void SDLInputReader::setInputStatus(std::list<uint32_t>* changedIds, std::map<uint32_t, float>* states, std::map<uint32_t, uint64_t>* times){
    this->changedIds = changedIds;
    this->states = states;
    this->times = times;
  }

} // namespace zbe
