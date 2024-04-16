/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sound3DOALPlayer.h
 * @since 2018-08-22
 * @date 2018-08-22
 * @author Degryll Ludo
 * @brief A behavior that plays 3d sounds.
 */

#ifndef ZBE_OAL_PLAYERS_SOUND3DOALPLAYER_H_
#define ZBE_OAL_PLAYERS_SOUND3DOALPLAYER_H_

#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/OAL/system/OALAudioStore.h"
#include "ZBE/OAL/tools/OALUtils.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/JSON/JSONFactory.h"

#include "ZBE/tools/graphics/Camera.h"

namespace zbe {

class ZBEAPI Sound3DOALPlayerFtry;

/** \brief A behavior that plays 3d sounds.
 */
class ZBEAPI Sound3DOALPlayer : public Behavior<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> {
public:
  friend class Sound3DOALPlayerFtry;
  const static uint64_t NEW = 0, PLAYING = 1, STOPPED = 2;

  Sound3DOALPlayer(std::shared_ptr<OALAudioStore> store, std::shared_ptr<Camera> cam) : store(store), cam(cam) {}

  ~Sound3DOALPlayer() {}

  /** \brief Plays the Sound3D.
   */
  void apply(std::shared_ptr<MAvatar<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> > avatar);

  void setCamera(std::shared_ptr<Camera> cam);

private:
  Sound3DOALPlayer() : store() {}
  void setUp(std::shared_ptr<OALAudioStore> store, std::shared_ptr<Camera> cam) {
    this->store = store;
    this->cam = cam;
  }

  std::shared_ptr<OALAudioStore> store;
  std::shared_ptr<Camera> cam;
};


class ZBEAPI Sound3DOALPlayerFtry : public Factory {
public:
  void create(std::string name, uint64_t);

  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >& mainRsrc = RsrcStore<Behavior<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >::getInstance();
  RsrcStore<Sound3DOALPlayer>& specificRsrc = RsrcStore<Sound3DOALPlayer>::getInstance();
  RsrcStore<OALAudioStore> &audioStoreRsrc = RsrcStore<OALAudioStore>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OAL_PLAYERS_SOUND3DOALPLAYER_H_
