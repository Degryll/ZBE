/**
 * Copyright 2012 Batis Degryll Ludo
 * @file State.h
 * @since 2017-06-04
 * @date 2017-06-04
 * @author Degryll Ludo Batis
 * @brief Defines the interface of a class with a state.
 */

#ifndef ZBE_ARCHETYPES_STATE_H
#define ZBE_ARCHETYPES_STATE_H

namespace zbe {

class State {
public:
  /** \brief Virtual destructor.
   */
  virtual ~State() {}

  /** \brief Setter for the state attribute.
   *  \param state The integer value for the state.
   */
  virtual void setState(uint64_t state) = 0;

  /** \brief Getter for the state attribute.
   *  \return The integer value of the state.
   */
  virtual uint64_t getState() = 0;
};

} // namespace zbe

#endif  // ZBE_ARCHETYPES_STATE_H



  /** \brief Setter for the state attribute.
   *  \param state The integer value for the state.
   */


