
#include "ZBE/degryllmain.h"

#include <SDL2/SDL.h>

int degryllmain(int argc, char* argv[]) {
    printf("--- Degryll main ---\n\n");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 480, 300, SDL_WINDOW_SHOWN);
    if (win == 0){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (ren == 0){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("data/images/test/pandarojo.bmp");
    if (bmp == 0){
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == 0){
        std::cout << "SDL_CreateTextureFromSurface Error: "
            << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

	SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    ClaseTest t(4);
    t.setValue(42);
    std::cout << "Hello world! " << t.getValue() << std::endl;
    getchar();

    return 0;
}
