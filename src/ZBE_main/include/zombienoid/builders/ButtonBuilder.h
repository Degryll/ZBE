/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ButtonBuilder.h
 * @since 2017-12-09
 * @date 2017-12-09
 * @author Degryll Ludo Batis
 * @brief ZBNoid button builder.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_BUILDERS_BUTTONBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_BUILDERS_BUTTONBUILDER_H

#include <memory>
#include <cstdint>

#include "zombienoid/ZBNoid.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/zbe.h"

namespace zombienoid {

/** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */
class ButtonBuilder {
public:

  ButtonBuilder(const ButtonBuilder& rhs)
    : brdcstHI(), xvalue(), yvalue(), area(), daemon(), text(),
      graphics(), textGraphics(), asDrwListId(), spsDrwListId() {
    brdcstHI = rhs.brdcstHI;
    xvalue = rhs.xvalue;
    yvalue = rhs.yvalue;
    area = rhs.area;
    daemon = rhs.daemon;
    text = rhs.text;
    graphics = rhs.graphics;
    textGraphics = rhs.textGraphics;
    asDrwListId = rhs.asDrwListId;
    spsDrwListId = rhs.spsDrwListId;
  }

  ButtonBuilder& operator=(const ButtonBuilder& rhs) {
    brdcstHI = rhs.brdcstHI;
    xvalue = rhs.xvalue;
    yvalue = rhs.yvalue;
    area = rhs.area;
    daemon = rhs.daemon;
    text = rhs.text;
    graphics = rhs.graphics;
    textGraphics = rhs.textGraphics;
    asDrwListId = rhs.asDrwListId;
    spsDrwListId = rhs.spsDrwListId;
    return *this;
  }

  ~ButtonBuilder() {}

  /** \brief It will finish the game if the number of lifes reaches 0
   */
  static ButtonBuilder aButton() {return (ButtonBuilder());}

  inline ButtonBuilder& withBroadcastHI(BroadcastIH* brdcstHI)                            { this->brdcstHI = brdcstHI; return (*this);};
  inline ButtonBuilder& withMouseX(std::shared_ptr<zbe::Value<double> > xvalue)           {this->xvalue = xvalue; return (*this);}
  inline ButtonBuilder& withMouseY(std::shared_ptr<zbe::Value<double> > yvalue)           {this->yvalue = yvalue; return (*this);}
  inline ButtonBuilder& withArea(zbe::Region2D area)                                      {this->area = area; return (*this);}
  inline ButtonBuilder& withDaemon(std::shared_ptr<zbe::Daemon> daemon)                   {this->daemon = daemon; return (*this);}
  inline ButtonBuilder& withGraphics(uint64_t graphics)                                   {this->graphics = graphics; return (*this);}
  inline ButtonBuilder& withText(std::string text)                                        {this->text = text; return (*this);}
  inline ButtonBuilder& withTextGraphics(uint64_t textGraphics)                           {this->textGraphics = textGraphics; return (*this);}
  inline ButtonBuilder& inDrawList(uint64_t asDrwListId)                                  {this->asDrwListId = asDrwListId; return (*this);}
  inline ButtonBuilder& inTextList(uint64_t spsDrwListId)                                 {this->spsDrwListId = spsDrwListId; return (*this);}

  void build();

private:
  ButtonBuilder() : brdcstHI(),  xvalue(), yvalue(), area(), daemon(), text(), graphics(), textGraphics(), asDrwListId(), spsDrwListId() {}

  BroadcastIH* brdcstHI;
  std::shared_ptr<zbe::Value<double> > xvalue;
  std::shared_ptr<zbe::Value<double> > yvalue;
  zbe::Region2D area;
  std::shared_ptr<zbe::Daemon> daemon;
  std::string text;
  uint64_t graphics;
  uint64_t textGraphics;
  uint64_t asDrwListId;
  uint64_t spsDrwListId;
};


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_BUILDERS_BUTTONBUILDER_H
