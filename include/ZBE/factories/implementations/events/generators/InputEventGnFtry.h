/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGeneratorFtry.h
 * @since 2025-10-15
 * @date 2025-10-15
 * @author Ludo
 * @brief Input event generator.
 */


#ifndef ZBE_FACTORIES_EVENTS_GENERATORS_INPUTEVENTGENERATORFTRY_H
#define ZBE_FACTORIES_EVENTS_GENERATORS_INPUTEVENTGENERATORFTRY_H

#include "ZBE/factories/Factory.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/system/SysError.h"
#include <nlohmann/json.hpp>
#include <string>

namespace zbe {


class InputEventGeneratorFtry : public Factory {
public:

  /** \brief Builds a InputEventGenerator.
   *  \param name Name for the created InputEventGenerator.
   *  \param cfgId InputEventGenerator's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<InputEventGenerator> so(new InputEventGenerator);
    daemonRsrc.insert("Daemon."s + name, so);
    iegRsrc.insert("InputEventGenerator."s + name, so);
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
      if (!j["eventId"].is_string()) {
        SysError::setError("InputEventGeneratorFtry config for eventId: "s + j["eventId"].get<std::string>() + ": must be a unsigned integer literal."s);
        return;
      }

      if (!j["contextTime"].is_string()) {
        SysError::setError("InputEventGeneratorFtry config for contextTime: "s + j["contextTime"].get<std::string>() + ": must be an context time name."s);
        return;
      }

      if (!j["inputBuffer"].is_string()) {
        SysError::setError("InputEventGeneratorFtry config for inputBuffer: "s + j["inputBuffer"].get<std::string>() + ": must be an inputBuffer name."s);
        return;
      }

      if (!j["inputTextBuffer"].is_string()) {
        SysError::setError("InputEventGeneratorFtry config for inputTextBuffer: "s + j["inputTextBuffer"].get<std::string>() + ": must be an inputTextBuffer."s);
        return;
      }

      std::string eventIdName = j["eventId"].get<std::string>();
      if(!uintStore.contains(eventIdName)) {
        SysError::setError("InputEventGeneratorFtry config for eventId: "s + eventIdName + " does not exits."s);
        return;
      }

      std::string contextTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + contextTimeName)) {
        SysError::setError("InputEventGeneratorFtry config for contextTime: "s + contextTimeName + " does not exits."s);
        return;
      }

      std::string inputBufferName = j["inputBuffer"].get<std::string>();
      if(!ibuffRsrc.contains(inputBufferName)) {
        SysError::setError("InputEventGeneratorFtry config for inputBuffer: "s + inputBufferName + " does not exits."s);
        return;
      }

      std::string inputTextBufferName = j["inputTextBuffer"].get<std::string>();
      if(!itBuffRsrc.contains(inputTextBufferName)) {
        SysError::setError("InputEventGeneratorFtry config for : "s + inputTextBufferName + " does not exits."s);
        return;
      }

      uint64_t eventId = uintStore.get(eventIdName);
      auto cTime = cTimeRsrc.get("ContextTime."s + contextTimeName);
      auto inputBuffer = ibuffRsrc.get(inputBufferName);
      auto inputTextBuffer = itBuffRsrc.get(inputTextBufferName);
      auto ieg = iegRsrc.get("InputEventGenerator."s + name);

      ieg->setEventID(eventId);
      ieg->setInputBuffer(inputBuffer);
      ieg->setInputTextBuffer(inputTextBuffer);
      ieg->setContextTime(cTime);
      ieg->setEventStore(&store);

    } else {
      SysError::setError("InputEventGenerator config for "s + name + " not found."s);
    }
  }


private:
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<InputEventGenerator>& iegRsrc = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
  EventStore& store = EventStore::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_EVENTS_GENERATORS_INPUTEVENTGENERATORFTRY_H
