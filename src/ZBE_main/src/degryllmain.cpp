
#include "degryllmain.h"

#include <sstream>
#include <fstream>
#include <cstdio>

#include <vector>

#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/Logger.h"
#include "ZBE/core/io/FileHandler.h"

#include "ZBE/core/tools/text/utf8.h"

#include "any_iterator.hpp"
#include "boost/iterator/iterator_categories.hpp"

#include "ZBE/core/tools/containers/ticket.h"
#include "ZBE/core/tools/containers/arrayList.h"
#include "ZBE/core/tools/containers/arrayListIterator.h"

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"

#include <memory>

int degryllmain(int argc, char* argv[]) {
  printf("--- Degryll main ---\n\n");

if (SDL_Init(SDL_INIT_VIDEO) != 0){
	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
}
SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
if (win == nullptr){
	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}
SDL_Window *win2 = SDL_CreateWindow("Hello World!2", 150, 100, 640, 480, SDL_WINDOW_SHOWN);
if (win == nullptr){
	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (ren == nullptr){
	SDL_DestroyWindow(win);
	std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}
SDL_Renderer *ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (ren == nullptr){
	SDL_DestroyWindow(win);
	std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}
//std::string imagePath = "data/images/zombieball/zombieball_back_640.png";
//SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
//if (bmp == nullptr){
//	SDL_DestroyRenderer(ren);
//	SDL_DestroyWindow(win);
//	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//	SDL_Quit();
//	return 1;
//}
//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
//SDL_FreeSurface(bmp);
//if (tex == nullptr){
//	SDL_DestroyRenderer(ren);
//	SDL_DestroyWindow(win);
//	std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//	SDL_Quit();
//	return 1;
//}

//SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *tex = IMG_LoadTexture(ren, "data/images/zombieball/zombieball_back_640.png");
	if (tex == nullptr){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
	}
	SDL_Texture *tex2 = IMG_LoadTexture(ren2, "data/images/zombieball/zombieball_back_640.png");
	if (tex == nullptr){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
	}
//	return texture;
//}

//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
for (int i = 0; i < 3; ++i){
	//First clear the renderer
	SDL_RenderClear(ren);
	SDL_RenderClear(ren2);
	//Draw the texture
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderCopy(ren2, tex2, NULL, NULL);
	//Update the screen
	SDL_RenderPresent(ren);
	SDL_RenderPresent(ren2);
	//Take a quick break after all that hard work
	SDL_Delay(1000);
}
SDL_DestroyTexture(tex);
SDL_DestroyRenderer(ren);
SDL_DestroyWindow(win);
SDL_DestroyTexture(tex2);
SDL_DestroyRenderer(ren2);
SDL_DestroyWindow(win2);
SDL_Quit();


//  zbe::Logger::createInstance()->setDefaultWriters();
//
//  int i = 42;
//  float d = 3.1416;
//  char a = 65;
//  std::string s = "Hola Mundo!";
//  int *pi = &i;
//
//  ZBE_LOG_INFO("Prueba Info." << d << "añadiendo un double.");
//  ZBE_LOG_DEBUG("Prueba Debug." << i << "un int y" << pi << "su puntero.");
//  ZBE_LOG_WARNING("Prueba Warning." << a << "un caracter");
//  ZBE_LOG_ERROR("Prueba Error." << s << "una cadena.");
//  ZBE_LOG("[PROPIA]","Prueba Propia.");
//
//
//  zbe::Vector2D v1;
//  printf("Construct v1: (%lf,%lf)\n",v1.x,v1.y);
//  v1.setCartesian(3,4);
//  printf("SetCartesian v1: (%lf,%lf)\n",v1.x,v1.y);
//  zbe::Vector2D v2 = v1;
//  printf("Construct copy v2: (%lf,%lf)\n",v2.x,v2.y);
//  printf("State v1: (%lf,%lf)\n",v1.x,v1.y);
//  v2.setCartesian(4,3);
//  printf("SetCartesian v2: (%lf,%lf)\n",v2.x,v2.y);
//  zbe::Vector2D v3;
//  printf("Construct v3: (%lf,%lf)\n",v3.x,v3.y);
//  v3 = v2;
//  printf("Assign v3: (%lf,%lf)\n",v3.x,v3.y);
//  printf("State v1: (%lf,%lf)\n",v1.x,v1.y);
//  printf("State v2: (%lf,%lf)\n",v2.x,v2.y);
//  zbe::Vector2D v4(v1+v2+v3);
//  printf("Construct v4 addition: (%lf,%lf)\n",v4.x,v4.y);
//  printf("State v1: (%lf,%lf)\n",v1.x,v1.y);
//  printf("State v2: (%lf,%lf)\n",v2.x,v2.y);
//  printf("State v3: (%lf,%lf)\n",v3.x,v3.y);
//  zbe::Vector2D v5;
//  printf("Construct v5: (%lf,%lf)\n",v5.x,v5.y);
//  v5 = v4 + v1 + v2;
//  printf("addition v5: (%lf,%lf)\n",v5.x,v5.y);
//  printf("State v1: (%lf,%lf)\n",v1.x,v1.y);
//  printf("State v2: (%lf,%lf)\n",v2.x,v2.y);
//  printf("State v3: (%lf,%lf)\n",v3.x,v3.y);
//  printf("State v4: (%lf,%lf)\n",v4.x,v4.y);
//
//  double aux;
//  int iterations = 100000000;
//  clock_t t;
//  for(int i = 0; i < 10; i++) {
//    t = clock();
//    for(int j = 0; j < iterations; j++) {
//      aux = 0;
//      zbe::Vector2D v1;
//      v1.setCartesian(3,4);
//      zbe::Vector2D v2 = v1;
//      v2.setCartesian(4,3);
//      zbe::Vector2D v3;
//      v3 = v2;
//      zbe::Vector2D v4(v1+v2+v3);
//      zbe::Vector2D v5;
//      v5 = v4 + v1 + v2;
//      aux += v5.x;
//    }
//    t = clock() - t;
//    printf ("Construct took me %ld clicks (%f seconds) %lf.\n",t,((float)t)/CLOCKS_PER_SEC,aux);
//  }
//
//  zbe::Ray<2> r;
//  r.o = {3.0,4.0};
//
//  zbe::Ray2D r2;
//  r2.o = {3.0,4.0};
//
//  zbe::Ray3D r3{{0.0,0.0,0.0},{10.0,10.0,0.0}};
//
//  printf("%lf, %lf, %lf, %lf, %lf, %lf\n",r3.o[0],r3.o[1],r3.o[2],r3.d[0],r3.d[1],r3.d[2]);
//
//  zbe::Sphere bola({4.0,5.0,0.0},1.0);
//
//  double time;
//  zbe::Point3D p;
//  bool collision = zbe::intersectionRaySphere(r3,bola,time,p);
//  //bool collision = zbe::intersectionRayNSphere<3>(r3,bola,time,p);
//
//  if(collision){
//    printf("Collision en (%lf,%lf,%lf) dentro de %lf sec.!!\n",p[0],p[1],p[2],time);
//  } else {
//    printf("NO Collision!!\n");
//  }

//  zbe::ArrayList<int> l(1);
//  l.insert(2);
//
//  zbe::ArrayListIterator<int> it(l.begin());
//
//  zbe::ArrayListIterator<int> itend(l.end());
//
//  printf("Inicialmente distintos: %d\n",it!=itend);
//  fflush(stdout);
//  it++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento son iguales: %d\n",it==itend);
//  fflush(stdout);
//
//  typedef IteratorTypeErasure::make_any_iterator_type<zbe::ArrayListIterator<int> >::type anynormaliterator;
//
//  anynormaliterator anibegin;
//  anynormaliterator aniend;
//  it = l.begin();
//  anibegin = it;
//  aniend = itend;
//
//  printf("Inicialmente distintos: %d\n",anibegin!=aniend);
//  fflush(stdout);
//  anibegin++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento son iguales: %d\n",anibegin==aniend);
//  fflush(stdout);
//
//  printf("TICKETED.\n");
//  fflush(stdout);
//
//  zbe::ArrayListTicketed<int> tl(2);
//  zbe::Ticket &t2 = tl.insert(2);
//  tl.insert(3);
//
//  t2.setINACTIVE();
//
//  zbe::ArrayListTicketedIterator<int> tit(tl.begin());
//
//  zbe::ArrayListTicketedIterator<int> titend(tl.end());
//
//  printf("Inicialmente distintos: %d\n",tit!=titend);
//  fflush(stdout);
//  tit++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento son iguales: %d\n",tit==titend);
//  fflush(stdout);
//
//  //typedef IteratorTypeErasure::make_any_iterator_type<zbe::ArrayListTicketedIterator<int> >::type anyticketediterator;
//  typedef IteratorTypeErasure::any_iterator<
//    int, // value type
//    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
//    int&, // reference type
//    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
//  > anyticketediterator;
//
//  anyticketediterator tanibegin;
//  anyticketediterator taniend;
//  tit = tl.begin();
//  tanibegin = tit;
//  taniend = titend;
//
//  printf("Inicialmente distintos: %d\n",tanibegin!=taniend);
//  fflush(stdout);
//  tanibegin++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento son iguales: %d\n",tanibegin==taniend);
//  fflush(stdout);
//
//  t2.setACTIVE();
//  tit = tl.begin();
//  tanibegin = tit;
//  taniend = titend;
//
//  anyticketediterator taux = tanibegin;
//
//  printf("Inicialmente distintos: %d\n",taux!=taniend);
//  fflush(stdout);
//  taux++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento NO iguales: %d\n",taux!=taniend);
//  fflush(stdout);
//  taux++;
//  printf("Incremento.\n");
//  fflush(stdout);
//  printf("Despues del incremento SI iguales: %d\n",taux==taniend);
//  fflush(stdout);
//
//
//  double x = 5.f;
//  double y = 4.f;
//  double m = std::sqrt(x*x+y*y);
//  double nx = x / m;
//  double ny = y / m;
//  double mn = std::sqrt(nx*nx+ny*ny);
//  std::cout << "Normal module: " << mn << std::endl;
//
//  printf("x(%lf), y(%lf), m(%.30lf), nx(%.30lf), ny(%lf), mn(%lf)\n\n",x,y,m,nx,ny,mn);

//  typedef IteratorTypeErasure::any_iterator<
//    int const,
//    boost::bidirectional_traversal_tag
//  > number_iterator;
//
//  std::vector<int> v(42,43);
//  number_iterator nit,endit;
//  nit = v.begin();
//  endit = v.end();
//  for(; nit != endit; nit++) {
//    printf("numero %d\n",*nit);
//  }
//
//  std::auto_ptr<zbe::node<int> > nodes(new zbe::node<int>(42));
//  nodes->append(new zbe::node<int>(37));
//  nodes->append(new zbe::node<int>(13));
//
//  zbe::node_iterator it(nodes.get());
//
//  //int auxn;
//
//  (*it).print(std::cout);
//
////  auxn = *it;
//
//  //printf("printf: %d\n",auxn);
//
//  std::cout << "antes:" << *it <<std::endl;
//  ++it;
//  std::cout << "antes:" << *it <<std::endl;
//  ++it;
//  std::cout << "antes:" << *it <<std::endl;
//
//  imprime(zbe::node_iterator(nodes.get()),zbe::node_iterator());



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
