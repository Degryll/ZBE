#include "ludomain.h"

#include <cstdio>

namespace ludo {

int ludomain(int argc, char** argv) {

  printf("\n");
  printf("+-------------------------+\n");
  printf("+   __                    +\n");
  printf("+  |  |  _   _ ___  __    +\n");
  printf("+  |  | | | | | _ \\/_ \\   +\n");
  printf("+  |  |_|_\\_/ / | | | |   +\n");
  printf("+  |_____|___/____/___/   +\n");
  printf("+                         +\n");
  printf("+-------------------------+\n");
  int option;
  printf("Introduzca una opcion:\n");
  printf("1 - opengl test\n");
  printf("2 - sdl audio test\n");
  printf("3 - test general\n");
  printf("4 - openal test\n");
  printf("5 - app test\n");
  printf("0 - salir\n");
  printf("--:");
  int readAmount = scanf ("%d",&option);
  while (readAmount!=1 || option<0 || option>5) {
    printf("Introduzca una opcion... que valga: ");
    readAmount = scanf ("%d",&option);
  }

  int out = 0;
  switch(option) {
  case 1:
    out = opengltest(argc,argv);
    break;
  case 2:
    out = sdlaudiotest(argc,argv);
    break;
  case 3:
    out = generaltest(argc,argv);
    break;
  case 4:
    out = openaltest(argc,argv);
    break;
  case 5:
    out = apptest(argc,argv);
    break;
  case 0:
    printf("�Y para que has venido?\n");
    break;
  default:
    printf("�como he llegado aqui?\n");
    break;
  }

  return (out);
}

} //namespace Ludo
