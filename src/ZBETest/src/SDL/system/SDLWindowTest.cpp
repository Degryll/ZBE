#include "gtest/gtest.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/SysError.h"

namespace SDLWindowTest {

  TEST(SDLImageStore, Store_img) {
    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
    //zbe::SysError::getFirstErrorString()

    std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("test", 100, 100);
    std::shared_ptr<zbe::SDLImageStore> imgStore = window->getImgStore();

    uint64_t imgId1 = imgStore->loadImg("data/test/img/testing_001.png");
    uint64_t imgId2 = imgStore->loadImg("data/test/img/testing_001.jpg");
    uint64_t imgId3 = imgStore->loadImg("data/test/img/testing_001.bmp");

    EXPECT_EQ(1, imgId1) << "First id for the first image.";
    EXPECT_EQ(2, imgId2) << "Second id for the second image.";
    EXPECT_EQ(3, imgId3) << "Third id for the third image.";

    EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finally no errors.";
    zbe::SysError::clear();
  }

}
