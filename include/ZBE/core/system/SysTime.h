/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SystemTime.h
 * @since 2016-06-05
 * @date 2016-06-12
 * @author Ludo
 * @brief Tool used to ask about system time.
 */


#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysTime.h"

#include <cstdint>

namespace zbe {

  /** \brief This class will store and manage the system time.
   */
  class SysTime {
    public:

      /** \brief Get the singleton instance of the SystemTime.
       * \return Singleton instance of the SystemTime.
       */
      static SysTime& getInstance() {
        static SysTime instance;
        return (instance);
      }

      /** \brief Get the total time passed until the end of last frame.
       * \return Total time passed until last frame.
       */
      inline uint64_t getTotalTime() {
        return total;
      }

      /** \brief Get the last frame duration.
       * \return Last frame duration.
       */
      inline uint64_t getFrameTime() {
        return frame;
      }

      /** \brief Set the Timer to be used by SystemTime.
       * \param timer Actual implementation of Timer to be used.
       */
      inline void setSystemTimer(Timer* timer) {
        if(!timer){
          zbe::SysError::setError(std::string("ERROR: System timer can only be set once"));
        } else {
          this->timer = timer;
        }
      }

      /** \brief Refreshes the SystemTime info using given Timer.
       */
      inline void update(){
        this->total = this->timer->totalTime();
        this->frame = this->timer->lapTime();
      }

    private:
      SysTime():timer(0),total(0),frame(0){}//!< Basic constructor to be used internally.

      Timer* timer;//!< Actual implementation of Timer to be used.
      uint64_t total;//!< Total time passed until the end of last frame.
      uint64_t frame;//!< Last frame duration
  };

}

#endif //SYSTEMTIME_H
