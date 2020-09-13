/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONSimpleOGLModelSheetLoader.h
* @since 2020-09-03
* @date 2020-09-03
* @author Batis Degryll Ludo
* @brief JSON loader for SimpleModelOGLModelSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/resources/loaders/RsrcLoader.h"


namespace zbe {

/** \brief JSON loader for SimpleModelOGLModelSheet's
*/
class JSONSimpleOGLModelSheetLoader : public RsrcLoader {
public:

 /** \brief Empty constructir. Creted object needs to be setup
  */
 JSONSimpleOGLModelSheetLoader() : window() {}

 /* \brief It sets up the window to be used.
 */
 void setWindow(std::shared_ptr<SDLOGLWindow> window) {
   this->window = window;
 }

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) {
   std::ifstream ifs(filePath);
   jsongl.JSONSimpleModelSheetFileLoad(ifs, window);
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

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONSIMPLEOGLMODELSHEETLOADER_H_
