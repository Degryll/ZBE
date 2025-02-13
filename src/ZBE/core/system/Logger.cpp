/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Logger.cpp
 * @since 2014-05-16
 * @date 2015-10-24
 * @author Degryll
 * @brief To create Logs.
 */

#include "ZBE/core/system/Logger.h"
#include "ZBE/core/io/FileHandler.h"

#include <iostream>

namespace zbe {

LoggerMsg& LoggerMsg::operator<<(bool b) {
  this->msg << ((b) ? "true" : "false");
  return (*this);
}

const int Logger::IDINFO = 1;
const int Logger::IDDEBUG = 2;
const int Logger::IDWARNING = 3;
const int Logger::IDERROR = 4;

const char Logger::TINFO[] = "[INFO]";
const char Logger::TDEBUG[] = "[DEBUG]";
const char Logger::TWARNING[] = "[WARNING]";
const char Logger::TERROR[] = "[ERROR]";

void Logger::setDefaultWriters() {
  addWriter(&defaultCommandLineWriter);
  addWriter(&defaultFileWriter);
}

void Logger::setDefaultCommandLineWriter() {
  addWriter(&defaultCommandLineWriter);
}

void Logger::setDefaultFileWriter() {
  addWriter(&defaultFileWriter);
}

void Logger::addWriter(WriterCallback callback) {
  writers.push_front(callback);
}

void Logger::defaultCommandLineWriter(int , const char *msgtype, const char *msg) {
  // cout is used instead of printf because is more easy to build test cases,
  // redirecting cout is simple and platform independent than redirecting
  // printf.
  std::cout << msgtype << msg << std::endl;
  std::cout.flush();
}

void Logger::defaultFileWriter(int , const char *msgtype, const char *msg) {
  FileHandler f("system.log","a");
  f.write(msgtype);
  f.writelnflush(msg);
}

void Logger::log(int ntype, const char *msgtype, LoggerMsg msg) {
  for(WriterCallback& writer : writers) {
    m.lock();
      writer(ntype, msgtype, msg.msg.str().c_str());
    m.unlock();
  }
}

}  // namespace zbe
