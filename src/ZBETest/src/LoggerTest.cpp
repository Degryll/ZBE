#include "gtest/gtest.h"

#include "ZBE/core/system/Logger.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/io/FileHandler.h"

TEST(Logger, stdoutLog) {
  zbe::Logger::createInstance()->setDefaultCommandLineWriter();
  std::streambuf* oldCout = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  int i = 42;
  float d = 3.1416;
  char a = 65;
  std::string s = "Hola Mundo!";
  int *pi = &i;
  bool t = true;

  ZBE_LOG_INFO("Prueba Info. " << d << " añadiendo un double.");
  ZBE_LOG_DEBUG("Prueba Debug. " << i << " un int y " << pi << " su puntero.");
  ZBE_LOG_WARNING("Prueba Warning. '" << a << "' un caracter");
  ZBE_LOG_ERROR("Prueba Error. \"" << s << "\" una cadena.");
  ZBE_LOG(33, "[PROPIA]","Prueba Propia -> " << t <<".");

  std::stringstream chk;
  chk << "[INFO]> Prueba Info. " << d << " añadiendo un double.\n";
  chk << "[DEBUG]" << __FILE__ << ":21> Prueba Debug. " << i << " un int y " << pi << " su puntero.\n";
  chk << "[WARNING]> Prueba Warning. '" << a << "' un caracter\n";
  chk << "[ERROR]> Prueba Error. \"" << s << "\" una cadena.\n";
  chk << "[PROPIA]> Prueba Propia -> true.\n";
  EXPECT_STREQ(chk.str().c_str(), strCout.str().c_str()) << "Checking std::cout.";

  std::cout.rdbuf(oldCout);

  zbe::Logger::deleteInstance();
}

void aFileWriter(int , const char * type, const char * msg) {
  zbe::FileHandler f("data/test/test.log", "a", true);
  f.write(type);
  f.writelnflush(msg);
}


TEST(Logger, FileLog) {
  const char filename[] = "data/test/test.log";
  EXPECT_FALSE(zbe::FileHandler::existDir(filename)) << "This dir does not exist.";

  zbe::Logger::createInstance()->addWriter(aFileWriter);

  int i = 42;
  float d = 3.1416;
  char a = 65;
  std::string s = "Hola Mundo!";
  int *pi = &i;
  bool t = true;

  ZBE_LOG_INFO("Prueba Info. " << d << " añadiendo un double.");
  ZBE_LOG_DEBUG("Prueba Debug. " << i << " un int y " << pi << " su puntero.");
  ZBE_LOG_WARNING("Prueba Warning. '" << a << "' un caracter");
  ZBE_LOG_ERROR("Prueba Error. \"" << s << "\" una cadena.");
  ZBE_LOG(33, "[PROPIA]","Prueba Propia -> " << t <<".");

  char buffer[256];

  zbe::FileHandler *f = new zbe::FileHandler(filename,"r");
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Open UTF-8 file for reading.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading first Line.";
  EXPECT_STREQ("[INFO]> Prueba Info. 3.1416 añadiendo un double.\n",buffer) << "Checking first line.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading second Line.";
  std::stringstream chk;
  chk << "[DEBUG]" << __FILE__ << ":60> Prueba Debug. " << i << " un int y " << pi << " su puntero.\n";
  EXPECT_STREQ(chk.str().c_str(),buffer) << "Checking second line.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading third Line.";
  EXPECT_STREQ("[WARNING]> Prueba Warning. 'A' un caracter\n",buffer) << "Checking third line.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading forth Line.";
  EXPECT_STREQ("[ERROR]> Prueba Error. \"Hola Mundo!\" una cadena.\n",buffer) << "Checking forth line.";

  EXPECT_TRUE(f->readln(buffer,256) != 0) << "Reading fifth Line.";
  EXPECT_STREQ("[PROPIA]> Prueba Propia -> true.\n",buffer) << "Checking fifth line.";

  delete f;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Close readed file.";

  // Remove file
  EXPECT_TRUE(zbe::FileHandler::exist(filename)) << "The file still exist.";
  EXPECT_EQ(0,zbe::FileHandler::rm(filename)) << "Delete file.";

  zbe::Logger::deleteInstance();
}
