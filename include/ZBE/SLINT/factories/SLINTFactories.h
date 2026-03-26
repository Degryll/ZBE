/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLFactories.h
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#ifndef ZBE_SLINT_FACTORIES_SLINTFACTORIES_H_
#define ZBE_SLINT_FACTORIES_SLINTFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"

#include "ZBE/SLINT/SLINTSDLOGLWindow.h"
#include "ZBE/SLINT/daemons/SLINTPostDrawDaemon.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class SLINTFactories : public Daemon {
public:
  ~SLINTFactories() = default;

  /** \brief It will Load the factories calling the load method.
  */
  void run() override {
    //load();
  };

  /** \brief It loads all factories.
  */
  static void load(RsrcStore<Factory>& factories) {
    //auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("SLINTSDLOGLWindowFtry", std::make_shared<SLINTSDLOGLWindowFtry>());
    factories.insert("SLINTPostDrawDaemonFtry", std::make_shared<SLINTPostDrawDaemonFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_SLINT_FACTORIES_SLINTFACTORIES_H_
