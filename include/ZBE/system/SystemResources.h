/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SystemResources.h
 * @since 2019-06-19
 * @date 2019-06-19
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all system resources.
 */

#ifndef ZBE_SYSTEM_SYSTEMRESOURCES_H_
#define ZBE_SYSTEM_SYSTEMRESOURCES_H_

#include <string>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI SystemResources : public Daemon {
public:
  ~SystemResources() {}

  /** \brief It will Load the system resources.
  */
  void run() override {
    load();
  };

  /** \brief It loads system resources.
  */
  static void load();

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();

};

}  // namespace zbe

#endif  // ZBE_SYSTEM_SYSTEMRESOURCES_H_
