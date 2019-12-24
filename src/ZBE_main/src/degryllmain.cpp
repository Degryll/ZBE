#include "degryllmain.h"

#include <cstdio>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//#include "ZBE/core/zbe.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"


//std::string text;
//std::vector<std::string> historial;

class Console : public zbe::Entity {
public:
  Console() : historial(), text(), current(0) {}

  void addutf8(std::string utf8) {
    if (SDL_strlen(utf8.c_str()) == 0 || utf8.c_str()[0] == '\n') return;
    text += utf8;
    current = historial.size();
  }
  void removeglyph() {
    while(1) {
      if (text.size()==0) {
        break;
      }
      if ((text.back() & 0x80) == 0x00) {
        /* One byte */
        text.pop_back();
        break;
      }
      if ((text.back() & 0xC0) == 0x80) {
        /* Byte from the multibyte sequence */
        text.pop_back();
      }
      if ((text.back() & 0xC0) == 0xC0) {
        /* First byte of multibyte sequence */
        text.pop_back();
        break;
      }
    }  // while(1)
  }
  void execute() {
    historial.push_back(text);
    text.clear();
    current++;
  }
  int first() { return std::max(0, current - 10); }
  int last() { return (current); }
  std::string getLine(size_t lineno) {
    using namespace std::string_literals;
    return (">> "s + historial[lineno]);
  }
  std::string command() {
    using namespace std::string_literals;
    return (">> "s + text);
  }

  void lookup() {current = std::max(0, current-1);}
  void lookdown() {current = std::min(int(historial.size()), current+1);}

private:
  std::vector<std::string> historial;
  std::string text;
  int current;
};

int degryllmain(int, char*[]) {
  printf("Hola Mundo!\n");

  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", 50, 50, 640, 480);

//  SDL_Init(SDL_INIT_VIDEO);
//  TTF_Init();

//  SDL_Window * window = SDL_CreateWindow("Console",
//      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
//      480, 0);

  auto fs = window->getFontStore();
  auto fid = fs->loadFont("data\\fonts\\Hack-Regular.ttf", 14, {192, 192, 192, 255});

//  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
//  TTF_Font *font = TTF_OpenFont("data\\fonts\\Hack-Regular.ttf", 14);
//  SDL_Color cf = {192, 192, 192, 255};
//  SDL_Color cb = {0, 0, 0, 255};

  glClearColor(0, 0, 0, 0);
//  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  Console c;

  bool quit = false;
  SDL_Event event;

  while (!quit) {
    window->clear();
//    SDL_RenderClear(renderer);
//    glClear(GL_COLOR_BUFFER_BIT);

    SDL_WaitEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEWHEEL:
        if (event.wheel.y > 0) {
          c.lookup();
        } else if (event.wheel.y < 0) {
          c.lookdown();
        }
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;
          case SDLK_RETURN:
            c.execute();
            break;
          case SDLK_BACKSPACE:
//            while(1) {
//              if (text.size()==0) {
//                break;
//              }
//              if ((text.back() & 0x80) == 0x00) {
//                /* One byte */
//                text.pop_back();
//                break;
//              }
//              if ((text.back() & 0xC0) == 0x80) {
//                /* Byte from the multibyte sequence */
//                text.pop_back();
//              }
//              if ((text.back() & 0xC0) == 0xC0) {
//                /* First byte of multibyte sequence */
//                text.pop_back();
//                break;
//              }
//            }
            c.removeglyph();
            break;
        }
        break;
        case SDL_TEXTINPUT:
//          if (SDL_strlen(event.text.text) == 0 || event.text.text[0] == '\n')// || markedRect.w < 0)
//              break;
//          text += event.text.text;
          c.addutf8(event.text.text);
          //fprintf(stderr, "Keyboard: text input \"%s\"\n", event.text.text);

          //if (SDL_strlen(text) + SDL_strlen(event.text.text) < sizeof(text))
          //    SDL_strlcat(text, event.text.text, sizeof(text));

          //fprintf(stderr, "text inputed: %s\n", text);

          // After text inputed, we can clear up markedText because it
          // is committed
          //markedText[0] = 0;
          //Redraw();
          break;
    }

    int w = 0;
    int h = 0;
    int posy = 0;
    for(int i = c.first(); i < c.last(); i++) {
      SDL_Texture* texture = fs->renderText(fid, c.getLine(i).c_str());
//      SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, c.getLine(i).c_str(), cf, cb);
//      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_QueryTexture(texture, 0, 0, &w, &h);
      SDL_Rect dst = {0, posy, w, h};
      window->render(texture, nullptr, &dst);
//      SDL_RenderCopy(renderer, texture, 0, &dst);
      posy += h;

//      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);

    }

    SDL_Texture* texture = fs->renderText(fid, c.command().c_str());
