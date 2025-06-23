#include "ZBE/core/io/FileHandler.h"

#include <cstdio>
#include <filesystem>
#include <fstream>

#include "ZBE/core/system/SysError.h"

namespace zbe {

namespace fs = std::filesystem;

//  const std::string FileHandler::SEPARATORS = "\\/";  // Común en todas plataformas

bool FileHandler::exist(const char* filename) {
    return fs::is_regular_file(filename);
}

bool FileHandler::existDir(const char* dirname) {
    return fs::is_directory(dirname);
}

bool FileHandler::rm(const char* filename) {
    std::error_code ec;
    return fs::remove(filename, ec);
}

bool FileHandler::rmdir(const char* dirname) {
    std::error_code ec;
    return fs::remove_all(dirname, ec) > 0;
}

FileHandler::FileHandler(const char* filename, const char* mode, bool createPath) : f(nullptr) {
    std::string filepath(filename);

    if (createPath) {
        fs::path dirPath = fs::path(filepath).parent_path();
        if (!dirPath.empty()) {
            std::error_code ec;
            if (!fs::create_directories(dirPath, ec) && ec) {
                SysError::setError("FILE ERROR: Can't create directory: " + dirPath.string());
                return;
            }
        }
    }

#if defined(_MSC_VER)  // Use "safe" fopen_s in MSVC
    if (fopen_s(&f, filename, mode) != 0) {
        f = nullptr;
    }
#else
    f = fopen(filename, mode);
#endif

    if (!f) {
        SysError::setError("FILE ERROR: Can't open file.");
    }
}

FileHandler::~FileHandler() {
    if (f && fclose(f)) {
        SysError::setError("FILE ERROR: Can't close file.");
    }
}

size_t FileHandler::read(void* buffer, size_t size, size_t count) {
    return fread(buffer, size, count, f);
}

char* FileHandler::readln(char* buffer, size_t buffersize) {
    return fgets(buffer, static_cast<int>(buffersize), f);
}

size_t FileHandler::write(const char* text) {
    int n = fprintf(f, "%s", text);
    if (n < 0) {
        SysError::setError("FILE ERROR: Can't write to file.");
        n = 0;
    }
    return static_cast<size_t>(n);
}

size_t FileHandler::write(const void* buffer, size_t size, size_t count) {
    return fwrite(buffer, size, count, f);
}

size_t FileHandler::writeflush(const char* text) {
    int n = fprintf(f, "%s", text);
    fflush(f);
    if (n < 0) {
        SysError::setError("FILE ERROR: Can't write to file.");
        n = 0;
    }
    return static_cast<size_t>(n);
}

size_t FileHandler::writeflush(const void* buffer, size_t size, size_t count) {
    size_t n = fwrite(buffer, size, count, f);
    fflush(f);
    return n;
}

size_t FileHandler::writeln(const char* text) {
    int n = fprintf(f, "%s\n", text);
    if (n < 0) {
        SysError::setError("FILE ERROR: Can't write to file.");
        n = 0;
    }
    return static_cast<size_t>(n);
}

size_t FileHandler::writeln(const void* buffer, size_t size, size_t count) {
    size_t n = fwrite(buffer, size, count, f);
    n += fwrite("\n", sizeof(char), 1, f);
    return n;
}

size_t FileHandler::writelnflush(const char* text) {
    int n = fprintf(f, "%s\n", text);
    fflush(f);
    if (n < 0) {
        SysError::setError("FILE ERROR: Can't write to file.");
        n = 0;
    }
    return static_cast<size_t>(n);
}

size_t FileHandler::writelnflush(const void* buffer, size_t size, size_t count) {
    size_t n = fwrite(buffer, size, count, f);
    n += fwrite("\n", sizeof(char), 1, f);
    fflush(f);
    return n;
}

void FileHandler::flush() {
    fflush(f);
}

bool FileHandler::createDirectories(std::string path) {
    std::error_code ec;
    if (!fs::create_directories(path, ec)) {
        if (!fs::exists(path)) {
            SysError::setError("FILE ERROR: Can't create directory: " + path);
            return false;
        }
    }
    return true;
}

}  // namespace zbe