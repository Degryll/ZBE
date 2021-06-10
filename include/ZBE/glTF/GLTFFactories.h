/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GLTFFactories.h
 * @since 2020-09-13
 * @date 2020-09-13
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all gltf factories.
 */

#ifndef ZBE_GLTF_GLTFFACTORIES_H_
#define ZBE_GLTF_GLTFFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/system.h"

#include "ZBE/glTF/resources/GlTFResourceLoader.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI GLTFFactories : public Daemon {
public:
  ~GLTFFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load(){
    auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("GlTFResourceLoaderFtry", std::make_shared<GlTFResourceLoaderFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_GLTF_GLTFFACTORIES_H_
