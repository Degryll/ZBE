/**
 * Copyright 2012 Batis Degryll Ludo
 * @file degryllmain.cpp
 * @since 2013-11-23
 * @date 2014-03-16
 * @author Degryll
 * @brief System to inform about errors.
 */

#include <string>

#include "ZBE/core/system/SysError.h"

namespace zbe {

int SysError::nerrors = 0;
std::string SysError::errorString = "";

int SysError::getErrors() {
  return (nerrors);
}

std::string SysError::getErrorString() {
  return (errorString);
}

void SysError::setError(std::string errorString) {
        if (!SysError::nerrors) {
                SysError::errorString = errorString;
        }
        SysError::nerrors++;
}

}  // namespace zbe
