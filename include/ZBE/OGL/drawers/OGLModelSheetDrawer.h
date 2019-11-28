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
template<typename T>
class OGLModelSheetDrawer : public Behavior<T> {
  public:
    OGLModelSheetDrawer(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.
    void operator=(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.

    /** \brief Empty constructor
     */
    OGLModelSheetDrawer()
      : gProgramID(), window(nullptr), rsOglMs(RsrcStore<OGLModelSheet<T> >::getInstance()) {}

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    OGLModelSheetDrawer(std::shared_ptr<SDLOGLWindow> window, uint64_t programId)
      : gProgramID(window->getShaderStore()->getShader(programId)), window(window), rsOglMs(RsrcStore<OGLModelSheet<T> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~OGLModelSheetDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<T> > entity) {
      T* avatar;
      assignAvatar(entity, &avatar);
      std::shared_ptr<OGLModelSheet<T> > oglMs = rsOglMs.get(avatar->getGraphics());
      OGLModel model = oglMs->generateSprite(avatar);
      GLuint modelViewLoc = glGetUniformLocation(gProgramID, "model" );
      glUniformMatrix4fv(modelViewLoc, 1, false, (GLfloat*) glm::value_ptr(model.modelMat));

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, model.textures[0]);
      glBindVertexArray(model.vao);

      glDrawElements( GL_TRIANGLES, model.nvertex, GL_UNSIGNED_INT, NULL );

      glBindVertexArray(0);
    }

    void setConfig(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
      this->window = window;
      gProgramID = window->getShaderStore()->getShader(programId);
    }

  private:
    GLuint gProgramID;
    std::shared_ptr<SDLOGLWindow> window;  //!< A SDL window with its context.
    //std::shared_ptr<SDLImageStore> imgStore; //!< Where the images are stored.
    RsrcStore<OGLModelSheet<T> >& rsOglMs; //!< Resource manager instance.
};

}  // namespace zbe

#endif  // ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_
