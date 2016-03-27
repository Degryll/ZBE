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
      return 0.0f;
    }
  }

  SDLInputReader * SDLInputReader::getInstance(){
    static SDLInputReader * instance = new SDLInputReader();

    return instance;
  }

  void SDLInputReader::setInputStatus(std::list<uint32_t>* changedIds, std::map<uint32_t, float>* states){
    this->changedIds = changedIds;
    this->states = states;
  }

} // namespace zbe
