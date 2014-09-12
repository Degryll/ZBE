/**
 * Copyright 2012 Batis Degryll Ludo
 * @file App.cpp
 * @since 2014-09-08
 * @date 2014-09-08
 * @author Ludo and Degryll
 * @brief Main application.
 */

#include "ZBE/core/system/App.h"

namespace zbe {

  void App::run() {
    setup();
    app();
    shutdown();
  }

}  // namespace zbe
