/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONGLSLProgramLoader.cpp
* @since 2021-05-11
* @date 2021-05-11
* @author Batis Degryll Ludo
* @brief JSON implementation of a RsrcDefLoader for audio.
*/

#include "ZBE/JSON/resources/JSONGLSLProgramLoader.h"

namespace zbe {

  void JSONGLSLProgramLoader::load(std::filesystem::path filePath) {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONGLSLProgramFileLoad(ifs, window, uintStore);
  }

}  // namespace zbe
