/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcLoaderDmn.cpp
 * @since 2019-04-03
 * @date 2019-04-03
 * @author Ludo Degryll Batis
 * @brief A Daemon capable of run a RsrcLoader
 */

#include "ZBE/daemons/RsrcLoaderDmn.h"

namespace zbe {

void RsrcLoaderDmn::run() {
  auto e = filePath.extension();
  if(rsrcLoader->isLoadable(e)){
    rsrcLoader->load(filePath);
  }
}

void RsrcLoaderDmn::setRsrcLoader(std::shared_ptr<RsrcLoader> loader) {
  rsrcLoader = loader;
}

void RsrcLoaderDmn::setUrl(std::string url) {
  filePath = url;
}

}  // namespace zbe
