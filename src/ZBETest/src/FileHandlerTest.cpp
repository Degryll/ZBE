#include "gtest/gtest.h"

#include "ZBE/core/io/FileHandler.h"
#include "ZBE/core/system/SysError.h"

TEST(FileHandler, Exist) {
  EXPECT_TRUE(zbe::FileHandler::exist("src/ZBETest/src/FileHandlerTest.cpp")) << "This file exist.";
  EXPECT_FALSE(zbe::FileHandler::exist("NOEXIST")) << "A file that does not exist.";
  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448.txt";
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "An UTF-8 filename and path.";
}

TEST(FileHandler, ExistDir) {
  EXPECT_TRUE(zbe::FileHandler::existDir("src/ZBETest/src")) << "This dir exist.";
  EXPECT_FALSE(zbe::FileHandler::existDir("NOEXIST")) << "A dir that does not exist.";
  EXPECT_FALSE(zbe::FileHandler::existDir("src/ZBETest/src/FileHandlerTest.cpp")) << "This file is not a dir.";
  char dirname[] = "data/test/\u65e5\u0448";
  EXPECT_TRUE(zbe::FileHandler::existDir(dirname)) << "An UTF-8 path.";
}

TEST(FileHandler, OpenClose) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Open existent file
  zbe::FileHandler *f = new zbe::FileHandler("src/ZBETest/src/FileHandlerTest.cpp","r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open file:" << zbe::SysError::getLastErrorString();
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close file.";

  // Open existent UTF-8 file
  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448.txt";
  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close UTF-8 file.";

  // Open no existent file
  f = new zbe::FileHandler("NOEXIST","r");
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Open no existent file and an error is set.";
  EXPECT_STREQ("FILE ERROR: Can't open file.",zbe::SysError::getLastErrorString().c_str()) << "Check for the expected error.";
  zbe::SysError::clear();
}

