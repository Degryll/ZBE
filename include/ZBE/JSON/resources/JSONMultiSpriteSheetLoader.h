/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONMultiSpriteSheetLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief SDL implementation of ImgLoader.
* of the loaded image.
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include "ZBE/resources/loaders/RsrcLoader.h"


namespace zbe {

/** \brief SDL implementation of ImgLoader.
*/
class ZBEAPI JSONMultiSpriteSheetLoader : public RsrcLoader {
public:

 /** \brief Builds an SDLImgLoader from a SDLImageStore and the file extension supported (PNG by default)
  *  \imgStore SDLImgLoader to use.
  *  \extension Extension supported. PNG by default.
  */
 JSONMultiSpriteSheetLoader() {}

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) {
   std::ifstream ifs(filePath);
   jsongl.JSONMultiSpriteSheetFileLoad(ifs);
 }

 /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
 bool isLoadable(std::filesystem::path extension) {
   static const std::filesystem::path ext(".json");
   return (ext.compare(extension) == 0);
 }

private:
  JSONGraphicsLoaders& jsongl = JSONGraphicsLoaders::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
