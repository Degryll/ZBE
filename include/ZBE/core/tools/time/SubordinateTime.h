/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SubordinateTime.h
 * @since 2018-07-11
 * @date 2018-07-11
 * @author Batis Degryll Ludo
 * @brief Tool used to ask about time inside a subordinated context.
 */

#ifndef ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_
#define ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_

#include <cstdint>
#include <memory>
#include <string>

#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

#include <nlohmann/json.hpp>

namespace zbe {

/** \brief Tool used to ask about time inside a subordinated context.
*/
class ZBEAPI SubordinateTime : public ContextTime {
public:

  // cppcheck-suppress noExplicitConstructor
  SubordinateTime(std::shared_ptr<ContextTime> parent = nullptr) : parent(parent) {}
  SubordinateTime(const SubordinateTime& sibling) : parent(sibling.parent) {}

  /** \brief Get the total time passed until the end of last frame.
  * \return Total time passed until last frame.
  */
  std::shared_ptr<ContextTime> clone() override {
    return std::make_shared<SubordinateTime>(this->parent);
  }

  static std::shared_ptr<ContextTime> child(std::shared_ptr<ContextTime> parent) {
    return std::make_shared<SubordinateTime>(parent);
  }

  void setParent(std::shared_ptr<ContextTime> parent) {
    this->parent = parent;
  }

  void  setName(std::string name) {
    this->name = name;
  }

  void updateInitTime() override {
    parent->updateInitTime();
    copyParentData();
  }

  void setEventTime(uint64_t eventTime) override {
    parent->setEventTime(eventTime);
    copyParentData();
  }

  void resume(uint64_t resumeTime) override {
    SysError::setDebug(name + " resumeTime:" + std::to_string(resumeTime));
    copyParentData();
    ContextTime::resume((resumeTime ? resumeTime : parent->getInitFrameTime() + parent->getCurrentTime()));
  }

  void update() override {
    // parent->update();    
    if (!paused) {
      copyParentData();
    }
  }
  
  uint64_t _getTotalTime() override {
    assert(false && "SubordinateTime::_getTotalTime() should not be called.");
    return 0;
  }

  uint64_t _getInitTime() override {
    assert(false && "SubordinateTime::_getInitTime() should not be called.");
    return 0;
  }

  // TODO por lo que sea este tiempo hace que el input event generator reciba siempre 0 - 2048 como tiempo de frame.
  // Revisa las instancias.
private:
  void copyParentData() {
    frame = parent->getFrameTime();
    lostTime = parent->getLostTime();
    initT = parent->getInitFrameTime();
    endT = parent->getEndFrameTime();
    eventT = parent->getEventTime();
    is_partFrame = parent->isPartialFrame();
    currentT = parent->getCurrentTime();
    remainT = parent->getRemainTime();
  }
DISABLE_DLL_WARN
  std::shared_ptr<ContextTime> parent;
  std::string name;
DISABLE_WARNING_POP()

};

class ZBEAPI SubordinateTimeFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto subordinateTime = std::make_shared<SubordinateTime>();
    subTimeStore.insert("SubordinateTime."s + name, subordinateTime);
    timeStore.insert("ContextTime."s + name, subordinateTime);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;

    std::shared_ptr<json> cfg = configStore.get(cfgId);
    if (!cfg) {
      SysError::setError("SubordinateTimeFtry config for "s + name + " not found."s);
      return;
    }

    auto subordinateTime = subTimeStore.get("SubordinateTime."s + name);
    if (!subordinateTime) {
      SysError::setError("SubordinateTimeFtry resource for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;
    std::string parentName = "DEFAULT";
    if (j.contains("parent") && j["parent"].is_string()) {
      parentName = j["parent"].get<std::string>();
    }

    auto parent = timeStore.get("ContextTime."s + parentName);
    if (!parent) {
      SysError::setError("SubordinateTimeFtry config for "s + name + " parent context time "s + parentName + " not found."s);
      return;
    }

    subordinateTime->setParent(parent);
    subordinateTime->setName(name);
    if (j.contains("startPaused") && j["startPaused"].is_boolean() && j["startPaused"].get<bool>()) {
      subordinateTime->pause();
    }
  }

  // TODO probar todo esto.

private:
  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SubordinateTime>& subTimeStore = RsrcStore<SubordinateTime>::getInstance();
  RsrcStore<ContextTime>& timeStore = RsrcStore<ContextTime>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_
