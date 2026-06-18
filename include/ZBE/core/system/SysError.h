/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.h
 * @since 2013-11-23
 * @date 2017-05-15
 * @author Degryll
 * @brief A system class ZBEAPI to inform about errors.
 */

#ifndef ZBE_CORE_SYSTEM_SYSERROR_H_
#define ZBE_CORE_SYSTEM_SYSERROR_H_

#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A system class ZBEAPI to inform about errors.
 *
 *  Store the number of errors (calls to setError) and the text for the first
 *  error.
 */
class ZBEAPI SysError {
public:

  /** \brief Set a new error
   *
   * \param errorString the description of the error
   * \sa getNErrors() and getFirstErrorString()
   */
  static void setError(std::string errorString);

  /** \brief Set a new warning
   *
   * \param msgString the description of the warning
   * \sa getNErrors() and getFirstErrorString()
   */
  static void setWarning(std::string msgString);

    /** \brief Set a new info message
    *
    * \param msgString the description of the info message
    * \sa getNErrors() and getFirstErrorString()
    */
  static void setInfo(std::string msgString);


  /** \brief Set a new debug message
   *
   * \param msgString the description of the debug message
   * \sa getNErrors() and getFirstErrorString()
   */
  static void setDebug(std::string msgString, bool trace = false);
};

}  // namespace zbe

#endif  // ZBE_CORE_SYSTEM_SYSERROR_H_
