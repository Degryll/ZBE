#ifndef LUDO_LUDOMAIN_H_
#define LUDOMAIN_H_

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/graphics/MultiSpriteSheet.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

namespace ludo {

  int ludomain(int argc, char* argv[]);

}  // namespace ludo

#endif  // LUDO_LUDOMAIN_H_
