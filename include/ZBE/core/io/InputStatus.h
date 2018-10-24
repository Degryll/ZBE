/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputStatus.h
 * @since 2016-08-21
 * @date 2018-08-12
 * @author Ludo
 * @brief Single input status representation.
 */

#ifndef ZBE_CORE_IO_INPUTSTATUS_H
#define ZBE_CORE_IO_INPUTSTATUS_H

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Single input status representation.
 */
class ZBEAPI InputStatus {
public:

  /** \brief Empty constructor (0 id, 0.0 status).
   */
  InputStatus() : id(), status(), time() {}

  /** \brief Construct an input status.
   *  \param id Id of the input (key, button, mouse move, etc.).
   *  \param status Status of the input (pressed, moved, etc.).
   *  \param time When the input was changed.
   */
  InputStatus(uint32_t id, float status, uint64_t time) : id(id), status(status), time(time) {}

  /** \brief Returns the id of the input element.
   *  \return Id of the input element (key, button, mouse move, etc.).
   */
  uint32_t getId() const { return id;}

  /** \brief Returns the status of the input source.
   *  \return Status of the input source (pressed, moved, etc.).
   */
  float getStatus() const { return status;}

  /** \brief Returns the timestamp in which this state is reached.
   *  \return Timestamp in which this state is reached.
   */
  uint64_t getTime() const { return time;}

  /** \brief "Less than" operator overloading.
   *  \return true if left hand element is less than right hand one.
   */
  bool operator<(const InputStatus& rhs) const {return time<rhs.getTime();}

private:

  uint32_t id;
  float status;
  uint64_t time;
};

}  // namespace zbe

#endif  // ZBE_CORE_IO_INPUTSTATUS_H
