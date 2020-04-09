/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Console.h
 * @since 2020-04-08
 * @date 2020-04-08
 * @author Degryll
 * @brief A console terminal.
 */

#ifndef ZBE_ENTITIES_IMPLEMENTATIONS_CONSOLE_H
#define ZBE_ENTITIES_IMPLEMENTATIONS_CONSOLE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A simple active game element in 2D..
 */
class Console : public zbe::Entity {
public:
  Console(uint64_t fontId) {
    auto fid = std::make_shared<zbe::SimpleValue<uint64_t> >(fontId);
    auto vc = std::make_shared<zbe::SimpleValue<std::string> >("");
    auto vl = std::make_shared<zbe::SimpleValue<int64_t> >(0);
    auto vh = std::make_shared<zbe::SimpleValue<std::vector<std::string> > >();
    addValues(fid, vc, vl, vh);
  }

  Console(std::shared_ptr<zbe::Value<uint64_t> > fid, std::shared_ptr<zbe::Value<std::string> > vc, std::shared_ptr<zbe::Value<int64_t> > vl, std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) {
    addValues(fid, vc, vl, vh);
  }

protected:
  void addValues(std::shared_ptr<zbe::Value<uint64_t> > fid, std::shared_ptr<zbe::Value<std::string> > vc, std::shared_ptr<zbe::Value<int64_t> > vl, std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) {
    this->setUint(1, fid);
    this->setString(1, vc);
    this->setInt(1, vl);
    this->setStringVector(1, vh);
  }
};

} // namespace zbe

#endif  // ZBE_ENTITIES_IMPLEMENTATIONS_CONSOLE_H
