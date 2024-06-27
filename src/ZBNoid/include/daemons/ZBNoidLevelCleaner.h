/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelCleaner.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid Clean each level.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBNoid.h"

#include "graphics/RsrcIDDictionary.h"

namespace zombienoid {
/** \brief Defines a daemon that Load each level.
 */
class ZBNoidLevelCleaner : public zbe::Daemon {
public:

  ZBNoidLevelCleaner() : demagnetizeDaemon(std::make_shared<zbe::BehaviorDaemon<zbe::TicketedFAEC<zbe::Positionable<2>, zbe::Avatar>, zbe::Avatar> >(std::make_shared<Demagnetizer>(ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET), zbe::RsrcStore<zbe::TicketedFAEC<zbe::Positionable<2>, zbe::Avatar> >::getInstance().get(ZBNCfg::DEMAGNETIZE_LIST))) {}
  ~ZBNoidLevelCleaner() {}

  void run() override;

private:
  std::shared_ptr<zbe::Daemon> demagnetizeDaemon;

};


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H
