/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SysTime.h
 * @since 2016-06-05
 * @date 2018-03-21
 * @author Ludo Degryll Batis
 * @brief Tool used to ask about system time.
 */

#ifndef ZBE_CORE_SYSTEM_SYSTEMTIME_H
#define ZBE_CORE_SYSTEM_SYSTEMTIME_H

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/tools/time/SubordinateTime.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This class ZBEAPI will store and manage the system time.
*/
class ZBEAPI SysTime : public ContextTime {
public:
  SysTime(const SysTime&) = delete;
  void operator=(const SysTime&) = delete;

  ~SysTime() {}

  /** \brief Get the singleton instance of the SystemTime.
  * \return Singleton instance of the SystemTime.
  */
  static std::shared_ptr<SysTime> getInstance() {
   static std::shared_ptr<SysTime> instance(new SysTime());
   return (instance);
  }

  /** \brief Get the total time passed until the end of last frame.
  * \return Total time passed until last frame.
  */
  std::shared_ptr<ContextTime> clone() override {
   return getInstance();
  }

  inline void setSystemTimer(std::shared_ptr<Timer> timer) {
    if (!timer) {
      zbe::SysError::setError(std::string("ERROR: System timer can only be set once"));
    } else {
      this->timer = timer;
    }
  }

private:
  SysTime() : timer(nullptr) {}  //!< Basic constructor to be used internally.

  std::shared_ptr<Timer> timer;      //!< Actual implementation of Timer to be used.

  uint64_t _getTotalTime() override {
    return static_cast<uint64_t>(timer->totalTime()) - lostTime;
  }

  uint64_t _getInitTime() override {
    return endT;
  }

};

} // namespace zbe

#endif  // ZBE_CORE_SYSTEM_SYSTEMTIME_H
