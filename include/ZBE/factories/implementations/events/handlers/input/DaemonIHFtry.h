/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonIHFtry.h
 * @since 2019-01-24
 * @date 2019-01-24
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonIH.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONIHFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONIHFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/events/handlers/input/DaemonIH.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonIH.
 */
class ZBEAPI DaemonIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict                 = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc       = RsrcStore<InputHandler>::getInstance();
  RsrcStore<DaemonIH> &dcihRsrc            = RsrcStore<DaemonIH>::getInstance();
  RsrcStore<Daemon> &daemonStore           = RsrcStore<Daemon>::getInstance();
  RsrcDictionary<ZBE_K> &keyDict           = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<InputEventGenerator> &iegStore = RsrcStore<InputEventGenerator>::getInstance();
};

/** \brief Factory for DaemonIH.
 */
template<typename T>
class ZBEAPI ConditionalDaemonIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
void create(std::string name, uint64_t) {
  using namespace std::string_literals;
  std::shared_ptr<ConditionalDaemonIH<T>> dcih = std::make_shared<ConditionalDaemonIH<T>>();

  uint64_t id = SysIdGenerator::getId();
  inputRsrc.insert(id, dcih);
  dict.insert("InputHandler."s + name, id);
  id = SysIdGenerator::getId();
  dcihRsrc.insert(id, dcih);
  dict.insert("ConditionalDaemonIH."s + name, id);
}

/** \brief Setup the desired tool. The tool will be complete after this step.
 *  \param name Name of the tool.
 *  \param cfgId Tool's configuration id.
 */
void setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;

    if (!j["daemon"].is_string()) {
      SysError::setError("ConditionalDaemonIH config for daemon: "s + j["daemon"].get<std::string>() + ": must be a daemon name."s);
      return;
    }

    std::string daemonName = j["daemon"].get<std::string>();
    if(!daemonStore.contains("Daemon."s + daemonName)) {
      SysError::setError("DaemonIH config for daemon: "s + daemonName + " is not a daemon name."s);
      return;
    }

    auto daemon = daemonStore.get("Daemon."s + daemonName);
    auto ih   = dcihRsrc.get("ConditionalDaemonIH."s + name);
    ih->setDaemon(daemon);

    bool haskey = j["key"].is_string();
    bool hasIeg = j["inputEventGenerator"].is_string();
    bool hasValue = j["value"].is_number_float();

    bool hasEqual = j["equal"].is_boolean();

    bool equal = true;

    if(hasEqual) {
      equal = j["equal"].get<bool>();
    }

    auto expected = JSONFactory::loadParamCfgDict<T>(tDict, j, "expected"s, "ConditionalDaemonIHFtry"s);
    if(!expected) {
      SysError::setError("ConditionalDaemonIHFtry config for expected is invalid"s);
      return;
    }

    auto condition = JSONFactory::loadParamCfgStore<Value<T>>(valueRsrc, j, "condition"s, "ConditionalDaemonIHFtry"s);
    if(!condition) {
      SysError::setError("ConditionalDaemonIHFtry config for condition is invalid"s);
      return;
    }

    ih->setCondition(*condition, *expected, equal);

    if(haskey != hasIeg) {
      if (!hasIeg) {
        SysError::setError("ConditionalDaemonIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      } else {
        SysError::setError("ConditionalDaemonIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }
    }

    if(hasValue) {
      float val = j["value"].get<float>();
      ih->setValue(val);
    }

    if(haskey) {
      std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
      if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
        SysError::setError("DaemonIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
        return;
      }

      std::string keyName = j["key"].get<std::string>();
      if(!keyDict.contains(keyName)) {
        SysError::setError("DaemonIHFtry config for key: "s + keyName + " is not a key name."s);
        return;
      }

      auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
      auto key    = keyDict.get(keyName);
      ieg->addHandler(key, ih);
    }

  } else {
    SysError::setError("DaemonIH config for "s + name + " not found."s);
  }
}


private:
  NameRsrcDictionary &dict                    = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc       = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc          = RsrcStore<InputHandler>::getInstance();
  RsrcStore<ConditionalDaemonIH<T>> &dcihRsrc = RsrcStore<ConditionalDaemonIH<T>>::getInstance();
  RsrcStore<Daemon> &daemonStore              = RsrcStore<Daemon>::getInstance();
  RsrcDictionary<ZBE_K> &keyDict              = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<InputEventGenerator> &iegStore    = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<Value<T>> &valueRsrc              = RsrcStore<Value<T>>::getInstance();
  RsrcDictionary<T> &tDict                    = RsrcDictionary<T>::getInstance();
};



