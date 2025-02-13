/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONGLSLProgramLoader.h
* @since 2020-09-16
* @date 2020-09-16
* @author Batis Degryll Ludo
* @brief JSON loader for JSONGLSLProgramFileLoad's
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief JSON loader for GLSL programss
*/
class ZBEAPI JSONGLSLProgramLoader : public RsrcLoader {
public:

 /* \brief It sets up the window to be used.
 */
 void setWindow(std::shared_ptr<SDLOGLWindow> window) {
   this->window = window;
 }

 /** \brief Loads a glsl program
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
  std::shared_ptr<SDLOGLWindow> window = nullptr;
  //RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& rsrcAnimSprt = RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >::getInstance();
  //RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet = RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  //NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMLOADER_H_
