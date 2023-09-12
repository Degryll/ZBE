/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.h
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */

#ifndef ZBE_FACTORIES_BASEFACTORIES_H_
#define ZBE_FACTORIES_BASEFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/RsrcFtry.h"
#include "ZBE/factories/implementations/entities/EntityFtry.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopExitFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopFtry.h"
#include "ZBE/factories/implementations/daemons/MasterDmnFtry.h"
#include "ZBE/factories/implementations/daemons/StateMachineDmnFtry.h"
#include "ZBE/factories/implementations/daemons/RsrcFolderLoaderDmnFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/BroadcastIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonClickIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/InputToValueFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonRecurrentTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/StateChangerAtorFtry.h"
#include "ZBE/factories/implementations/events/generators/TimeEventGnFtry.h"

#include "ZBE/events/handlers/input/TicketTogglerIH.h"
#include "ZBE/events/handlers/input/ParametricActivatorIH.h"
#include "ZBE/events/handlers/input/ActivatorIH.h"
#include "ZBE/events/handlers/input/KeyDownTicketEnablerIH.h"
#include "ZBE/events/handlers/input/CommonInputHandlers.h"
#include "ZBE/events/handlers/input/InputHandlers.h"
#include "ZBE/events/handlers/time/EntityEraser.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/daemons/OnceDaemon.h"
#include "ZBE/core/daemons/VoidDaemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/entities/builders/builders.h"

#include "ZBE/behaviors/SineOscillator.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/Rotation.h"
#include "ZBE/behaviors/Behaviors.h"
#include "ZBE/behaviors/BulletCreatorBhv.h"

#include "ZBE/creators/BulletCreator.h"

namespace zbe {

/** \brief Daemon capable of load all base factories.
 */
class ZBEAPI BaseFactories : public Daemon {
public:
  ~BaseFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    auto& factories = RsrcStore<Factory>::getInstance();

    RsrcStore<ContextTime>::getInstance().insert("ContextTime.DEFAULT", SysTime::getInstance());
    RsrcStore<Daemon>::getInstance().insert("Daemon.DEFAULT", std::make_shared<VoidDaemon>());

    // --- Builders
    factories.insert("EntityBldrFtry", std::make_shared<EntityBldrFtry>());
    factories.insert("EntitySetterFtry", std::make_shared<EntitySetterFtry>());

    // --- Entities
    factories.insert("EntityFtry", std::make_shared<EntityFtry>());

    // --- Values
    factories.insert("SimpleValueFtry", std::make_shared<SimpleValueFtry>());

    // --- Daemons
    factories.insert("MainLoopExitFtry", std::make_shared<MainLoopExitFtry>());
    factories.insert("MainLoopFtry", std::make_shared<MainLoopFtry>());
    factories.insert("MasterDmnFtry", std::make_shared<MasterDmnFtry>());
    factories.insert("OnceDaemonFtry", std::make_shared<OnceDaemonFtry>());
    factories.insert("StateMachineDmnFtry", std::make_shared<StateMachineDmnFtry>());
    factories.insert("RsrcFolderLoaderDmnFtry", std::make_shared<RsrcFolderLoaderDmnFtry>());

