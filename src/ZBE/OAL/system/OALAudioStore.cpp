/**
 * Copyright 2018 Batis Degryll Ludo
 * @file OALAudioStore.cpp
 *
 * @since 2018-08-19
 * @date 2018-08-19
 * @author Degryll Ludo
 * @brief A store for audio samples.
 */

#include "ZBE/OAL/system/OALAudioStore.h"
#include <stb_vorbis.h>

namespace zbe {

OALAudioStore::OALAudioStore() : audioCollection(), m() {
  audioCollection.push_back(ALuint());  // Id zero is discouraged
}

OALAudioStore::~OALAudioStore() {
  for(ALuint buf : audioCollection){
    alDeleteBuffers(1, &buf);
  }
}

uint64_t OALAudioStore::loadAudio(const char *url) {
  uint64_t id = 0;
  ALuint buffer = _loadAudio(url);
  m.lock();
    audioCollection.push_back(buffer);
    id = audioCollection.size() - 1;
  m.unlock();
  return id;
}

uint64_t OALAudioStore::reloadAudio(const char *url, uint64_t id) {
  m.lock();
    if (id >= audioCollection.size()) {
      zbe::SysError::setError(std::string("ERROR: Can't reload audio: ") + std::to_string(id) + std::string(". Audio doesn't exist."));
    } else {
      ALuint buffer = _loadAudio(url);
      ALuint old = audioCollection[id];
      alDeleteBuffers(1, &old);
      audioCollection[id] = buffer;
    }
  m.unlock();
  return id;
}

ALuint OALAudioStore::getAudio(uint64_t id) const {
  return audioCollection[id];
}

//------------------ private ------------------//

bool OALAudioStore::checkErrors(const char *job){
  ALCenum error = alGetError();
  if (isOALError(error)) {
    logOALError(job, formattedOALError(error));
    return true;
  }
  return false;

}

void OALAudioStore::logOALError(const char *job, std::string error) {
  zbe::SysError::setError(std::string("ERROR: OAL error while ") + std::string(job) + std::string(": ") + error);
}

ALuint OALAudioStore::_loadAudio(const char *url) {
  ALenum format;
  int channels, freq;
  short* data;
  int len = stb_vorbis_decode_filename(url, &channels, &freq, &data);

  if(!len) {zbe::SysError::setError(std::string("ERROR: Can't load audio file: ") + std::string(url) + std::string(". For an unknown reason."));}

	if(channels == 2) {
    format = AL_FORMAT_STEREO16;
	} else {
    format = AL_FORMAT_MONO16;
	}

  ALuint buffer = 0;
  alGenBuffers(static_cast<ALuint>(1), &buffer);

  if(checkErrors("generating buffer")) {
    free(data);
    return buffer;
  }

  alBufferData(buffer, format, data, len, freq);
  free(data);

  checkErrors("copying buffer");
  return buffer;
}

}  // namespace zbe
