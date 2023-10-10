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
#include "ZBE/events/Reactions.h"

#include "ZandBokzInteractionSystem.h"
#include "ZandBokzCustomAvatars.h"
#include "ZandBokzReactions.h"
#include "ZandBokzBehaviors.h"
#include "ZandBokzBuilders.h"

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

    using DirectedMovil = zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D>;
    using DirectedMovilList = zbe::TicketedForwardList<DirectedMovil>;
    using DirectedMovilFunct = zbe::Funct<void, std::shared_ptr<DirectedMovil>>;

    auto& factories = zbe::RsrcStore<zbe::Factory>::getInstance();
    factories.insert("InatorListFtry", std::make_shared<zbe::SimpleGenericFtry<InatorList> >(zbe::factories::listName));
    factories.insert("InerListFtry", std::make_shared<zbe::SimpleGenericFtry<InerList> >(zbe::factories::listName));

    factories.insert("Inator2DListFtry", std::make_shared<zbe::SimpleGenericFtry<Inator2DList> >(zbe::factories::listName));
    factories.insert("Iner2DListFtry", std::make_shared<zbe::SimpleGenericFtry<Iner2DList> >(zbe::factories::listName));

    factories.insert("IEG3DFtry", std::make_shared<IEG3DFtry>());
    factories.insert("IEG2DFtry", std::make_shared<IEG2DFtry>());

    factories.insert("InerBldrFtry", std::make_shared<InerBldrFtry>());
    factories.insert("InatorBldrFtry", std::make_shared<InatorBldrFtry>());

    factories.insert("Iner2DBldrFtry", std::make_shared<Iner2DBldrFtry>());
    factories.insert("Inator2DBldrFtry", std::make_shared<Inator2DBldrFtry>());

    factories.insert("ActorBldrFtry", std::make_shared<ActorBldrFtry>(std::initializer_list<std::string>{"solid"s, "platform"s}));
    factories.insert("ReactorBldrFtry", std::make_shared<ReactorBldrFtry>(std::initializer_list<std::string>{"solid"s, "platform"s}));

    factories.insert("Actor2DBldrFtry", std::make_shared<Actor2DBldrFtry>(std::initializer_list<std::string>{"solid"s}));
    factories.insert("Reactor2DBldrFtry", std::make_shared<Reactor2DBldrFtry>(std::initializer_list<std::string>{"solid"s}));

    factories.insert("ShapeMSphereBldrFtry", std::make_shared<ShapeMSphereBldrFtry>());
    factories.insert("ShapeMTriangleBldrFtry", std::make_shared<ShapeMTriangleBldrFtry>());

    factories.insert("ShapeTriangle2DBldrFtry", std::make_shared<ShapeTriangle2DBldrFtry>());
    factories.insert("ShapeMPoint2DBldrFtry", std::make_shared<ShapeMPoint2DBldrFtry>());

    factories.insert("MovingSphereAvtBldrFtry", std::make_shared<MovingSphereAvtBldrFtry>());
    factories.insert("MovingTriangle3DAvtBldrFtry", std::make_shared<zbe::MovingTriangle3DAvtBldrFtry>());

    factories.insert("BehaviorEntityBldrFtry2V", std::make_shared<zbe::BehaviorEntityBldrFtry<zbe::Vector3D, zbe::Vector3D>>());
    factories.insert("BehaviorEntityBldrFtry3V", std::make_shared<zbe::BehaviorEntityBldrFtry<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D>>());

    factories.insert("FunctOverAvtList2VDmnFtry", std::make_shared<zbe::FunctOverAvtListDmnFtry<MovilFunct, MovilList>>());
    factories.insert("FunctOverAvtList3VDmnFtry", std::make_shared<zbe::FunctOverAvtListDmnFtry<DirectedMovilFunct, DirectedMovilList>>());

    factories.insert("CopyVec2Mod2VFtry", std::make_shared<zbe::BuildCopyVectModuleBldrFtry<2, zbe::Vector3D, zbe::Vector3D>>());
    factories.insert("CopyVec2Mod3VFtry", std::make_shared<zbe::BuildCopyVectModuleBldrFtry<2, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D>>());

    factories.insert("CopyVec12VFtry", std::make_shared<zbe::GenericFtry<zbe::Funct<std::shared_ptr<zbe::Value<zbe::Vector3D>>, std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>>>,zbe::BuildCopyValueBldr<zbe::Vector3D, 1, zbe::Vector3D, zbe::Vector3D> > >(zbe::factories::functionName, "BuildCopyValueBldr"));
    factories.insert("CopyVec13VFtry", std::make_shared<zbe::GenericFtry<zbe::Funct<std::shared_ptr<zbe::Value<zbe::Vector3D>>, std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D>>>,zbe::BuildCopyValueBldr<zbe::Vector3D, 1, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D> > >(zbe::factories::functionName, "BuildCopyValueBldr"));
    factories.insert("CopyVec33VFtry", std::make_shared<zbe::GenericFtry<zbe::Funct<std::shared_ptr<zbe::Value<zbe::Vector3D>>, std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D>>>,zbe::BuildCopyValueBldr<zbe::Vector3D, 3, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D> > >(zbe::factories::functionName, "BuildCopyValueBldr"));

    using ZBKEntityEraserReactionBldr = zbe::EntityEraserReactionBldr<zbe::CollisionData3D, Solid>;
    using ZBKEntityEraserReactionBldrFunct = zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::CollisionData3D, Solid>>,std::shared_ptr<zbe::Entity>>;

    factories.insert("EntityEraserReactionBldrFtry", std::make_shared<zbe::GenericFtry<ZBKEntityEraserReactionBldrFunct, ZBKEntityEraserReactionBldr>>(zbe::factories::functionName, "EntityEraserReactionBldr"));

    factories.insert("ReverseDirectionReactionBldrFtry", std::make_shared<ReverseDirectionReactionBldrFtry<zbe::CollisionData3D, Solid>>());
    factories.insert("BounceReactionBldrFtry", std::make_shared<BounceReactionBldrFtry<zbe::CollisionData3D, Solid>>());
    factories.insert("AttachRepositionReactionBldrFtry", std::make_shared<AttachRepositionReactionBldrFtry>());
    factories.insert("AttachRedirectionReactionBldrFtry", std::make_shared<AttachRedirectionReactionBldrFtry>());

    factories.insert("GravityMotion3DFtry", std::make_shared<GravityMotion3DFtry>());
    factories.insert("OrientationRelativeVelSetterFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<double, double, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D >, OrientationRelativeVelSetter>>("Behavior", "OrientationRelativeVelSetter"));
    factories.insert("OrientationRelative2DVelSetterFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<double, double, zbe::Vector2D, zbe::Vector2D >, OrientationRelative2DVelSetter>>("Behavior", "OrientationRelative2DVelSetter"));
    factories.insert("Vec3DAccumBhvFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D >, Vec3DAccumBhv>>("Behavior", "Vec3DAccumBhv"));
    factories.insert("CopyV3DIfNotZeroBhvFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<zbe::Vector3D, zbe::Vector3D >, CopyV3DIfNotZeroBhv>>("Behavior", "CopyV3DIfNotZeroBhv"));
    factories.insert("ProjectV3DOnPlaneBhvFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<zbe::Vector2D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D >, ProjectV3DOnPlaneBhv>>("Behavior", "ProjectV3DOnPlaneBhv"));
    factories.insert("CalculeOrientationBhv", std::make_shared<zbe::GenericFtry<zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D , zbe::Vector3D >, CalculeOrientationBhv>>("Behavior", "CalculeOrientationBhv"));
    factories.insert("KeepDistanceBhvFtry", std::make_shared<zbe::GenericFtry<zbe::Behavior<double, zbe::Vector3D, zbe::Vector3D >, KeepDistanceBhv>>("Behavior", "KeepDistanceBhv"));

    factories.insert("TicketActivatorPlatformRctBldrFtry", std::make_shared<zbe::TicketActivatorRctBldrFtry<zbe::CollisionData3D, Platform>>());
    factories.insert("TicketDeactivatorPlatformRctBldrFtry", std::make_shared<zbe::TicketDeactivatorRctBldrFtry<zbe::CollisionData3D, Platform>>());

    factories.insert("TicketActivatorSolidRctBldrFtry", std::make_shared<zbe::TicketActivatorRctBldrFtry<zbe::CollisionData2D, Solid>>());
    factories.insert("TicketDeactivatorSolidRctBldrFtry", std::make_shared<zbe::TicketDeactivatorRctBldrFtry<zbe::CollisionData2D, Solid>>());

    factories.insert("StoreValuesPlatformRctBldrFtry", std::make_shared<zbe::StoreValuesRctBldrFtry<zbe::CollisionData3D, zbe::Vector3D, 3>>());

    factories.insert("MultiPlatformRctBldrFtry", std::make_shared<zbe::MultiRctBldrFtry<zbe::CollisionData3D, Platform>>());
    factories.insert("MultiSolid2DRctBldrFtry", std::make_shared<zbe::MultiRctBldrFtry<zbe::CollisionData2D, Solid>>());
    factories.insert("PrintfSolid2DRctBldrFtry", std::make_shared<zbe::PrintfRctBldrFtry<zbe::CollisionData2D, Solid>>());
    factories.insert("Triangle3Dto2DCacheBldrFtry", std::make_shared<Triangle3Dto2DCacheBldrFtry>());

    factories.insert("PlatformTraitBldrFtry", std::make_shared<PlatformTraitBldrFtry>());

    factories.insert("DoubleTwoV3DAvtBldrFtry", std::make_shared<zbe::MAvatarBldrFtry<double, zbe::Vector3D, zbe::Vector3D>>());
  }

};

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZFACTORIES_H_
