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

 #include "zombienoid/daemons/ZBNoidResourceLoader.h"

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
   BRICK_ITEM_TOTAL = 1,
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

const int64_t GAME_EXIT_VALUE = 0;
const int64_t GAME_START_VALUE = 1;
const char ZBENOID_WINDOW_TITLE[] = "ZBNoid";

const int64_t INITIAL_LIFES = 3;
const double BALL_SIZE_MIN = 0.25;
const double BALL_SIZE_MAX = 2;
const double BALL_SIZE_STEP = 0.25;
const double BALL_XPLODE_RATIO = 64.0;

const int BALL_MULTIPLIER_AMOUNT = 2;
const double BALL_MULTIPLIER_ANGLES[BALL_MULTIPLIER_AMOUNT] = {-30.0, 30.0};
const double BALL_ACCELERATION_RATIO = 3.0/2.0;
const double BALL_DECELERATION_RATIO = 1.0/BALL_ACCELERATION_RATIO;

const int BAR_NORMAL_STATE = 0;
const int BAR_STICKY_STATE = 1;
const int LIFE_ITEM_AMOUNT = 1;

const size_t RSRC_ID_DICT_SIZE = 20;

// BOARD
// -GRAPHICS
const int64_t BOARD_FRAMES = 8;
const zbe::Vector2D BOARD_DISPLACEMENT = zbe::Vector2D{800.0, 0.0};
const int64_t BOARD_FRAMETIME = 16000;
const zbe::Region2D BOARD_REGION = zbe::Region2D({0.0, 0.0}, {800.0, 600.0});
const int64_t BOARD_STATES = 2;
const zbe::Vector2D BOARD_SPRITE_DISPLACEMENT = zbe::Vector2D{0, 0};

// -SIZE
const double BOARD_WIDTH = WIDTH - (MARGIN * 2);
const double BOARD_HEIGHT = HEIGHT /*- (MARGIN * 2)*/;
const double SECURITY_MARGIN = MARGIN - BALL_SIZE_MAX * BALL_SIZE;
const double SECURITY_WIDTH = WIDTH - (SECURITY_MARGIN * 2);
const double SECURITY_HEIGHT = HEIGHT * 2;

// ITEM
// -GRAPHICS
const int64_t ITEM_FRAMES = 1;
const zbe::Vector2D ITEM_DISPLACEMENT = zbe::Vector2D{0.0, 0.0};
const int64_t ITEM_FRAMETIME = 1000;
const zbe::Region2D ITEM_REGION = zbe::Region2D({0.0, 0.0}, {32.0, 64.0});

// BRICK HIT ACTUATOR
const int64_t BRK_HIT_INCREMENT = -1;
const int64_t BRK_HIT_HIGHLIMIT = 10;
const int64_t BRK_HIT_LOWLIMIT = 0;
const int64_t BRK_HIT_DEADVALUE = BRK_HIT_LOWLIMIT - 1;

// BAR
// -GRAPHICS
const int64_t BAR_FRAMES = 1;
const zbe::Vector2D BAR_DISPLACEMENT = zbe::Vector2D{0.0, 0.0};
const int64_t BAR_FRAMETIME = 1000;
const zbe::Region2D BAR_REGION = zbe::Region2D({0.0, 0.0}, {161.0, 32.0});
const int64_t BAR_STATES = 2;

// BALL
// -GRAPHICS
const int64_t BALL_FRAMES = 1;
const zbe::Vector2D BALL_DISPLACEMENT = zbe::Vector2D{0.0, 0.0};
const int64_t BALL_FRAMETIME = 1000;
const zbe::Region2D BALL_REGION = zbe::Region2D({0.0, 0.0}, {64.0, 64.0});
const int64_t BALL_STATES = 2;

// EXPLOSION
// -GRAPHICS
const int64_t EXPLOSION_FRAMES = 6;
const zbe::Vector2D EXPLOSION_DISPLACEMENT = zbe::Vector2D{256.0, 0.0};
const int64_t EXPLOSION_FRAMETIME = zbe::SECOND/12;
const zbe::Region2D EXPLOSION_REGION = zbe::Region2D({0.0, 0.0}, {256.0, 256.0});
const int64_t EXPLOSION_STATES = 1;

