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
#include "ZBE/core/daemons/StateMachineDaemon.h"

#include "ZBE/core/events/generators/util/InputStatusManager.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"

#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/Interactionator.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/core/tools/containers/containers.h"

#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/daemons/MainLoop.h"

#include "ZBE/core/io/InputBuffer.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/Mobile.h"

#include "ZBE/entities/avatars/InteractionTester.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Resizable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

#include "ZBE/entities/Element2D.h"

#include "ZBE/events/handlers/actuators/EraserAtor.h"
#include "ZBE/events/handlers/actuators/BouncerAtor.h"
#include "ZBE/events/handlers/actuators/StateChangerAtor.h"

#include "ZBE/behaviors/Bounce.h"
#include "ZBE/behaviors/Erase.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/StateLTEraser.h"
#include "ZBE/behaviors/StateSetter.h"

#include "ZBE/events/handlers/actuators/ConditionalEraserAtor.h"
#include "ZBE/events/handlers/input/DaemonInputHandler.h"
#include "ZBE/events/handlers/input/InputToValue.h"

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/SDL/tools/SDLTimer.h"

#include "events/handlers/actuators/ItemCatcher.h"
#include "events/handlers/actuators/CustomVectorBouncerActuator.h"
#include "events/handlers/actuators/MagnetSticker.h"
#include "events/handlers/actuators/BallScorer.h"
#include "events/handlers/actuators/BallBoombizer.h"
#include "events/handlers/actuators/BrickHitStateActuator.h"

#include "events/handlers/ExitInputHandler.h"
#include "events/handlers/BroadcastIH.h"

#include "entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "entities/adaptors/BallCatorAdaptor.h"
#include "entities/adaptors/BlockConerAdaptor.h"
#include "entities/adaptors/BarConerAdaptor.h"
#include "entities/adaptors/BoardConerAdaptor.h"
#include "entities/adaptors/Element2DAnimatedSpriteAdaptor.h"
#include "entities/adaptors/Element2DDisplacedAnimatedSpriteAdaptor.h"

#include "entities/avatars/Scorer.h"

#include "entities/LifeCounter.h"

#include "daemons/items/LifeItem.h"
#include "daemons/items/BallMultiplierItem.h"
#include "daemons/items/BallAcceleratorItem.h"
#include "daemons/items/BallRadiusItem.h"
#include "daemons/items/StickyBarItem.h"

#include "daemons/ZombienoidDeathTester.h"
#include "daemons/ZombienoidLifeSubstractor.h"

#include "behaviors/InitialBallMagnetizer.h"
#include "behaviors/Demagnetizer.h"
#include "behaviors/BrickEraser.h"
#include "behaviors/XSetter.h"

#include "behaviors/builders/BallBuilder.h"
#include "behaviors/builders/ItemBuilder.h"


#include "ZBE/graphics/MultiSpriteSheet.h"
#include "graphics/SimpleSpriteSheet.h"

#include "daemons/ZBNoidResourceLoader.h"
#include "daemons/ZBNoidGameLoader.h"
#include "daemons/ZBNoidLevelLoader.h"
#include "daemons/ZBNoidLevelCleaner.h"
#include "daemons/ZBNoidLevelReset.h"

#include "builders/ZBNoidMainGameBuilder.h"
#include "builders/ZBNoidTitleBuilder.h"
#include "builders/ZBNoidWinScreenBuilder.h"
#include "builders/ZBNoidLostScreenBuilder.h"
#include "builders/ButtonBuilder.h"

#include "ZombienoidReactor.h"

#include "ZBNCfg.h"

namespace zombienoid {

using InteractionGenerator = zbe::InteractionEventGenerator<
                             ZombienoidReactor, zbe::CollisionSelector,
                             zbe::JointAE<zbe::Interactioner<ZombienoidReactor> >,
                             zbe::JointAE<zbe::Interactionator<ZombienoidReactor> > >;

using CustomBallBuilder = BallBuilder<
                          ZombienoidReactor,
                          zbe::TicketedFAE<zbe::Interactionator<ZombienoidReactor> >,
                          zbe::TicketedFAEC<zbe::AnimatedSprite>,
                          zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> >;

using CustomItemBuilder = ItemBuilder<
                          ZombienoidReactor,
                          zbe::TicketedFAE<zbe::Interactionator<ZombienoidReactor> >,
                          zbe::TicketedFAEC<zbe::AnimatedSprite>,
                          zbe::TicketedFAEC<zbe::Bouncer<2> ,zbe::Avatar> >;

} // namespace zombienoid
#endif  // ZOMBIENOID_ZBNOID_H
