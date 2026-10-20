/**
 * @file ImGuiResSelectorDrawDaemon.h
 * @brief ImGui daemon for selecting the display resolution.
 */

#ifndef ZBE_IMGUI_DAEMONS_IMGUIRESSELECTORDRAWDAEMON_H_
#define ZBE_IMGUI_DAEMONS_IMGUIRESSELECTORDRAWDAEMON_H_

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <imgui.h>
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/factories/Factory.h"
#include "nlohmann/json.hpp"

namespace zbe {

class ZBEAPI ImGuiResSelectorDrawDaemon : public Daemon {
public:
  struct Resolution {
    int displayIndex;
    int width;
    int height;
  };

  ImGuiResSelectorDrawDaemon(const ImGuiResSelectorDrawDaemon&) = delete;
  void operator=(const ImGuiResSelectorDrawDaemon&) = delete;

  ImGuiResSelectorDrawDaemon() = default;
  ~ImGuiResSelectorDrawDaemon() = default;

  void setWindow(std::shared_ptr<SDLWindow> value) { window = std::move(value); }
  void setTitle(const std::string& value) { title = value; }
  void setHorizontalAlign(float value) { horizontalAlign = std::clamp(value, 0.0f, 1.0f); }
  void setVerticalAlign(float value) { verticalAlign = std::clamp(value, 0.0f, 1.0f); }

  void run() override {
    if (!window) {
      return;
    }
    if (!initialized) {
      loadResolutions();
    }

    const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(displaySize.x * horizontalAlign,
                                   displaySize.y * verticalAlign),
                            ImGuiCond_Always,
                            ImVec2(horizontalAlign, verticalAlign));
    ImGui::Begin(title.empty() ? "Resolución de pantalla" : title.c_str(), nullptr,
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoSavedSettings |
                 ImGuiWindowFlags_NoBackground |
                 ImGuiWindowFlags_AlwaysAutoResize);

