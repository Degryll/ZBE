/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONFactories.h
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#ifndef ZBE_JSON_FACTORIES_JSONFACTORIES_H_
#define ZBE_JSON_FACTORIES_JSONFACTORIES_H_

#include <string>

#include "ZBE/JSON/resources/JSONImgDefLoader.h"
#include "ZBE/JSON/resources/JSONGLSLProgramLoaderFtry.h"
#include "ZBE/JSON/resources/JSONMultiSpriteSheetLoader.h"
#include "ZBE/JSON/resources/JSONOGLModelSheetLoaders.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/GenericFtry.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI JSONFactories : public Daemon {
public:
  ~JSONFactories() = default;

  /** \brief It will Load the factories calling the load method.
  */
  void run() override {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    using namespace std::string_literals;

    auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("JSONImgDefLoaderFtry"s, std::make_shared<GenericFtry<RsrcDefLoader, JSONImgDefLoader> >("RsrcDefLoader", "JSONImgDefLoader"));
    factories.insert("JSONMultiSprtSheetLoaderFtry"s, std::make_shared<GenericFtry<RsrcLoader, JSONMultiSpriteSheetLoader> >("RsrcLoader", "JSONMultiSpriteSheetLoader"));
    factories.insert("JSONLookAtOGLModelSheetLoaderFtry"s, std::make_shared<JSONLookAtOGLModelSheetLoaderFtry>());
    factories.insert("JSONSimpleOGLModelSheetLoaderFtry"s, std::make_shared<JSONSimpleOGLModelSheetLoaderFtry>());
    factories.insert("JSONGLSLProgramLoaderFtry"s, std::make_shared<JSONGLSLProgramLoaderFtry>());
    factories.insert("JSONSpriteOGLModelSheetLoaderFtry"s, std::make_shared<JSONSpriteOGLModelSheetLoaderFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_JSON_FACTORIES_JSONFACTORIES_H_
