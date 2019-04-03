#include "gtest/gtest.h"

#include <filesystem>
#include <memory>
#include <string>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/resources/loaders/RsrcDefLoader.h"
#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/OAL/resources/OALAudioLoader.h"
#include "ZBE/OAL/system/OALAudioStore.h"
#include "ZBE/OAL/daemons/OALContextDaemon.h"

#include "ZBE/JSON/resources/JSONAudioDefLoader.h"


namespace OALAudioLoaderTest {

TEST(AudioAndDefTest, Load_folder) {

  zbe::OALContextDaemon oalContextDmn;
  oalContextDmn.run();

EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
std::shared_ptr<zbe::OALAudioStore> audioStore = std::make_shared<zbe::OALAudioStore>();

std::shared_ptr<zbe::RsrcDefLoader> odl = std::make_shared<zbe::JSONAudioDefLoader>();
std::shared_ptr<zbe::RsrcLoader> rsrcl = std::make_shared<zbe::OALAudioLoader>(audioStore, odl);
zbe::RsrcFolderLoader rsrcfl(rsrcl);
rsrcfl.load("data/test/audio");

EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors after folder load.";
zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

uint64_t test = nrd.get(zbe::cn::AUDIO + zbe::cn::SEPARATOR + std::string("test"));
uint64_t die = nrd.get(zbe::cn::AUDIO + zbe::cn::SEPARATOR + std::string("die"));
uint64_t diem = nrd.get(zbe::cn::AUDIO + zbe::cn::SEPARATOR + std::string("diem"));

EXPECT_NE(0, test) << "Must load all audios.";
EXPECT_NE(0, die) << "Must load all audios.";
EXPECT_NE(0, diem) << "Must load all audios.";

EXPECT_EQ(0, zbe::SysError::getNErrors()) << "No errors in name dictionary.";

zbe::SysError::clear();
}

}  // namespace OALAudioLoaderTest
