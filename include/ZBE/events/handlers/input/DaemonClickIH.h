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
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/**
 * brief Input handler capable of run a daemon if given coords are inside a given area.
 */
class DaemonClickIH : public InputHandler {
public:

/** \brief Constructs a DaemonClickIH from its raw data
 *  \param area area to use.
 *  \param xvalue Value where mouse x will be readed.
 *  \param yvalue Value where mouse y will be readed.
 *  \param daemon daemon to be executed when condition are met.
 */
DaemonClickIH(Region2D area, std::shared_ptr<Value<double> > xvalue, std::shared_ptr<Value<double> > yvalue, std::shared_ptr<Daemon> daemon) : a(area), xval(xvalue), yval(yvalue), d(daemon) {}

/** \brief exec daemon if click is inside given area.
 *  \param state input state.
 */
void run(uint32_t, float state) {
  if(state!=ZBE_KEYUP){
    return;
  }
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

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_DAEMONCLICKINPUTHANDLER_H
