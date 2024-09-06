/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateSetter.h
 * @since 2018-01-08
 * @date 2018-01-08
 * @author Degryll Ludo Bates
 * @brief Sets a given state to the entity.
 */

#ifndef ZBE_BEHAVIORS_STATESETTER_H_
#define ZBE_BEHAVIORS_STATESETTER_H_

#include <memory>
#include <cstdint>

#include "ZBE/core/behaviors/Behavior.h"


#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Sets a given state to the entity.
 */
class ZBEAPI StateSetter : virtual public Behavior<int64_t> {
public:

  /** \brief Empty constructor.
   */
  StateSetter() : state(0) {}

  /** \brief Parametrized constructor.
    \param state State that will be set.
   */
  StateSetter(int64_t state) : state(state) {}

  /** \brief Virtual destructor.
   */
  virtual ~StateSetter() {}

  /** \brief Set the state.
   */
  void setState(int64_t state) {this->state = state;}

  /** \brief Sets the entity state to given one.
   */
  void apply(std::shared_ptr<SAvatar<int64_t> > avatar) override {
    auto s = AvtUtil::get<1, int64_t>(avatar);
    s->set(state);
  }

private:
  int64_t state;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_STATESETTER_H_
