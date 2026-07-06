/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiMenuDrawDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Daemon that runs after the main loop.
 * at the end of every frame:
 * Shows the window (if double buffer changes it).
 */

#ifndef ZBE_SDL_DAEMONS_IMGUIMENUDRAWDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUIMENUDRAWDAEMON_H_

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include <imgui.h>
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/factories/Factory.h"
#include "nlohmann/json.hpp"

namespace zbe {

class ZBEAPI ImGuiMenuDrawDaemon : public Daemon {
public:
  ImGuiMenuDrawDaemon(const ImGuiMenuDrawDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiMenuDrawDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  ImGuiMenuDrawDaemon() {}

  /** \brief Destroys the ImGuiMenuDrawDaemon
   */
  ~ImGuiMenuDrawDaemon() = default;

  /** \brief Runs the daemon.
   */
  void run() override {
    const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    const ImGuiStyle& style = ImGui::GetStyle();

    const float buttonWidth = 220.0f;
    const float itemSpacing = style.ItemSpacing.y;
    const float itemHeight = ImGui::GetFrameHeight();

    const float itemCount = static_cast<float>(menuItems.size());

    const float titleHeight =
        menuTitle.empty()
            ? 0.0f
            : ImGui::CalcTextSize(menuTitle.c_str()).y + itemSpacing;

    const float totalButtonsHeight =
        (itemCount * itemHeight) +
        (itemCount > 0.0f ? (itemCount - 1.0f) * itemSpacing : 0.0f);

    const float totalHeight = titleHeight + totalButtonsHeight;

    // Overlay invisible ocupando toda la pantalla
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(displaySize);

    ImGui::Begin("##menu_overlay", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBackground);

    // Punto inicial centrado verticalmente
    float startY = (displaySize.y - totalHeight) * verticalAlign;
    ImGui::SetCursorPos(ImVec2(0.0f, startY));

    // Dibujar título centrado
    if (!menuTitle.empty()) {
        ImGui::SetWindowFontScale(titleFontScale);
        const float titleWidth = ImGui::CalcTextSize(menuTitle.c_str()).x;
        ImGui::SetCursorPosX((displaySize.x - titleWidth) * horizontalAlign);
        ImGui::TextUnformatted(menuTitle.c_str());
        ImGui::SetWindowFontScale(1.0f); // Restore scale
        ImGui::Dummy(ImVec2(0.0f, itemSpacing));
    }

    // Dibujar botones centrados
    ImGui::SetWindowFontScale(itemsFontScale);
    for (const auto& item : menuItems) {
      ImGui::SetCursorPosX((displaySize.x - buttonWidth) * horizontalAlign);

        if (ImGui::Button(item.first.c_str(), ImVec2(buttonWidth, itemHeight))) {
            if (item.second) {
                item.second->run();
            }
        }

        ImGui::Dummy(ImVec2(0.0f, itemSpacing));
    }
    ImGui::SetWindowFontScale(1.0f); // Restore scale

    ImGui::End();
  }

  void addMenuItem(const std::string& label, const std::shared_ptr<Daemon>& daemon) {
    SysError::setDebug("Adding menu item: " + label, false);
    menuItems.emplace_back(label, daemon);
  }

  void setMenuTitle(const std::string& title) {
    SysError::setDebug("Setting menu title: " + title, false);
    menuTitle = title;
  }

  void setHorizontalAlign(float a) { horizontalAlign = std::clamp(a, 0.0f, 1.0f); }
  void setVerticalAlign(float a)   { verticalAlign   = std::clamp(a, 0.0f, 1.0f); }
  void setTitleFontScale(float scale) { titleFontScale = std::max(scale, 0.1f); }
  void setItemsFontScale(float scale) { itemsFontScale = std::max(scale, 0.1f); }

private:
  std::vector<std::pair<std::string, std::shared_ptr<Daemon>>> menuItems;
  std::string menuTitle;
  float horizontalAlign = 0.5f;
  float verticalAlign = 0.5f;
  float titleFontScale = 1.5f;
  float itemsFontScale = 1.0f;
};

class ZBEAPI ImGuiMenuDrawDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    auto dmn = std::make_shared<ImGuiMenuDrawDaemon>();
    mainRsrc.insert("Daemon."s + name, dmn);
    specificRsrc.insert("ImGuiMenuDrawDaemon."s + name, dmn);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;

    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    if (!cfg) {
      SysError::setError("ImGuiMenuDrawDaemonFtry config for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;
    auto dmn = specificRsrc.get("ImGuiMenuDrawDaemon."s + name);
    if (!dmn) {
      SysError::setError("ImGuiMenuDrawDaemonFtry daemon for "s + name + " not found."s);
      return;
    }

    if (j.contains("title")) {
      if (!j["title"].is_string()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - title must be a string."s);
        return;
      }
      dmn->setMenuTitle(j["title"].get<std::string>());
    }

    if (j.contains("horizontalAlign")) {
      if (!j["horizontalAlign"].is_number()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - horizontalAlign must be a number."s);
      } else {
        dmn->setHorizontalAlign(j["horizontalAlign"].get<float>());
      }
    }

    if (j.contains("verticalAlign")) {
      if (!j["verticalAlign"].is_number()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - verticalAlign must be a number."s);
      } else {
        dmn->setVerticalAlign(j["verticalAlign"].get<float>());
      }
    }

    if (j.contains("titleFontScale")) {
      if (!j["titleFontScale"].is_number()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - titleFontScale must be a number."s);
      } else {
        dmn->setTitleFontScale(j["titleFontScale"].get<float>());
      }
    }

    if (j.contains("itemsFontScale")) {
      if (!j["itemsFontScale"].is_number()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - itemsFontScale must be a number."s);
      } else {
        dmn->setItemsFontScale(j["itemsFontScale"].get<float>());
      }
    }

    if (!j.contains("items") || !j["items"].is_array()) {
      SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - items must be an array."s);
      return;
    }

    for (const auto& item : j["items"]) {
      if (!item.is_object()) {
        continue;
      }
      if (!item.contains("label") || !item["label"].is_string()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - each item needs a string label."s);
        continue;
      }
      if (!item.contains("daemon") || !item["daemon"].is_string()) {
        SysError::setError("Bad config for ImGuiMenuDrawDaemonFtry - each item needs a string daemon."s);
        continue;
      }
      auto label = item["label"].get<std::string>();
      auto daemonName = item["daemon"].get<std::string>();
      auto daemon = mainRsrc.get("Daemon."s + daemonName);
      if (!daemon) {
        SysError::setError("ImGuiMenuDrawDaemonFtry daemon not found: "s + daemonName);
        continue;
      }
      dmn->addMenuItem(label, daemon);
    //   TODO: No está entrando a pintar. aparentemente no activa el ticket del demonio del menú.
    //   ¿Igual se pintan y no se ven?
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiMenuDrawDaemon>& specificRsrc = RsrcStore<ImGuiMenuDrawDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUIMENUDRAWDAEMON_H_
