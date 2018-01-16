#include "zombienoid/ZBNoid.h"

namespace zombienoid {

// Basic zbe::ResourceManager: List of collisionators and collisioners for collision. List of zbe::AnimatedSprite and zbe::SingleTextSprite for drawing
zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisioner<ZombienoidReactor> > >& ZBNCfg::rmTFAEConer = zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisioner<ZombienoidReactor> > >::getInstance();
zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> > >& ZBNCfg::rmTFAECator = zbe::ResourceManager<zbe::TicketedFAE<zbe::Collisionator<ZombienoidReactor> > >::getInstance();
zbe::ResourceManager<zbe::JointAE<zbe::Collisionator<ZombienoidReactor> > >& ZBNCfg::rmJAECator = zbe::ResourceManager<zbe::JointAE<zbe::Collisionator<ZombienoidReactor> > >::getInstance();
zbe::ResourceManager<zbe::JointAE<zbe::Collisioner<ZombienoidReactor> > >& ZBNCfg::rmJAEConer = zbe::ResourceManager<zbe::JointAE<zbe::Collisioner<ZombienoidReactor> > >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::AnimatedSprite> >& ZBNCfg::rmTFAECAnimSprt = zbe::ResourceManager<zbe::TicketedFAEC<zbe::AnimatedSprite> >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::SingleTextSprite> >& ZBNCfg::rmTFAECSTextSprt = zbe::ResourceManager<zbe::TicketedFAEC<zbe::SingleTextSprite> >::getInstance();
zbe::ResourceManager<zbe::JointAEC<zbe::AnimatedSprite> >& ZBNCfg::rmJAECAnimSprt = zbe::ResourceManager<zbe::JointAEC<zbe::AnimatedSprite> >::getInstance();
zbe::ResourceManager<zbe::JointAEC<zbe::SingleTextSprite> >& ZBNCfg::rmJAECSTextSprt = zbe::ResourceManager<zbe::JointAEC<zbe::SingleTextSprite> >::getInstance();
// Basic zbe::ResourceManager for zbe::SpriteSheet Drawer
zbe::ResourceManager<zbe::SpriteSheet<zbe::AnimatedSprite> >& ZBNCfg::rmSSheetAnimSprt = zbe::ResourceManager<zbe::SpriteSheet<zbe::AnimatedSprite> >::getInstance();
// Specific zbe::ResourceManager for interactions: Actuators
zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >* > >& ZBNCfg::rmFLAWBlock = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >* > >::getInstance();
zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated> >* > >& ZBNCfg::rmFLAWItem = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated> >* > >::getInstance();
zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable> >* > >& ZBNCfg::rmFLAWBall = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable> >* > >::getInstance();
zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >& ZBNCfg::rmFLAWExplosion = zbe::ResourceManager<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >::getInstance();
// Specific zbe::ResourceManager for Behaviors
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated> >& ZBNCfg::rmTFAECStat = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated> >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Movable<2> > >& ZBNCfg::rmTFAECMov2D = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Movable<2> > >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated, zbe::Avatar, zbe::Positionable<2> > >& ZBNCfg::rmTFAECStatAvtPos2D = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Stated, zbe::Avatar, zbe::Positionable<2> > >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Positionable<2>, zbe::Avatar > >& ZBNCfg::rmTFAECPos2DAvt = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Positionable<2>, zbe::Avatar > >::getInstance();
zbe::ResourceManager<zbe::JointAEC<zbe::Positionable<2>, zbe::Avatar > >& ZBNCfg::rmJAECPos2DAvt = zbe::ResourceManager<zbe::JointAEC<zbe::Positionable<2>, zbe::Avatar > >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Avatar, Scorer> >& ZBNCfg::rmTFAECAvtScor = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Avatar, Scorer> >::getInstance();
zbe::ResourceManager<zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable> >& ZBNCfg::rmTFAECBncr2DRsz = zbe::ResourceManager<zbe::TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable> >::getInstance();
// Behaviors
zbe::ResourceManager<zbe::Behavior<zbe::Positionable<2> > >& ZBNCfg::rmBPos2D = zbe::ResourceManager<zbe::Behavior<zbe::Positionable<2> > >::getInstance();
zbe::ResourceManager<zbe::Behavior<zbe::Movable<2> > >& ZBNCfg::rmBMov2D = zbe::ResourceManager<zbe::Behavior<zbe::Movable<2> > >::getInstance();
// daemons
zbe::ResourceManager<zbe::Daemon>& ZBNCfg::rmD = zbe::ResourceManager<zbe::Daemon>::getInstance();
// Values
zbe::ResourceManager<zbe::Value<int64_t> >& ZBNCfg::rmVInt64 = zbe::ResourceManager<zbe::Value<int64_t> >::getInstance();
zbe::ResourceManager<zbe::Value<double> >& ZBNCfg::rmVDouble = zbe::ResourceManager<zbe::Value<double> >::getInstance();

// Ticket ids.
uint64_t ZBNCfg::COLLISION_TICKET;
uint64_t ZBNCfg::DRAW_TICKET;
uint64_t ZBNCfg::BEHAVE_TICKET;
uint64_t ZBNCfg::MAGNET_TICKET;
uint64_t ZBNCfg::BOOM_TEXTSPRITE_TICKET;
uint64_t ZBNCfg::STICKY_LIST_TICKET;
// Event ids.
uint64_t ZBNCfg::INPUTEVENT;
uint64_t ZBNCfg::TIMEEVENT;
uint64_t ZBNCfg::COLLISIONEVENT;
// List joints for collisiontors, sprites and text sprites.
uint64_t ZBNCfg::CTS_JOINT;
uint64_t ZBNCfg::AS_JOINT;
uint64_t ZBNCfg::ATS_JOINT;
// Actuators list.
uint64_t ZBNCfg::BOARD_ACTUATORS_LIST;
uint64_t ZBNCfg::ITEM_ACTUATORS_LIST;
uint64_t ZBNCfg::BRICK_ACTUATORS_LIST;
uint64_t ZBNCfg::BALL_ACTUATORS_LIST;
uint64_t ZBNCfg::EXPLOSION_ACTUATORS_LIST;
uint64_t ZBNCfg::BAR_ACTUATORS_LIST;
// Behaviors list
uint64_t ZBNCfg::BRICK_LIST;
uint64_t ZBNCfg::BALLSPAWN_LIST;
uint64_t ZBNCfg::BALL_LIST;
uint64_t ZBNCfg::ITEM_LIST;
uint64_t ZBNCfg::MOUSE_CONTROL_LIST;
uint64_t ZBNCfg::BALL_MOUSE_CONTROL_LIST;
uint64_t ZBNCfg::DEMAGNETIZE_LIST;
uint64_t ZBNCfg::EXPLSION_ERASE_LIST;
uint64_t ZBNCfg::STICKY_STATE_LIST;
// Collisionables list
uint64_t ZBNCfg::BOARD_COLLISIONER_LIST;
uint64_t ZBNCfg::BRICK_COLLISIONER_LIST;
uint64_t ZBNCfg::BAR_COLLISIONER_LIST;
// Collisionables list
uint64_t ZBNCfg::BOOM_COLLISIONATOR_LIST;
// Collisionables list joints
uint64_t ZBNCfg::BALL_CBS_JOINT;
uint64_t ZBNCfg::ITEM_CBS_JOINT;
// zbe::AnimatedSprite list
uint64_t ZBNCfg::BOOM_AS_LIST;
uint64_t ZBNCfg::BOARD_AS_LIST;
uint64_t ZBNCfg::BRICK_AS_LIST;
uint64_t ZBNCfg::BAR_AS_LIST;
// TextSprite list
uint64_t ZBNCfg::TEXT_TS_LIST;
// Sprite sheet ids
uint64_t ZBNCfg::ITEM_SS;
uint64_t ZBNCfg::BRICK_SS;
uint64_t ZBNCfg::BALL_SS;
uint64_t ZBNCfg::EXPLSION_SS;
uint64_t ZBNCfg::BAR_SS;
uint64_t ZBNCfg::BOARD_SS;
// Image ids
uint64_t ZBNCfg::BOARD_GRAPHICS;
uint64_t ZBNCfg::ITEM_LIFE_GRAPHICS;
uint64_t ZBNCfg::ITEM_MULTIPLIER_GRAPHICS;
uint64_t ZBNCfg::ITEM_ACCEL_GRAPHICS;
uint64_t ZBNCfg::ITEM_DECEL_GRAPHICS;
uint64_t ZBNCfg::ITEM_BIGGER_GRAPHICS;
uint64_t ZBNCfg::ITEM_SMALLER_GRAPHICS;
uint64_t ZBNCfg::ITEM_MAGNET_GRAPHICS;
uint64_t ZBNCfg::ITEM_P100_GRAPHICS;
uint64_t ZBNCfg::ITEM_P200_GRAPHICS;
uint64_t ZBNCfg::ITEM_P500_GRAPHICS;
uint64_t ZBNCfg::ITEM_P999_GRAPHICS;
uint64_t ZBNCfg::ITEM_PN5000_GRAPHICS;
uint64_t ZBNCfg::BRICK_GRAHPICS;
uint64_t ZBNCfg::BAR_GRAPHICS;
uint64_t ZBNCfg::BAR_GRAPHICS_GREY;
uint64_t ZBNCfg::BALL_N_GRAPHICS;
uint64_t ZBNCfg::BALL_B_GRAPHICS;
uint64_t ZBNCfg::EXPLODE_GRAPHICS;
// Font ids
uint64_t ZBNCfg::BOOM_TEXT_FONT;
uint64_t ZBNCfg::TEXT_FONT;
// Value ids
uint64_t ZBNCfg::NLIFES;
uint64_t ZBNCfg::NBRICKS;
uint64_t ZBNCfg::NPOINTS;
uint64_t ZBNCfg::NBALLS;
uint64_t ZBNCfg::STICKY_ITEM_STATE;
uint64_t ZBNCfg::MOUSE_X_POS;
// Builder ids
uint64_t ZBNCfg::ITEM_BUILDER;
uint64_t ZBNCfg::BALL_BUILDER;
// Daemon ids
uint64_t ZBNCfg::BALL_BUILDER_DAEMON;

void ZBNCfg::initIds() {

  // Ticket ids.
  COLLISION_TICKET = zbe::SysIdGenerator::getId();
  DRAW_TICKET = zbe::SysIdGenerator::getId();
  BEHAVE_TICKET = zbe::SysIdGenerator::getId();
  MAGNET_TICKET = zbe::SysIdGenerator::getId();
  BOOM_TEXTSPRITE_TICKET = zbe::SysIdGenerator::getId();
  STICKY_LIST_TICKET = zbe::SysIdGenerator::getId();
  // Event ids.
  INPUTEVENT = zbe::SysIdGenerator::getId();
  TIMEEVENT = zbe::SysIdGenerator::getId();
  COLLISIONEVENT = zbe::SysIdGenerator::getId();
  // List joints for collisiontors, sprites and text sprites.
  CTS_JOINT = zbe::SysIdGenerator::getId();
  AS_JOINT = zbe::SysIdGenerator::getId();
  ATS_JOINT = zbe::SysIdGenerator::getId();
  // Actuators list.
  BOARD_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  ITEM_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  BRICK_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  BALL_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  EXPLOSION_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  BAR_ACTUATORS_LIST = zbe::SysIdGenerator::getId();
  // Behaviors list
  BRICK_LIST = zbe::SysIdGenerator::getId();
  BALLSPAWN_LIST = zbe::SysIdGenerator::getId();
  BALL_LIST = zbe::SysIdGenerator::getId();
  ITEM_LIST = zbe::SysIdGenerator::getId();
  MOUSE_CONTROL_LIST = zbe::SysIdGenerator::getId();
  BALL_MOUSE_CONTROL_LIST = zbe::SysIdGenerator::getId();
  DEMAGNETIZE_LIST = zbe::SysIdGenerator::getId();
  EXPLSION_ERASE_LIST = zbe::SysIdGenerator::getId();
  STICKY_STATE_LIST = zbe::SysIdGenerator::getId();
  // Collisionables list
  BOARD_COLLISIONER_LIST = zbe::SysIdGenerator::getId();
  BRICK_COLLISIONER_LIST = zbe::SysIdGenerator::getId();
  BAR_COLLISIONER_LIST = zbe::SysIdGenerator::getId();
  // Collisionables list
  BOOM_COLLISIONATOR_LIST = zbe::SysIdGenerator::getId();
  // Collisionables list joints
  BALL_CBS_JOINT = zbe::SysIdGenerator::getId();
  ITEM_CBS_JOINT = zbe::SysIdGenerator::getId();
  // zbe::AnimatedSprite list
  BOOM_AS_LIST = zbe::SysIdGenerator::getId();
  BOARD_AS_LIST = zbe::SysIdGenerator::getId();
  BRICK_AS_LIST = zbe::SysIdGenerator::getId();
  BAR_AS_LIST = zbe::SysIdGenerator::getId();
  // TextSprite list
  TEXT_TS_LIST = zbe::SysIdGenerator::getId();
  // Sprite sheet ids
  ITEM_SS = zbe::SysIdGenerator::getId();
  BRICK_SS = zbe::SysIdGenerator::getId();
  BALL_SS = zbe::SysIdGenerator::getId();
  EXPLSION_SS = zbe::SysIdGenerator::getId();
  BAR_SS = zbe::SysIdGenerator::getId();
  BOARD_SS = zbe::SysIdGenerator::getId();
  // Image ids
  BOARD_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_LIFE_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_MULTIPLIER_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_ACCEL_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_DECEL_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_BIGGER_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_SMALLER_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_MAGNET_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_P100_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_P200_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_P500_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_P999_GRAPHICS = zbe::SysIdGenerator::getId();
  ITEM_PN5000_GRAPHICS = zbe::SysIdGenerator::getId();
  BRICK_GRAHPICS = zbe::SysIdGenerator::getId();
  BAR_GRAPHICS = zbe::SysIdGenerator::getId();
  BAR_GRAPHICS_GREY = zbe::SysIdGenerator::getId();
  BALL_N_GRAPHICS = zbe::SysIdGenerator::getId();
  BALL_B_GRAPHICS = zbe::SysIdGenerator::getId();
  EXPLODE_GRAPHICS = zbe::SysIdGenerator::getId();
  // Font ids
  BOOM_TEXT_FONT = zbe::SysIdGenerator::getId();
  TEXT_FONT = zbe::SysIdGenerator::getId();
  // Value ids
  NLIFES = zbe::SysIdGenerator::getId();
  NBRICKS = zbe::SysIdGenerator::getId();
  NPOINTS = zbe::SysIdGenerator::getId();
  NBALLS = zbe::SysIdGenerator::getId();
  STICKY_ITEM_STATE = zbe::SysIdGenerator::getId();
  MOUSE_X_POS = zbe::SysIdGenerator::getId();
  // Builder ids
  ITEM_BUILDER = zbe::SysIdGenerator::getId();
  BALL_BUILDER = zbe::SysIdGenerator::getId();
  // Daemon ids
  BALL_BUILDER_DAEMON = zbe::SysIdGenerator::getId();
}
}
