/**
 * Copyright 2012 Batis Degryll Ludo
 * @file zandboks.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBoks game.
 */

#include "ZBE/core/zbe.h"

int main(int /*argc*/, char** /*argv*/) {
    printf("Hello ZandBoks\n");
    zbe::ResourceManager<int>::getInstance();
}
