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

#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/tools/time/SubordinateTime.h"

namespace zbe {

/** \brief This class will store and manage the system time.
*/
class SysTime : public ContextTime {
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
  std::shared_ptr<ContextTime> clone() {
   return getInstance();
  }

  inline void setSystemTimer(Timer* timer) {
    if (!timer) {
      zbe::SysError::setError(std::string("ERROR: System timer can only be set once"));
    } else {
      this->timer = timer;
    }
  }

private:
  SysTime() : timer(0) {}  //!< Basic constructor to be used internally.

  Timer* timer;      //!< Actual implementation of Timer to be used.

  uint64_t _getTotalTime() {
    return timer->totalTime() - lostTime;
  }

  uint64_t _getInitTime() {
    return endT;
  }

};

} // namespace zbe

#endif  // ZBE_CORE_SYSTEM_SYSTEMTIME_H
