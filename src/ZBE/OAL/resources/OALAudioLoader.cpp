/**
* Copyright 2012 Batis Degryll Ludo
* @file OALAudioLoader.cpp
* @since 2019-03-19
* @date 2019-03-19
* @author Batis Degryll Ludo
* @brief RsrcLoader implementation caplable of load ogg files into OAL system.
*/

#include <cstdio>
#include <iostream>

#include "ZBE/OAL/resources/OALAudioLoader.h"

namespace zbe {

void OALAudioLoader::load(std::filesystem::path filePath) {
  uint64_t audioId = audioStore->loadAudio(filePath.string().c_str());
  if(audioId > 0) {
    std::filesystem::path defFilePath = generateDefPath(filePath);
    audioDefLoader->loadRsrcDef(defFilePath, audioId);
  }
}

bool OALAudioLoader::isLoadable(std::filesystem::path extension) {
  return (ext.compare(extension) == 0);
}

std::filesystem::path OALAudioLoader::generateDefPath(const std::filesystem::path& p) {
  std::filesystem::path ext = audioDefLoader->getExtension();
  std::filesystem::path out = p;
  return (out.replace_extension(ext));
}

std::filesystem::path OALAudioLoader::ext = std::filesystem::path(".ogg");

}  // namespace zbe
