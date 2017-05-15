/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.cpp
 * @since 2013-11-23
 * @date 2017-05-15
 * @author Degryll
 * @brief System to inform about errors.
 */

#include "ZBE/core/system/SysError.h"

#include <string>

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
