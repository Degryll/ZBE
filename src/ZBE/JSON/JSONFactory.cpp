/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONFactory.cpp
 * @since 2026-12-05
 * @date 2026-12-05
 * @author Degryll Batis Ludo
 * @brief Define the basic functionality of every entity.
 */

#include "ZBE/JSON/JSONFactory.h"

namespace zbe {
namespace JSONFactory {
using namespace nlohmann;

Vector3D parseV3DFromCfg(nlohmann::json cfgValue, std::string paramName, std::string factoryName) {
    using namespace std::string_literals;
    std::size_t c = 0;
    Vector3D val;
    for (auto item : cfgValue.items()) {
      if(item.value().is_number_float()) {
        val[c++] = item.value().get<double>();
      } else {
        SysError::setError(factoryName + " cant parse "s + paramName + " cause it has invalid content."s);
        break;
      }
    }
    return val;
}

}
}  // namespace zbe