    // --- Behaviors
    factories.insert("SineOscillatorFFtry", std::make_shared<SineOscillatorFFtry>());
    factories.insert("SineOscillatorV3DFtry", std::make_shared<SineOscillatorV3DFtry>());
    factories.insert("FixedUniformLinearMotion3DFtry", std::make_shared<FixedUniformLinearMotion3DFtry>());
    factories.insert("RelativeUniformLinearMotion3DFtry", std::make_shared<RelativeUniformLinearMotion3DFtry>());
    factories.insert("UniformLinearMotion3DFtry", std::make_shared<GenericFtry<Behavior<Vector3D, Vector3D>, UniformLinearMotion3D>>("Behavior", "UniformLinearMotion3D"));
    factories.insert("UniformLinearMotion2DFtry", std::make_shared<GenericFtry<Behavior<Vector2D, Vector2D>, UniformLinearMotion2D>>("Behavior", "UniformLinearMotion2D"));
    factories.insert("UniformLinearMotion2DOnPlane", std::make_shared<GenericFtry<Behavior<Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D >, UniformLinearMotion2DOnPlane>>("Behavior", "UniformLinearMotion2DOnPlane"));
    factories.insert("Rotation3DFtry", std::make_shared<Rotation3DFtry>());
    factories.insert("ExcentricalRotation3DFtry", std::make_shared<ExcentricalRotation3DFtry>());
    factories.insert("LimitedExcentricalRotation3DFtry", std::make_shared<LimitedExcentricalRotation3DFtry>());
    factories.insert("BulletCreatorBhvFtry", std::make_shared<BulletCreatorBhvFtry>());
    factories.insert("TicketDeactivatorBvrFtry", std::make_shared<TicketDeactivatorBvrFtry>());
    factories.insert("TicketActivatorBvrFtry", std::make_shared<TicketActivatorBvrFtry>());
    factories.insert("Vector3DSetterFixedBvrFtry", std::make_shared<ValueSetterFixedBvrFtry<Vector3D>>());
    factories.insert("CopyVectorResizedBvrFtry", std::make_shared<GenericFtry<Behavior<Vector3D, Vector3D, double>, CopyVectorResizedBvr>>("Behavior", "CopyVectorResizedBvr"));

    // --- Events
    // --- --- Event generators
    factories.insert("TimeEventGnFtry", std::make_shared<TimeEventGnFtry>());
    factories.insert("InputEventGeneratorFtry", std::make_shared<InputEventGeneratorFtry>());


    // --- --- Event input handlers
    factories.insert("BroadcastIHFtry", std::make_shared<BroadcastIHFtry>());
    factories.insert("DaemonClickIHFtry", std::make_shared<DaemonClickIHFtry>());
    factories.insert("DaemonIHFtry", std::make_shared<DaemonIHFtry>());
    factories.insert("InputToValueFtry", std::make_shared<InputToValueFtry>());
    factories.insert("TicketTogglerIHFtry", std::make_shared<TicketTogglerIHFtry>());
    factories.insert("ParametricActivatorIHFtry", std::make_shared<ParametricActivatorIHFtry>());
    factories.insert("ActivatorIHFtry", std::make_shared<ActivatorIHFtry>());
    factories.insert("KeyDownTicketEnablerIHFtry", std::make_shared<KeyDownTicketEnablerIHFtry>());
    factories.insert("V3DKeyValueSetterIHFtry", std::make_shared<KeyValueSetterIHFtry<Vector3D>>());
    factories.insert("DoubleKeyValueSetterIHFtry", std::make_shared<KeyValueSetterIHFtry<double>>());
    factories.insert("Add2DVelIHBldrFtry", std::make_shared<AddVelIHBldrFtry<2>>());


    // --- --- Event time handlers
    factories.insert("DaemonRecurrentTimeHandlerFtry", std::make_shared<DaemonRecurrentTimeHandlerFtry>());
    factories.insert("DaemonTimeHandlerFtry", std::make_shared<DaemonTimeHandlerFtry>());
    factories.insert("TicketEraserFtry", std::make_shared<TicketEraserFtry>());
    factories.insert("EntityEraserTHFtry", std::make_shared<EntityEraserTHFtry>());
    factories.insert("EntityEraserTHBldrFtry", std::make_shared<GenericFtry<Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>, EntityEraserTHBldr> >(factories::functionName, "EntityEraserTHBldr"));
    factories.insert("EntityTimerBldrFtry", std::make_shared<EntityTimerBldrFtry>());


    // --- --- creators
    factories.insert("BulletCreatorFtry", std::make_shared<BulletCreatorFtry>());

    // --- Others
    factories.insert("RsrcFtry", std::make_shared<RsrcFtry>());


    // RsrcFolderLoaderDmnFtry -> BASE
    // MainLoopFtry -> BASE
    // MainLoopExitFtry -> BASE
    // ValueUFtry -> BASE (ValueIFtry, ValueFFtry, ...)
    //
    // TimeEventGnFtry -> BASE
    // DaemonTimeHandlerFtry -> BASE
    //
    // BehaviorDmnFtry -> BASE
  }

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_BASEFACTORIES_H_
