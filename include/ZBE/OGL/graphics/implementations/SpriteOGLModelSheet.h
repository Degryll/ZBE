/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteOGLModelSheet.h
 * @since 2018-06-09
 * @date 2018-06-09
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a model containing an sprite from a given entity.
 */

#ifndef ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SPRITEOGLMODELSHEET_H_
#define ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SPRITEOGLMODELSHEET_H_

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

#include "ZBE/resources/definitions.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
class SpriteOGLModelSheet : public OGLModelSheet<uint64_t, Vector2D, Vector2D> { // TODO llevar esto tipos al JSONGraphicsLoaders (linea 74)
public:
  SpriteOGLModelSheet(std::shared_ptr<SDLOGLWindow> window)
    : spriteDefintion(), vao(), textures(), mode(), nvertex(),  type(), offset(nullptr), window(window) {
    using namespace std::string_literals;
    auto id = dict.get("model.DEFAULT2D"s);
    auto modelInfo = window->getModelStore()->getModel(id);
    this->vao = std::get<0>(modelInfo);
    this->nvertex = std::get<1>(modelInfo);
    this->mode = GL_TRIANGLES;
    this->type = GL_UNSIGNED_INT;
  }

  /** \brief Virtual destructor
  */
  virtual ~SpriteOGLModelSheet() = default; //!< Virtual destrutor.

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  OGLModel generateModel(std::shared_ptr<MAvatar<uint64_t, Vector2D, Vector2D> > avatar) {
    auto prepos = avatar->get<1, Vector2D>();
    Vector2D pos = prepos->get();
    Vector2D size = avatar->get<2, Vector2D>()->get();
    //uint64_t gid = avatar->get<3, uint64_t>()->get();
    auto cTime = avatar->getContextTime();

    uint64_t time = cTime->getTotalTime() % (spriteDefintion.img.frameAmount * spriteDefintion.img.frameTime);
    uint64_t frame = time/spriteDefintion.img.frameTime;

    auto p = spriteDefintion.img.texCoord.p + (spriteDefintion.img.texCoordOffset *  frame);
    auto t = glm::vec3(p[0], p[1], 0.0);
    auto s = glm::vec3(spriteDefintion.img.texCoord.v.x, spriteDefintion.img.texCoord.v.y, 1.0);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), t);
    glm::mat4 scale     = glm::scale(    glm::mat4(1.0f), s);
    glm::mat4 tx = translate * scale;

    auto p2 = pos + spriteDefintion.drawOffset;
    auto t2 = glm::vec3(p2[0], p2[1], 0.0);
    int w, h;
    window->getDrawableSize(&w, &h);
    glm::vec3 s2{size.x * spriteDefintion.scale.x * spriteDefintion.img.region.v.x / w, size.y * spriteDefintion.scale.y * spriteDefintion.img.region.v.y / h, 1.0};

    translate = glm::translate(glm::mat4(1.0f), t2);
    scale     = glm::scale(    glm::mat4(1.0f), s2);
    glm::mat4 m = translate * scale;
    return OGLModel(vao, textures, mode, nvertex, type, offset, m, tx);
  }

  void setSprite(SprtDef sd){
      spriteDefintion = sd;
      textures.push_back(window->getTextureStore()->getTexture(spriteDefintion.img.imgSrcId));
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  SprtDef spriteDefintion;
  GLuint vao;
  std::vector<GLuint> textures;
  GLenum  mode;
  GLsizei nvertex;
  GLenum  type;
  const GLvoid* offset;

  std::shared_ptr<SDLOGLWindow> window;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SPRITEOGLMODELSHEET_H_
