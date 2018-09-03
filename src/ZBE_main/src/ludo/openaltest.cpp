#include "ludo/openaltest.h"

#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/zbe.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/OAL/entities/avatars/Sound3D.h"
#include "ZBE/OAL/entities/avatars/implementations/BaseSound3D.h"

#include "ZBE/OAL/players/Sound3DOALPlayer.h"

#include "ZBE/OAL/system/OALAudioStore.h"

namespace ludo {

void printError() {
  ALCenum error = alGetError();
  if (error != AL_NO_ERROR) {
    if (error == AL_INVALID_NAME) {
      printf("AL_INVALID_NAME\n");
    } else if (error == AL_INVALID_ENUM) {
      printf("AL_INVALID_ENUM\n");
    } else if (error == AL_INVALID_VALUE) {
      printf("AL_INVALID_VALUE\n");
    } else if (error == AL_INVALID_OPERATION) {
      printf("AL_INVALID_OPERATION\n");
    } else if (error == AL_OUT_OF_MEMORY) {
      printf("AL_OUT_OF_MEMORY\n");
    } else{
      printf("OAL unknown error: %d\n", error);
    }
  }
}

static ALCchar* list_audio_devices(const ALCchar *devices) {
  const ALCchar *device = devices, *next = devices + 1;
  size_t len = 0;
  ALCchar *out = (ALCchar*) malloc(sizeof(ALCchar)*1024);

  fprintf(stdout, "Devices list:\n");
  fprintf(stdout, "----------\n");
  while (device && *device != '\0' && next && *next != '\0') {
    strcpy(out, (char*)device);
    fprintf(stdout, "%s\n", device);
    len = strlen(device);
    device += (len + 1);
    next += (len + 2);
  }
  fprintf(stdout, "----------\n");
  return out;
}

int openaltest(int , char **) {
  printf("Checking if ALC_ENUMERATION_EXT is present\n");

  ALboolean enumeration;
  enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

  printf("Device enumeration ");
  if (enumeration == AL_FALSE) {
    printf("unsupported\n");
  } else {
    printf("supported\n");
  }

  ALCchar* last = list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

  printf("Load audio device %s\n", last);
  ALCdevice *device;
  device = alcOpenDevice(last);

  if (!device) {
    printf("Failed to load audio device\n");
    printError();
  }

  printf("Creating context\n");

  ALCcontext *context;

  context = alcCreateContext(device, NULL);
  if (!alcMakeContextCurrent(context)) {
    printf("Context error\n");
    printError();
  }

  printf("Source generation ( were the audio comes from )\n");

  ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

  alListener3f(AL_POSITION, 0, 0, 1.0f);
  alListener3f(AL_VELOCITY, 0, 0, 0);
  alListenerfv(AL_ORIENTATION, listenerOri);

  std::shared_ptr<zbe::OALAudioStore> store = std::make_shared<zbe::OALAudioStore>();

  uint64_t bufferId = store->loadAudio("data/test/audio/die_m.ogg");

  zbe::Sound3DOALPlayer player(store);

  std::shared_ptr<zbe::AvatarEntityFixed<zbe::Sound3D> > aefS3D = std::make_shared<zbe::AvatarEntityFixed<zbe::Sound3D> >();
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Sound3D> > aec = std::make_shared<zbe::AvatarEntityContainer<zbe::Sound3D> >(aefS3D);

  std::shared_ptr<zbe::Entity> entity = std::make_shared<zbe::Entity>();

  std::array<uint64_t, 3> pointIds = {1,2,3};
  std::array<uint64_t, 3> velIds = {4,5,6};
  std::array<uint64_t, 1> audioIds = {7};

  std::shared_ptr<zbe::Value<double> > px = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(pointIds[0], px);

  std::shared_ptr<zbe::Value<double> > py = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(pointIds[1], py);

  std::shared_ptr<zbe::Value<double> > pz = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(pointIds[2], pz);

  std::shared_ptr<zbe::Value<double> > vx = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(velIds[0], vx);

  std::shared_ptr<zbe::Value<double> > vy = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(velIds[1], vy);

  std::shared_ptr<zbe::Value<double> > vz = std::make_shared<zbe::SimpleValue<double> >(0.0);
  entity->setDouble(velIds[2], vz);

  zbe::EntityIds<3> point(entity, pointIds);
  zbe::EntityIds<3> velocity(entity, velIds);
  zbe::EntityIds<1> ticket(entity, audioIds);
  uint64_t audioId = bufferId;

  zbe::BaseSound3D* sound3D = new zbe::BaseSound3D(point, velocity, ticket, audioId);

  aefS3D->setAvatar(sound3D);

  printf("Loop\n");

  int count =  0;
  float coord = 0.0f;
  while (!sound3D->isStopped()) {

   count++;
   player.apply(aec);
   alListener3f(AL_POSITION, 2 * sin(coord), 2 * cos(coord), 1.0f);
   alListener3f(AL_VELOCITY, 0, 0, 0);
   alListenerfv(AL_ORIENTATION, listenerOri);

   coord = coord + 0.00001f;

  }

  device = alcGetContextsDevice(context);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  return 0;
}

}  // namespace ludo