    if (resolutions.empty()) {
      ImGui::TextUnformatted("No hay resoluciones disponibles.");
    } else {
      const Resolution& selected = resolutions[selectedResolution];
      const std::string selectedLabel = formatResolution(selected);
      if (ImGui::BeginCombo("Resolución", selectedLabel.c_str())) {
        for (size_t i = 0; i < resolutions.size(); ++i) {
          const bool isSelected = selectedResolution == i;
          const std::string label = formatResolution(resolutions[i]);
          if (ImGui::Selectable(label.c_str(), isSelected)) {
            selectedResolution = i;
          }
          if (isSelected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
      ImGui::Checkbox("Pantalla completa", &fullscreen);
      if (ImGui::Button("Aplicar")) {
        const Resolution& resolution = resolutions[selectedResolution];
        window->setResolution(resolution.width, resolution.height, fullscreen,
                              resolution.displayIndex);
      }
    }

    ImGui::End();

    // El botón de aplicar deber permitir ejecutar un demonio configurable adicional.
    // En ese demonio se ejecutarán comportamientos que modifiquen aquellas cosas que dependan de la resolción
    // Por ejemplo: La localización del HUD y del crosshairs
    // Comportamiento que multiplique dos valores (resolucion y colocación relativa) y los guarde como entero en un tercer valor (posicioin real).
    // Cada entida estará en la lista de ese comportamiento tantas veces como sea necesario para calcular su colocación en pantall.
    // Este comportamiento se ejecutará cada vez que se cambie la resolución, y también al iniciar el juego, para calcular la colocación inicial de cada elemento.
  }

private:
  static std::string formatResolution(const Resolution& resolution) {
    return "Monitor " + std::to_string(resolution.displayIndex + 1) + " - " +
           std::to_string(resolution.width) + " x " + std::to_string(resolution.height);
  }

  void loadResolutions() {
    initialized = true;
    SDL_Window* sdlWindow = window->getSDL_Window();
    if (!sdlWindow) {
      SysError::setError("ImGuiResSelectorDrawDaemon requires a created SDL window.");
      return;
    }

    const int displayCount = SDL_GetNumVideoDisplays();
    if (displayCount < 0) {
      SysError::setError(std::string("ImGuiResSelectorDrawDaemon could not list displays: ") +
                         SDL_GetError());
      return;
    }

    for (int displayIndex = 0; displayIndex < displayCount; ++displayIndex) {
      const int modeCount = SDL_GetNumDisplayModes(displayIndex);
      if (modeCount < 0) {
        SysError::setError(std::string("ImGuiResSelectorDrawDaemon could not list display modes: ") +
                           SDL_GetError());
        continue;
      }
      for (int modeIndex = 0; modeIndex < modeCount; ++modeIndex) {
        SDL_DisplayMode mode{};
        if (SDL_GetDisplayMode(displayIndex, modeIndex, &mode) != 0) {
          SysError::setError(std::string("ImGuiResSelectorDrawDaemon could not read a display mode: ") +
                             SDL_GetError());
          continue;
        }
        if (mode.w <= 0 || mode.h <= 0) {
          continue;
        }
        const auto duplicate = std::find_if(resolutions.begin(), resolutions.end(),
            [displayIndex, &mode](const Resolution& resolution) {
              return resolution.displayIndex == displayIndex &&
                     resolution.width == mode.w && resolution.height == mode.h;
            });
        if (duplicate == resolutions.end()) {
          resolutions.push_back({displayIndex, mode.w, mode.h});
        }
      }
    }

    // TODO: Remove hardcoded resolutions and rely on SDL_GetDisplayMode to get available resolutions.
    resolutions.push_back({0, 1920, 1080});
    resolutions.push_back({0, 1280, 720});
    resolutions.push_back({0, 800, 600});
    resolutions.push_back({0, 640, 480});
    resolutions.push_back({1, 3860, 2160});
    resolutions.push_back({1, 1920, 1080});
    resolutions.push_back({1, 1280, 720});
    resolutions.push_back({1, 800, 600});
    resolutions.push_back({2, 1920, 1080});
    resolutions.push_back({2, 1280, 720});
    resolutions.push_back({2, 800, 600});


    if (resolutions.empty()) {
      SysError::setError("ImGuiResSelectorDrawDaemon found no display resolutions.");
      return;
    }

    int currentWidth = 0;
    int currentHeight = 0;
    SDL_GetWindowSize(sdlWindow, &currentWidth, &currentHeight);
    const int currentDisplay = SDL_GetWindowDisplayIndex(sdlWindow);
    fullscreen = (SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_FULLSCREEN) != 0;
    const auto currentResolution = std::find_if(resolutions.begin(), resolutions.end(),
        [currentDisplay, currentWidth, currentHeight](const Resolution& resolution) {
          return resolution.displayIndex == currentDisplay &&
                 resolution.width == currentWidth && resolution.height == currentHeight;
        });
    if (currentResolution != resolutions.end()) {
      selectedResolution = static_cast<size_t>(currentResolution - resolutions.begin());
    }
  }

  std::shared_ptr<SDLWindow> window;
  std::string title;
  float horizontalAlign = 0.5f;
  float verticalAlign = 0.5f;
  std::vector<Resolution> resolutions;
  size_t selectedResolution = 0;
  bool initialized = false;
  bool fullscreen = false;
};

class ZBEAPI ImGuiResSelectorDrawDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    auto daemon = std::make_shared<ImGuiResSelectorDrawDaemon>();
    mainRsrc.insert("Daemon."s + name, daemon);
    specificRsrc.insert("ImGuiResSelectorDrawDaemon."s + name, daemon);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    auto config = configRsrc.get(cfgId);
    auto daemon = specificRsrc.get("ImGuiResSelectorDrawDaemon."s + name);
    if (!config || !daemon) {
      SysError::setError("ImGuiResSelectorDrawDaemonFtry resources not found for "s + name);
      return;
    }
    const auto& data = *config;
    if (!data.is_object()) {
      SysError::setError("ImGuiResSelectorDrawDaemonFtry config must be an object.");
      return;
    }
    if (!data.contains("window") || !data["window"].is_string()) {
      SysError::setError("ImGuiResSelectorDrawDaemonFtry requires a window string.");
      return;
    }
    auto window = windowRsrc.get("SDLWindow."s + data["window"].get<std::string>());
    if (!window) {
      SysError::setError("ImGuiResSelectorDrawDaemonFtry SDLWindow not found for "s + name);
      return;
    }
    daemon->setWindow(window);

    if (data.contains("title")) {
      if (!data["title"].is_string()) {
        SysError::setError("ImGuiResSelectorDrawDaemonFtry title must be a string.");
      } else {
        daemon->setTitle(data["title"].get<std::string>());
      }
    }
    if (data.contains("horizontalAlign")) {
      if (!data["horizontalAlign"].is_number()) {
        SysError::setError("ImGuiResSelectorDrawDaemonFtry horizontalAlign must be a number.");
      } else {
        daemon->setHorizontalAlign(data["horizontalAlign"].get<float>());
      }
    }
    if (data.contains("verticalAlign")) {
      if (!data["verticalAlign"].is_number()) {
        SysError::setError("ImGuiResSelectorDrawDaemonFtry verticalAlign must be a number.");
      } else {
        daemon->setVerticalAlign(data["verticalAlign"].get<float>());
      }
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiResSelectorDrawDaemon>& specificRsrc = RsrcStore<ImGuiResSelectorDrawDaemon>::getInstance();
  RsrcStore<SDLWindow>& windowRsrc = RsrcStore<SDLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_IMGUI_DAEMONS_IMGUIRESSELECTORDRAWDAEMON_H_
