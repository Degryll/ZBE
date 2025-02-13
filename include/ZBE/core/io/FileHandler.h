/**
 * Copyright 2012 Batis Degryll Ludo
 * @file FileHandler.h
 * @since 2014-05-25
 * @date 2018-03-20
 * @author Degryll Batis Ludo
 * @brief class ZBEAPI capable of handle files in UTF8.
 */

#ifndef ZBE_CORE_IO_FILEHANDLER_H
#define ZBE_CORE_IO_FILEHANDLER_H

#ifdef __linux__
#include <errno.h>

#elif _WIN32
#include <windows.h>

#endif // OS

#include <string>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief class ZBEAPI capable of handle files in UTF8.
 */
class ZBEAPI FileHandler {
public:
#ifdef __linux__
  const std::string SEPARATORS = "\\/";  //!< Directory separators "\" and "/"

#elif _WIN32
  static const std::wstring SEPARATORS;  //!< Directory separators "\" and "/"

#endif // OS

  /** \brief Copy constructor. It builds another FileHandler over the same file as given one.
   *  \param rhs Instance to copy.
   */
  FileHandler(const FileHandler& rhs) : f(rhs.f) {}

  /** \brief Parametrized constructor.
   *  \param filename File path and name to open.
   *  \param mode Open mode (see fopen).
   *  \param createPath If the path should be created (default false).
   */
  FileHandler(const char* filename, const char* mode, bool createPath = false);

  /** \brief Destroys this FileHandler and closes the file.
   */
  ~FileHandler();

  /** \brief Copy operator. Makes current instance work over the same file as given one.
   *  \param rhs Instance to copy.
   */
  FileHandler& operator=(const FileHandler& rhs) {
    f = rhs.f;
    return (*this);
  }

  /** \brief Test if a filename is a normal file.
   *  \param filename The path to test.
   *  \return True if filename is a normal file.
   *  \sa existDir
   */
  static bool exist(const char* filename);

  /** \brief Test if a filename is a directory.
   *  \param filename The path to test.
   *  \return True if filename is a directory.
   *  \sa exist
   */
  static bool existDir(const char* dirname);

  /** \brief Removes a normal file.
   *  \param filename Path to the file to be removed.
   *  \return 0 on success.
   *  \sa rmdir
   */
  static bool rm(const char* filename);

  /** \brief Removes a directory.
   *  \param dirname Path to the file to be removed.
   *  \return 0 on success.
   *  \sa rm
   */
  static bool rmdir(const char* dirname);

  /** \brief Read elements from the file.
   *  \param buffer Buffer to store the data read.
   *  \param size Size in byte of each element.
   *  \param count Number of elements to read.
   *  \return Bytes read.
   */
  size_t read(void* buffer, size_t size, size_t count);

  /** \brief Read lines of text from the file.
   *  \param buffer Buffer to store the text read.
   *  \param size Size maximum number of bytes read.
   *  \return buffer.
   */
  char*  readln(char* buffer, size_t buffersize);

  /** \brief Write a text into the file.
   *  \param text Text to be written
   *  \return Number of bytes written.
   */
  size_t write(const char* text);

  /** \brief Write elements into the file.
   *  \param buffer Buffer with the elements
   *  \param size Size in bytes of each element
   *  \param count Number of elements to be written
   *  \return Number of bytes written.
   */
  size_t write(const void* buffer, size_t size, size_t count);

  /** \brief Write a text and flush the file.
   *  \param text Text to be written
   *  \return Number of bytes written.
   */
  size_t writeflush(const char* text);

  /** \brief Write elements and flush the file.
   *  \param buffer Buffer with the elements
   *  \param size Size in bytes of each element
   *  \param count Number of elements to be written
   *  \return Number of bytes written.
   */
  size_t writeflush(const void* buffer, size_t size, size_t count);

  /** \brief Write a text and a new line (\n) into the file.
   *  \param text Text to be written
   *  \return Number of bytes written.
   */
  size_t writeln(const char* text);

  /** \brief Write elements and a new line (\n) into the file.
   *  \param buffer Buffer with the elements
   *  \param size Size in bytes of each element
   *  \param count Number of elements to be written
   *  \return Number of bytes written.
   */
  size_t writeln(const void* buffer, size_t size, size_t count);

  /** \brief Write a text, a new line and flush the file.
   *  \param text Text to be written
   *  \return Number of bytes written.
   */
  size_t writelnflush(const char* text);

  /** \brief Write elements, a new line (\n) and flush the file.
   *  \param buffer Buffer with the elements
   *  \param size Size in bytes of each element
   *  \param count Number of elements to be written
   *  \return Number of bytes written.
   */
  size_t writelnflush(const void* buffer, size_t size, size_t count);

  /** \brief Flush the file, ensure that all pending writes are finished.
   */
  void flush();

//seek and set get pos

protected:
#ifdef __linux__
  /** \brief Create a directory .
   *  \param path Path to be created
   *  \return Zero on success.
   */
  bool createDirectories(std::string path);

#elif _WIN32
  /** \brief Create a directory .
   *  \param path Path to be created
   *  \return Zero on success.
   */
  bool createDirectories(std::wstring path);

#endif // OS

private:
  FILE *f;  //!< File object.
};

}  // namespace zbe

#endif  // ZBE_CORE_IO_FILEHANDLER_H
