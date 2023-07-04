/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONSimpleOGLModelSheetLoader.h
* @since 2020-09-03
* @date 2020-09-03
* @author Batis Degryll Ludo
* @brief JSON loader for SimpleModelOGLModelSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#include "ZBE/JSON/resources/JSONOGLModelSheetLoaders.h"

namespace zbe {

  /** \brief Load an image
   *  \param filePath Path to image file.
   *  \return An id to the image loaded.
   */
  void JSONSimpleOGLModelSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONSimpleModelSheetFileLoad(ifs, window, nrd, rsrcModelSheet, graphicsStore);
  }

  /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
  void JSONSpriteOGLModelSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONSpriteOGLModelSheetFileLoad(ifs, window, rsrcModelSheet, nrd, rsrcImgDef);
  }

  /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
  void JSONLookAtOGLModelSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONLookAtOGLModelSheetFileLoad(ifs, window, nrd, rsrcModelSheet, graphicsStore);
  }
}  // namespace zbe
