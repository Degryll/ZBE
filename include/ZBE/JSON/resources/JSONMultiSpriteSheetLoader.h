/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONMultiSpriteSheetLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON loader for MultiSpriteSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief SDL implementation of ImgLoader.
*/
class ZBEAPI JSONMultiSpriteSheetLoader : public RsrcLoader {
public:

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) override;

 /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
 bool isLoadable(std::filesystem::path extension) override {
   static const std::filesystem::path ext(".json");
   return (ext.compare(extension) == 0);
 }

private:
  RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& rsrcAnimSprt = RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
  RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet = RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >::getInstance();
  RsrcStore<ImgDef>& rsrcImgDef = RsrcStore<ImgDef>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
