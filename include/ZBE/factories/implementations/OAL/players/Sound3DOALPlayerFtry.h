/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sound3DOALPlayerFtry.h
 * @since 2025-10-21
 * @date 2025-10-21
 * @author Degryll Ludo
 * @brief Factory for Sound3DOALPlayer.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_OAL_PLAYERS_SOUND3DOALPLAYERFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_OAL_PLAYERS_SOUND3DOALPLAYERFTRY_H_

#include <string>
#include <nlohmann/json.hpp>
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/OAL/players/Sound3DOALPlayer.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

class Sound3DOALPlayerFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<Sound3DOALPlayer> s3daolp(new Sound3DOALPlayer);
    mainRsrc.insert("Behavior."s + name, s3daolp);
    specificRsrc.insert("Sound3DOALPlayer."s + name, s3daolp);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("Sound3DOALPlayerFtry config for "s + name + " not found."s);
      return;
    }
    auto j = *cfg;
    auto s3daolp = specificRsrc.get("Sound3DOALPlayer."s + name);
    auto audioStore = JSONFactory::StoreLoader<OALAudioStore>::loadParamCfgStoreP(audioStoreRsrc, j, "OALAudioStore", "audiostore"s, "Sound3DOALPlayerFtry"s);
    if(!audioStore) {
      SysError::setError("Sound3DOALPlayerFtry config for audiostore is invalid"s);
      return;
    }
    auto cam = JSONFactory::StoreLoader<Camera>::loadParamCfgStoreP(cameraRsrc, j,"Camera", "camera"s, "Sound3DOALPlayerFtry"s);
    if(!cam) {
      SysError::setError("Sound3DOALPlayerFtry config for camera is invalid"s);
      return;
    }

    s3daolp->setUp(*audioStore, *cam);
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >& mainRsrc = RsrcStore<Behavior<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >::getInstance();
  RsrcStore<Sound3DOALPlayer>& specificRsrc = RsrcStore<Sound3DOALPlayer>::getInstance();
  RsrcStore<OALAudioStore> &audioStoreRsrc = RsrcStore<OALAudioStore>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_OAL_PLAYERS_SOUND3DOALPLAYERFTRY_H_
