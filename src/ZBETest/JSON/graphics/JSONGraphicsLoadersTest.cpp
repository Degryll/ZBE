#include "gtest/gtest.h"

#include <unordered_map>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/graphics/MultiSpriteSheet.h"

namespace JSONGraphicsLoadersTest {

TEST(JSONGraphicsLoaders, load_succes) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    std::ifstream i("data/test/json/testjson_001.json");
    std::unordered_map<std::string, zbe::ImgDef> m = zbe::JSONImgDefFileLoad(i, 0);

    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no parse or type errors.";

    auto it = m.find("playerSheet.jump1");
    EXPECT_NE(m.end(), it) << "Element playerSheet.jump1 must be present.";
    zbe::ImgDef idef = it->second;
    EXPECT_EQ(1000, idef.frameTime) << "Jump sprite frameTime must be 1000.";
    EXPECT_EQ(6, idef.frameAmount) << "Jump sprite frameAmount must be 6.";
    EXPECT_EQ(zbe::Region2D({0.0,0.0}, {0.5,0.5}), idef.region) << "Jump sprite region must be 0.0, 0.0, 0.5, 0.5.";
    EXPECT_EQ(zbe::Vector2D({0.0,0.0}), idef.regionOffset) << "Jump sprite regionOffset must be 0.0, 0.0.";

    it = m.find("playerSheet.run");
    EXPECT_NE(m.end(), it) << "Element playerSheet.jump1 must be present.";
    idef = it->second;
    EXPECT_EQ(500, idef.frameTime) << "Run sprite frameTime must be 1000.";
    EXPECT_EQ(2, idef.frameAmount) << "Run sprite frameAmount must be 6.";
    EXPECT_EQ(zbe::Region2D({0.5,0.5}, {1.0,1.0}), idef.region) << "Run sprite region must be 0.5, 0.5, 1.0, 1.0.";
    EXPECT_EQ(zbe::Vector2D({1.0,0.0}), idef.regionOffset) << "Run sprite regionOffset must be 1.0, 0.0.";

    zbe::SysError::clear();
}

TEST(JSONGraphicsLoaders, load_fail_no_file) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    std::ifstream i("data/test/json/nofile.json");
    std::unordered_map<std::string, zbe::ImgDef> m = zbe::JSONImgDefFileLoad(i, 0);

    EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Must be no parse or type errors.";
    zbe::SysError::clear();
}

TEST(JSONGraphicsLoaders, load_fail_uncomplete_file) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    std::ifstream i("data/test/json/testjson_002.json");
    std::unordered_map<std::string, zbe::ImgDef> m = zbe::JSONImgDefFileLoad(i, 0);

    EXPECT_EQ(2, zbe::SysError::getNErrors()) << "Must be no parse or type errors.";
    zbe::SysError::clear();
}

}  //namespace JSONGraphicsLoadersTest
