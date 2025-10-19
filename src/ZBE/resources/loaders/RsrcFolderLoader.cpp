/**
* Copyright 2015 Batis Degryll Ludo
* @file RsrcFolderLoader.cpp
* @since 2018-07-07
* @date 2018-07-07
* @author Batis Degryll Ludo
* @brief class ZBEAPI that loads all compatible resources within a folder.
*/

#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include <filesystem>
#include <string>
#include <string_view>

namespace zbe {
void RsrcFolderLoader::load(std::filesystem::path folder) {
  namespace fs = std::filesystem;

  if (!fs::exists(folder) || !fs::is_directory(folder)) {
    return;
  }
  for (const auto& entry : fs::directory_iterator(folder)) {
    if (entry.is_regular_file() && rsrcLoader->isLoadable(entry.path().extension())) {
      rsrcLoader->load(entry.path().lexically_normal().make_preferred());
    }
  }
}

}  // namespace zbe
