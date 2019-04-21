/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcFolderLoaderDmn.cpp
 * @since 2019-04-03
 * @date 2019-04-03
 * @author Ludo Degryll Batis
 * @brief A Daemon capable of run a RsrcLoader
 */

#include "ZBE/daemons/RsrcFolderLoaderDmn.h"

namespace zbe {

void RsrcFolderLoaderDmn::run() {
  rsrcFolderLoader->load(folderPath);
}

void RsrcFolderLoaderDmn::setRsrcFolderLoader(std::shared_ptr<RsrcFolderLoader> loader) {
  rsrcFolderLoader = loader;
}

void RsrcFolderLoaderDmn::setUrl(std::string folder) {
  folderPath = folder;
}

}  // namespace zbe
