/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2018-03-27
 * @author Ludo Batis Degryll
 * @brief Input event generator, implementation file.
 */

#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zbe {

void InputEventGenerator::run() {
  std::vector<InputStatus> currentInput;
  inputBuffer->getRange(contextTime->getInitFrameTime(), contextTime->getEndFrameTime(), currentInput);
  auto it = currentInput.begin();
  while (it != currentInput.end() && ! mism.generate(*it)){
    ++it;
  }

  if (it!= currentInput.end()) {
    auto time = it->getTime();
    ++it;
    for(; it != currentInput.end(); ++it) {
      if (it->getTime()!=time) {
        break;
      }
      mism.generate(*it);
    } // for each currentInput
  }

  if (handler != nullptr) {
    std::vector<InputText> itv;
    inputTextBuffer->getFirstInRange(contextTime->getInitFrameTime(), contextTime->getEndFrameTime(), itv);
    for(auto input : itv) {
      TextEvent* e = new TextEvent(eventId, input.getTime(), input.getText(), handler);
      store.storeEvent(e);
    } // for each currentInput
  }
}

void InputEventGeneratorFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<InputEventGenerator> so = std::shared_ptr<InputEventGenerator>(new InputEventGenerator);
  daemonRsrc.insert("Daemon."s + name, so);
  iegRsrc.insert("InputEventGenerator."s + name, so);
}

void InputEventGeneratorFtry::setup(std::string name, uint64_t cfgId) {
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

  } else {
    SysError::setError("SineOscillatorFFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
