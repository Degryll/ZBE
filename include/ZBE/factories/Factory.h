/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Factory.h
 * @since 2018-09-03
 * @date 2018-09-03
 * @author Ludo Degryll Batis
 * @brief Define the interface of a Factory.
 */

#ifndef ZBE_FACTORIES_FACTORY_H_
#define ZBE_FACTORIES_FACTORY_H_

#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI Factory {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Factory() {}

  /** \brief Create the desired tool, probably incomplete.
   *  \param name Name for the created tool.
   *  \param cfgId Tool's configuration id.
   */
  virtual void create(std::string name, uint64_t cfgId) = 0;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  virtual void setup(std::string name, uint64_t cfgId) = 0;

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_FACTORY_H_
