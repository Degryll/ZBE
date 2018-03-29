/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.cpp
 * @since 2013-11-23
 * @date 2018-03-27
 * @author Degryll Batis Ludo
 * @brief System to inform about errors.
 */

#include "ZBE/core/system/SysError.h"

namespace zbe {

int SysError::nerrors = 0;
std::string SysError::errorString = "";

int SysError::getNErrors() {
  return (nerrors);
}

std::string SysError::getFirstErrorString() {
  return (errorString);
}

void SysError::setError(std::string errorString) {
  if (!SysError::nerrors) {
          SysError::errorString = errorString;
  }
  SysError::nerrors++;
}

void SysError::clear() {
  SysError::nerrors = 0;
  SysError::errorString = "";
}

}  // namespace zbe
