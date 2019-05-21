/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONAppLoader.h
 * @since 2019-02-21
 * @date 2019-02-21
 * @author Batis Degryll Ludo
 * @brief Implementation of RsrcLoader capable of load an app config from a .json file
 */

#ifndef ZBE_RESOURCES_LOADERS_IMPLEMENTATIONS_JSONAPPLOADER_H_
#define ZBE_RESOURCES_LOADERS_IMPLEMENTATIONS_JSONAPPLOADER_H_

#include <fstream>
#include <string>
#include <filesystem>
#include <forward_list>

#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"
#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

namespace zbe {

/** \brief Implementation of RsrcLoader capable of load an app config from a .json file
 */
class ZBEAPI JSONAppLoader : public RsrcLoader {
public:
  using json = nlohmann::json;

  /** \brief Empty constructor.
   */
  JSONAppLoader() : cfgStore(RsrcStore<json>::getInstance()),
                    ftryStore(RsrcStore<Factory>::getInstance()),
                    appData() {}

  /** \brief Loads the app config
   *  \param filePath Path to resource file.
   */
  void load(std::filesystem::path filePath);


  /** \brief Tells if a file extension is loadable.
   *  \param extension resource file extension.
   *  \return True if the extensions is loadable by the given implementation.
   */
  bool isLoadable(std::filesystem::path extension);

private:
  struct FtryData {
    FtryData() : ftry(), name(), cfgId() {}
    std::shared_ptr<Factory> ftry;
    std::string name;
    uint64_t cfgId;
  };

  void loadLiteralConfig(std::string name, json& value);
  FtryData readFactoryConfig(json ftryCfg);

  RsrcStore<json>& cfgStore = RsrcStore<json>::getInstance();
  RsrcStore<Factory>& ftryStore = RsrcStore<Factory>::getInstance();

  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<std::string>& stringStore = RsrcDictionary<std::string>::getInstance();

  std::forward_list<FtryData> appData;
};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_IMPLEMENTATIONS_JSONAPPLOADER_H_
