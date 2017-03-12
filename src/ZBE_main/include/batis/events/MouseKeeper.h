/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MouseKeeper.h
 * @since 2017-02-12
 * @date 2017-03-12
 * @author Batis
 * @brief Stores actual and previous mouse coordinates
 */

#ifndef ZBE_MAIN_BATIS_EVENTS_MOUSEYKEEPER
#define ZBE_MAIN_BATIS_EVENTS_MOUSEYKEEPER

namespace batis {

class MouseKeeper {
	public:

  	static MouseKeeper& getInstance() {
      static MouseKeeper instance;
      return (instance);
  	}

    double getX() {return x;}
    double getY() {return y;}
    void setX(double mouseX) {x = mouseX;}
    void setY(double mouseY) {y = mouseY;}

	private:
    double x;
    double y;
};
} //namespace batis

#endif //ZBE_MAIN_GAME_EVENTS_MOUSEYKEEPER
