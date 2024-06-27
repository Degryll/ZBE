/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoHandlers.h
 * @since 2020-11-26
 * @date 2020-11-26
 * @author Ludo
 * @brief Test Chai behavior
 */

#ifndef LUDO_BEHAVIORS_CHAIBEHAVIOR_H
#define LUDO_BEHAVIORS_CHAIBEHAVIOR_H

#include <cstdio>
#include <memory>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

namespace ludo {

template <typename T, typename... Ts>
class ChaiBehaviorFtry;

/** \brief Oscillates given avatar's value.
 */
template <typename T, typename... Ts>
class ChaiBehavior : virtual public Behavior<T, T...> {
public:
  friend class ChaiBehaviorFtry<T, T...>;
  void apply(std::shared_ptr<MAvatar<T, T...> > avatar) override {
    
  };
}

} //namespace ludo

#endif //LUDO_BEHAVIORS_CHAIBEHAVIOR_H
