#include <cstdio>

#include "batismain.h"
#include "degryllmain.h"
#include "ludomain.h"
//#include "gamemain.h"
#include "testing.h"
#include "tempmain.h"
#include "tempcleanmain.h"
//#include "tinygltf/gltfmain.h"
int gltfmain(int argc, char **argv){}

int main(int argc, char* argv[]) {
  int option;
  printf("Introduzca una opcion:\n");
  printf("1 - batismain\n");
  printf("2 - degryllmain\n");
  printf("3 - ludomain\n");
  printf("#4 - gamemain\n");
  printf("5 - testing\n");
  printf("6 - gltf test\n");
  printf("7 - temporal prueba interacciones\n");
  printf("8 - temporal prueba interacciones limpito\n");
  printf("0 - salir\n");
  printf("--:");
  int readAmount = scanf ("%d",&option);
  while (readAmount!=1 || option<0 || option>8) {
    printf("Introduzca una opcion... que valga: ");
    readAmount = scanf ("%d",&option);
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
      out = ludo::ludomain(argc,argv);
    break;
    case 4:
      //out = gamemain(argc,argv);
    break;
    case 5:
      out = testing::testingmain(argc,argv);
    break;
    case 6:
      out = gltfmain(argc,argv);
    break;
    case 7:
      out = temp::tempmain(argc,argv);
    break;
    case 8:
      out = tempclean::tempcleanmain(argc,argv);
    break;
    case 0:
      printf("�Y para que has venido?\n");
    break;
    default:
      printf("�como he llegado aqui?\n");
    break;
  }

printf("                     ______ \n");
printf("                   <((((((\\\\\\ \n");
printf("                   /      . }\\ \n");
printf("                   ;--..--._|} \n");
printf("(\\                 '--/\\--'  ) \n");
printf(" \\\\                | '-'  :'| \n");
printf("  \\\\               . -==- .-| \n");
printf("   \\\\               \\.__.'   \\--._ \n");
printf("   [\\\\          __.--|       //  _/'--. \n");
printf("   \\ \\\\       .'-._ ('-----'/ __/      \\ \n");
printf("    \\ \\\\     /   __>|      | '--.       | \n");
printf("     \\ \\\\   |   \\   |     /    /       / \n");
printf("      \\ '\\ /     \\  |     |  _/       / \n");
printf("       \\  \\       \\ |     | /        / \n");
printf("8======================================D\n");
printf("|             Esta muerto?             |\n|             ...Terminado             |\n");
printf("C======================================8\n");
printf("\n\ncon salida %d\n",out);
getchar();

  return (out);
}
