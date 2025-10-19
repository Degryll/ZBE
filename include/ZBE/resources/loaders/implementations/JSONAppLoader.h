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
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/tools.h"

namespace zbe {

/** \brief Implementation of RsrcLoader capable of load an app config from a .json file
 */
class ZBEAPI JSONAppLoader : public RsrcLoader {
public:
  using json = nlohmann::json;

  /** \brief Empty constructor.
   */
  JSONAppLoader() : cfgStore(nullptr),
                    ftryStore(nullptr),
                    appLists(),
                    appFactories() {}

  /** \brief Loads the app config
   *  \param filePath Path to resource file.
   */
  void load(std::filesystem::path filePath) override;


  /** \brief Tells if a file extension is loadable.
   *  \param extension resource file extension.
   *  \return True if the extensions is loadable by the given implementation.
   */
  bool isLoadable(std::filesystem::path extension) override;

  // RsrcStore<Factory>& getFactoryStore() { return *ftryStore; }

  void setFactoryStore(RsrcStore<Factory>* ftryStore) { this->ftryStore = ftryStore;}
  void setConfigStore(RsrcStore<json>* cfgStore) { this->cfgStore = cfgStore;}
  void setV2DStore(RsrcDictionary<Vector2D>* v2dStore) { this->v2dStore = v2dStore;}
  void setV3DStore(RsrcDictionary<Vector3D>* v3dStore) { this->v3dStore = v3dStore;}
  void setIntStore(RsrcDictionary<int64_t>* intStore) { this->intStore = intStore;}
  void setUIntStore(RsrcDictionary<uint64_t>* uintStore) { this->uintStore = uintStore;}
  void setDoubleStore(RsrcDictionary<double>* doubleStore) { this->doubleStore = doubleStore;}
  void setFloatStore(RsrcDictionary<float>* floatStore) { this->floatStore = floatStore;}
  void setStringStore(RsrcDictionary<std::string>* stringStore) { this->stringStore = stringStore;}
  void setCallableStore(RsrcStore<Funct<void>>* callableRsrc) { this->callableRsrc = callableRsrc;}

private:
  struct FtryData {
    FtryData() = default;
    std::shared_ptr<Factory> ftry;
    std::string name;
    uint64_t cfgId;
  };

DISABLE_DLL_WARN
  void loadLiteralConfig(std::string name, json& value);
  FtryData readFactoryConfig(json ftryCfg);
  void checkAndCall(json& call, json& phase);

  RsrcStore<json>* cfgStore = nullptr;
  RsrcStore<Factory>* ftryStore = nullptr;

  RsrcDictionary<Vector2D>* v2dStore = nullptr;
  RsrcDictionary<Vector3D>* v3dStore = nullptr;

  RsrcDictionary<int64_t>* intStore = nullptr;
  RsrcDictionary<uint64_t>* uintStore = nullptr;
  RsrcDictionary<double>* doubleStore = nullptr;
  RsrcDictionary<float>* floatStore = nullptr;
  RsrcDictionary<std::string>* stringStore = nullptr;

  RsrcStore<Funct<void>>* callableRsrc = nullptr;

  std::forward_list<FtryData> appLists;
  std::forward_list<FtryData> appFactories;
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_IMPLEMENTATIONS_JSONAPPLOADER_H_
