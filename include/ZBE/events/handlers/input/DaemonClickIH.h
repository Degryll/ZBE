/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonClickIH.h
 * @since 2018-01-22
 * @date 2018-01-22
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon if given coords are inside a given area.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H
#define ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H

#include "ZBE/core/events/handlers/InputHandler.h"

#include <memory>
#include <algorithm>

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/**
 * brief Input handler capable of run a daemon if given coords are inside a given area.
 */
class DaemonClickIH : public InputHandler {
public:

DaemonClickIH(Region2D area, std::shared_ptr<Value<double> > xvalue, std::shared_ptr<Value<double> > yvalue, std::shared_ptr<Daemon> daemon) : a(area), xval(xvalue), yval(yvalue), d(daemon) {}

void run(float) {
  double x = xval->getValue();
  double y = yval->getValue();
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

} //namespace zbe

#endif //ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H
