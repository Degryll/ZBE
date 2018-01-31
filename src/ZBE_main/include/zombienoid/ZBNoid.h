/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ButtonBuilder.h
 * @since 2017-12-09
 * @date 2017-12-09
 * @author Degryll Ludo Batis
 * @brief ZBNoid button builder.
 */

#ifndef ZOMBIENOID_ZBNOID_H
#define ZOMBIENOID_ZBNOID_H

#include "ZBE/core/zbe.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/daemons/MainLoopExit.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"
#include "ZBE/core/daemons/StateMachineDaemon.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/core/tools/containers/containers.h"

#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/MainLoop.h"

#include "ZBE/core/io/InputBuffer.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/Mobile.h"

#include "ZBE/entities/avatars/InteractionTester.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Resizable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

#include "ZBE/entities/Element2D.h"

#include "ZBE/events/handlers/actuators/EraserActuator.h"
#include "ZBE/events/handlers/actuators/BouncerActuator.h"
#include "ZBE/events/handlers/actuators/StateChangerActuator.h"

#include "ZBE/behaviors/Bounce.h"
#include "ZBE/behaviors/Erase.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/StateLTEraser.h"
#include "ZBE/behaviors/StateSetter.h"

#include "ZBE/events/handlers/actuators/ConditionalEraserActuator.h"
#include "ZBE/events/handlers/input/DaemonInputHandler.h"
#include "ZBE/events/handlers/input/InputToValue.h"

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/SDL/tools/SDLTimer.h"

#include "zombienoid/events/handlers/actuators/ItemCatcher.h"
#include "zombienoid/events/handlers/actuators/CustomVectorBouncerActuator.h"
#include "zombienoid/events/handlers/actuators/MagnetSticker.h"
#include "zombienoid/events/handlers/actuators/BallScorer.h"
#include "zombienoid/events/handlers/actuators/BallBoombizer.h"
#include "zombienoid/events/handlers/actuators/BrickHitStateActuator.h"

#include "zombienoid/events/handlers/ExitInputHandler.h"
#include "zombienoid/events/handlers/BroadcastIH.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"
#include "zombienoid/entities/adaptors/BlockConerAdaptor.h"
#include "zombienoid/entities/adaptors/BarConerAdaptor.h"
#include "zombienoid/entities/adaptors/BoardConerAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DDisplacedAnimatedSpriteAdaptor.h"

#include "zombienoid/entities/avatars/Scorer.h"

#include "zombienoid/entities/LifeCounter.h"

#include "zombienoid/daemons/items/LifeItem.h"
#include "zombienoid/daemons/items/BallMultiplierItem.h"
#include "zombienoid/daemons/items/BallAcceleratorItem.h"
#include "zombienoid/daemons/items/BallRadiusItem.h"
#include "zombienoid/daemons/items/StickyBarItem.h"

#include "zombienoid/daemons/ZombienoidDeathTester.h"
#include "zombienoid/daemons/ZombienoidLifeSubstractor.h"

#include "zombienoid/behaviors/Demagnetizer.h"
#include "zombienoid/behaviors/BrickEraser.h"
#include "zombienoid/behaviors/XSetter.h"

#include "zombienoid/behaviors/builders/BallBuilder.h"
#include "zombienoid/behaviors/builders/ItemBuilder.h"


#include "zombienoid/graphics/MultiSpriteSheet.h"
#include "zombienoid/graphics/SimpleSpriteSheet.h"

#include "zombienoid/daemons/ZBNoidResourceLoader.h"
#include "zombienoid/daemons/ZBNoidGameLoader.h"
#include "zombienoid/daemons/ZBNoidLevelLoader.h"
#include "zombienoid/daemons/ZBNoidLevelCleaner.h"
#include "zombienoid/daemons/ZBNoidLevelReset.h"

#include "zombienoid/builders/ZBNoidMainGameBuilder.h"
#include "zombienoid/builders/ZBNoidTitleBuilder.h"
#include "zombienoid/builders/ZBNoidWinScreenBuilder.h"
#include "zombienoid/builders/ZBNoidLostScreenBuilder.h"
#include "zombienoid/builders/ButtonBuilder.h"

#include "zombienoid/ZombienoidReactor.h"

#include "zombienoid/ZBNCfg.h"

namespace zombienoid {

using InteractionGenerator = zbe::InteractionEventGenerator<
                             ZombienoidReactor, zbe::CollisionSelector<ZombienoidReactor>,
                             zbe::JointAE<zbe::Collisioner<ZombienoidReactor> >,
                             zbe::JointAE<zbe::Collisionator<ZombienoidReactor> > >;

using CustomBallBuilder = BallBuilder<
                          ZombienoidReactor,
                          zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> >,
                          zbe::TicketedFAEC<zbe::AnimatedSprite>,
                          zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> >;

using CustomItemBuilder = ItemBuilder<
                          ZombienoidReactor,
                          zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> >,
                          zbe::TicketedFAEC<zbe::AnimatedSprite>,
                          zbe::TicketedFAEC<zbe::Movable<2> > >;

} // namespace zombienoid
#endif  // ZOMBIENOID_ZBNOID_H
