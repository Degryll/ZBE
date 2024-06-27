/**
* Copyright 2012 Batis Degryll Ludo
* @file OALAudioLoader.h
* @since 2019-03-19
* @date 2019-03-19
* @author Batis Degryll Ludo
* @brief RsrcLoader implementation caplable of load ogg files into OAL system.
*/

#ifndef ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_
#define ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_

#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcDefLoader.h"

#include "ZBE/OAL/system/OALAudioStore.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

class ZBEAPI OALAudioLoader : public RsrcLoader {
public:

  OALAudioLoader() : audioStore(), audioDefLoader() {}

  OALAudioLoader(std::shared_ptr<OALAudioStore> audioStore, std::shared_ptr<RsrcDefLoader> audioDefLoader)
    : audioStore(audioStore), audioDefLoader(audioDefLoader) {}

  void setUp(std::shared_ptr<OALAudioStore> audioStore, std::shared_ptr<RsrcDefLoader> audioDefLoader) {
    this->audioStore = audioStore;
    this->audioDefLoader = audioDefLoader;
  }  

  void load(std::filesystem::path filePath) override ;

  bool isLoadable(std::filesystem::path extension) override ;

private:

 std::filesystem::path generateDefPath(const std::filesystem::path& p);

 std::shared_ptr<OALAudioStore> audioStore;
 std::shared_ptr<RsrcDefLoader> audioDefLoader;
 static std::filesystem::path ext;

};

class ZBEAPI OALAudioLoaderFtry : public Factory {
public:
   void create(std::string name, uint64_t) override {
     using namespace std::string_literals;

     auto loader = std::make_shared<OALAudioLoader>();
     specificRsrc.insert("OALAudioLoader."s + name, loader);
     mainRsrc.insert("RsrcLoader."s + name, loader);
   }

   void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    if(!cfg) {
      SysError::setError("OALAudioLoaderFtry config for "s + name + " not found."s);
      return;
    }
    auto oalal = specificRsrc.get("OALAudioLoader."s + name);
    auto j = *cfg;

    auto defLoader = JSONFactory::loadParamCfgStoreP<RsrcDefLoader>(rsrcDefLoaderRsrc, j, "RsrcDefLoader", "audiodef"s, "OALAudioLoaderFtry"s);
    if(!defLoader) {
      SysError::setError("OALAudioLoaderFtry config for audiodef is invalid"s);
      return;
    }

    auto audioStore = JSONFactory::loadParamCfgStoreP<OALAudioStore>(audioStoreRsrc, j, "OALAudioStore", "audiostore"s, "OALAudioLoaderFtry"s);
    if(!audioStore) {
      SysError::setError("OALAudioLoaderFtry config for audiostore is invalid"s);
      return;
    }

    oalal->setUp(*audioStore, *defLoader);
   }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<OALAudioLoader> &specificRsrc = RsrcStore<OALAudioLoader>::getInstance();
  RsrcStore<RsrcLoader> &mainRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<RsrcDefLoader> &rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  RsrcStore<OALAudioStore> &audioStoreRsrc = RsrcStore<OALAudioStore>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_