class ZBNCfg {
public:
  // Ticket ids.
  static uint64_t COLLISION_TICKET;
  static uint64_t DRAW_TICKET;
  static uint64_t BEHAVE_TICKET;
  static uint64_t MAGNET_TICKET;
  static uint64_t BOOM_TEXTSPRITE_TICKET;
  static uint64_t STICKY_LIST_TICKET;
  // Event ids.
  static uint64_t INPUTEVENT;
  static uint64_t TIMEEVENT;
  static uint64_t COLLISIONEVENT;
  // List joints for collisiontors, sprites and text sprites.
  static uint64_t CTS_JOINT;
  static uint64_t AS_JOINT;
  static uint64_t ATS_JOINT;
  // Actuators list.
  static uint64_t BOARD_ACTUATORS_LIST;
  static uint64_t ITEM_ACTUATORS_LIST;
  static uint64_t BRICK_ACTUATORS_LIST;
  static uint64_t BALL_ACTUATORS_LIST;
  static uint64_t EXPLOSION_ACTUATORS_LIST;
  static uint64_t BAR_ACTUATORS_LIST;
  // Behaviors list
  static uint64_t BRICK_LIST;
  static uint64_t BALLSPAWN_LIST;
  static uint64_t BALL_LIST;
  static uint64_t ITEM_LIST;
  static uint64_t MOUSE_CONTROL_LIST;
  static uint64_t DEMAGNETIZE_LIST;
  static uint64_t EXPLSION_ERASE_LIST;
  static uint64_t STICKY_STATE_LIST;
  // Collisionables list
  static uint64_t BRICK_COLLISIONER_LIST;
  // Collisionables list
  static uint64_t BOOM_COLLISIONATOR_LIST;
  // Collisionables list joints
  static uint64_t BALL_CBS_JOINT;
  static uint64_t ITEM_CBS_JOINT;
  // AnimatedSprite list
  static uint64_t BOOM_AS_LIST;
  // TextSprite list
  static uint64_t TEXT_TS_LIST;
  // Sprite sheet ids
  static uint64_t ITEM_SS;
  static uint64_t BRICK_SS;
  static uint64_t BALL_SS;
  static uint64_t EXPLSION_SS;
  static uint64_t BAR_SS;
  static uint64_t BOARD_SS;
  // Image ids
  static uint64_t BOARD_GRAPHICS;
  static uint64_t ITEM_LIFE_GRAPHICS;
  static uint64_t ITEM_MULTIPLIER_GRAPHICS;
  static uint64_t ITEM_ACCEL_GRAPHICS;
  static uint64_t ITEM_DECEL_GRAPHICS;
  static uint64_t ITEM_BIGGER_GRAPHICS;
  static uint64_t ITEM_SMALLER_GRAPHICS;
  static uint64_t ITEM_MAGNET_GRAPHICS;
  static uint64_t ITEM_P100_GRAPHICS;
  static uint64_t ITEM_P200_GRAPHICS;
  static uint64_t ITEM_P500_GRAPHICS;
  static uint64_t ITEM_P999_GRAPHICS;
  static uint64_t ITEM_PN5000_GRAPHICS;
  static uint64_t BRICK_GRAHPICS;
  static uint64_t BAR_GRAPHICS;
  static uint64_t BAR_GRAPHICS_GREY;
  static uint64_t BALL_N_GRAPHICS;
  static uint64_t BALL_B_GRAPHICS;
  static uint64_t EXPLODE_GRAPHICS;
  // Font ids
  static uint64_t BOOM_TEXT_FONT;
  static uint64_t TEXT_FONT;

  static void initIds();
private:
  ZBNCfg() {}
};

} //namespace zombienoid

 #endif  // ZOMBIENOID_ZBNOID_H
