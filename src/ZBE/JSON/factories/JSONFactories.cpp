/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONFactories.cpp
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#include <string>

#include "ZBE/JSON/factories/JSONFactories.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/JSON/resources/JSONImgDefLoader.h"
#include "ZBE/JSON/resources/JSONMultiSpriteSheetLoader.h"
#include "ZBE/factories/implementations/GenericFtry.h"

namespace zbe {

void JSONFactories::load() {
  using namespace std::string_literals;

  auto& factories = RsrcStore<Factory>::getInstance();
  factories.insert("JSONImgDefLoaderFtry"s, std::make_shared<GenericFtry<RsrcDefLoader, JSONImgDefLoader> >("RsrcDefLoader", "JSONImgDefLoader"));
  factories.insert("JSONMultiSprtSheetLoaderFtry"s, std::make_shared<GenericFtry<RsrcLoader, JSONMultiSpriteSheetLoader> >("RsrcLoader", "JSONMultiSpriteSheetLoader"));

}

}  // namespace zbe
