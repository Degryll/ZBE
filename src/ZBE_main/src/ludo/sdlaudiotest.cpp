#include "ludo/sdlaudiotest.h"

namespace ludo {

int sdlaudiotest(int, char** ) {
//   if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//     printf("Failed to init audio:  %s\n", SDL_GetError());
//     return -1;
//   }

//   printf("SDL audio loaded\n");
//   if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
//     return -2;

//   Mix_Music *music = NULL;
//   Mix_Chunk *wave = NULL;
//   printf("Errors?:  %s\n", SDL_GetError());
// // Load our sound effect
//   wave = Mix_LoadWAV("data/test/audio/die.ogg");
//   if (wave == NULL)
//     return -1;

//   // Load our music
//   music = Mix_LoadMUS("data/test/audio/test.ogg");
//   if (music == NULL)
//     return -3;

//   printf("data/test/audio/test.ogg loaded\n");
//   printf("Errors?:  %s\n", SDL_GetError());
//   if ( Mix_PlayChannel(0, wave, 0) == -1 )
//     return -1;

//   if ( Mix_PlayMusic( music, -1) == -1 )
//     return -4;

//   printf("Errors?:  %s\n", SDL_GetError());
//   int i;
//   do {
//     i = Mix_PlayingMusic();
//     printf("Playing:  %d\n", i);
//     printf("Playing others:  %d\n", Mix_Playing(0));
//   } while(i);

//   Mix_FreeMusic(music);

//   Mix_FreeChunk(wave);

//   // quit SDL_mixer
//   Mix_CloseAudio();

//   return 0;
}

}
