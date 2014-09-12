/*
 * CollisionData.cpp
 *
 *  Created on: 22/08/2013
 *      Author: ludo
 */

#include "ZBE/core/CollisionData.h"

namespace zbe {

  void CollisionData::react(double time) {
      d->react(b, n, p, time);
      b->react(d, n, p, time);
  }

}
