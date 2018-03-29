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

#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"

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

  /** \brief set max time for a frame. If a frame lasts longer
   *  than this value the excess will be ignored.
   *  \param  time Desired max frame time
   */
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
    return (initT < endT);
  }

  /** \brief Return true if remains time to finish the actual frame.
   * \return True if the actual frame is not finished yet.
   */
  inline void updateInitTime() {
    initT = eventT;
  }

  /** \brief Set the time of the first interrupt, probably an event.
   *  \param eventTime time in which current events occured
   */
  inline void setEventTime(int64_t eventTime) {
    if (eventTime <= endT) {
      eventT = eventTime;
      is_partFrame = true;
    } else {
      eventT = endT;
      is_partFrame = false;
    }
    currentT = eventT - initT;
    remainT = endT - eventT;
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

  /** \brief Get current frame time.
   * \return Current frame time.
   */
  inline int64_t getCurrentTime() {
    return currentT;
  }

  /** \brief Get remaining frame time.
   * \return Remaining frame time.
   */
  inline int64_t getRemainTime() {
    return remainT;
  }

  /** \brief Get the partial frame time.
   * \return Partial frame time.
   */
  inline int64_t getEventTime() {
    return eventT;
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
    eventT = initT;
    currentT = eventT - initT;
    remainT = endT - eventT;
 }

private:
  SysTime() : timer(0), total(0), frame(0), lostTime(0),
            initT(0), endT(0), eventT(0), is_partFrame(false), currentT(0), remainT(0) {}//!< Basic constructor to be used internally.

  Timer* timer;      //!< Actual implementation of Timer to be used.
  int64_t total;     //!< Total time passed until the end of last frame.
  int64_t frame;     //!< Last frame duration
  int64_t lostTime;  //!< Accumulated Total Time - Max frame time
  int64_t initT;     //!< Initial frame time.
  int64_t endT;      //!< End frame time.
  int64_t eventT;    //!< Partial frame time.
  bool is_partFrame; //!< Is partial frame?
  int64_t currentT;  //!< Time available to behave.
  int64_t remainT;   //!< Time available to new events.

  static int64_t maxFrameTime;  //!< No frame will be longer than this.
};

} // namespace zbe

#endif  // ZBE_CORE_SYSTEM_SYSTEMTIME_H
