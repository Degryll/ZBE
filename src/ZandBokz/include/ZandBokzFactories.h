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
#include "ZandBokzReactions.h"

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

    //using InatorList = zbe::TicketedForwardList<Inator>;
    using Movil = zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>;
    using MovilList = zbe::TicketedForwardList<Movil>;
    using MovilFunct = zbe::Funct<void, std::shared_ptr<Movil>>;

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

    factories.insert("BehaviorEntityBldrFtry", std::make_shared<zbe::BehaviorEntityBldrFtry<zbe::Vector3D, zbe::Vector3D>>());

    factories.insert("FunctOverAvtListDmnFtry", std::make_shared<zbe::FunctOverAvtListDmnFtry<MovilFunct, MovilList>>());

    //factories.insert("CopyVelFtry", std::make_shared<zbe::GenericFtry<zbe::Funct<std::shared_ptr<zbe::Value<zbe::Vector3D>>, std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>>>, zbe::BuildCopyValueBldr<zbe::Vector3D, 2, zbe::Vector3D, zbe::Vector3D> > >(zbe::factories::functionName, "BuildCopyValueBldr"));
    factories.insert("CopyVelFtry", std::make_shared<zbe::BuildCopyVectModuleBldrFtry<2, zbe::Vector3D, zbe::Vector3D>>());

    factories.insert("CopyPosFtry", std::make_shared<zbe::GenericFtry<zbe::Funct<std::shared_ptr<zbe::Value<zbe::Vector3D>>, std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>>>,zbe::BuildCopyValueBldr<zbe::Vector3D, 1, zbe::Vector3D, zbe::Vector3D> > >(zbe::factories::functionName, "BuildCopyValueBldr"));
//Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>
//Funct<std::shared_ptr<Funct<void, NewCollisionData<3>, Solid> >, std::shared_ptr<zbe::Entity> >
    using ZBKEntityEraserReactionBldr = zbe::EntityEraserReactionBldr<zbe::CollisionData3D, Solid>;
    using ZBKEntityEraserReactionBldrFunct = zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::CollisionData3D, Solid>>,std::shared_ptr<zbe::Entity>>;
//std::shared_ptr<ZBKEntityEraserReactionBldrFunct> blabla =  std::make_shared<ZBKEntityEraserReactionBldr>();
    factories.insert("EntityEraserReactionBldrFtry", std::make_shared<zbe::GenericFtry<ZBKEntityEraserReactionBldrFunct, ZBKEntityEraserReactionBldr>>(zbe::factories::functionName, "EntityEraserReactionBldr"));
    
    factories.insert("ReverseDirectionReactionBldrFtry", std::make_shared<ReverseDirectionReactionBldrFtry<zbe::CollisionData3D, Solid>>());
    factories.insert("BounceReactionBldrFtry", std::make_shared<BounceReactionBldrFtry<zbe::CollisionData3D, Solid>>());
  }

};

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZFACTORIES_H_
