/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLFactories.h
 * @since 2020-09-14
 * @date 2020-09-14
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all OGL factories.
 */

#ifndef ZBE_OGL_FACTORIES_OGLFACTORIES_H_
#define ZBE_OGL_FACTORIES_OGLFACTORIES_H_

#include <string>

#include "ZBE/tools/graphics/CameraFtry.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/OGL/drawers/OGLModelSheetDrawerFtry.h"
#include "ZBE/OGL/factories/daemons/OGLPostDrawFtry.h"
#include "ZBE/OGL/factories/daemons/OGLPreDrawFtry.h"
#include "ZBE/OGL/daemons/OGLPreDrawer.h"
#include "ZBE/OGL/daemons/ShadersSetter.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI OGLFactories : public Daemon {
public:
  ~OGLFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("CameraFtry", std::make_shared<CameraFtry>());
    factories.insert("OGLPostDrawFtry", std::make_shared<OGLPostDrawFtry>());
    factories.insert("OGLPreDrawFtry" , std::make_shared<OGLPreDrawFtry>());
    factories.insert("OGLModelSheetDrawerFtry" , std::make_shared<OGLModelSheetDrawerFtry<5, uint64_t, double,  double, Vector3D, Vector3D> >());
    factories.insert("OGLLookAtModelSheetDrawerFtry" , std::make_shared<OGLModelSheetDrawerFtry<5, uint64_t, double,  Vector3D, Vector3D, Vector3D> >());
    factories.insert("OGLSpriteSheetDrawerFtry" , std::make_shared<OGLModelSheetDrawerFtry<3, uint64_t, Vector2D, Vector2D> >());
    factories.insert("OGLParametricSpriteSheetDrawerFtry" , std::make_shared<OGLModelSheetDrawerFtry<5, uint64_t, int64_t, int64_t, Vector2D, Vector2D> >());
    factories.insert("ShadersSetter2DFtry", std::make_shared<ShadersSetter2DFtry>());
    factories.insert("ShadersSetter3DFtry", std::make_shared<ShadersSetter3DFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_OGL_FACTORIES_OGLFACTORIES_H_
