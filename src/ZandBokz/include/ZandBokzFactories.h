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
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/events/interactionSystem.h"
#include "ZBE/entities/builders/builders.h"

#include "ZandBokzInteractionSystem.h"
#include "ZandBokzCustomAvatars.h"


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
  }

  /** \brief It loads all factories.
  */
  static void load() {
    using namespace std::string_literals;
    auto& factories = zbe::RsrcStore<zbe::Factory>::getInstance();
    factories.insert("InatorListFtry", std::make_shared<zbe::SimpleGenericFtry<InatorList> >(zbe::factories::listName));
    factories.insert("InerListFtry", std::make_shared<zbe::SimpleGenericFtry<InerList> >(zbe::factories::listName));

    factories.insert("IEGFtry", std::make_shared<IEGFtry>());

    factories.insert("InerBldrFtry", std::make_shared<InerBldrFtry>());
    factories.insert("InatorBldrFtry", std::make_shared<InatorBldrFtry>());

    factories.insert("ActorBldrFtry", std::make_shared<ActorBldrFtry>(std::initializer_list<std::string>{"solid"s}));
    factories.insert("ReactorBldrFtry", std::make_shared<ReactorBldrFtry>(std::initializer_list<std::string>{"solid"s}));
    factories.insert("ShapeBldrFtry", std::make_shared<ShapeBldrFtry>());

    factories.insert("MovingSphereAvtBldrFtry", std::make_shared<MovingSphereAvtBldrFtry>());

  }

};

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZFACTORIES_H_
