/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BroadcastIHFtry.h
 * @since 2019-01-14
 * @date 2019-01-14
 * @author Ludo Degryll Batis
 * @brief Factory for BroadcastIH.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"

#include "ZBE/events/handlers/input/BroadcastIH.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

/** \brief Factory for BroadcastIH.
 */
class BroadcastIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<BroadcastIH> bih = std::make_shared<BroadcastIH>();

    uint64_t id = SysIdGenerator::getId();
    inputRsrc.insert(id, bih);
    dict.insert("InputHandler."s + name, id);
    id = SysIdGenerator::getId();
    bihRsrc.insert(id, bih);
    dict.insert("BroadcastIH."s + name, id);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BroadcastIHFtry config for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;


    bool haskey = j["key"].is_string();
    bool hasIeg = j["inputEventGenerator"].is_string();

    json handlers = j["handlers"];
    auto bih = bihRsrc.get("BroadcastIH."s + name);
    for (auto hnd : handlers) {
      if (hnd.is_string()){
        std::string handlerName = hnd.get<std::string>();
        bih->addHandler(inputRsrc.get("InputHandler."s + handlerName));
      } else {
        SysError::setError("BroadcastIHFtry handlers config contains an invalid element ."s);
      }
    }

    if(haskey != hasIeg) {
      if (!hasIeg) {
        SysError::setError("BroadcastIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      } else {
        SysError::setError("BroadcastIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }
    }

    if(haskey) {
      auto ieg = JSONFactory::StoreLoader<InputEventGenerator>::loadParamCfgStoreP(iegStore, j, "InputEventGenerator"s, "inputEventGenerator"s, "BroadcastIHFtry"s);
      if(!ieg) {
        SysError::setError("BroadcastIHFtry config for inputEventGenerator is invalid"s);
        return;
      }

      auto key = JSONFactory::DictLoader<ZBE_K>::loadParamCfgDict(keyDict, j, "key"s, "BroadcastIHFtry"s);
      if(!key) {
        SysError::setError("BroadcastIHFtry config for key is invalid"s);
        return;
      }

      (*ieg)->addHandler(*key, bih);
    }

  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc = RsrcStore<InputHandler>::getInstance();
  RsrcStore<BroadcastIH> &bihRsrc = RsrcStore<BroadcastIH>::getInstance();
  RsrcDictionary<ZBE_K> &keyDict           = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore = RsrcStore<InputEventGenerator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_
