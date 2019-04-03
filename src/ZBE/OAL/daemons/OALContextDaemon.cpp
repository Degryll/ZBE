/**
 * Copyright 2011 Batis Degryll Ludo
 * @file SDLWindowDaemon.cpp
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Ludo Degryll Batis
 * @brief Daemon that generates a SDLWindow.
 */

#include "ZBE/OAL/daemons/OALContextDaemon.h"

#include <memory>

namespace zbe {

void OALContextDaemon::run() {
  using namespace std::string_literals;
  ALboolean enumeration;
  enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
  if (enumeration == AL_FALSE) {
    SysError::setError("OAL device enumeration unsupported."s);
    return;
  }

  ALCchar* last = getLastAudioDevice(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

  ALCdevice *device;
  device = alcOpenDevice(last);

  if (!device) {
    SysError::setError("OAL Failed to load audio device: "s + formattedOALError(alGetError()));
  }

  ALCcontext *context;

  context = alcCreateContext(device, NULL);
  if (!alcMakeContextCurrent(context)) {
    SysError::setError("OAL Context creation error: "s + formattedOALError(alGetError()));
  }
}

ALCchar* OALContextDaemon::getLastAudioDevice(const ALCchar *devices) {
  const ALCchar *device = devices, *next = devices + 1;
  size_t len = 0;
  ALCchar *out = (ALCchar*) malloc(sizeof(ALCchar)*1024);

  while (device && *device != '\0' && next && *next != '\0') {
    strcpy(out, (char*)device);
    fprintf(stdout, "%s\n", device);
    len = strlen(device);
    device += (len + 1);
    next += (len + 2);
  }
  return out;
}

}  // namespace zbe
