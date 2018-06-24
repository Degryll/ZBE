/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetDrawer.h
 * @since 2017-06-15
 * @date 2018-02-25
 * @author Ludo
 * @brief Class that know how to draw using SpriteSheets.
 */

#ifndef ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_
#define ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_

#include <memory>
#include <cstdio>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/OGL/graphics/OGLModelSheet.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {

/** \brief Class that know how to draw using SpriteSheets.
 */
template<typename T>
class OGLModelSheetDrawer : public Behavior<T> {
  public:
    OGLModelSheetDrawer(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.
    void operator=(const OGLModelSheetDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    OGLModelSheetDrawer(std::shared_ptr<SDLOGLWindow> window, uint64_t programId)
      : gProgramID(window->getShaderStore()->getShader(programId)), window(window), rmglms(RsrcStore<OGLModelSheet<T> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~OGLModelSheetDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<T> > entity) {
      T* avatar;
      assignAvatar(entity, &avatar);
      std::shared_ptr<OGLModelSheet<T> > glms = rmglms.get(avatar->getGraphics());
      OGLModel model = glms->generateSprite(avatar);
      GLuint modelViewLoc = glGetUniformLocation(gProgramID, "model" );
      glUniformMatrix4fv(modelViewLoc, 1, false, (GLfloat*) glm::value_ptr(model.modelMat));

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, model.textures[0]);

      glBindVertexArray(model.vao);

      glDrawElements( GL_TRIANGLES, model.nvertex, GL_UNSIGNED_INT, NULL );
    }

  private:
    GLuint gProgramID;
    std::shared_ptr<SDLOGLWindow> window;  //!< A SDL window with its context.
    //std::shared_ptr<SDLImageStore> imgStore; //!< Where the images are stored.
    RsrcStore<OGLModelSheet<T> >& rmglms; //!< Resource manager instance.
};

}  // namespace zbe

#endif  // ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWER_H_
