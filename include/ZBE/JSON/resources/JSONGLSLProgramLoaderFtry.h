/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONGLSLProgramLoaderFtry.h
 * @since 2020-09-09
 * @date 2020-09-09
 * @author Degryl, Ludo, Batis
 * @brief Factory for JSONGLSLProgramLoader.
 */

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMFILELOADERFTRY_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMFILELOADERFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>


#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/JSON/resources/JSONGLSLProgramLoader.h"

namespace zbe {

/** \brief Factory for JSONGLSLProgramLoader.
 */
class JSONGLSLProgramLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a JSONGLSLProgramFileLoad.
   *  \param name Name for the created JSONGLSLProgramFileLoad.
   *  \param cfgId JSONGLSLProgramFileLoad's configuration id.
   */
   void create(std::string name, uint64_t) override {
     using namespace std::string_literals;

     auto jsoglmsl = std::make_shared<JSONGLSLProgramLoader>();
     rsrclRsrc.insert("RsrcLoader."s + name, jsoglmsl);
     jsonglslplRsrc.insert("JSONGLSLProgramLoader."s + name, jsoglmsl);
   }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
   void setup(std::string name, uint64_t cfgId) override {
     using namespace std::string_literals;
     using namespace nlohmann;
     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

     if(cfg) {
       auto j = *cfg;
       json window = j["window"];
       if(!window.is_string()) {
         SysError::setError("Bad config for JSONGLSLProgramLoaderFtry - window."s + window.get<std::string>());
         return;
       }

       auto winname = j["window"].get<std::string>();
       auto win = sdlOGLWindowRsrc.get("SDLOGLWindow."s + winname);

       auto jsglslpl = jsonglslplRsrc.get("JSONGLSLProgramLoader."s + name);
       jsglslpl->setWindow(win);
     } else {
       SysError::setError("JSONGLSLProgramLoaderFtry config for "s + name + " not found."s);
     }
   }


private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdlOGLWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<JSONGLSLProgramLoader> &jsonglslplRsrc = RsrcStore<JSONGLSLProgramLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrclRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMFILELOADERFTRY_H_
