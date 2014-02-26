#include <iostream>
#include <cstdio>

#include <SDL2/SDL.h>

#include "ZBE/test.h"

int main(int argc, char *argv[]) {
    ClaseTest t(4);
    t.setValue(42);
    std::cout << "Hello world! " << t.getValue() << std::endl;
    getchar();
    return 0;
}
