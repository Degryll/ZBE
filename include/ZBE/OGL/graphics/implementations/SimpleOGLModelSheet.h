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

  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t modelId, uint64_t texId)
    : vao(std::get<0>(window->getModelStore()->getModel(modelId))), nvertex(std::get<1>(window->getModelStore()->getModel(modelId))), textures() {
      textures.push_back(window->getTextureStore()->getTexture(texId));
  }

  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t graphicsId)
    : graphic(RsrcStore<OGLGraphics>::getInstance().get(graphicsId)), vao(graphic->vao), nvertex(graphic->nvertex), textures{graphic->texid} {}

  SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, std::string graphicsId)
    : graphic(RsrcStore<OGLGraphics>::getInstance().get(graphicsId)), vao(graphic->vao), nvertex(graphic->nvertex), textures{graphic->texid} {}

  /** \brief Virtual destructor
  */
  virtual ~SimpleOGLModelSheet() {} //!< Virtual destrutor.

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  OGLModel generateModel(std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar) {
    Vector3D pos = avatar->get<1, Vector3D>()->get();
    glm::vec3 glPos(pos.x, pos.y, pos.z);
    Vector3D ori = avatar->get<2, Vector3D>()->get();
    glm::vec3 glOri(ori.x, ori.y, ori.z);
    float angle = (float) avatar->get<3, double>()->get();
    float baseScale = (float) avatar->get<4, double>()->get();;
    glm::mat4 mat(1.0);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);
    glm::mat4 rotate    = glm::rotate(   glm::mat4(1.0f), angle, glOri);
    glm::mat4 scale     = glm::scale(    glm::mat4(1.0f), glm::vec3(baseScale));
    glm::mat4 m = translate * scale * rotate;

    return OGLModel(vao, nvertex, textures, m);
  };

private:
  std::shared_ptr<OGLGraphics> graphic;
  GLuint vao;
  GLsizei nvertex;
  std::vector<GLuint> textures;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SIMPLEOGLMODELSHEET_H_
