/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleOGLModelSheet.h
 * @since 2018-06-09
 * @date 2018-06-09
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SIMPLEOGLMODELSHEET_H_
#define ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SIMPLEOGLMODELSHEET_H_

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/OGL/graphics/OGLModel.h"
#include "ZBE/OGL/graphics/OGLModelSheet.h"
#include "ZBE/OGL/graphics/OGLGraphics.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
class ZBEAPI SimpleOGLModelSheet : public OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> {
public:

  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t modelId, uint64_t texId);
  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t graphicsId, RsrcStore<OGLGraphics> &graphicsStore);
  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, std::string graphicsName, RsrcStore<OGLGraphics> &graphicsStore);

  /** \brief Virtual destructor
  */
  virtual ~SimpleOGLModelSheet() = default; //!< Virtual destrutor.

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  OGLModel generateModel(std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar);

private:
  std::shared_ptr<OGLGraphics> graphic;
  GLuint vao;
  std::vector<GLuint> textures;
  GLenum  mode;
  GLsizei nvertex;
  GLenum  type;
  const GLvoid* offset;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SIMPLEOGLMODELSHEET_H_