//    SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, c.command().c_str(), cf, cb);
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, 0, 0, &w, &h);
    SDL_Rect dst = {0, posy, w, h};

    window->render(texture, nullptr, &dst);
//    SDL_RenderCopy(renderer, texture, 0, &dst);
//    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

//    window->glSwap();
    window->present();
//    SDL_RenderPresent(renderer);
  }

//  TTF_CloseFont(font);
//  SDL_DestroyRenderer(renderer);
//  SDL_DestroyWindow(window);
//  TTF_Quit();
//  SDL_Quit();

  getchar();
  return (0);
}

///*
//  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely.
//*/
///* A simple program to test the Input Method support in the SDL library (2.0+) */
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_ttf.h"
//
////#include "SDL2/SDL_test_common.h"
//
//#define DEFAULT_WINDOW_WIDTH 640
//#define DEFAULT_PTSIZE  30
////#define DEFAULT_FONT    "/System/Library/Fonts/华文细黑.ttf"
//#define DEFAULT_FONT    "data/fonts/Hack-Regular.ttf"
//#define MAX_TEXT_LENGTH 256
//
//static SDL_Renderer * renderer;
//
////static SDLTest_CommonState *state;
//static SDL_Rect textRect, markedRect;
////static SDL_Color lineColor = {0,0,0,0};
////static SDL_Color backColor = {255,255,255,0};
//static SDL_Color textColor = {0,0,0,0};
//static char text[MAX_TEXT_LENGTH], markedText[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
//static int cursor = 0;
//static TTF_Font *font;
//
//size_t utf8_length(unsigned char c)
//{
//    c = (unsigned char)(0xff & c);
//    if (c < 0x80)
//        return 1;
//    else if ((c >> 5) ==0x6)
//        return 2;
//    else if ((c >> 4) == 0xe)
//        return 3;
//    else if ((c >> 3) == 0x1e)
//        return 4;
//    else
//        return 0;
//}
//
//char *utf8_next(char *p)
//{
//    size_t len = utf8_length(*p);
//    size_t i = 0;
//    if (!len)
//        return 0;
//
//    for (; i < len; ++i)
//    {
//        ++p;
//        if (!*p)
//            return 0;
//    }
//    return p;
//}
//
//char *utf8_advance(char *p, size_t distance)
//{
//    size_t i = 0;
//    for (; i < distance && p; ++i)
//    {
//        p = utf8_next(p);
//    }
//    return p;
//}
//
//void usage()
//{
//    printf("usage: testime [--font fontfile]\n");
//    exit(0);
//}
//
//void InitInput() {
//    /* Prepare a rect for text input */
//    textRect.x = textRect.y = 100;
//    textRect.w = DEFAULT_WINDOW_WIDTH - 2 * textRect.x;
//    textRect.h = 50;
//
//    text[0] = 0;
//    markedRect = textRect;
//    markedText[0] = 0;
//
//    SDL_StartTextInput();
//}
//
//void CleanupVideo() {
//    SDL_StopTextInput();
//    TTF_CloseFont(font);
//    TTF_Quit();
//}
//
//
//void _Redraw(SDL_Renderer * renderer) {
//    int w = 0, h = textRect.h;
//    SDL_Rect cursorRect, underlineRect;
//
//    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
//    SDL_RenderFillRect(renderer,&textRect);
//
//    if (*text)
//    {
//        SDL_Surface *textSur = TTF_RenderUTF8_Blended(font, text, textColor);
//        SDL_Rect dest = {textRect.x, textRect.y, textSur->w, textSur->h };
//
//        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,textSur);
//        SDL_FreeSurface(textSur);
//
//        SDL_RenderCopy(renderer,texture,NULL,&dest);
//        SDL_DestroyTexture(texture);
//        TTF_SizeUTF8(font, text, &w, &h);
//    }
//
//    markedRect.x = textRect.x + w;
//    markedRect.w = textRect.w - w;
//    if (markedRect.w < 0)
//    {
//        // Stop text input because we cannot hold any more characters
//        SDL_StopTextInput();
//        return;
//    }
//    else
//    {
//        SDL_StartTextInput();
//    }
//
//    cursorRect = markedRect;
//    cursorRect.w = 2;
//    cursorRect.h = h;
//
//    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
//    SDL_RenderFillRect(renderer,&markedRect);
//
//    if (markedText[0])
//    {
//        if (cursor)
//        {
//            char *p = utf8_advance(markedText, cursor);
//            char c = 0;
//            if (!p)
//                p = &markedText[strlen(markedText)];
//
//            c = *p;
//            *p = 0;
//            TTF_SizeUTF8(font, markedText, &w, 0);
//            cursorRect.x += w;
//            *p = c;
//        }
//        SDL_Surface *textSur = TTF_RenderUTF8_Blended(font, markedText, textColor);
//        SDL_Rect dest = {markedRect.x, markedRect.y, textSur->w, textSur->h };
//        TTF_SizeUTF8(font, markedText, &w, &h);
//        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,textSur);
//        SDL_FreeSurface(textSur);
//
//        SDL_RenderCopy(renderer,texture,NULL,&dest);
//        SDL_DestroyTexture(texture);
//
//        underlineRect = markedRect;
//        underlineRect.y += (h - 2);
//        underlineRect.h = 2;
//        underlineRect.w = w;
//
//        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
//        SDL_RenderFillRect(renderer,&markedRect);
//    }
//
//    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
//    SDL_RenderFillRect(renderer,&cursorRect);
//
//    SDL_SetTextInputRect(&markedRect);
//}
//
//void Redraw() {
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//        SDL_RenderClear(renderer);
//
//        _Redraw(renderer);
//
//        SDL_RenderPresent(renderer);
////    }
//}
//
//int degryllmain(int, char *[]) {
//    int done;
//    SDL_Event event;
//    const char *fontname = DEFAULT_FONT;
//
//    SDL_Init(SDL_INIT_VIDEO);
//
//    /* Initialize fonts */
//    TTF_Init();
//
//    font = TTF_OpenFont(fontname, DEFAULT_PTSIZE);
//    if (! font)
//    {
//        fprintf(stderr, "Failed to find font: %s\n", TTF_GetError());
//        exit(-1);
//    }
//
//    printf("Using font: %s\n", fontname);
//    atexit(SDL_Quit);
//
//    InitInput();
//    /* Create the windows and initialize the renderers */
//    SDL_Window * window = SDL_CreateWindow("Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WINDOW_WIDTH, 480, 0);
//    renderer = SDL_CreateRenderer(window, -1, 0);
//    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
//    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
//    SDL_RenderClear(renderer);
//
//    Redraw();
//    /* Main render loop */
//    done = 0;
//    while (!done) {
//        /* Check for events */
//        while (SDL_PollEvent(&event)) {
//            //SDLTest_CommonEvent(state, &event, &done);
//            switch(event.type) {
//                case SDL_KEYDOWN: {
//                    switch (event.key.keysym.sym)
//                    {
//                        case SDLK_RETURN:
//                             text[0]=0x00;
//                             Redraw();
//                             break;
//                        case SDLK_BACKSPACE:
//                             {
//                                 int textlen=SDL_strlen(text);
//
//                                 do {
//                                     if (textlen==0)
//                                     {
//                                         break;
//                                     }
//                                     if ((text[textlen-1] & 0x80) == 0x00)
//                                     {
//                                         /* One byte */
//                                         text[textlen-1]=0x00;
//                                         break;
//                                     }
//                                     if ((text[textlen-1] & 0xC0) == 0x80)
//                                     {
//                                         /* Byte from the multibyte sequence */
//                                         text[textlen-1]=0x00;
//                                         textlen--;
//                                     }
//                                     if ((text[textlen-1] & 0xC0) == 0xC0)
//                                     {
//                                         /* First byte of multibyte sequence */
//                                         text[textlen-1]=0x00;
//                                         break;
//                                     }
//                                 } while(1);
//
//                                 Redraw();
//                             }
//                             break;
//                    }
//
//                    if (done)
//                    {
//                        break;
//                    }
//
//                    fprintf(stderr,
//                            "Keyboard: scancode 0x%08X = %s, keycode 0x%08X = %s\n",
//                            event.key.keysym.scancode,
//                            SDL_GetScancodeName(event.key.keysym.scancode),
//                            event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
//                    break;
//
//                case SDL_TEXTINPUT:
//                    if (SDL_strlen(event.text.text) == 0 || event.text.text[0] == '\n' ||
//                        markedRect.w < 0)
//                        break;
//
//                    fprintf(stderr, "Keyboard: text input \"%s\"\n", event.text.text);
//
//                    if (SDL_strlen(text) + SDL_strlen(event.text.text) < sizeof(text))
//                        SDL_strlcat(text, event.text.text, sizeof(text));
//
//                    fprintf(stderr, "text inputed: %s\n", text);
//
//                    // After text inputed, we can clear up markedText because it
//                    // is committed
//                    markedText[0] = 0;
//                    Redraw();
//                    break;
//
//                case SDL_TEXTEDITING:
//                    fprintf(stderr, "text editing \"%s\", selected range (%d, %d)\n",
//                            event.edit.text, event.edit.start, event.edit.length);
//
//                    strcpy(markedText, event.edit.text);
//                    cursor = event.edit.start;
//                    Redraw();
//                    break;
//                }
//                break;
//
//            }
//        }
//    }
//    CleanupVideo();
//    return 0;
//}
