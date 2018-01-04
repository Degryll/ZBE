#include "zombienoid/ZBNoid.h"

namespace zombienoid {
  // Ticket ids.
  uint64_t ZBNCfg::COLLISION_TICKET;
  uint64_t ZBNCfg::DRAW_TICKET;
  uint64_t ZBNCfg::BEHAVE_TICKET;
  uint64_t ZBNCfg::MAGNET_TICKET;
  uint64_t ZBNCfg::BOOM_TEXTSPRITE_TICKET;
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
  uint64_t ZBNCfg::DEMAGNETIZE_LIST;
  uint64_t ZBNCfg::EXPLSION_ERASE_LIST;
  // Collisionables list
  uint64_t ZBNCfg::BRICK_COLLISIONER_LIST;
  // Collisionables list
  uint64_t ZBNCfg::BOOM_COLLISIONATOR_LIST;
  // Collisionables list joints
  uint64_t ZBNCfg::BALL_CBS_JOINT;
  uint64_t ZBNCfg::ITEM_CBS_JOINT;
  // AnimatedSprite list
  uint64_t ZBNCfg::BOOM_AS_LIST;
  // TextSprite list
  uint64_t ZBNCfg::TEXT_TS_LIST;
  // Sprite sheet ids
  uint64_t ZBNCfg::ITEM_SS;
  uint64_t ZBNCfg::BRICK_SS;
  uint64_t ZBNCfg::BALL_SS;
  uint64_t ZBNCfg::EXPLSION_SS;
  uint64_t ZBNCfg::BAR_SS;
  uint64_t ZBNCfg::BOARD_SS;
  // Image paths
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

  void ZBNCfg::initIds() {
    // Ticket ids.
    COLLISION_TICKET = zbe::SysIdGenerator::getId();
    DRAW_TICKET = zbe::SysIdGenerator::getId();
    BEHAVE_TICKET = zbe::SysIdGenerator::getId();
    MAGNET_TICKET = zbe::SysIdGenerator::getId();
    BOOM_TEXTSPRITE_TICKET = zbe::SysIdGenerator::getId();
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
    DEMAGNETIZE_LIST = zbe::SysIdGenerator::getId();
    EXPLSION_ERASE_LIST = zbe::SysIdGenerator::getId();
    // Collisionables list
    BRICK_COLLISIONER_LIST = zbe::SysIdGenerator::getId();
    // Collisionables list
    BOOM_COLLISIONATOR_LIST = zbe::SysIdGenerator::getId();
    // Collisionables list joints
    BALL_CBS_JOINT = zbe::SysIdGenerator::getId();
    ITEM_CBS_JOINT = zbe::SysIdGenerator::getId();
    // AnimatedSprite list
    BOOM_AS_LIST = zbe::SysIdGenerator::getId();
    // TextSprite list
    TEXT_TS_LIST = zbe::SysIdGenerator::getId();
    // Sprite sheet ids
    ITEM_SS = zbe::SysIdGenerator::getId();
    BRICK_SS = zbe::SysIdGenerator::getId();
    BALL_SS = zbe::SysIdGenerator::getId();
    EXPLSION_SS = zbe::SysIdGenerator::getId();
    BAR_SS = zbe::SysIdGenerator::getId();
    BOARD_SS = zbe::SysIdGenerator::getId();
    // Image paths
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
  }
}
