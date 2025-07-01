/**
* Copyright 2015 Batis Degryll Ludo
* @file RsrcFolderLoader.h
* @since 2018-07-07
* @date 2018-07-07
* @author Batis Degryll Ludo
* @brief class ZBEAPI that loads all compatible resources within a folder.
*/

#ifndef ZBE_RESOURCES_LOADERS_RSRCFOLDERLOADER_H_
#define ZBE_RESOURCES_LOADERS_RSRCFOLDERLOADER_H_

#include <filesystem>
#include <memory>

#include "ZBE/resources/loaders/RsrcLoader.h"

namespace zbe {

/** \brief Interface for classes that loads images. It will return an identifier
*/
class RsrcFolderLoader : public RsrcLoader {
public:

  RsrcFolderLoader() : rsrcLoader(nullptr) {}

  explicit RsrcFolderLoader(std::shared_ptr<RsrcLoader> rsrcLoader) : rsrcLoader(rsrcLoader) {}

  void setRsrcLoader(std::shared_ptr<RsrcLoader> rsrcLoader) {
    this->rsrcLoader = rsrcLoader;
  }
  
  void load(std::filesystem::path folder) override;

  bool isLoadable(std::filesystem::path) override { return false; }
  
private:
DISABLE_DLL_WARN
  std::shared_ptr<RsrcLoader> rsrcLoader;
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_RSRCFOLDERLOADER_H_
