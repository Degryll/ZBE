/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImgFolderLoader.h
 * @since 2018-04-19
 * @date 2018-04-19
 * @author Batis Degryll Ludo
 * @brief Class that loads all images & image definitions within a folder.
 * of the loaded image.
 */

#ifndef ZBE_RESOURCES_LOADERS_IMGFOLDERLOADER_H_
#define ZBE_RESOURCES_LOADERS_IMGFOLDERLOADER_H_

#include <filesystem>
#include <memory>

#include "ZBE/resources/loaders/ImgDefLoader.h"
#include "ZBE/resources/loaders/ImgLoader.h"

namespace zbe {

/** \brief Interface for classes that loads images. It will return an identifier
 */
class ImgFolderLoader {
public:
  ImgFolderLoader(std::shared_ptr<ImgLoader> imgLoader, std::shared_ptr<ImgDefLoader> imgDefLoader)
    : imgLoader(imgLoader), imgDefLoader(imgDefLoader) {}

  void load(std::string folder);

private:
  std::filesystem::path generateDefPath(const std::filesystem::path& p);
  std::shared_ptr<ImgLoader> imgLoader;
  std::shared_ptr<ImgDefLoader> imgDefLoader;

};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_IMGFOLDERLOADER_H_