TEST(FileHandler, CreateDeleteFile) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_FALSE(zbe::FileHandler::exist("NOEXIST")) << "A file that does not exist.";

  // Create no existent file
  zbe::FileHandler *f = new zbe::FileHandler("NOEXIST","w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create File.";
  EXPECT_TRUE(zbe::FileHandler::exist("NOEXIST")) << "Now the file exist.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close File.";

  // Remove existent file
  EXPECT_TRUE(zbe::FileHandler::exist("NOEXIST")) << "The file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm("NOEXIST")) << "Delete file.";
  EXPECT_FALSE(zbe::FileHandler::exist("NOEXIST")) << "The file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";

  // Create no existent UTF-8 file
  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448bar.txt";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "A UTF-8 file that does not exist.";
  f = new zbe::FileHandler(filename,"w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create UTF-8 File.";
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "Now the UTF-8 file exist.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close UTF-8 file.";

  // Remove existent UTF-8 file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}

TEST(FileHandler, CreateDeleteDirFile) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_FALSE(zbe::FileHandler::exist("foo/bar")) << "A file that does not exist.";
  EXPECT_FALSE(zbe::FileHandler::existDir("foo")) << "A dir that does not exist.";

  // Create no existent file and dir
  zbe::FileHandler *f = new zbe::FileHandler("foo/bar","w",true);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create File.";
  EXPECT_TRUE(zbe::FileHandler::exist("foo/bar")) << "Now the file exist.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close File.";

  // Remove existent file and dir
  EXPECT_TRUE(zbe::FileHandler::exist("foo/bar")) << "The file and dir still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm("foo/bar")) << "Delete file.";
  EXPECT_FALSE(zbe::FileHandler::exist("foo/bar")) << "The file no longer exist.";
  EXPECT_EQ(0,zbe::FileHandler::rmdir("foo")) << "Delete dir.";
  EXPECT_FALSE(zbe::FileHandler::existDir("foo")) << "The dir no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";

  // Create no existent UTF-8 file and dir
  char filename[] = "data/test/\u65e5\u0448foo/\u65e5\u0448bar.txt";
  char dirname[] = "data/test/\u65e5\u0448foo";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "A UTF-8 file that does not exist.";
  EXPECT_FALSE(zbe::FileHandler::existDir(dirname)) << "A UTF-8 dir that does not exist.";

  f = new zbe::FileHandler(filename,"w",true);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create UTF-8 file and dir.";
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "Now the UTF-8 file and dir exist.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close UTF-8 file.";

  // Remove existent UTF-8 file and dir
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file and dir still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::FileHandler::rmdir(dirname)) << "Delete UTF-8 dir.";
  EXPECT_FALSE(zbe::FileHandler::existDir(dirname)) << "The UTF-8 dir no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}

TEST(FileHandler, Read) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Open File
  zbe::FileHandler *f = new zbe::FileHandler("src/ZBETest/src/FileHandlerTest.cpp","r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open file.";

  char buffer[17];
  buffer[16] = 0;
  EXPECT_EQ(static_cast<size_t>(16),f->read(buffer,1,16)) << "Reading first 16 bytes.";
  EXPECT_STREQ("#include \"gtest/",buffer) << "Checking the first 16 bytes.";
  EXPECT_EQ(static_cast<size_t>(16),f->read(buffer,1,16)) << "Reading second 16 bytes.";
  EXPECT_STREQ("gtest.h\"\n\n#inclu",buffer) << "Checking the second 16 bytes.";
  EXPECT_EQ(static_cast<size_t>(16),f->read(buffer,1,16)) << "Reading third 16 bytes.";
  EXPECT_STREQ("de \"ZBE/core/io/",buffer) << "Checking the third 16 bytes.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close file.";

  // Open UTF-8 File
  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448.txt";
  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file.";

  EXPECT_EQ(static_cast<size_t>(16),f->read(buffer,1,16)) << "Reading first 16 bytes.";
  EXPECT_STREQ("\xef\xbb\xbf\"testutf82.tx",buffer) << "Checking the first 16 bytes.";
  EXPECT_EQ(static_cast<size_t>(14),f->read(buffer,1,14)) << "Reading second 14 bytes.";
  buffer[14] = 0;
  EXPECT_STREQ("t\" \"Hello, \u4e16",buffer) << "Checking the second 14 bytes.";
  EXPECT_EQ(static_cast<size_t>(16),f->read(buffer,1,16)) << "Reading third 16 bytes.";
  EXPECT_STREQ("\u754c\" \u65e5\u0448 fin\na",buffer) << "Checking the third 16 bytes.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close file.";
}

TEST(FileHandler, ReadLine) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  // Open File
  zbe::FileHandler *f = new zbe::FileHandler("src/ZBETest/src/FileHandlerTest.cpp","r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open file.";

  char buffer[256];
  buffer[255] = 0;
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading first Line.";
  EXPECT_STREQ("#include \"gtest/gtest.h\"\n",buffer) << "Checking first line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading second Line.";
  EXPECT_STREQ("\n",buffer) << "Second line." << buffer;
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading third Line.";
  EXPECT_STREQ("#include \"ZBE/core/io/FileHandler.h\"\n",buffer) << "Checking third line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close file.";

  // Open UTF-8 File
  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448.txt";
  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading first Line.";
  EXPECT_STREQ("\xef\xbb\xbf\"testutf82.txt\" \"Hello, \u4e16\u754c\" \u65e5\u0448 fin\n",buffer) << "Checking first line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading second Line.";
  EXPECT_STREQ("asdflo, \u4e16\n",buffer) << "Checking second line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading third Line.";
  EXPECT_STREQ("\u754c\" \u65e5\u0448 hello\n",buffer) << "Checking third line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close file.";
}

TEST(FileHandler, Write) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448bar.txt";
  zbe::FileHandler *f = new zbe::FileHandler(filename,"w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for writing.";

  char buffer[256];
  strcpy(buffer,"Some txt with utf-8 character like \u65e5 or \u4e16. ");
  EXPECT_EQ(static_cast<size_t>(47),f->write(buffer,1,47)) << "Write first line.";
  strcpy(buffer,"Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n");
  EXPECT_EQ(static_cast<size_t>(48),f->write(buffer,1,48)) << "Write second line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close writed file.";

  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for reading.";

  EXPECT_EQ(static_cast<size_t>(47),f->read(buffer,1,47)) << "Reading first 47 bytes.";
  buffer[47] = 0;
  EXPECT_STREQ("Some txt with utf-8 character like \u65e5 or \u4e16. ",buffer) << "Checking first 47 bytes.";
  EXPECT_EQ(static_cast<size_t>(48),f->read(buffer,1,48)) << "Reading another 45 bytes.";
  buffer[48] = 0;
  EXPECT_STREQ("Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n",buffer) << "Checking another 45 bytes.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close readed file.";

  // Remove UTF-8 file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}

TEST(FileHandler, Writeline) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448bar2.txt";
  zbe::FileHandler *f = new zbe::FileHandler(filename,"w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for writing.";

  char buffer[256];
  strcpy(buffer,"Some txt with utf-8 character like \u65e5 or \u4e16. ");
  EXPECT_EQ(static_cast<size_t>(48),f->writeln(buffer,1,47)) << "Write first line.";
  strcpy(buffer,"Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n");
  EXPECT_EQ(static_cast<size_t>(49),f->writeln(buffer,1,48)) << "Write second line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close writed file.";

  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for reading.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading first Line.";
  EXPECT_STREQ("Some txt with utf-8 character like \u65e5 or \u4e16. \n",buffer) << "Checking first line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading second Line.";
  EXPECT_STREQ("Used for testing.\n",buffer) << "Checking second line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading third Line.";
  EXPECT_STREQ("\t Something more 5$326\u00f1\u00d1\u00fc.\n",buffer) << "Checking third line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading forth Line.";
  EXPECT_STREQ("\n",buffer) << "Checking forth line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close readed file.";

  // Remove UTF-8 file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}

TEST(FileHandler, WriteNullTerminated) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448bar.txt";
  zbe::FileHandler *f = new zbe::FileHandler(filename,"w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for writing.";

  char buffer[256];
  strcpy(buffer,"Some txt with utf-8 character like \u65e5 or \u4e16. ");
  EXPECT_EQ(static_cast<size_t>(47),f->write(buffer)) << "Write first line.";
  strcpy(buffer,"Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n");
  EXPECT_EQ(static_cast<size_t>(48),f->write(buffer)) << "Write second line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close writed file.";

  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for reading.";

  EXPECT_EQ(static_cast<size_t>(47),f->read(buffer,1,47)) << "Reading first 47 bytes.";
  buffer[47] = 0;
  EXPECT_STREQ("Some txt with utf-8 character like \u65e5 or \u4e16. ",buffer) << "Checking first 47 bytes.";
  EXPECT_EQ(static_cast<size_t>(48),f->read(buffer,1,48)) << "Reading another 45 bytes.";
  buffer[48] = 0;
  EXPECT_STREQ("Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n",buffer) << "Checking another 45 bytes.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close readed file.";

  // Remove UTF-8 file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}

TEST(FileHandler, WritelineNullTerminated) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  char filename[] = "data/test/\u65e5\u0448/\u65e5\u0448bar2.txt";
  zbe::FileHandler *f = new zbe::FileHandler(filename,"w");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for writing.";

  char buffer[256];
  strcpy(buffer,"Some txt with utf-8 character like \u65e5 or \u4e16. ");
  EXPECT_EQ(static_cast<size_t>(48),f->writeln(buffer)) << "Write first line.";
  strcpy(buffer,"Used for testing.\n\t Something more 5$326\u00f1\u00d1\u00fc.\n");
  EXPECT_EQ(static_cast<size_t>(49),f->writeln(buffer)) << "Write second line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close writed file.";

  f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for reading.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading first Line.";
  EXPECT_STREQ("Some txt with utf-8 character like \u65e5 or \u4e16. \n",buffer) << "Checking first line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading second Line.";
  EXPECT_STREQ("Used for testing.\n",buffer) << "Checking second line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading third Line.";
  EXPECT_STREQ("\t Something more 5$326\u00f1\u00d1\u00fc.\n",buffer) << "Checking third line.";
  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading forth Line.";
  EXPECT_STREQ("\n",buffer) << "Checking forth line.";
  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close readed file.";

  // Remove UTF-8 file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The UTF-8 file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete UTF-8 file.";
  EXPECT_FALSE(zbe::FileHandler::exist(filename)) << "The UTF-8 file no longer exist.";
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No errors.";
}
