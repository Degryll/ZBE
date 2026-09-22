/**
 * @file ImGuiCFGDrawDaemon.h
 * @brief ImGui daemon for editing entity values.
 */

#ifndef ZBE_IMGUI_DAEMONS_IMGUICFGDRAWDAEMON_H_
#define ZBE_IMGUI_DAEMONS_IMGUICFGDRAWDAEMON_H_

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <imgui.h>
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/factories/Factory.h"
#include "nlohmann/json.hpp"

namespace zbe {

class ZBEAPI ImGuiCFGDrawDaemon : public Daemon {
public:
  enum class ValueType { BOOL, INT, UINT, FLOAT, DOUBLE, VECTOR2D, VECTOR3D, STRING };

  struct ValueItem {
    std::string label;
    uint64_t valueIdx = 0;
    ValueType type = ValueType::FLOAT;
    double min = -100.0;
    double max = 100.0;
    double step = 0.01;
    size_t stringLength = 128;
    std::vector<char> text;
  };

  ImGuiCFGDrawDaemon(const ImGuiCFGDrawDaemon&) = delete;
  void operator=(const ImGuiCFGDrawDaemon&) = delete;

  ImGuiCFGDrawDaemon() = default;
  ~ImGuiCFGDrawDaemon() = default;

  void setEntity(std::shared_ptr<Entity> value) { entity = value; }
  void setMenuTitle(const std::string& value) { title = value; }
  void setHorizontalAlign(float value) { horizontalAlign = std::clamp(value, 0.0f, 1.0f); }
  void setVerticalAlign(float value) { verticalAlign = std::clamp(value, 0.0f, 1.0f); }
  void setTitleFontScale(float value) { titleFontScale = std::max(value, 0.1f); }
  void setItemsFontScale(float value) { itemsFontScale = std::max(value, 0.1f); }

  void addValue(const ValueItem& value) {
    values.push_back(value);
  }

  void run() override {
    if (!entity) {
      return;
    }
    const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(displaySize.x * horizontalAlign,
                                   displaySize.y * verticalAlign),
                            ImGuiCond_Always,
                            ImVec2(horizontalAlign, verticalAlign));
    ImGui::Begin(title.empty() ? "Entity configuration" : title.c_str(), nullptr,
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoSavedSettings |
                 ImGuiWindowFlags_NoBackground);
    if (!title.empty()) {
      ImGui::SetWindowFontScale(titleFontScale);
      ImGui::TextUnformatted(title.c_str());
      ImGui::SetWindowFontScale(1.0f);
      ImGui::Dummy(ImVec2(0.0f, ImGui::GetStyle().ItemSpacing.y));
    }
    ImGui::SetWindowFontScale(itemsFontScale);
    for (auto& item : values) {
      drawValue(item);
    }
    ImGui::SetWindowFontScale(1.0f);
    ImGui::End();
  }

private:
  static double quantize(double value, const ValueItem& item) {
    if (item.step <= 0.0) {
      return value;
    }
    value = item.min + std::round((value - item.min) / item.step) * item.step;
    return std::clamp(value, item.min, item.max);
  }

  static void drawNumber(const char* label, double& value, const ValueItem& item) {
    if (ImGui::SliderScalar(label, ImGuiDataType_Double, &value,
                            &item.min, &item.max, "%.6f")) {
      value = quantize(value, item);
    }
  }

