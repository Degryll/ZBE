/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiStyleLoadDaemon.h
 * @since 2026-07-02
 * @brief Daemon that sets ImGui to light theme and optionally loads a custom font.
 */

#ifndef ZBE_SDL_DAEMONS_IMGUISTYLELOADDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUISTYLELOADDAEMON_H_

#include <imgui.h>
#include <string>
#include <nlohmann/json.hpp>
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/factories/Factory.h"

namespace zbe {

class ZBEAPI ImGuiStyleLoadDaemon : public Daemon {
public:
  ImGuiStyleLoadDaemon(const ImGuiStyleLoadDaemon&) = delete;
  void operator=(const ImGuiStyleLoadDaemon&) = delete;

  ImGuiStyleLoadDaemon() = default;
  ~ImGuiStyleLoadDaemon() = default;

  void setFontPath(const std::string& path, float size = 16.0f) {
    fontPath = path;
    fontSize = size;
  }

  void run() override {
    if (!applied) {
      ImGui::StyleColorsLight();
      ImGuiStyle& style = ImGui::GetStyle();
      style.WindowRounding = 4.0f;
      style.FrameRounding = 4.0f;
      style.GrabRounding = 4.0f;
      style.FrameBorderSize = 0.5f;
      style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.69f, 0.64f, 0.73f, 0.94f);
      style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.40f, 0.40f, 0.40f, 0.20f);
      style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.40f, 0.40f, 0.40f, 0.80f);
      style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.24f, 0.24f, 0.24f, 0.60f);
      style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.40f, 0.40f, 0.40f, 0.30f);
      style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
      style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.80f, 0.80f, 0.80f, 0.60f);
      style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.80f, 0.80f, 0.80f, 0.60f);
      style.Colors[ImGuiCol_Button]                 = ImVec4(0.73f, 0.44f, 0.17f, 0.62f);
      style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.90f, 0.83f, 0.07f, 0.79f);
      style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
      style.Colors[ImGuiCol_Header]                 = ImVec4(0.90f, 0.90f, 0.90f, 0.45f);
      style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.89f, 0.89f, 0.90f, 0.80f);
      style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.87f, 0.87f, 0.87f, 0.80f);
      style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
      style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
      style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
      style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
      style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.90f, 0.90f, 0.90f, 0.80f);
      style.Colors[ImGuiCol_Tab]                    = ImVec4(0.68f, 0.68f, 0.68f, 0.78f);
      style.Colors[ImGuiCol_TabSelected]            = ImVec4(0.73f, 0.73f, 0.73f, 0.84f);
      style.Colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.87f, 0.87f, 0.87f, 0.80f);
      style.Colors[ImGuiCol_TabDimmed]              = ImVec4(0.57f, 0.57f, 0.57f, 0.82f);
      style.Colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.65f, 0.65f, 0.65f, 0.84f);
      style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
      style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
      style.Colors[ImGuiCol_TextLink]               = ImVec4(0.87f, 0.87f, 0.87f, 0.80f);
      style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
      style.Colors[ImGuiCol_NavCursor]              = ImVec4(0.90f, 0.90f, 0.90f, 0.80f);

      // Cargar fuente si se ha configurado
      if (!fontPath.empty()) {
        ImGuiIO& io = ImGui::GetIO();
        customFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
        if (customFont) {
          io.Fonts->Build();
        }
      }

      applied = true;
    }
  }

  ImFont* getFont() const {
    return customFont;
  }

private:
  bool applied = false;
  std::string fontPath;
  float fontSize = 16.0f;
  ImFont* customFont = nullptr;
};

class ZBEAPI ImGuiStyleLoadDaemonFtry : public Factory {
public:

  /** \brief Create the desired daemon, probably incomplete.
   *  \param name Name for the created daemon.
   *  \param cfgId Daemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    auto dmn = std::make_shared<ImGuiStyleLoadDaemon>();
    dmnRsrc.insert("Daemon."s + name, dmn);
    styleLoadDmnRsrc.insert("ImGuiStyleLoadDaemon."s + name, dmn);
  }

  /** \brief Setup the desired daemon. The daemon will be complete after this step.
   *  \param name Name of the daemon.
   *  \param cfgId Daemon's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;

    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if (cfg) {
      auto daemon = styleLoadDmnRsrc.get("ImGuiStyleLoadDaemon."s + name);
      if (!daemon) {
        SysError::setError("ImGuiStyleLoadDaemonFtry: daemon not found for "s + name);
        return;
      }

      // Leer configuración opcional de fuente
      if (cfg->contains("font") && cfg->at("font").is_object()) {
        const auto& fontConfig = cfg->at("font");
        if (fontConfig.contains("path") && fontConfig.at("path").is_string()) {
          std::string fontPath = fontConfig.at("path").get<std::string>();
          float fontSize = 16.0f;

          if (fontConfig.contains("size")) {
            if (!fontConfig.at("size").is_number()) {
              SysError::setError("ImGuiStyleLoadDaemonFtry config for font.size: must be a number."s);
              return;
            }
            fontSize = fontConfig.at("size").get<float>();
          }

          daemon->setFontPath(fontPath, fontSize);
        }
      }
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiStyleLoadDaemon>& styleLoadDmnRsrc = RsrcStore<ImGuiStyleLoadDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUILIGHTSTYLEDAEMON_H_