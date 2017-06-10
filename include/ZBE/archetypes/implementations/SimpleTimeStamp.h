/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTimeStamp.h
 * @since 2017-06-07
 * @date 2017-06-07
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the TimeStamp archetype.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETIMESTAMP_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETIMESTAMP_H

#include "ZBE/archetypes/TimeStamp.h"

namespace zbe {

/** \brief Simple implementation of the TimeStamp archetype.
 */
class SimpleTimeStamp : virtual public TimeStamp {
public:
  /** \brief Parametrized constructor. Set the size of the archetype.
   *  \param width Size of the archetype.
   */
  SimpleTimeStamp(int64_t timeStamp) :t(timeStamp) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleTimeStamp() {}

  /** \brief Set the time stamp.
   *  \param timeStamp Time stamp.
   *  \sa getTimeStamp
   */
  void setTimeStamp(int64_t timeStamp) {t = timeStamp;}

  /** \brief Return a time stamp.
   *  \return The time stamp.
   *  \sa setTimeStamp
   */
  int64_t getTimeStamp() {return (t);}

private:
  int64_t t;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETIMESTAMP_H
