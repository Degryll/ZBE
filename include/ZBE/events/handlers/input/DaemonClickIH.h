/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonClickIH.h
 * @since 2018-01-22
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon if given coords are inside a given area.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H
#define ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H

#include <memory>
#include <algorithm>

#include "ZBE/core/io/Input.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/**
 * brief Input handler capable of run a daemon if given coords are inside a given area.
 */
class ZBEAPI DaemonClickIH : public InputHandler {
public:

/** \brief Constructs a DaemonClickIH from its raw data
 *  \param area area to use.
 *  \param xvalue Value where mouse x will be readed.
 *  \param yvalue Value where mouse y will be readed.
 *  \param daemon daemon to be executed when condition are met.
 */
DaemonClickIH() : a(), xval(nullptr), yval(nullptr), d(nullptr) {}


/** \brief Constructs a DaemonClickIH from its raw data
 *  \param area area to use.
 *  \param xvalue Value where mouse x will be readed.
 *  \param yvalue Value where mouse y will be readed.
 *  \param daemon daemon to be executed when condition are met.
 */
DaemonClickIH(Region2D area, std::shared_ptr<Value<double> > xvalue, std::shared_ptr<Value<double> > yvalue, std::shared_ptr<Daemon> daemon) : a(area), xval(xvalue), yval(yvalue), d(daemon) {}

/** \brief Set Value<double> where x pointer coor will be found
 *  \param xvalue where x pointer coor will be found.
 */
void setXValue(std::shared_ptr<Value<double> > xvalue) {
  this->xval = xvalue;
}

/** \brief Set Value<double> where y pointer coor will be found
 *  \param yvalue where y pointer coor will be found.
 */
void setYValue(std::shared_ptr<Value<double> > yvalue) {
  this->yval = yvalue;
}

/** \brief Set the area where the daemon will be launch.
 *  \param area where the daemon will be launch.
 */
void setArea(Region2D area) {
  this->a = area;
}

/** \brief Set the Daemon to run.
 *  \param daemon the Daemon to run.
 */
void setDaemon(std::shared_ptr<Daemon> daemon) {
  this->d = daemon;
}

/** \brief exec daemon if click is inside given area.
 *  \param state input state.
 */
void run(uint32_t, float state) {
  if(!almost_equal(state, ZBE_KEYUP)) override {
    return;
  }
  double x = xval->get();
  double y = yval->get();
  double minx = std::min(a.p.x, a.p.x + a.v.x);
  double miny = std::min(a.p.y, a.p.y + a.v.y);
  double maxx = std::max(a.p.x, a.p.x + a.v.x);
  double maxy = std::max(a.p.y, a.p.y + a.v.y);
  if(x > minx && x < maxx && y > miny && y < maxy) {
    d->run();
  }
}

private:
  Region2D a;
  std::shared_ptr<Value<double> > xval;
  std::shared_ptr<Value<double> > yval;
  std::shared_ptr<Daemon> d;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H
