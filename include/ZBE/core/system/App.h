/**
 * Copyright 2012 Batis Degryll Ludo
 * @file App.h
 * @since 2014-09-08
 * @date 2014-09-09
 * @author Ludo and Degryll
 * @brief Main application.
 */


#ifndef CORE_SYSTEM_APP_H_
#define CORE_SYSTEM_APP_H_

#include "ZBE/core/archetypes/Runnable.h"

namespace zbe {

class App : Runnable{
public:
  virtual ~App() {}

  virtual void setup() {}
  virtual void app() = 0;
  virtual void shutdown() {}

  void run();
  // TODO maybe this functions should be undefined to avoid errors
  virtual void pause() {}
  virtual void resume() {}
  virtual void restart() {}
};

}  // namespace zbe

#endif  // CORE_SYSTEM_APP_H_
