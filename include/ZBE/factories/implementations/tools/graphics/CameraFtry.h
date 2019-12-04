/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CameraFtry.h
 * @since 2019-11-02
 * @date 2019-11-02
 * @author Ludo Degryll Batis
 * @brief Factory for Cameras.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_TOOLS_GRAPHICS_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_TOOLS_GRAPHICS_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

/** \brief Factory for Master Daemons.
 */
class ZBEAPI CameraFtry : virtual public Factory {
public:

  /** \brief Builds a CameraFtry.
   *  \param name Name for the created CameraFtry.
   *  \param cfgId CameraFtry's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Value<Vector3D> > &vec3DValues = RsrcStore<Value<Vector3D> >::getInstance();
  RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_TOOLS_GRAPHICS_H_
