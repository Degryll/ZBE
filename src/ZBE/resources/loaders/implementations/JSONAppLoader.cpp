/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONAppLoader.cpp
 * @since 2019-02-21
 * @date 2019-02-21
 * @author Batis Degryll Ludo
 * @brief Implementation of RsrcLoader capable of load an app config from a .json file
 */

#include "ZBE/resources/loaders/implementations/JSONAppLoader.h"

namespace zbe {

void JSONAppLoader::load(std::filesystem::path filePath) {
  using namespace std::string_literals;
  std::ifstream ifs(filePath);
  json appCfg;
  try {
    ifs >> appCfg;

    json literals = appCfg["literals"];
    for(auto& literalCfg : literals.items()) {
      loadLiteralConfig(literalCfg.key(), literalCfg.value());
    }

    json phases = appCfg["phases"];
    for(auto& phase : phases){
      json factories = phase["factories"];
      for(auto& ftryCfg : factories) {
        appFactories.push_front(readFactoryConfig(ftryCfg));
      }
      for(auto ftryData : appFactories) {
        ftryData.ftry->create(ftryData.name, ftryData.cfgId);
      }
      for(auto ftryData : appFactories) {
        ftryData.ftry->setup(ftryData.name, ftryData.cfgId);
      }
      appFactories.clear();
    }
  } catch (json::parse_error &e) {
    SysError::setError("ERROR: Json on "s + filePath.u8string() + " failed to parse: "s + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError("ERROR: Unexpected type error on json app load: "s + std::string(e.what()));
  }
}

bool JSONAppLoader::isLoadable(std::filesystem::path extension) {
  static const std::filesystem::path ext(".json");
  return (ext.compare(extension) == 0);
}

void JSONAppLoader::loadLiteralConfig(std::string name, json& value) {
  if(value.is_number_integer()) {
    intStore.insert(name, value.get<int64_t>());
    uintStore.insert(name, value.get<uint64_t>());
  } else if (value.is_number_float()) {
    doubleStore.insert(name, value.get<float>());
  } else if (value.is_string()) {
    std::string aux = value.get<std::string>();
    stringStore.insert(name, aux);
  } else {
    SysError::setError(std::string("ERROR: Json failed to parse. Key ") + name + std::string(" contains invalid value. Its neither an integer, float or string. Value: ") + value.dump());
  }
}

JSONAppLoader::FtryData JSONAppLoader::readFactoryConfig(json ftryCfg) {
  FtryData fd;
  json aux;
  aux = ftryCfg["factory"];
  if(aux.is_string()) {
    fd.ftry = ftryStore.get(aux.get<std::string>());
  } else {
    SysError::setError(std::string("ERROR: Json failed to parse. \"factory\" is not a string."));
  }

  aux = ftryCfg["name"];
  if(aux.is_string()) {
    fd.name = aux.get<std::string>();
  } else {
    SysError::setError(std::string("ERROR: Json failed to parse. \"name\" is not a string."));
  }
  fd.cfgId = cfgStore.insert(std::make_shared<json>(ftryCfg["config"]));
  return fd;
}

}  // namespace zbe
