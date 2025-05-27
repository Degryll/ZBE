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
#include <vorbis/vorbisfile.h>

//#include "../extlibs/stb/stb_vorbis.h" //<stb_vorbis.h>

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
      std::vector<char> bufferData;
    ALenum format;
    ALsizei freq;

    // Abrir el archivo
#ifdef _WIN32
    FILE* file;
    fopen_s(file, url, "rb");
#else
    FILE* file = fopen(url, "rb");
#endif // OS
    if (!file) {
        std::cerr << "Error abriendo el archivo: " << url << std::endl;
        return 0;
    }

    // Cargar el archivo OGG
    OggVorbis_File oggFile;
    if (ov_open(file, &oggFile, nullptr, 0) < 0) {
        std::cerr << "Error al abrir el archivo OGG" << std::endl;
        fclose(file);
        return 0;
    }

    // Obtener información del audio
    vorbis_info* info = ov_info(&oggFile, -1);
    freq = static_cast<ALsizei>(info->rate);
    format = (info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    // Leer datos y almacenarlos en un buffer
    char tempBuffer[4096];
    int bitStream;
    long bytes;
    do {
        bytes = ov_read(&oggFile, tempBuffer, sizeof(tempBuffer), 0, 2, 1, &bitStream);
        if (bytes > 0) {
            bufferData.insert(bufferData.end(), tempBuffer, tempBuffer + bytes);
        }
    } while (bytes > 0);

    // Cerrar el archivo OGG
    ov_clear(&oggFile);

    // Crear y cargar buffer en OpenAL
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, bufferData.data(), static_cast<ALsizei>(bufferData.size()), freq);

    return buffer; // Devuelve el identificador del buffer
}

}  // namespace zbe
