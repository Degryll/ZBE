/**
 * Copyright 2018 Batis Degryll Ludo
 * @file OALAudioStore.cpp
 *
 * @since 2018-08-28
 * @date 2018-08-28
 * @author Degryll Ludo
 * @brief Utility functions for OAL
 */

#include "ZBE/OAL/tools/OALUtils.h"

namespace zbe {

std::string formattedOALError(ALCenum error){
  if (error != AL_NO_ERROR) {
    if (error == AL_INVALID_NAME) {
      return std::string("AL_INVALID_NAME");
    } else if (error == AL_INVALID_ENUM) {
      return std::string("AL_INVALID_ENUM");
    } else if (error == AL_INVALID_VALUE) {
      return std::string("AL_INVALID_VALUE");
    } else if (error == AL_INVALID_OPERATION) {
      return std::string("AL_INVALID_OPERATION");
    } else if (error == AL_OUT_OF_MEMORY) {
      return std::string("AL_OUT_OF_MEMORY");
    } else{
      return std::string("OAL unknown error:")+ std::to_string(error);
    }
  }
  return std::string("No error");
}

bool isOALError(ALCenum error){
  return error != AL_NO_ERROR;
}


}  // namespace zbe
