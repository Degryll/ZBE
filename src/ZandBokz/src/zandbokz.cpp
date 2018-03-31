/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokz.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBokz game.
 */

#include "ZBE/core/zbe.h"

int main(int /*argc*/, char** /*argv*/) {
    printf("Hello ZandBokz\n");
    zbe::ResourceManager<int>::getInstance();
}
