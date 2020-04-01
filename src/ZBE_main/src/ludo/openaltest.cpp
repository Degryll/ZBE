#include "ludo/openaltest.h"

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

#include "ZBE/JSON/resources/JSONAudioDefLoader.h"

#include "ZBE/OAL/resources/OALAudioLoader.h"

#include "ZBE/OAL/daemons/OALContextDaemon.h"

#include "ZBE/OAL/entities/avatars/Sound3D.h"
#include "ZBE/OAL/entities/avatars/implementations/BaseSound3D.h"

#include "ZBE/OAL/players/Sound3DOALPlayer.h"

#include "ZBE/OAL/system/OALAudioStore.h"

namespace ludo {

int openaltest(int , char **) {
  using namespace zbe;

  OALContextDaemon oalContextDmn;
  oalContextDmn.run();

  printf("Source generation ( were the audio comes from )\n");

  ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

  alListener3f(AL_POSITION, 0, 0, 1.0f);
  alListener3f(AL_VELOCITY, 0, 0, 0);
  alListenerfv(AL_ORIENTATION, listenerOri);

  std::shared_ptr<OALAudioStore> store = std::make_shared<OALAudioStore>();

  uint64_t bufferId = store->loadAudio("data/test/audio/die_m.ogg");

  Sound3DOALPlayer player(store);

  std::shared_ptr<Entity> ent = std::make_shared<Entity>();


  std::shared_ptr<Value<Vector3D> > pV = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<Vector3D> > vV = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<uint64_t> > stateV = std::make_shared<SimpleValue<uint64_t> >(0);
  std::shared_ptr<Value<uint64_t> > sourceV = std::make_shared<SimpleValue<uint64_t> >(0);
  std::shared_ptr<Value<uint64_t> > idV = std::make_shared<SimpleValue<uint64_t> >(bufferId);

  ent->setVector3D(1, pV);
  ent->setVector3D(2, vV);

  ent->setUint(1, idV);
  ent->setUint(2, sourceV);
  ent->setUint(3, stateV);

  std::array<uint64_t, 5> a1{ {1, 2, 3, 1, 2} };
  std::shared_ptr<MAvatar<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> > avatar = std::make_shared<MBaseAvatar<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >(ent, a1);


  printf("Loop\n");

  int count =  0;
  float coord = 0.0f;
  uint64_t current = stateV->get();
  while (current!=3) {

   count++;
   player.apply(avatar);
   alListener3f(AL_POSITION, 2 * sin(coord), 2 * cos(coord), 1.0f);
   alListener3f(AL_VELOCITY, 0, 0, 0);
   alListenerfv(AL_ORIENTATION, listenerOri);

   coord = coord + 0.00001f;
   current = stateV->get();
  }
  // TODO
  // device = alcGetContextsDevice(context);
  // alcMakeContextCurrent(NULL);
  // alcDestroyContext(context);
  // alcCloseDevice(device);

  return 0;
}

}  // namespace ludo
