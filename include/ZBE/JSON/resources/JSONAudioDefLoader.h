/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONAudioDefLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON implementation of a RsrcDefLoader for audio.
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONAUDIODEFLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONAUDIODEFLOADER_H_

#include <fstream>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/resources/contextnames.h"

#include "ZBE/resources/loaders/RsrcDefLoader.h"

namespace zbe {

/** \brief JSON implementation of a RsrcDefLoader for audio.
 */
class ZBEAPI JSONAudioDefLoader : public RsrcDefLoader {
public:

 /** \brief Load an audio definition
  *  \param url Image definition file to be loaded.
  *  \param imgId Associated audio id
  *  \return An id to the audio definition.
  */
 void loadRsrcDef(const std::filesystem::path& url, uint64_t imgId) override;

 /** \brief Returns the file extension.
  *  \return The file extension.
  */
 const std::filesystem::path getExtension() override {
   static const std::filesystem::path p(".json");
   return p;
 }

private:
 using json = nlohmann::json;
 NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONAUDIODEFLOADER_H_
