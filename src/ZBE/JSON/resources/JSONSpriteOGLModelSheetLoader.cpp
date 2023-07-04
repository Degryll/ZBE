/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONMultiSpriteSheetLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON loader for MultiSpriteSheet's
*/

#include "ZBE/JSON/resources/JSONSpriteOGLModelSheetLoader.h"

namespace zbe {

  /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
  void JSONSpriteOGLModelSheetLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONSpriteOGLModelSheetFileLoad(ifs, window, rsrcModelSheet, nrd, rsrcImgDef);
  }
}  // namespace zbe