/** \brief Factory for DaemonIH.
 */
template<typename T>
class ZBEAPI ConditionalCompositeIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
void create(std::string name, uint64_t) {
  using namespace std::string_literals;
  std::shared_ptr<ConditionalCompositeIH<T>> ccih = std::make_shared<ConditionalCompositeIH<T>>();
  inputRsrc.insert("InputHandler."s + name, ccih);
  ccihRsrc.insert("ConditionalCompositeIH."s + name, ccih);
}

/** \brief Setup the desired tool. The tool will be complete after this step.
 *  \param name Name of the tool.
 *  \param cfgId Tool's configuration id.
 */
void setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;

    if (!j["handler"].is_string()) {
      SysError::setError("ConditionalCompositeIH config for handler: "s + j["handler"].get<std::string>() + ": must be a Input Handler name."s);
      return;
    }

    std::string handlerName = j["handler"].get<std::string>();
    if(!inputRsrc.contains("InputHandler."s + handlerName)) {
      SysError::setError("ConditionalCompositeIH config for handler: "s + handlerName + " is not an InputHandler name."s);
      return;
    }

    auto subIh = inputRsrc.get("InputHandler."s + handlerName);

    auto ih   = ccihRsrc.get("ConditionalCompositeIH."s + name);
    ih->setInputHandler(subIh);

    bool haskey = j["key"].is_string();
    bool hasIeg = j["inputEventGenerator"].is_string();

    bool hasEqual = j["equal"].is_boolean();

    bool equal = true;

    if(hasEqual) {
      equal = j["equal"].get<bool>();
    }

    auto expected = JSONFactory::loadParamCfgDict<T>(tDict, j, "expected"s, "ConditionalCompositeIHFtry"s);
    if(!expected) {
      SysError::setError("ConditionalCompositeIHFtry config for expected is invalid"s);
      return;
    }

    auto condition = JSONFactory::loadParamCfgStore<Value<T>>(valueRsrc, j, "condition"s, "ConditionalCompositeIHFtry"s);
    if(!condition) {
      SysError::setError("ConditionalCompositeIHFtry config for condition is invalid"s);
      return;
    }

    ih->setCondition(*condition, *expected, equal);

    if(haskey != hasIeg) {
      if (!hasIeg) {
        SysError::setError("ConditionalCompositeIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      } else {
        SysError::setError("ConditionalCompositeIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }
    }

    if(haskey) {
      std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
      if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
        SysError::setError("ConditionalCompositeIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
        return;
      }

      std::string keyName = j["key"].get<std::string>();
      if(!keyDict.contains(keyName)) {
        SysError::setError("ConditionalCompositeIHFtry config for key: "s + keyName + " is not a key name."s);
        return;
      }

      auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
      auto key    = keyDict.get(keyName);
      ieg->addHandler(key, ih);
    }

  } else {
    SysError::setError("ConditionalCompositeIHFtry config for "s + name + " not found."s);
  }
}


private:
  NameRsrcDictionary &dict                    = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc       = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc          = RsrcStore<InputHandler>::getInstance();
  RsrcStore<ConditionalCompositeIH<T>> &ccihRsrc = RsrcStore<ConditionalCompositeIH<T>>::getInstance();
  RsrcDictionary<ZBE_K> &keyDict              = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<InputEventGenerator> &iegStore    = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<Value<T>> &valueRsrc              = RsrcStore<Value<T>>::getInstance();
  RsrcDictionary<T> &tDict                    = RsrcDictionary<T>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONIHFTRY_H_
