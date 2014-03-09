
#include "ZBE/degryllmain.h"

int degryllmain(int argc, char* argv[]) {
    printf("--- Degryll main ---\n\n");

    ClaseTest t(4);
    t.setValue(42);
    std::cout << "Hello world! " << t.getValue() << std::endl;
    getchar();

    return 0;
}
