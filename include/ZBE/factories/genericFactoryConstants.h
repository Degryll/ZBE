/**
 * Copyright 2012 Batis Degryll Ludo
 * @file genericFactoryConstants.h
 * @since 2022-02-09
 * @date 2019-02-09
 * @author Ludo Degryll Batis
 * @brief Constants for generic factories.
 */


#ifndef ZBE_FACTORIES_GENERICFACTORYCONSTANTS_H_
#define ZBE_FACTORIES_GENERICFACTORYCONSTANTS_H_

#include <string>

namespace zbe {
  namespace factories {
    using namespace std::string_literals;

    static const std::string listName = "List"s;
    static const std::string functionName = "Function"s;
    static const std::string separator = "."s;
    static const std::string contextimeName = "ContextTime"s;
  }
}  // namespace zbe

#endif  // ZBE_FACTORIES_GENERICFACTORYCONSTANTS_H_
