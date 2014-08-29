/**
 * Copyright 2012 Batis Degryll Ludo
 * @file FileHandler.cpp
 * @since 2014-05-25
 * @date 2014-05-25
 * @author Degryll
 * @brief To handle files and directories.
 */

#include "ZBE/core/io/FileHandler.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/utf8.h"
#include "sys/stat.h"
#include <stdio.h>

namespace zbe {

#ifdef __linux__
//  const std::string FileHandler::SEPARATORS("\\/");

#elif _WIN32
  const std::wstring FileHandler::SEPARATORS(L"\\/");

#endif // OS

bool FileHandler::exist(const char* filename) {
#ifdef __linux__
  struct stat buffer;
  return (stat(filename, &buffer) == 0 && (buffer.st_mode & S_IFREG));

#elif _WIN32
  std::wstring fn;
  zbe::utf8to16(back_inserter(fn),filename);

  struct _stat buffer;
  return (_wstat(fn.c_str(), &buffer) == 0 && (buffer.st_mode & _S_IFREG));

#endif // OS
}

bool FileHandler::existDir(const char* dirname) {
#ifdef __linux__
  struct stat buffer;
  return (stat(dirname, &buffer) == 0 && (buffer.st_mode & S_IFDIR));

#elif _WIN32
  std::wstring fn;
  zbe::utf8to16(back_inserter(fn),dirname);

  struct _stat buffer;
  return (_wstat(fn.c_str(), &buffer) == 0 && (buffer.st_mode & _S_IFDIR));

#endif // OS
}

int FileHandler::rm(const char* filename) {
#ifdef __linux__
  return (remove(filename));

#elif _WIN32
  std::wstring fn;
  zbe::utf8to16(back_inserter(fn),filename);

  return (_wremove(fn.c_str()));

#endif // OS
}

bool FileHandler::rmdir(const char* dirname) {
#ifdef __linux__
  return (remove(dirname));

#elif _WIN32
  std::wstring fn;
  zbe::utf8to16(back_inserter(fn),dirname);

  return (!RemoveDirectoryW(fn.c_str()));

#endif // OS
}

FileHandler::FileHandler(const char* filename, const char* mode, bool createPath) {
#ifdef __linux__
  std::string s(filename);
  if (createPath) {
    size_t lastslash = s.find_last_of(SEPARATORS);
    if(lastslash != std::string::npos) {
      if (createDirectories(s.substr(0,lastslash))) return;
    }
  }

  if(!(f=fopen(filename, mode))) {
    SysError::setError("FILE ERROR: Can't open file.");
  }

#elif _WIN32
  std::wstring fn;
  zbe::utf8to16(back_inserter(fn),filename);

  if (createPath) {
    size_t lastslash = fn.find_last_of(SEPARATORS);
    if(lastslash != std::wstring::npos) {
      if (createDirectories(fn.substr(0,lastslash))) return;
    }
  }

  std::wstring m;
  zbe::utf8to16(back_inserter(m),mode);
  if(_wfopen_s(&f,fn.c_str(), m.c_str())) {
    SysError::setError("FILE ERROR: Can't open file.");
  }

#endif // OS
}

FileHandler::~FileHandler() {
  if(fclose(f)) {
    SysError::setError("FILE ERROR: Can't close file.");
  }
}

size_t FileHandler::read(void* buffer, size_t size, size_t count) {
  return (fread(buffer,size,count,f));
}

char* FileHandler::readln(char* buffer, size_t buffersize) {
  return fgets(buffer,buffersize,f);
}

size_t FileHandler::write(const char* text) {
  int n = fprintf(f,"%s",text);

  if(n < 0) {
    zbe::SysError::setError("FILE ERROR: Can't write to file.");
    n = 0;
  }
  return static_cast<size_t>(n);
}

size_t FileHandler::write(const void* buffer, size_t size, size_t count) {
  return (fwrite(buffer,size,count,f));
}

size_t FileHandler::writeflush(const char* text) {
  int n = fprintf(f,"%s",text);
  fflush(f);
  if(n < 0) {
    zbe::SysError::setError("FILE ERROR: Can't write to file.");
    n = 0;
  }
  return static_cast<size_t>(n);
}

size_t FileHandler::writeflush(const void* buffer, size_t size, size_t count) {
  size_t n = fwrite(buffer,size,count,f);
  fflush(f);
  return (n);
}

size_t FileHandler::writeln(const char* text) {
  int n = fprintf(f,"%s\n",text);

  if(n < 0) {
    zbe::SysError::setError("FILE ERROR: Can't write to file.");
    n = 0;
  }
  return static_cast<size_t>(n);
}

size_t FileHandler::writeln(const void* buffer, size_t size, size_t count) {
  size_t n = fwrite(buffer,size,count,f);
  n += fwrite("\n",sizeof(char),1,f);
  return (n);
}

size_t FileHandler::writelnflush(const char* text) {
  int n = fprintf(f,"%s\n",text);
  fflush(f);
  if(n < 0) {
    zbe::SysError::setError("FILE ERROR: Can't write to file.");
    n = 0;
  }
  return static_cast<size_t>(n);
}

size_t FileHandler::writelnflush(const void* buffer, size_t size, size_t count) {
  size_t n = fwrite(buffer,size,count,f);
  n += fwrite("\n",sizeof(char),1,f);
  fflush(f);
  return (n);
}

void FileHandler::flush() {
  fflush(f);
}

#ifdef __linux__

bool FileHandler::createDirectories(std::string path) {
    std::size_t slashIndex = path.find_last_of(SEPARATORS);
    if(slashIndex != std::string::npos) {
      createDirectories(path.substr(0, slashIndex));
    }

    if(mkdir(path.c_str(), 0777)) {
      if (errno != EEXIST) {
        SysError::setError("FILE ERROR: Can't create directory.");
        return 1;
      }
    }

    return 0;
}

#elif _WIN32

bool FileHandler::createDirectories(std::wstring path) {
    std::size_t slashIndex = path.find_last_of(SEPARATORS);
    if(slashIndex != std::wstring::npos) {
      createDirectories(path.substr(0, slashIndex));
    }

    BOOL result = ::CreateDirectoryW(path.c_str(), 0);
    if(result == FALSE) {
      if (GetLastError() != ERROR_ALREADY_EXISTS) {
        SysError::setError("FILE ERROR: Can't create directory.");
        return 1;
      }
    }

    return 0;
}

#endif // OS

}  // namespace zbe
