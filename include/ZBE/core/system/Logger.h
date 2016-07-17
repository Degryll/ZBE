/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Logger.h
 * @since 2014-05-16
 * @date 2015-10-24
 * @author Degryll
 * @brief To create Logs.
 */

#ifndef CORE_SYSTEM_LOGGER_H
#define CORE_SYSTEM_LOGGER_H

#include <vector>
#include <forward_list>
#include <string>
#include <sstream>
#include <mutex>

/** \brief Add a [INFO] annotation to the logs.
 *
 *  Used to add information messages to the logs.
 */
#define ZBE_LOG_INFO(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::NINFO, zbe::Logger::TINFO, lm << "> " << MSG); } while(0)

/** \brief Add a [DEBUG] annotation to the logs.
 *
 *  Used to add debug messages to the logs, this annotation also include the
 *  file and line where the message comes from.
 */
#define ZBE_LOG_DEBUG(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::NDEBUG, zbe::Logger::TDEBUG, lm << __FILE__ << ":" << __LINE__ << "> " << MSG); } while(0)

/** \brief Add a [WARNING] annotation to the logs.
 *
 *  Used to add warning messages to the logs.
 */
#define ZBE_LOG_WARNING(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::NWARNING, zbe::Logger::TWARNING, lm << "> " << MSG); } while(0)

/** \brief Add a [ERROR] annotation to the logs.
 *
 *  Used to add error messages to the logs.
 */
#define ZBE_LOG_ERROR(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::NERROR, zbe::Logger::TERROR, lm << "> " << MSG); } while(0)

/** \brief Add an user defined annotation to the logs.
 *
 *  Used to add messages to the logs with custom type ([TYPE]).
 */
#define ZBE_LOG_OTHER(MSGTYPE,MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(-1,MSGTYPE, lm << "> " << MSG); } while(0)

/** \brief Add an user defined annotation to the logs.
 *
 *  Used to add messages to the logs with custom type ([TYPE]) and type number (NTYPE).
 */
#define ZBE_LOG(NTYPE,MSGTYPE,MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(NTYPE, MSGTYPE, lm << "> " << MSG); } while(0)

namespace zbe {

/** \brief Wrapper class to use the operator "<<" in the log messages.
 *
 *  This class is not used directly.
 *
 *  This class let us use the operator "<<" to concatenate distinct type of variables.
 *  i.e.:
 *
 *        int a = 3;
 *        double b = 3.1415;
 *        bool c = true;
 *        ZBE_LOG_INFO("A message with " << a << " variables ( " << b << ") of distinct type: " << c);
 *
 *  > [INFO]> A message with 3 variables (3.1415) of distinct type: true;
 *
 *  This class also change the printed value of a bool variable from 1 or 0 to
 *  "true" or "false.
 *
 *  To use a custom type in the message composition, the new type should define an operator<<
 *  that returns a stringstream compatible type, i.e. a std::string.
 */
class LoggerMsg {
public:
  /** \brief Void constructor.
   */
  LoggerMsg() {};

  /** \brief Copy constructor.
   */
  LoggerMsg(const LoggerMsg &l) {this->msg << l.msg.str();};

  ~LoggerMsg() {};

  /** \brief Define operator<< to build a std::stringstream.
   */
  template <typename T>
  LoggerMsg& operator<< (T t);

  /** \brief Specialization of operator<< for bool values (to print "true" or "false" instead of 1 or 0).
   */
  LoggerMsg& operator<<(bool b);

  std::stringstream msg; //!< Used to store the Logger message.
};

template <typename T>
LoggerMsg& LoggerMsg::operator<<(T t) {
  this->msg << t;
  return (*this);
}

/** \brief A class to handle logs.
 *
 *  This class implements singleton pattern so:
 *
 *    - There is no constructor, someone should call createInstance one to create the unique Logger.
 *    - To configure the Logger call getInstance and use the pointer to the unique Logger to configure it.
 *    - To use the Logger use directly the [macros](@ref Logger.h), i.e.:
 *
 *          int a = 3;
 *          double b = 3.1415;
 *          bool c = true;
 *          ZBE_LOG_INFO("A message with " << a << " variables ( " << b << ") of distinct type: " << c);
 *          ZBE_LOG_DEBUG("A debug message, it includes the file and line number automatically.");
 *          ZBE_LOG_WARNING("A warning message.");
 *          ZBE_LOG_ERROR("An error message.");
 *          ZBE_LOG("CUSTOM","A message for a user defined type.");
 *
 *    > [INFO]> A message with 3 variables (3.1415) of distinct type: true\n
 *    > [DEBUG]/path/file.cpp:123> A debug message, it includes the file and line number automatically.\n
 *    > [WARNING]> A warning message.\n
 *    > [ERROR]> A warning message.\n
 *    > [CUSTOM]> A message for a user defined type.\n
 *
 *  Before use this class (with the [macros](@ref Logger.h)) you need to configure the writers,
 *  this means, tell the Logger what kind of logs (file, console, etc.) do you want to use. You can set default writes calling:
 *  - `setDefaultFileWriter()` for file logs, it writes to `./system.log`.
 *  - `setDefaultCommandLineWriter()` for console logs (write to `stdout`).
 *  - `setDefaultWriters()` to set both writers.
 */
class Logger {
public:
  static const int NINFO;       //!< Id of INFO annotations
  static const int NDEBUG;      //!< Id of DEBUG annotations
  static const int NWARNING;    //!< Id of WARNING annotations
  static const int NERROR;      //!< Id of ERROR annotations
  static const char TINFO[];    //!< Text of INFO annotations
  static const char TDEBUG[];   //!< Text of DEBUG annotations
  static const char TWARNING[]; //!< Text of WARNING annotations
  static const char TERROR[];   //!< Text of ERROR annotations

