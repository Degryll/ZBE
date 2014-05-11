/**
 * Copyright 2012 Batis Degryll Ludo
 * @file degryllmain.cpp
 * @since 2013-11-23
 * @date 2014-03-16
 * @author Degryll
 * @brief System to inform about errors.
 */

#ifndef SRC_TOOLS_SYSTEM_SYSERROR_H_
#define SRC_TOOLS_SYSTEM_SYSERROR_H_

#include <string>

namespace zbe {

class SysError {
public:
        static void setError(std::string errorString);

        static int getErrors();
        static std::string getErrorString();

private:
        static int nerrors;
        static std::string errorString;
};

}  // namespace zbe

#endif  // SRC_TOOLS_SYSTEM_SYSERROR_H_
