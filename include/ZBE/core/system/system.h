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
  #else
    #define ZBEAPI __declspec(dllimport)
  #endif

  #define ZBECALL __cdecl

#else
  #define ZBEAPI
  #define ZBECALL

#endif // OS

#endif  // ZBE_CORE_SYSTEM_SYSTEM_H_
