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

#include <SDL2/SDL.h>

#include "ZBE/SDL/events/SDLEventWatcher.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class ImGuiEventWatcher : public SDLEventWatcher {
public:

  /** \brief Empty Destructor
   */
  ~ImGuiEventWatcher() {}

  void set(std::shared_ptr<InputBuffer>, std::shared_ptr<InputTextBuffer>, std::shared_ptr<ContextTime>) {}

  void watch(SDL_Event event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
  }
};

}  // namespace zbe

#endif  // ZBE_IMGUI_EVENTS_IMGUIEVENTWATCHER_H