  void drawValue(ValueItem& item) {
    switch (item.type) {
      case ValueType::BOOL: {
        auto value = entity->getBool(item.valueIdx);
        if (value) {
          bool current = value->get();
          if (ImGui::Checkbox(item.label.c_str(), &current)) value->set(current);
        }
        break;
      }
      case ValueType::INT: {
        auto value = entity->getInt(item.valueIdx);
        if (value) {
          int64_t current = value->get();
          int64_t min = static_cast<int64_t>(item.min);
          int64_t max = static_cast<int64_t>(item.max);
          if (ImGui::SliderScalar(item.label.c_str(), ImGuiDataType_S64, &current, &min, &max)) {
            value->set(static_cast<int64_t>(quantize(static_cast<double>(current), item)));
          }
        }
        break;
      }
      case ValueType::UINT: {
        auto value = entity->getUint(item.valueIdx);
        if (value) {
          uint64_t current = value->get();
          uint64_t min = static_cast<uint64_t>(std::max(0.0, item.min));
          uint64_t max = static_cast<uint64_t>(std::max(0.0, item.max));
          if (ImGui::SliderScalar(item.label.c_str(), ImGuiDataType_U64, &current, &min, &max)) {
            value->set(static_cast<uint64_t>(quantize(static_cast<double>(current), item)));
          }
        }
        break;
      }
      case ValueType::FLOAT: {
        auto value = entity->getFloat(item.valueIdx);
        if (value) {
          float current = value->get();
          float min = static_cast<float>(item.min);
          float max = static_cast<float>(item.max);
          if (ImGui::SliderFloat(item.label.c_str(), &current, min, max)) {
            value->set(static_cast<float>(quantize(current, item)));
          }
        }
        break;
      }
      case ValueType::DOUBLE: {
        auto value = entity->getDouble(item.valueIdx);
        if (value) {
          double current = value->get();
          drawNumber(item.label.c_str(), current, item);
          if (current != value->get()) value->set(current);
        }
        break;
      }
      case ValueType::VECTOR2D:
      case ValueType::VECTOR3D: {
        const size_t dimension = item.type == ValueType::VECTOR2D ? 2 : 3;
        if (item.type == ValueType::VECTOR2D) {
          auto value = entity->getVector2D(item.valueIdx);
          if (value) {
            Vector2D currentValue = value->get();
            for (size_t i = 0; i < dimension; ++i) {
              std::string label = item.label + "[" + std::to_string(i) + "]";
              double current = currentValue[i];
              drawNumber(label.c_str(), current, item);
              currentValue[i] = current;
            }
            value->set(currentValue);
          }
        } else {
          auto value = entity->getVector3D(item.valueIdx);
          if (value) {
            Vector3D currentValue = value->get();
            for (size_t i = 0; i < dimension; ++i) {
              std::string label = item.label + "[" + std::to_string(i) + "]";
              double current = currentValue[i];
              drawNumber(label.c_str(), current, item);
              currentValue[i] = current;
            }
            value->set(currentValue);
          }
        }
        break;
      }
      case ValueType::STRING: {
        auto value = entity->getString(item.valueIdx);
        if (value) {
          const size_t length = std::max<size_t>(1, item.stringLength);
          if (item.text.size() != length + 1) item.text.assign(length + 1, '\0');
          if (!ImGui::IsItemActive()) {
            std::strncpy(item.text.data(), value->get().c_str(), length);
            item.text[length] = '\0';
          }
          if (ImGui::InputText(item.label.c_str(), item.text.data(), item.text.size())) {
            value->set(std::string(item.text.data()));
          }
        }
        break;
      }
    }
  }

  std::shared_ptr<Entity> entity;
  std::string title;
  float horizontalAlign = 0.5f;
  float verticalAlign = 0.5f;
  float titleFontScale = 1.5f;
  float itemsFontScale = 1.0f;
  std::vector<ValueItem> values;
};

