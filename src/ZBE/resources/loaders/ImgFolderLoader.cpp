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
   if(imgLoader->isLoadable(p.path().extension())){
     uint64_t imgId = imgLoader->loadImg(p);
     if(imgId > 0) {
       std::filesystem::path defFilePath = generateDefPath(p.path());
       imgDefLoader->loadImgDef(defFilePath, imgId);
     }
   }
 }  // for auto& p
}

std::filesystem::path ImgFolderLoader::generateDefPath(const std::filesystem::path& p) {
  std::filesystem::path ext = imgDefLoader->getExtension();
  std::filesystem::path out = p;
  return (out.replace_extension(ext));
}

}  // namespace zbe
