/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputText.h
 * @since 2020-03-25
 * @date 2020-03-25
 * @author Degryll
 * @brief Single input text representation.
 */

#ifndef ZBE_CORE_IO_INPUTTEXT_H
#define ZBE_CORE_IO_INPUTTEXT_H

#include <cstdint>
#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Single input text representation.
 */
class ZBEAPI InputText {
public:

  /** \brief Empty constructor (0 id, 0.0 status).
   */
  InputText() : text(), time() {}

  /** \brief Construct an input status.
   *  \param text The input Text.
   *  \param time When the input was changed.
   */
  InputText(std::string text, uint64_t time) : text(text), time(time) {}

  /** \brief Returns the input text.
   *  \return The input text.
   */
  std::string getText() const { return text;}

  /** \brief Returns the timestamp in which this text is typed.
   *  \return Timestamp in which this text is typed.
   */
  uint64_t getTime() const { return time;}

  /** \brief "Less than" operator overloading to sort by time.
   *  \return true if left hand element happend earlier than the right hand one.
   */
  bool operator<(const InputText& rhs) const {return time<rhs.getTime();}

private:
  std::string text;
  uint64_t time;
};

}  // namespace zbe

#endif  // ZBE_CORE_IO_INPUTTEXT_H
