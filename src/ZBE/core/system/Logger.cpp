/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Logger.cpp
 * @since 2014-05-16
 * @date 2014-05-16
 * @author Degryll
 * @brief To create Logs.
 */

#include "ZBE/core/system/Logger.h"
#include "ZBE/core/io/FileHandler.h"

#include <iostream>

namespace zbe {

Logger* Logger::_instance = nullptr;

LoggerMsg& LoggerMsg::operator<<(bool b) {
  this->msg << ((b) ? "true" : "false");
  return (*this);
}

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

void Logger::setDefaultFileWriters() {
  addWriter(&defaultFileWriter);
}

void Logger::addWriter(WriterCallback callback) {
  writers.push_front(callback);
}

void Logger::defaultCommandLineWriter(const char * type, const char * msg) {
  // cout is used instead of printf because is more easy to build test cases,
  // redirecting cout is simple and platform inddependent than redirecting
  // printf.
  std::cout << type << msg << std::endl;
  fflush(stdout);
}

void Logger::defaultFileWriter(const char * type, const char * msg) {
  FileHandler f("system.log","a");
  f.write(type);
  f.writelnflush(msg);
}

void Logger::log(const char * type, LoggerMsg msg) {
  for(WriterCallback& writer : writers) {
    m.lock();
      writer(type, msg.msg.str().c_str());
    m.unlock();
  }
}

}  // namespace zbe
