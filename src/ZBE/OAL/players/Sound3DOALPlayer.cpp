/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sound3DOALPlayer.cpp
 * @since 2018-08-28
 * @date 2018-08-28
 * @author Degryll Ludo
 * @brief A behavior that plays 3d sounds.
 */

#include "ZBE/OAL/players/Sound3DOALPlayer.h"

namespace zbe {

void Sound3DOALPlayer::apply(std::shared_ptr<MAvatar<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> > avatar) {
//  Sound3D* sound;
//  assignAvatar(aec, &sound);
//  ALuint source;
  ALint source_state;

  auto pV = AvtUtil::get<1, Vector3D>(avatar); // position value
  auto vV = AvtUtil::get<2, Vector3D>(avatar); // velocity value
  auto stateV = AvtUtil::get<3, uint64_t>(avatar); // sound state value
  auto sourceV = AvtUtil::get<4, uint64_t>(avatar); // source value
  auto idV = AvtUtil::get<5, uint64_t>(avatar); // source state value

  Vector3D p = pV->get();
  Vector3D v = vV->get();
  uint64_t state = stateV->get();
  ALuint source;// = (ALuint)sourceV->get();
  uint64_t id = idV->get();

  if(state == NEW){
    alGenSources((ALuint)1, &source);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, p.x, p.y, p.z);
    alSource3f(source, AL_VELOCITY, v.x, v.y, p.z);
    ALuint buffer = store->getAudio(id);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    sourceV->set((uint64_t)source);
    if(source_state != AL_PLAYING) {
      ALCenum error = alGetError();
      SysError::setError(std::string("ERROR: Unable to play sound with id ") + std::to_string(id) + std::string(". OpenAL error nun:") + std::to_string(error));
      stateV->set(STOPPED);
      return;
    }
  } else if(state == PLAYING) {
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    if(source_state == AL_STOPPED) {
      stateV->set(STOPPED);
      // TODO ¿Eliminar avatar?
    } else {
      source = (ALuint)sourceV->get();
      alSource3f(source, AL_POSITION, p.x, p.y, p.z);
      alSource3f(source, AL_VELOCITY, v.x, v.y, p.z);
    }
  } else {
    SysError::setError(std::string("ERROR: Sound avatar with audio id ") + std::to_string(id) + std::string(" has an unexpected state"));
  }
}

void Sound3DOALPlayerFtry::create(std::string name, uint64_t cfgId){
  using namespace std::string_literals;

  std::shared_ptr<Sound3DOALPlayer> s3daolp = std::shared_ptr<Sound3DOALPlayer>(new Sound3DOALPlayer);
  mainRsrc.insert("Behavior."s + name, s3daolp);
  specificRsrc.insert("Sound3DOALPlayer."s + name, s3daolp);
}

void Sound3DOALPlayerFtry::setup(std::string name, uint64_t cfgId){
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(!cfg) {
    SysError::setError("Sound3DOALPlayerFtry config for "s + name + " not found."s);
    return;
  }
  auto j = *cfg;
  auto s3daolp = specificRsrc.get("Sound3DOALPlayer."s + name);
  auto audioStore = JSONFactory::loadParamCfgStoreP<OALAudioStore>(audioStoreRsrc, j, "OALAudioStore", "audiostore"s, "Sound3DOALPlayerFtry"s);
  if(!audioStore) {
    SysError::setError("Sound3DOALPlayerFtry config for audiostore is invalid"s);
    return;
  }
  s3daolp->setUp(*audioStore);
}

}  // namespace zbe
