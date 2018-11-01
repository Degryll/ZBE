/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleModelOGLModelSheet.h
 * @since 2018-06-09
 * @date 2018-06-09
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SINGLEMODELOGLMODELSHEET_H_
#define ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SINGLEMODELOGLMODELSHEET_H_

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ZBE/entities/avatars/SingleModel.h"

#include "ZBE/OGL/graphics/OGLModel.h"
#include "ZBE/OGL/graphics/OGLModelSheet.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
class SingleModelOGLModelSheet : public OGLModelSheet<SingleModel> {
public:
  SingleModelOGLModelSheet(const SingleModelOGLModelSheet&) = delete;
  void operator=(const SingleModelOGLModelSheet&) = delete;

  SingleModelOGLModelSheet(std::shared_ptr<SDLOGLWindow> window, uint64_t modelId, uint64_t texId)
    : vao(std::get<0>(window->getModelStore()->getModel(modelId))), nvertex(std::get<1>(window->getModelStore()->getModel(modelId))), textures() {
      textures.push_back(window->getTextureStore()->getTexture(texId));
    }

  /** \brief Virtual destructor
  */
  virtual ~SingleModelOGLModelSheet() {} //!< Virtual destrutor.

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  OGLModel generateSprite(SingleModel* sModel) {
    Point3D pos = sModel->getPosition();
    glm::vec3 glPos(pos.x, pos.y, pos.z);
    Vector3D ori = sModel->getOrientation();
    glm::vec3 glOri(ori.x, ori.y, ori.z);
    float angle = sModel->getAngle();
    float baseScale = sModel->getScale();
    glm::mat4 mat(1.0);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);
    glm::mat4 rotate    = glm::rotate(   glm::mat4(1.0f), angle, glOri);
    glm::mat4 scale     = glm::scale(    glm::mat4(1.0f), glm::vec3(baseScale));
    glm::mat4 m = translate * scale * rotate;

    return OGLModel(vao, nvertex, textures, m);
  };

private:
  GLuint vao;
  GLsizei nvertex;
  std::vector<GLuint> textures;
};

}  // namespace zbe

#endif  // ZBE_OGL_GRAPHICS_IMPLEMENTATIONS_SINGLEMODELOGLMODELSHEET_H_
