/**
 * Copyright 2012 Batis Degryll Ludo
 * @file FileHandler.h
 * @since 2014-05-25
 * @date 2014-08-23
 * @author Degryll
 * @brief To handle files.
 */

#ifndef CORE_IO_FILEHANDLER_H
#define CORE_IO_FILEHANDLER_H

#ifdef __linux__
  //something something

#elif _WIN32
  #include <windows.h>
  #include <sys/stat.h>

#endif // OS

#include <string>

namespace zbe {

class FileHandler {
  public:
#ifdef __linux__
  static const std::string SEPARATORS;

#elif _WIN32
  static const std::wstring SEPARATORS;

#endif // OS

    static bool exist(const char* filename);
    static bool existDir(const char* filename);
    static int rm(const char* filename);
    static bool rmdir(const char* filename);

    FileHandler(const char* filename, const char* mode, bool createPath = false);
    ~FileHandler();

    size_t read(void* buffer, size_t size, size_t count);
    char*  readln(char* buffer, size_t buffersize);

    size_t write(const char* text);
    size_t write(const void* buffer, size_t size, size_t count);
    size_t writeflush(const char* text);
    size_t writeflush(const void* buffer, size_t size, size_t count);

    size_t writeln(const char* text);
    size_t writeln(const void* buffer, size_t size, size_t count);
    size_t writelnflush(const char* text);
    size_t writelnflush(const void* buffer, size_t size, size_t count);

    void flush();

  //seek and set get pos

  protected:
#ifdef __linux__
  //something something

#elif _WIN32
    bool createDirectories(std::wstring path);

#endif // OS

  private:
    FILE *f;
    // [TODO] Degryll puede ser interesante
    // [TODO] Degryll que el path use DirHandler
//    const char* filename;
//    const char* name;
//    const char* ext;
//    const char* abspath;
};

}  // namespace zbe

#endif // CORE_IO_FILEHANDLER_H
