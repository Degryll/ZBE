/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONImgDefLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON implementation of a RsrcDefLoader for images.
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_

#include <fstream>
#include <filesystem>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include "ZBE/resources/loaders/RsrcDefLoader.h"

namespace zbe {

/** \brief JSON implementation of a RsrcDefLoader for images.
 */
class ZBEAPI JSONImgDefLoader : public RsrcDefLoader {
public:
 /** \brief Load an image definition
  *  \param url Image definition file to be loaded.
  *  \param imgId Associated image id
  *  \return An id to the image definition.
  */
 void loadRsrcDef(const std::filesystem::path& url, uint64_t imgId) {
   std::ifstream ifs(url);
   jsongl.JSONImgDefFileLoad(ifs, imgId);
 }

 /** \brief Returns the file extension.
  *  \return The file extension.
  */
 const std::filesystem::path getExtension() {
   static const std::filesystem::path p(".json");
   return p;
 }
private:
  JSONGraphicsLoaders& jsongl = JSONGraphicsLoaders::getInstance();
};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_