  //Logger(bool standard = false);
  //Logger(const char *filename, bool commandLine = false);
  //virtual ~Logger();

  /** \brief Create the Logger instance
   *
   *  Create the unique logger.
   *
   *  Call it only once. Remember to call `deleteInstance()` when you finish using it.
   *
   * \sa getInstance() and deleteInstance()
   */
  static Logger* createInstance() {return (_instance = new Logger);}

  /** \brief Delete the Logger instance
   *
   *  Delete the unique logger.
   *
   * \sa createInstance()
   */
  static void    deleteInstance() {delete _instance;}

  /** \brief Return the Logger instance
   *
   *  Used to configure the Logger, to use it you don't need to access the Logger directly, you should use the defined [macros](@ref Logger.h).
   *
   * \sa createInstance() and deleteInstance()
   */
  static Logger* getInstance()    {return (_instance);}

  /** \brief Add a file writer to the Logger.
   *
   *  If this writer is set, it will print every log message to `./system.log`.
   *
   * \sa setDefaultCommandLineWriter(), setDefaultWriters() and addWriter()
   */
  void setDefaultFileWriter();

  /** \brief Add a command line writer to the Logger.
   *
   *  If this writer is set, it will print every log message to `stdout` (usually the command line).
   *
   * \sa setDefaultFileWriter(), setDefaultWriters() and addWriter()
   */
  void setDefaultCommandLineWriter();

  /** \brief Add a file and command line writers to the Logger.
   *
   *  If this writer is set, it will print every log message to `stdout` and `./system.log`.
   *  Is the same as calling `setDefaultFileWriter()` and `setDefaultCommandLineWriter()`.
   *
   * \sa setDefaultFileWriter(), setDefaultCommandLineWriter() and addWriter()
   */
  void setDefaultWriters();

  /** \brief Define a user defined writer to use with the Logger.
   *
   *  A `WriterCallback` is a function pointer like this:
   *
   *      void (*)(int ntype, const char * msgtype, const char * msg);
   *
   *  - ntype: represent the type of the annotation to the log. Use it to differentiate annotations (i.e. changing colors).
   *  - msgtype: a text to identify the annotation, typically, a name surrounded by "[" and "]" (i.e. [INFO] or [DEBUG]).
   *  - msg: the message to be annotated.
   *
   * \sa setDefaultFileWriter(), setDefaultCommandLineWriter() and setDefaultWriters()
   */
  using WriterCallback = void (*)(int ntype, const char * msgtype, const char * msg);

  /** \brief Add a user defined writer to the Logger.
   *
   *  A writer should be declared as a `WriterCallbak` function.
   *
   *  Each time you use the Logger (using the [macros](@ref Logger.h)), it calls all the functions added to the Logger.
   *
   * \sa setDefaultFileWriter(), setDefaultCommandLineWriter() and setDefaultWriters()
   */
  void addWriter(WriterCallback callback);
  // TODO delWriter

  /** \brief Log a new annotation.
   *
   *  Don't use this function directly, use the [macros](@ref Logger.h).
   */
  void log(int ntype, const char * msgtype, LoggerMsg msg);

protected:
  /** \brief Definition of the file writer.
   */
  static void defaultFileWriter(int ntype, const char * msgtype, const char * msg);

  /** \brief Definition of the command line writer.
   */
  static void defaultCommandLineWriter(int ntype, const char * msgtype, const char * msg);

private:
  static Logger* _instance;
  std::string filename;
  std::forward_list<WriterCallback> writers;
  std::mutex m;

  Logger() {}
};

}  // namespace zbe

#endif  // CORE_SYSTEM_LOGGER_H
