/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONSimpleOGLModelSheetLoaderFtry.h
 * @since 2020-09-09
 * @date 2020-09-09
 * @author Degryl, Ludo, Batis
 * @brief Factory for JSONSimpleOGLModelSheetLoader.
 */

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADERFTRY_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADERFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>


#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/JSON/resources/JSONSimpleOGLModelSheetLoader.h"

namespace zbe {

/** \brief Factory for JSONSimpleOGLModelSheetLoader.
 */
class ZBEAPI JSONSimpleOGLModelSheetLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a JSONSimpleOGLModelSheetLoader.
   *  \param name Name for the created JSONSimpleOGLModelSheetLoader.
   *  \param cfgId JSONSimpleOGLModelSheetLoader's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdlOGLWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<JSONSimpleOGLModelSheetLoader> &jsoglmslRsrc = RsrcStore<JSONSimpleOGLModelSheetLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrclRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADERFTRY_H_
