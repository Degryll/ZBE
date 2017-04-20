/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SysTime.h
 * @since 2016-06-05
 * @date 2016-06-12
 * @author Ludo Degryll Batis
 * @brief Tool used to ask about system time.
 */

#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"

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

      static void setMaxFrameTime(int64_t time) {
        maxFrameTime = time;
      }

      /** \brief Get the total time passed until the end of last frame.
       * \return Total time passed until last frame.
       */
      inline int64_t getTotalTime() {
        return total;
      }

      /** \brief Get the last frame duration.
       * \return Last frame duration.
       */
      inline int64_t getFrameTime() {
        return frame;
      }

      /** \brief Get the time lost by performance issues.
       * \return lost time.
       */
      inline int64_t getLostTime() {
        return lostTime;
      }

      /** \brief Return true if remains time to finish the actual frame.
       * \return True if the actual frame is not finished yet.
       */
      inline bool isFrameRemaining() {
        initT = partT;
        return (initT < endT);
      }

      /** \brief Set the time of the first interrupt, probably an event.
       */
      inline void setPartialFrameTime(int64_t partialFrameTime) {
        if (partialFrameTime <= endT) {
          partT = partialFrameTime;
          is_partFrame = true;
        } else {
          partT = endT;
          is_partFrame = false;
        }
        subframe = partT - initT;
      }

      /** \brief Return true if we're resolving a partial frame.
       * \return True if the actual frame is partial.
       */
      inline bool isPartialFrame() {
        return (is_partFrame);
      }

      /** \brief Get the initial frame time.
       * \return Sub frame time.
       */
      inline int64_t getInitFrameTime() {
        return initT;
      }

      /** \brief Get the end frame time.
       * \return Sub frame time.
       */
      inline int64_t getEndFrameTime() {
        return endT;
      }

      /** \brief Get the available frame time.
       * \return Sub frame time.
       */
      inline int64_t getSubFrameTime() {
        return subframe;
      }

      /** \brief Get the partial frame time.
       * \return Partial frame time.
       */
      inline int64_t getPartialFrameTime() {
        return partT;
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
        int64_t actual = timer->totalTime();
        int64_t finalTime = actual - lostTime;
        int64_t realFrameTime = finalTime - total;
        if (realFrameTime < maxFrameTime){
          total = finalTime;
          frame = realFrameTime;
        } else {
          total += maxFrameTime;
          lostTime += (realFrameTime - maxFrameTime);
          frame = maxFrameTime;
        }

        initT = endT;
        endT = total;
        subframe = endT - initT;
        partT = initT;
     }

    private:
      SysTime() : timer(0), total(0), frame(0), lostTime(0),
                initT(0), endT(0), partT(0), is_partFrame(false), subframe(0) {}//!< Basic constructor to be used internally.

      Timer* timer;      //!< Actual implementation of Timer to be used.
      int64_t total;     //!< Total time passed until the end of last frame.
      int64_t frame;     //!< Last frame duration
      int64_t lostTime;  //!< Accumulated Total Time - Max frame time
      int64_t initT;     //!< Initial frame time.
      int64_t endT;      //!< End frame time.
      int64_t partT;     //!< Partial frame time.
      bool is_partFrame; //!< Is partial frame?
      int64_t subframe;  //!< Ask ludo.

      static int64_t maxFrameTime;  //!< No frame will be longer than this.
  };

}

#endif //SYSTEMTIME_H
