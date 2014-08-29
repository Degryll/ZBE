/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Logger.h
 * @since 2014-05-16
 * @date 2014-05-16
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

#define ZBE_LOG_INFO(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::TINFO, lm << "> " << MSG); } while(0)

#define ZBE_LOG_DEBUG(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::TDEBUG, lm << __FILE__ << ":" << __LINE__ << "> " << MSG); } while(0)

#define ZBE_LOG_WARNING(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::TWARNING, lm << "> " << MSG); } while(0)

#define ZBE_LOG_ERROR(MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(zbe::Logger::TERROR, lm << "> " << MSG); } while(0)

#define ZBE_LOG(TYPE,MSG) \
do{ zbe::LoggerMsg lm; \
    zbe::Logger::getInstance()->log(TYPE, lm << "> " << MSG); } while(0)

namespace zbe {

class LoggerMsg {
  public:
    LoggerMsg() {};
    LoggerMsg(const LoggerMsg &l) {this->msg << l.msg.str();};

    virtual ~LoggerMsg() {};

    LoggerMsg& operator<<(bool b);

    template <typename T>
    LoggerMsg& operator<< (T t);

    std::stringstream msg;
};

template <typename T>
LoggerMsg& LoggerMsg::operator<<(T t) {
  this->msg << t;
  return (*this);
}

class Logger {
  public:
    static const char TINFO[];
    static const char TDEBUG[];
    static const char TWARNING[];
    static const char TERROR[];

    //Logger(bool standard = false);
    //Logger(const char *filename, bool commandLine = false);
    //virtual ~Logger();

    static Logger* createInstance() {return (_instance = new Logger);}
    static void    deleteInstance() {delete _instance;}
    static Logger* getInstance()    {return (_instance);}

    void setDefaultWriters();
    void setDefaultCommandLineWriter();
    void setDefaultFileWriters();

    using WriterCallback = void (*)(const char * type, const char * msg);

    void addWriter(WriterCallback callback);

    void log(const char * type, LoggerMsg msg);

  protected:
    static void defaultCommandLineWriter(const char * type, const char * msg);
    static void defaultFileWriter(const char * type, const char * msg);

  private:
    static Logger* _instance;
    //int typeno;
    //std::vector<const char*> typeStr;
    std::string filename;
    std::forward_list<WriterCallback> writers;
    std::mutex m;

    Logger() {}
};

}  // namespace zbe

#endif  // CORE_SYSTEM_LOGGER_H
