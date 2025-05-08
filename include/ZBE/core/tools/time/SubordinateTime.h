/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SubordinateTime.h
 * @since 2018-07-11
 * @date 2018-07-11
 * @author Batis Degryll Ludo
 * @brief Tool used to ask about time inside a subordinated context.
 */

#ifndef ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_
#define ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/time/ContextTime.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Tool used to ask about time inside a subordinated context.
*/
class ZBEAPI SubordinateTime : public ContextTime {
public:

  // cppcheck-suppress noExplicitConstructor
  SubordinateTime(std::shared_ptr<ContextTime> parent) : parent(parent) {}
  SubordinateTime(const SubordinateTime& sibling) : parent(sibling.parent) {}

  /** \brief Get the total time passed until the end of last frame.
  * \return Total time passed until last frame.
  */
  std::shared_ptr<ContextTime> clone() override {
    return std::make_shared<SubordinateTime>(this->parent);
  }

  static std::shared_ptr<ContextTime> child(std::shared_ptr<ContextTime> parent) {
    return std::make_shared<SubordinateTime>(parent);
  }

private:
  std::shared_ptr<ContextTime> parent;
  uint64_t _getTotalTime() override {
    return parent->getTotalTime() - lostTime;
  }

  uint64_t _getInitTime() override {
    return parent->getInitFrameTime() - lostTime;
  }

};



}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TIME_SUBORDINATETIME_H_
