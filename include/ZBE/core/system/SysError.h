/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.h
 * @since 2013-11-23
 * @date 2015-10-21
 * @author Degryll
 * @brief A system class to inform about errors.
 */

#ifndef CORE_SYSTEM_SYSERROR_H_
#define CORE_SYSTEM_SYSERROR_H_

#include <string>

namespace zbe {

/** \brief A system class to inform about errors.
 *
 *  Store the number of errors (calls to setError) and the text for the first
 *  error.
 */
class SysError {
public:

  /** \brief Set a new error
   *
   *  Increment the error counter in 1. If this is the first call, also stores
   *  the errorString string.
   *
   * \param errorString the description of the error
   * \sa getNErrors() and getFirstErrorString()
   */
  static void setError(std::string errorString);

  /** \brief Return the number of calls to setError.
   *
   * \return the number of errors so far.
   * \sa setError() and clear()
   */
  static int getNErrors();

  /** \brief Return the error message of the first error.
   *
   *  If there is, at least, one call to setError, this function
   *  return the string message of the first error, empty string otherwise.
   *
   * \return the first (if any) error string.
   * \sa setError() and clear()
   */
  static std::string getFirstErrorString();

  /** \brief Set error counter to 0 and empty the error string.
   */
  static void clear();

private:
        static int nerrors;
        static std::string errorString;
};

}  // namespace zbe

#endif  // CORE_SYSTEM_SYSERROR_H_
