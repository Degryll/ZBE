/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImgFolderLoader.cpp
 * @since 2018-04-23
 * @date 2018-04-23
 * @author Batis Degryll Ludo
 * @brief Class that loads all images & image definitions within a folder.
 * of the loaded image.
 */

#include "ZBE/resources/loaders/ImgFolderLoader.h"

namespace zbe {

void ImgFolderLoader::load(std::string folder) {
  namespace fs = std::filesystem;
  for(auto& p : fs::directory_iterator(folder)) {
    if(imgLoader->isLoadable(p.extension())){
      uint64_t imgId = imgLoader->loadImg(p);
      if(imgId > 0) {
        imgDefLoader->loadImgDef(generateDefPath(p), imgId);
      }
    }
  }  // for auto& p
}

std::filesystem::path ImgFolderLoader::generateDefPath(std::filesystem::path p) {
  return (p.replace_extension(imgDefLoader->getExtension()));
}

}  // namespace zbe
