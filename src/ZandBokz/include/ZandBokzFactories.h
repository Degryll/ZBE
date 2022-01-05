/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.h
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */


#ifndef ZANDBOKZ_ZANDBOKZFACTORIES_H_
#define ZANDBOKZ_ZANDBOKZFACTORIES_H_

#include <string>
#include <memory>

#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/events/interactionSystem.h"
#include "ZBE/entities/builders/builders.h"

#include "ZandBokz/include/ZandBokzInteractionSystem.h"


namespace zandbokz {

/** \brief Daemon capable of load all base factories.
 */
class ZandBokzFactories : public zbe::Daemon {
public:
  ~ZandBokzFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    auto& factories = zbe::RsrcStore<zbe::Factory>::getInstance();

    factories.insert("ZandBokzIEGFtry", std::make_shared<ZandBokzIEGFtry>());
    // factories.insert("InteractionerBldrFtry", ...);
    // factories.insert("InteractionatorBldrFtry", ...);
    // factories.insert("EntityBldrFtry", ...);
    // factories.insert("ShapeBldrFtry", ...);
    // factories.insert("ReactorBldrFtry", ...);
    // factories.insert("ActorBldrFtry", ...);
  }

};

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZFACTORIES_H_
