#ifndef LUDO_LUDOMAIN_H_
#define LUDO_LUDOMAIN_H_

#include <set>
#include <cstdio>

#include "ludo/behaviors/LudoBehaviors.h"
#include "ludo/daemons/LudoDaemons.h"
#include "ludo/drawers/LudoDrawers.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/events/handlers/LudoActuators.h"
#include "ludo/events/handlers/LudoHandlers.h"

#include "ludo/opengltest.h"
#include "ludo/openaltest.h"
#include "ludo/sdlaudiotest.h"
#include "ludo/generaltest.h"
#include "ludo/apptest.h"

namespace ludo {

  int ludomain(int argc, char* argv[]);

}  // namespace ludo

#endif  // LUDO_LUDOMAIN_H_
