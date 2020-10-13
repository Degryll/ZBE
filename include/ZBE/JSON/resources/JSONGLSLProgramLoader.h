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

namespace zbe {

/** \brief JSON loader for GLSL programss
*/
class JSONGLSLProgramLoader : public RsrcLoader {
public:

 /** \brief Empty constructir. Creted object needs to be setup
  */
 JSONGLSLProgramLoader() : window() {}

 /* \brief It sets up the window to be used.
 */
 void setWindow(std::shared_ptr<SDLOGLWindow> window) {
   this->window = window;
 }

 /** \brief Loads a glsl program
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) {
   std::ifstream ifs(filePath);
   jsongl.JSONGLSLProgramFileLoad(ifs, window);
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
  std::shared_ptr<SDLOGLWindow> window;
  JSONGraphicsLoaders& jsongl = JSONGraphicsLoaders::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONGLSLPROGRAMLOADER_H_
