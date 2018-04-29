#include "gtest/gtest.h"

#include <fstream>
#include <iostream>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/graphics/MultiSpriteSheet.h"
#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

namespace JSONGraphicsLoadersTest {

// "data/test/\u65e5\u0448/\u65e5\u0448.txt";

TEST(JSONGraphicsLoaders, load_succes) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    std::ifstream i("data/test/json/testjson_001.json");
    zbe::JSONImgDefFileLoad(i, 1);

    zbe::RsrcStore<zbe::ImgDef>& rsrc = zbe::RsrcStore<zbe::ImgDef>::getInstance();
    zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no parse or type errors.";

    uint64_t id = nrd.get("playerSheet.jump1");
    ASSERT_NE(0, id) << "Element playerSheet.jump1 must be present in NameRsrcDictionary";
    std::shared_ptr<zbe::ImgDef> idef = rsrc.get(id);
    ASSERT_TRUE(idef!=false) << "playerSheet.jump1 id must have an ImgDef stored in the RsrcStore";
    EXPECT_EQ(1000, idef->frameTime) << "Jump sprite frameTime must be 1000.";
    EXPECT_EQ(6, idef->frameAmount) << "Jump sprite frameAmount must be 6.";
    EXPECT_EQ(zbe::Region2D({0.0,0.0}, {0.5,0.5}), idef->region) << "Jump sprite region must be 0.0, 0.0, 0.5, 0.5.";
    EXPECT_EQ(zbe::Vector2D({0.0,0.0}), idef->regionOffset) << "Jump sprite regionOffset must be 0.0, 0.0.";

    id = nrd.get("playerSheet.run");
    ASSERT_NE(0, id) << "Element playerSheet.run must be present in NameRsrcDictionary";
    idef = rsrc.get(id);
    ASSERT_TRUE(idef!=false) << "playerSheet.run id must have an ImgDef stored in the RsrcStore";
    EXPECT_EQ(500, idef->frameTime) << "Run sprite frameTime must be 1000.";
    EXPECT_EQ(2, idef->frameAmount) << "Run sprite frameAmount must be 6.";
    EXPECT_EQ(zbe::Region2D({0.5,0.5}, {1.0,1.0}), idef->region) << "Run sprite region must be 0.5, 0.5, 1.0, 1.0.";
    EXPECT_EQ(zbe::Vector2D({1.0,0.0}), idef->regionOffset) << "Run sprite regionOffset must be 1.0, 0.0.";

    zbe::SysError::clear();
}

TEST(JSONGraphicsLoaders, DISABLED_load_succes_utf8) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    // std::ifstream i("data/test/json/\u65e5\u0448.json");
    std::ifstream i("data/test/json/testjson_003.json");

    zbe::JSONImgDefFileLoad(i, 0);

    zbe::RsrcStore<zbe::ImgDef>& rsrc = zbe::RsrcStore<zbe::ImgDef>::getInstance();
    zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no parse or type errors.";

    uint64_t id = nrd.get("playerSheet.jump1");
    ASSERT_NE(0, id) << "Element playerSheet.jump1 must be present in NameRsrcDictionary";
    std::shared_ptr<zbe::ImgDef> idef = rsrc.get(id);
    ASSERT_TRUE(idef!=false) << "playerSheet.jump1 id must have an ImgDef stored in the RsrcStore";

    EXPECT_EQ(1000, idef->frameTime) << "Jump sprite frameTime must be 1000.";
    EXPECT_EQ(6, idef->frameAmount) << "Jump sprite frameAmount must be 6.";
    EXPECT_EQ(zbe::Region2D({0.0,0.0}, {0.5,0.5}), idef->region) << "Jump sprite region must be 0.0, 0.0, 0.5, 0.5.";
    EXPECT_EQ(zbe::Vector2D({0.0,0.0}), idef->regionOffset) << "Jump sprite regionOffset must be 0.0, 0.0.";

    zbe::SysError::clear();
}

// TEST(JSONGraphicsLoaders, load_fail_no_file) {
//     EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
//
//     std::ifstream i("data/test/json/nofile.json");
//     zbe::JSONImgDefFileLoad(i, 1);
//
//     EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Must be parse errors";
//     zbe::SysError::clear();
// }

TEST(JSONGraphicsLoaders, load_fail_uncomplete_file) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

    std::ifstream i("data/test/json/testjson_002.json");
    zbe::JSONImgDefFileLoad(i, 1);

    EXPECT_EQ(2, zbe::SysError::getNErrors()) << "Must be content errors";
    zbe::SysError::clear();
}

}  //namespace JSONGraphicsLoadersTest
