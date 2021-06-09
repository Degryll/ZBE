/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONAudioDefLoader.cpp
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON implementation of a RsrcDefLoader for audio.
*/

#include "ZBE/JSON/resources/JSONAudioDefLoader.h"

namespace zbe {

void JSONAudioDefLoader::loadRsrcDef(const std::filesystem::path& url, uint64_t audioId){
  std::ifstream ifs(url);
  json j;
  try {
    ifs >> j;
    std::string name = j["name"];
    nrd.insert(cn::AUDIO + cn::SEPARATOR + name, audioId);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONAudioDefLoader - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONAudioDefLoader - ERROR: Json failed to load audio def for id ") + std::to_string(audioId) + std::string(" because: ") + std::string(e.what()));
  }
}

}  // namespace zbe
