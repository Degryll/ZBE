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
#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#else
#include <execinfo.h>
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

std::string print_stacktrace() {
#ifdef _WIN32
  const int MAX_FRAMES = 100;
  void* frames[MAX_FRAMES];
  HANDLE process = GetCurrentProcess();
  SymInitialize(process, NULL, TRUE);
  int size = CaptureStackBackTrace(0, MAX_FRAMES, frames, NULL);
  std::string output = "Call stack (" + std::to_string(size) + " frames):\n";
  for (int i = 0; i < size; ++i) {
    DWORD64 address = (DWORD64)frames[i];
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen = MAX_SYM_NAME;
    if (SymFromAddr(process, address, 0, pSymbol)) {
      output += std::to_string(i) + ": " + std::string(pSymbol->Name) + " at 0x" + std::to_string(address) + "\n";
    } else {
      output += std::to_string(i) + ": 0x" + std::to_string(address) + "\n";
    }
  }
  SymCleanup(process);
  return output;
#else
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
#endif
}


namespace zbe {

void SysError::setError(std::string errorString) {
  SPDLOG_ERROR("{}", errorString);
  // TODO ¿Esta es la forma en la que queremos mostrar el stack trace?
  SPDLOG_TRACE("Generating stack trace:" + print_stacktrace());
}

void SysError::setWarning(std::string msgString) {
  SPDLOG_WARN("{}", msgString);
  SPDLOG_TRACE("Generating stack trace:" + print_stacktrace());
}

void SysError::setInfo(std::string msgString) {
  SPDLOG_INFO("{}", msgString);
}

void SysError::setDebug(std::string msgString, bool trace) {
  SPDLOG_DEBUG("{}", msgString);
  if (trace) {
    SPDLOG_TRACE("Generating stack trace:" + print_stacktrace());
  }
}

}  // namespace zbe
