/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.h
 * @since 2013-11-23
 * @date 2014-03-16
 * @author Degryll
 * @brief System to inform about errors.
 */

#ifndef CORE_SYSTEM_SYSERROR_H_
#define CORE_SYSTEM_SYSERROR_H_

#include <string>

namespace zbe {

class SysError {
public:
  static void setError(std::string errorString);

  static int getNErrors();
  static std::string getLastErrorString();

  static void clear();

private:
        static int nerrors;
        static std::string errorString;
};

}  // namespace zbe

#endif  // CORE_SYSTEM_SYSERROR_H_
