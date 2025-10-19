/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonClickIHFtry.h
 * @since 2019-01-24
 * @date 2019-01-24
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonClickIH.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/events/handlers/input/DaemonClickIH.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonClickIH.
 */
class DaemonClickIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<DaemonClickIH> dcih = std::make_shared<DaemonClickIH>();

    uint64_t id = SysIdGenerator::getId();
    inputRsrc.insert(id, dcih);
    dict.insert("InputHandler."s + name, id);
    id = SysIdGenerator::getId();
    dcihRsrc.insert(id, dcih);
    dict.insert("DaemonClickIH."s + name, id);
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
      json daemonCfg = j["daemon"];
      auto dcih = dcihRsrc.get("DaemonClickIH."s + name);
      if (daemonCfg.is_string()){
        std::string daemonName = daemonCfg.get<std::string>();
        dcih->setDaemon(daemonRsrc.get("Daemon."s + daemonName));
      } else {
        SysError::setError("DaemonClickIH handler daemon config for "s + name + " is invalid."s);
      }
      json xcfg = j["x"];
      json ycfg = j["y"];
      json hcfg = j["h"];
      json wcfg = j["w"];

      if (xcfg.is_number() && ycfg.is_number() && hcfg.is_number() && wcfg.is_number()){
        dcih->setArea(Region2D({xcfg.get<double>(), ycfg.get<double>()},{hcfg.get<double>(),wcfg.get<double>()}));
      } else {
        SysError::setError("DaemonClickIH handler box config for "s + name + " is invalid."s);
      }

      json xValcfg = j["xval"];
      json yValcfg = j["yval"];

      if (xValcfg.is_string() && yValcfg.is_string()){
        dcih->setYValue(valueDRsrc.get("ValueD."s + yValcfg.get<std::string>()));
        dcih->setXValue(valueDRsrc.get("ValueD."s + xValcfg.get<std::string>()));
      } else {
        SysError::setError("DaemonClickIH handler pointer input config for "s + name + " is invalid."s);
      }

    } else {
      SysError::setError("DaemonClickIH config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc = RsrcStore<InputHandler>::getInstance();
  RsrcStore<DaemonClickIH> &dcihRsrc = RsrcStore<DaemonClickIH>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_
