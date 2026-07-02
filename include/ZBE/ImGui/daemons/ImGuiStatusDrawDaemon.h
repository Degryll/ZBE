/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiStatusDrawDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Daemon that runs after the main loop.
 * at the end of every frame:
 * Shows the window (if double buffer changes it).
 */

#ifndef ZBE_SDL_DAEMONS_IMGUISTATUSDRAWDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUISTATUSDRAWDAEMON_H_

#include <memory>
#include <tuple>

#include <imgui.h>
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

namespace zbe {

class ZBEAPI ImGuiStatusDrawDaemon : public Daemon {
public:
  ImGuiStatusDrawDaemon(const ImGuiStatusDrawDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiStatusDrawDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  ImGuiStatusDrawDaemon() {}

  /** \brief Destroys the ImGuiStatusDrawDaemon
   */
  ~ImGuiStatusDrawDaemon() = default;

  /** \brief Runs the daemon.
   */
  void run() override {

    if (lists.empty()) {
      auto allLists = lRsrcStore.getByPrefix(factories::baseListName);
      for (const auto& list : allLists) {
        lists.push_back({list.first, list.second});
      }
      showSizes.resize(lists.size(), 0);
    }

    // if (punishers.empty()) {
    //   auto allPunishers = punisherRsrc.getByPrefix("Punisher");
    //   for (const auto& punisher : allPunishers) {
    //     auto listPtr = lRsrcStore.get(punisher.second->getListName());
    //     if (listPtr) {
    //       punishers.push_back({punisher.first, punisher.second, listPtr});
    //     } else {
    //       SysError::setError(std::string("Punisher ") + punisher.first + " has a non existing list: " + punisher.second->getListName());
    //     }
    //   }
    //   showPunisherDetails.resize(punishers.size(), 0);
    // }

    ImGui::Begin("Estado del sistema");

    // Mostrar FPS
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", static_cast<double>(io.Framerate));

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Listas")) {
        bool prevSelectAll = selectAll;
        ImGui::Checkbox("Seleccionar todos", &selectAll);
        if (selectAll != prevSelectAll) {
            for (size_t i = 0; i < showSizes.size(); ++i) {
                showSizes[i] = selectAll ? 1 : 0;
            }
        }
        ImGui::Separator();

        for (size_t i = 0; i < lists.size(); ++i) {
            const auto& pair = lists[i];
            bool checked = showSizes[i];
            if (checked) {
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
            }
            ImGui::Checkbox(pair.first.c_str(), &checked);
            showSizes[i] = checked;
            if (checked) {
                ImGui::SameLine();
                ImGui::Text("%lu", pair.second->getSize());
            }
            ImGui::PopStyleColor();
        }
    }

    if (ImGui::CollapsingHeader("Punishers")) {
        bool prevSelectAllP = selectAllPunishers;
        ImGui::Checkbox("Seleccionar todos", &selectAllPunishers);
        if (selectAllPunishers != prevSelectAllP) {
            for (size_t i = 0; i < showPunisherDetails.size(); ++i) {
                showPunisherDetails[i] = selectAllPunishers ? 1 : 0;
            }
        }
        ImGui::Separator();

        for (size_t i = 0; i < punishers.size(); ++i) {
            const auto& tpl = punishers[i];
            bool checked = showPunisherDetails[i];
            if (checked) {
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
            }
            ImGui::Checkbox(std::get<0>(tpl).c_str(), &checked);
            showPunisherDetails[i] = checked;
            if (checked) {
                ImGui::SameLine();
                uint64_t size = std::get<2>(tpl)->getSize();
                ImGui::Text("%s: %lu", std::get<0>(tpl).c_str(), size);
            }
            ImGui::PopStyleColor();
        }
    }

    ImGui::End();
  }

private:
  bool show_demo_window = true;
  RsrcStore<TickFListBase>& lRsrcStore = RsrcStore<TickFListBase>::getInstance();
  RsrcStore<BasePunisher>& punisherRsrc = RsrcStore<BasePunisher>::getInstance();
  std::vector<std::pair<std::string, std::shared_ptr<TickFListBase>>> lists; // Ejemplo de recurso común para almacenar las listas a mostrar.
  std::vector<char> showSizes;
  bool selectAll = false;
  std::vector<std::tuple<std::string, std::shared_ptr<BasePunisher>, std::shared_ptr<TickFListBase>>> punishers;
  std::vector<char> showPunisherDetails;
  bool selectAllPunishers = false;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUISTATUSDRAWDAEMON_H_
