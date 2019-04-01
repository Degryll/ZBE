/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Ftry.h
 * @since 2018-11-07
 * @date 2018-11-21
 * @author Ludo Degryll Batis
 * @brief Generic Factory.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_GENERICFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_GENERICFTRY_H_

#include <string>

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Generic Factory.
 */
template <typename Generic, typename Specific>
class GenericFtry : virtual public Factory {
public:
  /** \brief Parametrized constructor
    * \param type Dictionary entry for this item.
    */
  GenericFtry(std::string gtype, std::string stype) : gtype(gtype), stype(stype) {}

  /** \brief Creates an item from a file.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t);

  /** \brief Set-up an item.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string, uint64_t) {}

private:
  RsrcStore<Generic> &grsrc = RsrcStore<Generic>::getInstance();
  RsrcStore<Specific> &srsrc = RsrcStore<Specific>::getInstance();
  std::string gtype;
  std::string stype;
};

template <typename Generic, typename Specific>
void GenericFtry<Generic, Specific>::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  auto i = std::make_shared<Specific>();
  grsrc.insert(gtype + "."s + name, i);
  srsrc.insert(stype + "."s + name, i);
}

} // namespace ZBE

#endif // ZBE_FACTORIES_IMPLEMENTATIONS_GENERICFTRY_H_
