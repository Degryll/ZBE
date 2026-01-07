/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SysError.cpp
 * @since 2013-11-23
 * @date 2018-03-27
 * @author Degryll Batis Ludo
 * @brief System to inform about errors.
 */

#include "ZBE/core/system/SysError.h"
#include <spdlog/spdlog.h>
#include <execinfo.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cstdio>

std::string print_stacktrace() {
  // TODO: Decidir si queremo usar esta forma de buscar el call stack.
  // Con este método el ejecutable (ZandBokz) no muestra su propio stack trace.
  // Eso incluye todo el código que se compila desde ZandBokz por estar en un .h
  const int MAX_FRAMES = 100;
  void* frames[MAX_FRAMES];

  // Captura el call stack
  int size = backtrace(frames, MAX_FRAMES);

  // Convierte las direcciones en símbolos legibles
  char** symbols = backtrace_symbols(frames, size);

  std::string output = "Call stack (" + std::to_string(size) + " frames):\n";
  for (int i = 0; i < size; ++i) {
      output += std::to_string(i) + ": " + std::string(symbols[i]) + "\n";
  }

  free(symbols);
  return output;
}


namespace zbe {

int SysError::nerrors = 0;
std::string SysError::errorString = "";

int SysError::getNErrors() {
  return (nerrors);
}

std::string SysError::getFirstErrorString() {
  return (errorString);
}

void SysError::setError(std::string errorString) {
  SPDLOG_ERROR("SysError: {}", errorString);
  // TODO ¿Esta es la forma en la que queremos mostrar el stack trace?
  SPDLOG_TRACE("Generating stack trace:" + print_stacktrace());
  if (!SysError::nerrors) {
          SysError::errorString = errorString;
  }
  SysError::nerrors++;
}

void SysError::clear() {
  SysError::nerrors = 0;
  SysError::errorString = "";
}

}  // namespace zbe
