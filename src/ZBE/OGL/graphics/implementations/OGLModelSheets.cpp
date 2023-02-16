/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleOGLModelSheet.cpp
 * @since 2021-05-20
 * @date 2021-05-20
 * @author Ludo Degryll Batis
 * @brief implementation of SimpleOGLModelSheet.
 */

#include "ZBE/OGL/graphics/implementations/OGLModelSheets.h"
#include "ZBE/core/tools/math/math.h"

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
  Vector3D dir = avatar->get<2, Vector3D>()->get();
  glm::vec3 glDir(dir.x, dir.y, dir.z);
  float angle = (float) avatar->get<3, double>()->get();
  float baseScale = (float) avatar->get<4, double>()->get();;
  glm::mat4 mat(1.0);

  glm::mat4 translate = glm::translate(mat, glPos);
  glm::mat4 rotate    = glm::rotate(   mat, angle, glDir);
  glm::mat4 scale     = glm::scale(    mat, glm::vec3(baseScale));
  glm::mat4 m = translate * scale * rotate;

  return OGLModel(vao, textures, mode, nvertex, type, offset, m, glm::mat4(1.0f));
}


LookAtOGLModelSheet::LookAtOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t modelId, uint64_t texId)
  : vao(std::get<0>(window->getModelStore()->getModel(modelId))), nvertex(std::get<1>(window->getModelStore()->getModel(modelId))), textures() {
    textures.push_back(window->getTextureStore()->getTexture(texId));
}

LookAtOGLModelSheet::LookAtOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t graphicsId, RsrcStore<OGLGraphics> &graphicsStore)
  : graphic(graphicsStore.get(graphicsId)), vao(graphic->vao), textures{graphic->texid}, mode(graphic->mode), nvertex(graphic->nvertex), type(graphic->type), offset(graphic->offset) {}

LookAtOGLModelSheet::LookAtOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, std::string graphicsName, RsrcStore<OGLGraphics> &graphicsStore)
: graphic(nullptr), vao(0), textures(), mode(0), nvertex(0), type(0), offset(nullptr) { // TODO Find a way to write this using an initilaizer list
  using namespace std::string_literals;
  if (!graphicsStore.contains(graphicsName)) {
    SysError::setError("LookAtOGLModelSheet for graphic: "s + graphicsName + " is not a LookAtOGLModelSheet literal."s);
  }

  graphic = graphicsStore.get(graphicsName);
  vao = graphic->vao;
  textures.push_back(graphic->texid);
  mode = graphic->mode;
  nvertex = graphic->nvertex;
  type = graphic->type;
  offset = graphic->offset;
}

OGLModel LookAtOGLModelSheet::generateModel(std::shared_ptr<MAvatar<uint64_t, double, Vector3D, Vector3D, Vector3D> > avatar) {
  Vector3D pos = avatar->get<1, Vector3D>()->get();
  glm::vec3 glPos(pos.x, pos.y, pos.z);
  Vector3D dir = avatar->get<2, Vector3D>()->get();
  dir.normalize();
  glm::vec3 glDir(dir.x, dir.y, dir.z);
  Vector3D upw = avatar->get<3, Vector3D>()->get();
  upw = upw.normalize();
  glm::vec3 glUpw(upw.x, upw.y, upw.z);

  Vector3D nor = cross(dir, upw);
  nor.normalize();
  glm::vec3 glNor(nor.x, nor.y, nor.z);


  float baseScale = (float) avatar->get<4, double>()->get();;
  glm::mat4 mat(1.0);

  glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);

//   // We will initially asume the same origin for all the models.
//   // In the future we can pass it by parameter

  // glm::vec3 x(1.0,0.0,0.0);
  // glm::vec3 y(0.0,1.0,0.0);
  // glm::vec3 z(0.0,0.0,1.0);

  // glm::vec3 x(1.0,0.0,0.0);
  // glm::vec3 y(0.0,0.0,1.0);
  // glm::vec3 z(0.0,1.0,0.0);

  // glm::vec3 x(0.0,1.0,0.0);
  // glm::vec3 y(0.0,0.0,1.0);
  // glm::vec3 z(1.0,0.0,0.0);

  // glm::vec3 x(0.0,1.0,0.0);
  // glm::vec3 y(1.0,0.0,0.0);
  // glm::vec3 z(0.0,0.0,1.0);

  // glm::vec3 x(0.0,0.0,1.0);
  // glm::vec3 y(1.0,0.0,0.0);
  // glm::vec3 z(0.0,1.0,0.0);

  // glm::vec3 x(0.0,0.0,1.0);
  // glm::vec3 y(0.0,1.0,0.0);
  // glm::vec3 z(1.0,0.0,0.0);

  glm::vec3 x(1.0,0.0,0.0);
  glm::vec3 y(0.0,1.0,0.0);
  glm::vec3 z(0.0,0.0,1.0);

  // glm::mat4 rotate({
  //   glm::dot(glDir, x), glm::dot(glNor, x), glm::dot(glUpw, x),
  //   glm::dot(glDir, y), glm::dot(glNor, y), glm::dot(glUpw, y),
  //   glm::dot(glDir, z), glm::dot(glNor, z), glm::dot(glUpw, z)
  // });

  // glm::mat4 rotate({
  //   glm::dot(glNor, x), glm::dot(glUpw, x), glm::dot(glDir, x),
  //   glm::dot(glNor, y), glm::dot(glUpw, y), glm::dot(glDir, y),
  //   glm::dot(glNor, z), glm::dot(glUpw, z), glm::dot(glDir, z)
  // });

  glm::mat4 rotate({
    glm::dot(glNor, x), glm::dot(glNor, y), glm::dot(glNor, z),
    glm::dot(glUpw, x), glm::dot(glUpw, y), glm::dot(glUpw, z),
    glm::dot(glDir, x), glm::dot(glDir, y), glm::dot(glDir, z)
  });

  glm::mat4 rotate90  = glm::rotate(glm::mat4(1.0f), -(float)PI/2.0f, glm::vec3(1.0,0.0,0.0));

  //glm::mat4 rotate(1.0f);

  //TODO: la matemática parece correcta pero tenemos los vectores emputecidos.
  //Hay que ver cual es cual.

  // glm::mat4 rotate({
  //   X'x   Y'x   Z'x
  //   X'y   Y'y   Z'y
  //   X'z   Y'z   Z'z
  // });
//  https://stackoverflow.com/questions/21828801/how-to-find-correct-rotation-from-one-vector-to-another
  glm::mat4 scale     = glm::scale(    glm::mat4(1.0f), glm::vec3(baseScale));
  glm::mat4 m = translate * scale * rotate * rotate90;

  return OGLModel(vao, textures, mode, nvertex, type, offset, m, glm::mat4(1.0f));
}

}  // namespace zbe
