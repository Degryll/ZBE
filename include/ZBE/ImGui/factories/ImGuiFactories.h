/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.h
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */

 // ZBE/ImGui/factories/ImGuiFactories.h
#ifndef ZBE_IMGUI_FACTORIES_IMGUIFACTORIES_H_
#define ZBE_IMGUI_FACTORIES_IMGUIFACTORIES_H_

#include <string>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/SDL/OGL/ImGui/ImGuiSDLOGLWindow.h"
#include "ZBE/ImGui/daemons/ImGuiPostLoopDaemon.h"
#include "ZBE/ImGui/daemons/ImGuiPreLoopDaemon.h"
#include "ZBE/ImGui/events/ImGuiEventWatcher.h"
#include "ZBE/ImGui/daemons/ImGuiStatusDrawDaemon.h"
#include "ZBE/ImGui/daemons/ImGuiMenuDrawDaemon.h"
#include "ZBE/ImGui/daemons/ImGuiStyleEditorDaemon.h"
#include "ZBE/ImGui/daemons/ImGuiStyleLoadDaemon.h"

namespace zbe {

/** \brief Daemon capable of load all base factories.
 */
class ImGuiFactories : public Daemon {
public:
  ~ImGuiFactories() = default;

  /** \brief It will Load the factories calling the load method.
  */
  void run() override {
    //load();
  };

  /** \brief It loads all factories.
  */
  static void load(RsrcStore<Factory>& factories) {
    // --- Behaviors
    factories.insert("ImGuiSDLOGLWindowFtry", std::make_shared<ImGuiSDLOGLWindowFtry>());
    factories.insert("ImGuiPostLoopDaemonFtry", std::make_shared<ImGuiPostLoopDaemonFtry>());
    factories.insert("ImGuiPreLoopDaemonFtry", std::make_shared<ImGuiPreLoopDaemonFtry>());
    factories.insert("ImGuiEventWatcherFtry", std::make_shared<ImGuiEventWatcherFtry>());
    factories.insert("ImGuiStatusDrawDaemonFtry", std::make_shared<GenericFtry<Daemon, ImGuiStatusDrawDaemon>>("Daemon", "ImGuiStatusDrawDaemon"));
    factories.insert("ImGuiMenuDrawDaemonFtry", std::make_shared<ImGuiMenuDrawDaemonFtry>());
    factories.insert("ImGuiStyleEditorDaemonFtry", std::make_shared<GenericFtry<Daemon, ImGuiStyleEditorDaemon>>("Daemon", "ImGuiStyleEditorDaemon"));
    factories.insert("ImGuiStyleLoadDaemonFtry", std::make_shared<ImGuiStyleLoadDaemonFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_IMGUI_FACTORIES_IMGUIFACTORIES_H_