class ZBEAPI ImGuiCFGDrawDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    auto daemon = std::make_shared<ImGuiCFGDrawDaemon>();
    mainRsrc.insert("Daemon."s + name, daemon);
    specificRsrc.insert("ImGuiCFGDrawDaemon."s + name, daemon);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using nlohmann::json;
    auto config = configRsrc.get(cfgId);
    auto daemon = specificRsrc.get("ImGuiCFGDrawDaemon."s + name);
    if (!config || !daemon) {
      SysError::setError("ImGuiCFGDrawDaemonFtry resources not found for "s + name);
      return;
    }
    const json& data = *config;
    if (!data.contains("entity") || !data["entity"].is_string()) {
      SysError::setError("ImGuiCFGDrawDaemonFtry requires an entity string.");
      return;
    }
    auto entity = entityStore.get("Entity."s + data["entity"].get<std::string>());
    if (!entity) {
      SysError::setError("ImGuiCFGDrawDaemonFtry entity not found for "s + name);
      return;
    }
    daemon->setEntity(entity);
    if (data.contains("title") && data["title"].is_string()) daemon->setMenuTitle(data["title"].get<std::string>());
    if (data.contains("horizontalAlign")) {
      if (!data["horizontalAlign"].is_number()) {
        SysError::setError("ImGuiCFGDrawDaemonFtry horizontalAlign must be a number.");
      } else {
        daemon->setHorizontalAlign(data["horizontalAlign"].get<float>());
      }
    }
    if (data.contains("verticalAlign")) {
      if (!data["verticalAlign"].is_number()) {
        SysError::setError("ImGuiCFGDrawDaemonFtry verticalAlign must be a number.");
      } else {
        daemon->setVerticalAlign(data["verticalAlign"].get<float>());
      }
    }
    if (data.contains("titleFontScale")) {
      if (!data["titleFontScale"].is_number()) {
        SysError::setError("ImGuiCFGDrawDaemonFtry titleFontScale must be a number.");
      } else {
        daemon->setTitleFontScale(data["titleFontScale"].get<float>());
      }
    }
    if (data.contains("itemsFontScale")) {
      if (!data["itemsFontScale"].is_number()) {
        SysError::setError("ImGuiCFGDrawDaemonFtry itemsFontScale must be a number.");
      } else {
        daemon->setItemsFontScale(data["itemsFontScale"].get<float>());
      }
    }
    if (!data.contains("items") || !data["items"].is_array()) {
      SysError::setError("ImGuiCFGDrawDaemonFtry requires an items array.");
      return;
    }
    for (const auto& entry : data["items"]) {
      if (!entry.is_object() || !entry.contains("valueIdx") || !entry.contains("type") || !entry["valueIdx"].is_string() || !entry["type"].is_string()) {
        SysError::setError("ImGuiCFGDrawDaemonFtry items require string valueIdx and type.");
        continue;
      }
      ImGuiCFGDrawDaemon::ValueItem item;
      item.label = entry.value("label", entry["valueIdx"].get<std::string>());
      item.valueIdx = uintStore.get(entry["valueIdx"].get<std::string>());
      if (!setType(entry["type"].get<std::string>(), item.type)) {
        SysError::setError("Unknown ImGuiCFGDrawDaemon value type: "s + entry["type"].get<std::string>());
        continue;
      }
      if (item.type == ImGuiCFGDrawDaemon::ValueType::STRING) {
        if (!entry.contains("stringLength") || !entry["stringLength"].is_number_unsigned() || entry["stringLength"].get<size_t>() == 0) {
          SysError::setError("ImGuiCFGDrawDaemon string items require a positive stringLength.");
          continue;
        }
        item.stringLength = entry["stringLength"].get<size_t>();
      }
      item.min = entry.value("min", item.min);
      item.max = entry.value("max", item.max);
      item.step = entry.value("step", item.step);
      daemon->addValue(item);
    }
  }

private:
  static bool setType(const std::string& name, ImGuiCFGDrawDaemon::ValueType& type) {
    if (name == "bool") type = ImGuiCFGDrawDaemon::ValueType::BOOL;
    else if (name == "int" || name == "int64") type = ImGuiCFGDrawDaemon::ValueType::INT;
    else if (name == "uint" || name == "uint64") type = ImGuiCFGDrawDaemon::ValueType::UINT;
    else if (name == "float") type = ImGuiCFGDrawDaemon::ValueType::FLOAT;
    else if (name == "double") type = ImGuiCFGDrawDaemon::ValueType::DOUBLE;
    else if (name == "vector2d" || name == "Vector2D") type = ImGuiCFGDrawDaemon::ValueType::VECTOR2D;
    else if (name == "vector3d" || name == "Vector3D") type = ImGuiCFGDrawDaemon::ValueType::VECTOR3D;
    else if (name == "string") type = ImGuiCFGDrawDaemon::ValueType::STRING;
    else return false;
    return true;
  }

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiCFGDrawDaemon>& specificRsrc = RsrcStore<ImGuiCFGDrawDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_IMGUI_DAEMONS_IMGUICFGDRAWDAEMON_H_