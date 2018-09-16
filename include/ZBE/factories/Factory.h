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

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class Factory {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Factory() {}

  /** \brief Do the behavior work over the given entity
   *  \param entity The entity to behave.
   */
  virtual void build(std::string name, uint64_t cfgId) = 0;

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_FACTORY_H_
