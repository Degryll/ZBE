/**
 * Copyright 2012 Batis Degryll Ludo
 * @file system.h
 * @since 2018-10-17
 * @date 2018-10-17
 * @author Batis Degryll Ludo
 * @brief
 */

#ifndef ZBE_CORE_SYSTEM_SYSTEM_H_
#define ZBE_CORE_SYSTEM_SYSTEM_H_

#ifdef _WIN32

  #ifdef ZBE_EXPORTS
    #define ZBEAPI __declspec(dllexport)
    #define EXPIMP_TEMPLATE
  #else
    #define ZBEAPI __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
  #endif

  #define ZBECALL __cdecl

#else
  #define ZBEAPI
  #define ZBECALL

#endif // OS

#ifdef _MSC_VER
  #pragma warning(disable:C4458)
  #define DISABLE_WARNING_PUSH(code) \
    __pragma(warning(push))          \
    __pragma(warning(disable : code))

  #define DISABLE_WARNING_POP() \
    __pragma(warning(pop))
  #define DISABLE_DLL_WARN DISABLE_WARNING_PUSH(4251)
#else
  #define DISABLE_WARNING_PUSH(code)
  #define DISABLE_DLL_WARN
  #define DISABLE_WARNING_POP()
#endif

#endif  // ZBE_CORE_SYSTEM_SYSTEM_H_
