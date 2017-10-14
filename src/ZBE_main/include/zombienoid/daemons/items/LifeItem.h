/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ItemCatcher.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable of increase an value.
 */

#ifndef ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_LIFEITEM
#define ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_LIFEITEM

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/shared/Value.h"

namespace zombienoid {

/** \brief Daemon capable of increase an value.
 */
class LifeItem : public zbe::Daemon {
public:
  LifeItem(std::shared_ptr<zbe::Value<int64_t> > lifes, int64_t amount): l(lifes), amount(amount) {}
  void run(){
      l->add(amount);
  }

private:
  std::shared_ptr<zbe::Value<int64_t> > l;
  int64_t amount;
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_LIFEITEM
