/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONMultiSpriteSheetLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON loader for MultiSpriteSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#include "ZBE/JSON/resources/JSONMultiSpriteSheetLoader.h"

namespace zbe {

  /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
  void JSONMultiSpriteSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONMultiSpriteSheetFileLoad(ifs, rsrcAnimSprt, nrd, rsrcModelSheet, rsrcImgDef);
  }
}  // namespace zbe
