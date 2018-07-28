/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ContextTime.h
 * @since 2018-07-11
 * @date 2018-07-11
 * @author Batis Degryll Ludo
 * @brief Tool used to ask about time inside a context.
 */

#ifndef ZBE_CORE_TOOLS_TIME_CONTEXTTIME_H_
#define ZBE_CORE_TOOLS_TIME_CONTEXTTIME_H_

#include <cstdint>
#include <memory>

namespace zbe {

class SubordinateTime;

/** \brief
*/
class ContextTime {
public:
  ContextTime() : frame(0), lostTime(0), initT(0), endT(0), eventT(0), is_partFrame(false), currentT(0), remainT(0), paused(false), resumed(false) {}  //!< Basic constructor to be used internally.

  virtual ~ContextTime(){}


  /** \brief Get the total time passed until the end of last frame.
  * \return Total time passed until last frame.
  */
  virtual std::shared_ptr<ContextTime> clone() = 0;

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
    return endT;
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

  /** \brief Pauses the ContextTime.
   */
  void pause() {
    paused = true;
    remainT = 0;
    initT = endT;
  }

  /** \brief Resume the ContextTime.
   */
  void resume(int64_t resumeTime) {
    if (paused) {
      endT = resumeTime;
      paused = false;
    }
  }

  /** \brief Refreshes the SystemTime info using given Timer.
   */
  inline void update() {
    if (paused) {return;}
    initT = _getInitTime();
    int64_t finalTime = _getTotalTime();
    int64_t realFrameTime = finalTime - initT;
    int64_t total;
    if (realFrameTime < maxFrameTime) {
      total = finalTime;
      frame = realFrameTime;
    } else {
      total = initT + maxFrameTime;
      lostTime += (realFrameTime - maxFrameTime);
      frame = maxFrameTime;
    }

    endT = total;
    eventT = initT;
    currentT = eventT - initT;
    remainT = endT - eventT;
  }

protected:
  int64_t frame;     //!< Last frame duration
  int64_t lostTime;  //!< Accumulated Total Time - Max frame time
  int64_t initT;     //!< Initial frame time.
  int64_t endT;      //!< End frame time.
  int64_t eventT;    //!< Partial frame time.
  bool is_partFrame; //!< Is partial frame?
  int64_t currentT;  //!< Time available to behave.
  int64_t remainT;   //!< Time available to new events.
  bool paused;       //!< Time is paused
  bool resumed;      //!< Time is resumed
  static int64_t maxFrameTime;  //!< No frame will be longer than this.

private:
  virtual uint64_t _getTotalTime() = 0;
  virtual uint64_t _getInitTime() = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TIME_CONTEXTTIME_H_
