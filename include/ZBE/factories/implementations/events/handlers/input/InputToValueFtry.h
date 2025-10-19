/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputToValueFtry.h
 * @since 2019-01-24
 * @date 2019-01-24
 * @author Ludo Degryll Batis
 * @brief Factory for InputToValue.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_INPUTTOVALUEFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_INPUTTOVALUEFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/events/handlers/input/InputToValue.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for InputToValue.
 */
class InputToValueFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<InputToValue> itv = std::make_shared<InputToValue>();

    uint64_t id = SysIdGenerator::getId();
    inputRsrc.insert(id, itv);
    dict.insert("InputHandler."s + name, id);
    id = SysIdGenerator::getId();
    itvRsrc.insert(id, itv);
    dict.insert("InputToValue."s + name, id);
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
      auto itv = itvRsrc.get("InputToValue."s + name);
      json valcfg = j["value"];
      if (valcfg.is_string()){
        itv->setValue(valueDRsrc.get("ValueD."s + valcfg.get<std::string>()));
      } else {
        SysError::setError("InputToValue handler value name for "s + name + " is invalid."s);
      }

    } else {
      SysError::setError("InputToValue config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc = RsrcStore<InputHandler>::getInstance();
  RsrcStore<InputToValue> &itvRsrc = RsrcStore<InputToValue>::getInstance();
  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_INPUTTOVALUEFTRY_H_
