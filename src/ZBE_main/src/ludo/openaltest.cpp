#include "ludo/openaltest.h"

#include <cstdio>
#include <stdio.h>
#include <string.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <stb_vorbis.c>

namespace ludo {

void printError(){
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

  printf("Source generation ( were the audio comes from )\n");

	ALuint source;

  alGenSources((ALuint)1, &source);
  alSourcef(source, AL_PITCH, 1);
  alSourcef(source, AL_GAIN, 1);
  alSource3f(source, AL_POSITION, 0, 0, 0);
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  alSourcei(source, AL_LOOPING, AL_TRUE);

  printf("Buffer generation ( raw audio stream )\n");

  ALuint buffer;
  alGenBuffers((ALuint)1, &buffer);
  printError();

  printf("Loading an audio stream to the buffer\n");

  //ALsizei size, freq;
  ALenum format;
	ALint source_state;

  int channels;
  int rate;
  short* decoded;

  int len = stb_vorbis_decode_filename("data/test/audio/die_m.ogg", &channels, &rate, &decoded);

  if(!len) {
    printf("Failed to load ogg file\n");
  } else {
    printf("Len: %d\n", len);
  }

	if(channels == 2) {
    format = AL_FORMAT_STEREO16;
	} else {
    format = AL_FORMAT_MONO16;
	}

  printf("alBufferData call\n");
  alBufferData(buffer, format, decoded, len * 2, rate);
  printError();

  printf("alSourcei call\n");
  alSourcei(source, AL_BUFFER, buffer);
  printError();

  printf("alSourcePlay call\n");
  alSourcePlay(source);
  printError();

  printf("alGetSourcei call\n");
  alGetSourcei(source, AL_SOURCE_STATE, &source_state);
  printError();

  printf("WTF? init: %d play: %d pause: %d stop: %d \n", AL_INITIAL, AL_PLAYING, AL_PAUSED, AL_STOPPED);
  if(source_state == AL_INITIAL) {
      printf("A BIG NOPE FOR YOU: AL_INITIAL\n");
  } else if(source_state == AL_PLAYING) {
      printf("PLAYING!!!\n");
  } else if(source_state == AL_PAUSED) {
      printf("A BIG NOPE FOR YOU: AL_PAUSED\n");
  } else if(source_state == AL_STOPPED) {
      printf("A BIG NOPE FOR YOU: AL_STOPPED\n");
  } else {
      printf("WTF? %#06x\n", source_state);
  }

  printf("Loop\n");
  // check for errors
  int count =  0;
  float coord = 0.0f;
  while (true){//}source_state == AL_PLAYING) {

    count++;

    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    printError();

    alListener3f(AL_POSITION, 2 * sin(coord), 2 * cos(coord), 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    coord = coord + 0.000001f;

  }

  // cleanup context
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  device = alcGetContextsDevice(context);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  return 0;
}

}  // namespace ludo
