/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetDrawer.h
 * @since 2017-06-15
 * @date 2018-02-25
 * @author Ludo
 * @brief class ZBEAPI that know how to draw using SpriteSheets.
 */

#ifndef ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_
#define ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_

#include <memory>

#include <cstdio>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/OGL/graphics/OGLModelSheet.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief class ZBEAPI that know how to draw using SpriteSheets.
 */
template<unsigned idx, typename T, typename ...Ts>
class OGLModelSheetDrawer : public Behavior<T, Ts...> {
  public:
    OGLModelSheetDrawer(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.
    void operator=(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.

    /** \brief Empty constructor
     */
    OGLModelSheetDrawer() : gProgramID(), window(nullptr), rsOglMs(RsrcStore<OGLModelSheet<T, Ts...> >::getInstance()) {}

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    OGLModelSheetDrawer(std::shared_ptr<SDLOGLWindow> window, uint64_t programId)
      : gProgramID(window->getShaderStore()->getShader(programId)), window(window), rsOglMs(RsrcStore<OGLModelSheet<T, Ts...> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~OGLModelSheetDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<MAvatar<T, Ts...> > avatar) {
      std::shared_ptr<_Avatar<idx, uint64_t> > av = avatar;
      auto val = av->get();
      uint64_t gId = val->get();
      std::shared_ptr<OGLModelSheet<T, Ts...> > oglMs = rsOglMs.get(gId);

      OGLModel model = oglMs->generateModel(avatar);

      GLuint modelViewLoc = glGetUniformLocation(gProgramID, "model" );
      glUniformMatrix4fv(modelViewLoc, 1, false, (GLfloat*) glm::value_ptr(model.modelMat));

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, model.textures[0]);
      glBindVertexArray(model.vao);
      glDrawElements( model.mode, model.nvertex, model.type, model.offset );

      glBindVertexArray(0);
    }

    void setConfig(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
      this->window = window;
      gProgramID = window->getShaderStore()->getShader(programId);
    }

  private:
    GLuint gProgramID;
    std::shared_ptr<SDLOGLWindow> window = nullptr;  //!< A SDL window with its context.
    std::shared_ptr<SDLImageStore> imgStore; //!< Where the images are stored.
    RsrcStore<OGLModelSheet<T, Ts...> >& rsOglMs;
};

}  // namespace zbe

#endif  // ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_
