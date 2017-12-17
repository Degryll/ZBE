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
 #include "ZBE/core/daemons/Punishers.h"
 #include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"

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

 #include "ZBE/events/handlers/actuators/ConditionalEraserActuator.h"
 #include "ZBE/events/handlers/input/DaemonInputHandler.h"
 #include "ZBE/events/handlers/input/InputToValue.h"

 #include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
 #include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

 #include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
 #include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

 #include "ZBE/SDL/system/SDLWindow.h"
 #include "ZBE/SDL/system/SDLEventDispatcher.h"

 #include "ZBE/SDL/system/SDLImageStore.h"
 #include "ZBE/SDL/system/SDLTextFontStore.h"

 #include "ZBE/SDL/tools/SDLTimer.h"

 #include "zombienoid/events/handlers/actuators/ItemCatcher.h"
 #include "zombienoid/events/handlers/actuators/CustomVectorBouncerActuator.h"
 #include "zombienoid/events/handlers/actuators/MagnetSticker.h"
 #include "zombienoid/events/handlers/actuators/BallScorer.h"
 #include "zombienoid/events/handlers/actuators/BallBoombizer.h"
 #include "zombienoid/events/handlers/actuators/BrickHitStateActuator.h"

 #include "zombienoid/events/handlers/ExitInputHandler.h"

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

 #include "zombienoid/ZombienoidReactor.h"

 #include "zombienoid/graphics/MultiSpriteSheet.h"
 #include "zombienoid/graphics/SimpleSpriteSheet.h"

 namespace zombienoid {

using InteractionGenerator = zbe::InteractionEventGenerator<
  ZombienoidReactor, zbe::CollisionSelector<ZombienoidReactor>,
  zbe::JointAE<zbe::Collisioner<ZombienoidReactor> >,
  zbe::JointAE<zbe::Collisionator<ZombienoidReactor> > >;

using CustomBallBuilder = BallBuilder<
  ZombienoidReactor,
  zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> >,
  zbe::TicketedFAEC<zbe::AnimatedSprite>,
  zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable> >;

using CustomItemBuilder = ItemBuilder<
  ZombienoidReactor,
  zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> >,
  zbe::TicketedFAEC<zbe::AnimatedSprite>,
  zbe::TicketedFAEC<zbe::Movable<2> > >;

static const int64_t GAME_EXIT_VALUE = 0;
static const int64_t GAME_START_VALUE = 1;

enum {
   WIDTH = 1024,
   HEIGHT = 768,
   MARGIN = 32,
   NBALLS = 1,
   MAXBALLS = 1000,

   P_ACCUM_TIME = zbe::SECOND,
   P_EXTRA_ACCUM_TIME = zbe::SECOND / 4,
   POINTS_MULTIPLIER = 10,

   ITEM_TYPES = 12,
   ITEM_FALL_SPEED = 100,
   ITEM_WIDTH = 32,
   ITEM_HEIGHT = 64,

   ITEM_POINTS = 50,
   ITEM_POINTS_100 = 100,
   ITEM_POINTS_200 = 200,
   ITEM_POINTS_500 = 500,
   ITEM_POINTS_999 = 999,
   ITEM_POINTS_N5000 = -5000,

   ITEM_STICKY_TIME = zbe::SECOND*6,

   NBRICKS_X = 13,
   NBRICKS_Y = 11,
   BRICK_WIDTH = 64,
   BRICK_HEIGHT = 32,
   BRICKS_X_MARGIN = 64,
   BRICKS_Y_MARGIN = 64,
   BRICK_MAX_LEVEL = 3,
   BRICK_ITEM_SUCCES = 1,
   BRICK_ITEM_TOTAL = 10,
   SPECIAL_STATES = 2,

   BRICK_BOOMBIZER_STATE = 16,
   BALL_BOOM_STATE = 1,
   BOOM_TIME = zbe::SECOND*5,

   BALL_SIZE = 32,
   BALL_V_X = -300,
   BALL_V_Y = -300,

   BAR_I_WIDTH = 322,
   BAR_HEIGHT = 32,
   BAR_MARGIN = 32,

   TEXT_F_SIZE = 32,
   TEXT_B_SIZE = 18,
   TEXT_CHAR_W = 16,
   TEXT_CHAR_H = 30,

   LIFE_BOX_CHARS = 2,
   POINT_BOX_CHARS = 10,
   TEXT_BOX_MARGIN = 6
 };

 // Ticket ids.
 const int COLLISION_TICKET = zbe::SysIdGenerator::getId();
 const int DRAW_TICKET = zbe::SysIdGenerator::getId();
 const int BEHAVE_TICKET = zbe::SysIdGenerator::getId();
 const int MAGNET_TICKET = zbe::SysIdGenerator::getId();
 const int BOOM_TEXTSPRITE_TICKET = zbe::SysIdGenerator::getId();
 // Event ids.
 const int INPUTEVENT = zbe::SysIdGenerator::getId();
 const int TIMEEVENT = zbe::SysIdGenerator::getId();
 const int COLLISIONEVENT = zbe::SysIdGenerator::getId();
 // List joints for collisiontors, sprites and text sprites.
 const int CTS_JOINT = zbe::SysIdGenerator::getId();
 const int AS_JOINT = zbe::SysIdGenerator::getId();
 const int ATS_JOINT = zbe::SysIdGenerator::getId();
 // Actuators list.
 const int BOARD_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 const int ITEM_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 const int BRICK_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 const int BALL_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 const int EXPLOSION_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 const int BAR_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
 // Behaviors list
 const int BRICK_LIST = zbe::SysIdGenerator::getId();
 const int BALLSPAWN_LIST = zbe::SysIdGenerator::getId();
 const int BALL_LIST = zbe::SysIdGenerator::getId();
 const int ITEM_LIST = zbe::SysIdGenerator::getId();
 const int MOUSE_CONTROL_LIST = zbe::SysIdGenerator::getId();
 const int DEMAGNETIZE_LIST = zbe::SysIdGenerator::getId();
 const int EXPLSION_ERASE_LIST = zbe::SysIdGenerator::getId();
 // Collisionables list
 const int BRICK_COLLISIONER_LIST = zbe::SysIdGenerator::getId();
 // Collisionables list
 const int BOOM_COLLISIONATOR_LIST = zbe::SysIdGenerator::getId();
 // Collisionables list joints
 const int BALL_CBS_JOINT = zbe::SysIdGenerator::getId();
 const int ITEM_CBS_JOINT = zbe::SysIdGenerator::getId();
 // AnimatedSprite list
 const int BOOM_AS_LIST = zbe::SysIdGenerator::getId();
 // TextSprite list
 const int TEXT_TS_LIST = zbe::SysIdGenerator::getId();
 // Sprite sheet ids
 const int ITEM_SS = zbe::SysIdGenerator::getId();
 const int BRICK_SS = zbe::SysIdGenerator::getId();
 const int BALL_SS = zbe::SysIdGenerator::getId();
 const int EXPLSION_SS = zbe::SysIdGenerator::getId();
 const int BAR_SS = zbe::SysIdGenerator::getId();
 const int BOARD_SS = zbe::SysIdGenerator::getId();

 }

 #endif  // ZOMBIENOID_ZBNOID_H
