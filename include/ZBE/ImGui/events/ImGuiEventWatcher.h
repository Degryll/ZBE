/**
 * Copyright 2016 Batis Degryll Ludo
 * @file ImGuiEventWatcher.h
 * @since 2020-04-16
 * @date 2020-04-16
 * @author Degryll
 * @brief Watcher that send SDL Event to ImGui.
 */

#ifndef ZBE_IMGUI_EVENTS_IMGUIEVENTWATCHER_H
#define ZBE_IMGUI_EVENTS_IMGUIEVENTWATCHER_H

#include "ZBE/SDL/sdl_warning_suppressor.h"

#include "ZBE/SDL/events/SDLEventWatcher.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class ZBEAPI ImGuiEventWatcher : public SDLEventWatcher {
public:

  /** \brief Empty Destructor
   */
  virtual ~ImGuiEventWatcher() = default;

  //void set(std::shared_ptr<InputBuffer>, std::shared_ptr<InputTextBuffer>, std::shared_ptr<ContextTime>) {}

  void watch(SDL_Event event) override {
    ImGui_ImplSDL2_ProcessEvent(&event);
  }
};// namespace zbe

class ImGuiEventWatcherFtry : public Factory {
public:

  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<ImGuiEventWatcher> imGuiEventWatcher(new ImGuiEventWatcher);
    imGuiEventWatcherRsrc.insert("ImGuiEventWatcher."s + name, imGuiEventWatcher);
    sdlEWRSrc.insert("SDLEventWatcher."s + name, imGuiEventWatcher);
  }
  
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    auto cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if(!j["window"].is_string()) {
        SysError::setError("ImGuiEventWatcher config for window: "s + j["window"].get<std::string>() + ": must be a window name."s);
        return;
      }

      std::string windowName = j["window"].get<std::string>();
      if(!sdlEDRsrc.contains("ImGuiSDLOGLWindow."s + windowName + ".SDLEventDispatcher")) {
        SysError::setError("ImGuiEventWatcher config for window: "s + windowName + ".SDLEventDispatcher does not exits."s);
        return;
      }

      auto imGuiEventWatcher = imGuiEventWatcherRsrc.get("ImGuiEventWatcher."s + name);
      auto ed = sdlEDRsrc.get("ImGuiSDLOGLWindow."s + windowName + ".SDLEventDispatcher");
      ed->addWatcher(imGuiEventWatcher);

    } else {
      SysError::setError("KeyMouseEventWatcherFtry config for "s + name + " not found."s);
    }

  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ImGuiEventWatcher> &imGuiEventWatcherRsrc = RsrcStore<ImGuiEventWatcher>::getInstance();
  RsrcStore<SDLEventDispatcher>& sdlEDRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
  RsrcStore<SDLEventWatcher>& sdlEWRSrc = RsrcStore<SDLEventWatcher>::getInstance();
DISABLE_WARNING_POP()
};

}  

#endif  // ZBE_IMGUI_EVENTS_IMGUIEVENTWATCHER_H
