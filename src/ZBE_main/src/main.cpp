#include <cstdio>

#include "batismain.h"
#include "degryllmain.h"
#include "ludomain.h"

int main(int argc, char* argv[]) {
  int option;
  printf("Introduzca una opcion:\n");
  printf("1 - batismain\n");
  printf("2 - degryllmain\n");
  printf("3 - ludomain\n");
  printf("0 - salir\n");
  printf("--:");
  scanf ("%d",&option);
  while (option<0 || option>3) {
    printf("Introduzca una opcion... que valga: ");
    scanf ("%d",&option);
  }

  int out = 0;
  switch(option) {
    case 1:
      out = batismain(argc,argv);
    break;
    case 2:
      out = degryllmain(argc,argv);
    break;
    case 3:
      out = ludomain(argc,argv);
    break;
    case 0:
      printf("�Y para que has venido?\n");
    break;
    default:
      printf("�como he llegado aqui?\n");
    break;
  }

  printf("\n\n");
  printf("�Esta muerto?\n ...Terminado\ncon salida %d\n",out);
  getchar();

  return (out);
}