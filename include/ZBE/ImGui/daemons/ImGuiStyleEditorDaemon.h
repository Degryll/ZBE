/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiStyleEditorDaemon.h
 * @since 2026-07-01
 * @author GitHub Copilot
 * @brief Daemon that shows the ImGui style editor.
 */

#ifndef ZBE_SDL_DAEMONS_IMGUISTYLEEDITORDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUISTYLEEDITORDAEMON_H_

#include <imgui.h>
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

class ZBEAPI ImGuiStyleEditorDaemon : public Daemon {
public:
  ImGuiStyleEditorDaemon(const ImGuiStyleEditorDaemon&) = delete;
  void operator=(const ImGuiStyleEditorDaemon&) = delete;

  ImGuiStyleEditorDaemon() = default;
  ~ImGuiStyleEditorDaemon() = default;

  void run() override {
    ImGui::Begin("Style Editor");
    ImGui::ShowStyleEditor();
    ImGui::End();
  }
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUISTYLEEDITORDAEMON_H_
