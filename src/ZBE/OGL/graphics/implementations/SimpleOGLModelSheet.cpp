/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleOGLModelSheet.cpp
 * @since 2021-05-20
 * @date 2021-05-20
 * @author Ludo Degryll Batis
 * @brief implementation of SimpleOGLModelSheet.
 */

#include "ZBE/OGL/graphics/implementations/SimpleOGLModelSheet.h"

namespace zbe {

  SimpleOGLModelSheet::SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t modelId, uint64_t texId)
    : vao(std::get<0>(window->getModelStore()->getModel(modelId))), nvertex(std::get<1>(window->getModelStore()->getModel(modelId))), textures() {
      textures.push_back(window->getTextureStore()->getTexture(texId));
  }

  SimpleOGLModelSheet::SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t graphicsId, RsrcStore<OGLGraphics> &graphicsStore)
    : graphic(graphicsStore.get(graphicsId)), vao(graphic->vao), textures{graphic->texid}, mode(graphic->mode), nvertex(graphic->nvertex), type(graphic->type), offset(graphic->offset) {}

  SimpleOGLModelSheet::SimpleOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, std::string graphicsName, RsrcStore<OGLGraphics> &graphicsStore)
  : graphic(nullptr), vao(0), textures(), mode(0), nvertex(0), type(0), offset(nullptr) { // TODO Find a way to write this using an initilaizer list
      using namespace std::string_literals;
      if (!graphicsStore.contains(graphicsName)) {
        SysError::setError("SimpleOGLModelSheet for graphic: "s + graphicsName + " is not a SimpleOGLModelSheet literal."s);
      }

      graphic = graphicsStore.get(graphicsName);
      vao = graphic->vao;
      textures.push_back(graphic->texid);
      mode = graphic->mode;
      nvertex = graphic->nvertex;
      type = graphic->type;
      offset = graphic->offset;
    }

OGLModel SimpleOGLModelSheet::generateModel(std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar) {
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

  return OGLModel(vao, textures, mode, nvertex, type, offset, m, glm::mat4(1.0f));
}

}  // namespace zbe
