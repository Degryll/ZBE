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

void Sound3DOALPlayer::apply(std::shared_ptr<AvatarEntityContainer<Sound3D> > aec) {
  Sound3D* sound;
  assignAvatar(aec, &sound);
  ALuint source;
  ALint source_state;

  if(sound->isNew()){
    alGenSources((ALuint)1, &source);
    Point3D p = sound->getPosition();
    Vector3D v = sound->getVelocity();
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, p.x, p.y, p.z);
    alSource3f(source, AL_VELOCITY, v.x, v.y, p.z);
    ALuint buffer = store->getAudio(sound->getAudioId());
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    sound->setSource(source);
    if(source_state != AL_PLAYING) {
      ALCenum error = alGetError();
      SysError::setError(std::string("ERROR: Unable to play sound with id ") + std::to_string(sound->getAudioId()) + std::string(". OpenAL error nun:") + std::to_string(error));
      sound->stop();
      return;
    }
  } else if(sound->isPlaying()) {
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    if(source_state == AL_STOPPED) {
      sound->stop();
    } else {
      source = sound->getSource();
      Point3D p = sound->getPosition();
      Vector3D v = sound->getVelocity();
      alSource3f(source, AL_POSITION, p.x, p.y, p.z);
      alSource3f(source, AL_VELOCITY, v.x, v.y, p.z);
    }
  } else {
    SysError::setError(std::string("ERROR: Sound avatar with audio id ") + std::to_string(sound->getAudioId()) + std::string(" has an unexpected state"));
  }
}

}  // namespace zbe
