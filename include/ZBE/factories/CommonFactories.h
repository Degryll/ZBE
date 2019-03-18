/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CommonFactories.h
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#ifndef ZBE_FACTORIES_COMMONFACTORIES_H_
#define ZBE_FACTORIES_COMMONFACTORIES_H_

#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI CommonFactories : public Daemon {
public:
  ~CommonFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_COMMONFACTORIES_H_
