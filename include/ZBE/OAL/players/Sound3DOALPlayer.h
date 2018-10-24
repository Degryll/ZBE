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

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/system/SysError.h"

#include "ZBE/OAL/system/OALAudioStore.h"
#include "ZBE/OAL/tools/OALUtils.h"
#include "ZBE/OAL/entities/avatars/Sound3D.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A behavior that plays 3d sounds.
 */
class ZBEAPI Sound3DOALPlayer : public Behavior<Sound3D> {
public:
  Sound3DOALPlayer(std::shared_ptr<OALAudioStore> store) : store(store) {}

  /** \brief Virtual destructor.
   */
  ~Sound3DOALPlayer() {}

  /** \brief Plays the Sound3D.
   */
  void apply(std::shared_ptr<AvatarEntityContainer<Sound3D> > aec);

private:
  std::shared_ptr<OALAudioStore> store;

};

}  // namespace zbe

#endif  // ZBE_OAL_PLAYERS_SOUND3DOALPLAYER_H_
