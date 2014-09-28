
#include "degryllmain.h"

#include <sstream>
#include <fstream>
#include <cstdio>

//#include <SDL2/SDL.h>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/Logger.h"
#include "ZBE/core/io/FileHandler.h"

#include "ZBE/core/tools/text/utf8.h"

int degryllmain(int argc, char* argv[]) {
  printf("--- Degryll main ---\n\n");

  zbe::Logger::createInstance()->setDefaultWriters();

  int i = 42;
  float d = 3.1416;
  char a = 65;
  std::string s = "Hola Mundo!";
  int *pi = &i;

  ZBE_LOG_INFO("Prueba Info." << d << "añadiendo un double.");
  ZBE_LOG_DEBUG("Prueba Debug." << i << "un int y" << pi << "su puntero.");
  ZBE_LOG_WARNING("Prueba Warning." << a << "un caracter");
  ZBE_LOG_ERROR("Prueba Error." << s << "una cadena.");
  ZBE_LOG("[PROPIA]","Prueba Propia.");


//////////////////////////////////////////////////

//  char filename[] = {0xe6,0x97,0xa5,0xd1,0x88,0xf0,0x9d,0x84,0x9e,0x2e,0x74,0x78,0x74,0x00};
//  char buffer[256] = "";
//  zbe::FileHandler f(filename,"rb");
//  //int n = f.read(buffer,1,256);
//  int n;
//  f.readLine(buffer,256);
//  f.readLine(buffer,256);
//  f.readLine(buffer,256);
//  for(n = 0; buffer[n] != 0; n++);
//
//  std::wstring fn;
//  utf8::utf8to16(filename, filename + 15, back_inserter(fn));
//  printf("FILENAME: %x\n",fn.c_str()[3]);
//  MessageBoxW(
//              0,
//              fn.c_str(),
//              L"Filename",
//              MB_ICONINFORMATION | MB_SETFOREGROUND
//              );
//
//  std::wstring line;
//  utf8::utf8to16(buffer, buffer + n, back_inserter(line));
//  MessageBoxW(
//              0,
//              line.c_str(),
//              L"Content",
//              MB_ICONINFORMATION | MB_SETFOREGROUND
//              );
//
//  if(zbe::FileHandler::exist("prueba/asd.txt")) {
//    printf("Existe.\n");
//  } else {
//    printf("No existe.\n");
//  }
//
//  zbe::FileHandler ferror("prueba/asd.txt","wb",true);
//  if (zbe::SysError::getNErrors()) {
//    printf(zbe::SysError::getLastErrorString().c_str());
//  } else {
//    printf("Abierto satisfactoriamente.");
//  }
//  printf("\n\n");
//
//  if(zbe::FileHandler::exist("prueba/asd.txt")) {
//    printf("Existe.\n");
//  } else {
//    printf("No existe.\n");
//  }

//////////////////////////////////////////////////






//char fnutf8[] = {0xe6,0x97,0xa5,0xd1,0x88,0xf0,0x9d,0x84,0x9e,0x2e,0x74,0x78,0x74,0x00};
////std::wstring fn(L"asd.txt");
//std::wstring fn;
//utf8::utf8to16(fnutf8, fnutf8 + 22, back_inserter(fn));
////int posix_handle = _fileno(fopen("asd.txt", "r"));
//
////std::ifstream ifs(_fdopen(posix_handle, "r")); // 1
//char cutf8[256] = "";
//FILE* futf8 = _wfopen(fn.c_str(), L"rb");
//char auxt[16] = {0x22,0x48,0x65,0x6C,0x6C,0x6F,0x2C,0x20,0xE4,0xB8,0x96,0xE7,0x95,0x8C,0x22,0x00};
////fwrite(auxt,1,16,futf8);
////fclose(futf8);
////futf8 = _wfopen(fn.c_str(), L"rb");
//int el = fread(cutf8,1,256,futf8);
////cutf8[30] = 0;
//for(int i = 0; i < el; i++) {
//  printf("%x(%x)\n",cutf8[i],auxt[i]);
//}
//printf("\n");
//std::wstring line;
//utf8::utf8to16(auxt, auxt + 15, back_inserter(line));
//MessageBoxW(
//            0,
//            fn.c_str(),
//            L"Spanish text",
//            MB_ICONINFORMATION | MB_SETFOREGROUND
//            );
//std::wstring line2;
//utf8::utf8to16(cutf8, cutf8 + el, back_inserter(line2));
//MessageBoxW(
//            0,
//            line2.c_str(),
//            L"Spanish text",
//            MB_ICONINFORMATION | MB_SETFOREGROUND
//            );
////printf("%s\n",cutf8);
//fclose(futf8);
//
//  zbe::LoggerMsg msg;
//  zbe::Logger l;
//  l.log("INFO",__FILE__,__LINE__, msg << "Algo " << 42 << true);
//  getchar();

//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 480, 300, SDL_WINDOW_SHOWN);
//    if (win == 0){
//        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
//    if (ren == 0){
//        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    SDL_Surface *bmp = SDL_LoadBMP("data/images/test/pandarojo.bmp");
//    if (bmp == 0){
//        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
//    SDL_FreeSurface(bmp);
//    if (tex == 0){
//        std::cout << "SDL_CreateTextureFromSurface Error: "
//            << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    SDL_RenderClear(ren);
//    SDL_RenderCopy(ren, tex, NULL, NULL);
//    SDL_RenderPresent(ren);
//
//    SDL_Delay(2000);
//
//	SDL_DestroyTexture(tex);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(win);
//    SDL_Quit();

    std::cout << "Hello world! " << std::endl;
    getchar();

    return 0;
}
