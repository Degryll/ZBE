#include <iostream>

#include "ZBE/test.h"

int main() {
    ClaseTest t(4);
    t.setValue(42);
    std::cout << "Hello world! " << t.getValue() << std::endl;
    return 0;
}
