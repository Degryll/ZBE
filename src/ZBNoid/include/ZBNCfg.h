/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ButtonBuilder.h
 * @since 2017-12-09
 * @date 2017-12-09
 * @author Degryll Ludo Batis
 * @brief ZBNoid button builder.
 */

#ifndef ZOMBIENOID_ZBNCFG_H
#define ZOMBIENOID_ZBNCFG_H

#include "ZBE/core/zbe.h"

#include "ZombienoidReactor.h"

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/events/handlers/ActuatorWrapper.h"

#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/Resizable.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "entities/avatars/Scorer.h"

namespace zombienoid {

enum {
  LOADGAME = 0,
  MAINTITLE = 1,
  GAMERESET = 2,
  LOADLEVEL = 3,
  MAINGAME = 4,
  LOSTENDGAME = 5,
  WINENDGAME = 6,
  CLEARGAME = 7,
  EXIT = -1,

  START = GAMERESET,
  END = EXIT,

  RESETSUCCESS = CLEARGAME,

  GAMELOADSUCCESS = MAINTITLE,
  LEVELLOADSUCCESS = MAINGAME,
  LEVELCLEARSUCCESS = LOADLEVEL,

  MAINGAMEWIN = WINENDGAME,
  GONEXTLEVEL = CLEARGAME,
  MAINGAMEOVER = LOSTENDGAME,

  WIDTH = 1024,
  HEIGHT = 768,
  MARGIN = 32,
  INITBALLS = 1,
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

const int64_t IDLE_BUTTON_STATE = 0;

const size_t RSRC_ID_DICT_SIZE = 20;

// BUTTON
// -GRAPHICS
const int64_t BUTTON_FRAMES = 1;
const zbe::Vector2D BUTTON_DISPLACEMENT = zbe::Vector2D{256.0, 0.0};
const int64_t BUTTON_FRAMETIME = 1000;
const zbe::Region2D BUTTON_REGION = zbe::Region2D({0.0, 0.0}, {512.0, 128.0});
const int64_t BUTTON_STATES = 2;

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

  // Basic zbe::ResourceManager: List of entities for cleaning.
  static zbe::ResourceManager<zbe::TicketedForwardList<zbe::Entity> >& rmTFEntity;
  // Basic zbe::ResourceManager: List of collisionators and collisioners for collision. List of zbe::AnimatedSprite and zbe::SingleTextSprite for drawing
  static zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisioner<ZombienoidReactor> > >& rmTFAEConer;
  static zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> > >& rmTFAECator;
  static zbe::ResourceManager<zbe::JointAE<zbe::Collisionator<ZombienoidReactor> > >& rmJAECator;
  static zbe::ResourceManager<zbe::JointAE<zbe::Collisioner<ZombienoidReactor> > >& rmJAEConer;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::AnimatedSprite> >& rmTFAECAnimSprt;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::SingleTextSprite> >& rmTFAECSTextSprt;
  static zbe::ResourceManager<zbe::JointAEC<zbe::AnimatedSprite> >& rmJAECAnimSprt;
  static zbe::ResourceManager<zbe::JointAEC<zbe::SingleTextSprite> >& rmJAECSTextSprt;
  // Basic zbe::ResourceManager for zbe::SpriteSheet Drawer
  static zbe::ResourceManager<zbe::SpriteSheet<zbe::AnimatedSprite> >& rmSSheetAnimSprt;
  // Specific zbe::ResourceManager for interactions: Actuators
  static zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >* > >& rmFLAWBlock;
  static zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated> >* > >& rmFLAWItem;
  static zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable> >* > >& rmFLAWBall;
  static zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >& rmFLAWExplosion;
  // Specific zbe::ResourceManager for Behaviors
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated> >& rmTFAECStat;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Movable<2> > >& rmTFAECMov2D;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Avatar> >& rmTFAECBncr2DAvt;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated, zbe::Avatar, zbe::Positionable<2> > >& rmTFAECStatAvtPos2D;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Positionable<2>, zbe::Avatar > >& rmTFAECPos2DAvt;
  static zbe::ResourceManager<zbe::JointAEC<zbe::Positionable<2>, zbe::Avatar > >& rmJAECPos2DAvt;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Avatar, Scorer> >& rmTFAECAvtScor;
  static zbe::ResourceManager<zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> >& rmTFAECBncr2DRszAvt;
  // Behaviors
  static zbe::ResourceManager<zbe::Behavior<zbe::Positionable<2> > >& rmBPos2D;
  static zbe::ResourceManager<zbe::Behavior<zbe::Movable<2> > >& rmBMov2D;
  // daemons
  static zbe::ResourceManager<zbe::Daemon>& rmD;
  // Values
  static zbe::ResourceManager<zbe::Value<int64_t> >& rmVInt64;
  static zbe::ResourceManager<zbe::Value<double> >& rmVDouble;

  // Ticket ids.
  static uint64_t ENTITY_TICKET;
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
  // Entities lists.
  static uint64_t BALL_ENTITY_LIST;
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
  static uint64_t BALL_MOUSE_CONTROL_LIST;
  static uint64_t DEMAGNETIZE_LIST;
  static uint64_t EXPLSION_ERASE_LIST;
  static uint64_t STICKY_STATE_LIST;
  // Collisionables list
  static uint64_t BOARD_COLLISIONER_LIST;
  static uint64_t BRICK_COLLISIONER_LIST;
  static uint64_t BAR_COLLISIONER_LIST;
  // Collisionables list
  static uint64_t BOOM_COLLISIONATOR_LIST;
  static uint64_t BALL_COLLISIONATOR_LIST;
  // Collisionables list joints
  static uint64_t BALL_CBS_JOINT;
  static uint64_t ITEM_CBS_JOINT;
  // zbe::AnimatedSprite list
  static uint64_t BOOM_AS_LIST;
  static uint64_t BALL_AS_LIST;
  static uint64_t BOARD_AS_LIST;
  static uint64_t BRICK_AS_LIST;
  static uint64_t BAR_AS_LIST;
  static uint64_t TITLE_BUTTONS_AS_LIST;
  static uint64_t WIN_BUTTONS_AS_LIST;
  static uint64_t LOST_BUTTONS_AS_LIST;
  // TextSprite list
  static uint64_t TEXT_TS_LIST;
  static uint64_t TITLE_BUTTONS_TS_LIST;
  static uint64_t WIN_BUTTONS_TS_LIST;
  static uint64_t LOST_BUTTONS_TS_LIST;
  // Sprite sheet ids
  static uint64_t BUTTON_SS;
  static uint64_t ITEM_SS;
  static uint64_t BRICK_SS;
  static uint64_t BALL_SS;
  static uint64_t EXPLSION_SS;
  static uint64_t BAR_SS;
  static uint64_t BOARD_SS;
  // Image ids
  static uint64_t BUTTON_GRAPHICS;
  static uint64_t SELECTED_BUTTON_GRAPHICS;
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
  // Value ids
  static uint64_t GAMESTATE;
  static uint64_t NLIFES;
  static uint64_t NBRICKS;
  static uint64_t NPOINTS;
  static uint64_t NBALLS;
  static uint64_t STICKY_ITEM_STATE;
  static uint64_t MOUSE_X_POS;
  // Builder ids
  static uint64_t ITEM_BUILDER;
  static uint64_t BALL_BUILDER;
  // Daemon ids
  static uint64_t BALL_BUILDER_DAEMON;
  static uint64_t BALL_MAGNETIZER_DAEMON;

  static void initIds();
 private:
  ZBNCfg() {}
};

} //namespace zombienoid

#endif  // ZOMBIENOID_ZBNCFG_H
