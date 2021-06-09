/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONSimpleOGLModelSheetLoader.h
* @since 2020-09-03
* @date 2020-09-03
* @author Batis Degryll Ludo
* @brief JSON loader for SimpleModelOGLModelSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#include "ZBE/JSON/resources/JSONSimpleOGLModelSheetLoader.h"

namespace zbe {

  /** \brief Load an image
   *  \param filePath Path to image file.
   *  \return An id to the image loaded.
   */
  void JSONSimpleOGLModelSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONSimpleModelSheetFileLoad(ifs, window, rsrcAnimSprt, nrd, rsrcModelSheet, graphicsStore);
    //JSONGraphicsLoaders::JSONMultiSpriteSheetFileLoad(ifs, rsrcAnimSprt, nrd, rsrcModelSheet, rsrcImgDef);
  }
}  // namespace zbe
