#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/zbe.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/resources/contextnames.h"

#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/JSON/resources/JSONAudioDefLoader.h"

#include "ZBE/OAL/resources/OALAudioLoader.h"
#include "ZBE/OAL/daemons/OALContextDaemon.h"

#include "ZBE/OAL/entities/avatars/Sound3D.h"
#include "ZBE/OAL/entities/avatars/implementations/BaseSound3D.h"

#include "ZBE/OAL/players/Sound3DOALPlayer.h"

#include "ZBE/OAL/system/OALAudioStore.h"

namespace ludo {
  int openaltest(int argc, char **argv);
}
