/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDLOGLWindow.h
 * @since 2018-05-28
 * @date 2018-05-28
 * @author Degryll Ludo
 * @brief Defines the following structures:
 *  - SDLOGLWindow: Create a windows using SDL 2.0. with OpenGL support
 *  - OGLTextureStore:
 */

#ifndef ZBE_SDL_SYSTEM_SDLOGLWINDOW_H_
#define ZBE_SDL_SYSTEM_SDLOGLWINDOW_H_

#include <memory>
#include <mutex>
#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

const int ZBE_GL_MAJOR_VERSION = 3;
const int ZBE_GL_MINOR_VERSION = 3;

class ZBEAPI OGLTextureStore;
class ZBEAPI OGLModelStore;
class ZBEAPI OGLShaderStore;

/**
 * @class ZBEAPI SDLOGLWindow
 * @brief Used to create windows using SDL 2.0. with OpenGL support.
 */
class ZBEAPI SDLOGLWindow : public SDLWindow {
public:
  SDLOGLWindow(const SDLOGLWindow&) = delete;  //!< Does not make sense to "copy" a SDLOGLWindow.
  void operator=(const SDLOGLWindow&) = delete;  //!< Does not make sense to "copy" a SDLOGLWindow.

  /** \brief Creates a new SDLOGLWindow and a Renderer.
   *
   *  Creates a new SDLOGLWindow and a Renderer with the size and flags specified.
   *  \param title Title of the Window.
   *  \param width Width of the Window.
   *  \param height Height of the Window.
   *  \param window_flags Flags for the SDLOGLWindow creation. Default no flags.
   *  \param rederer_flags Flags for the Renderer creation. Default no flags.
   */
  SDLOGLWindow(const char* title, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0) : SDLWindow(title, width, height, window_flags | SDL_WINDOW_OPENGL, rederer_flags), texStore(std::make_shared<OGLTextureStore>()), modelStore(std::make_shared<OGLModelStore>()), shaderStore(std::make_shared<OGLShaderStore>()) {
    createGLContext();
  }

  /** \brief Creates a new SDLOGLWindow and a Renderer in a specific position.
   *
   *  Creates a new SDLOGLWindow and a Renderer with the position, size and flags specified.
   *  \param title Title of the Window.
   *  \param x X coordinates of the initial position of the window.
   *  \param y Y coordinates of the initial position of the window..
   *  \param width Width of the Window.
   *  \param height Height of the Window.
   *  \param window_flags Flags for the SDLOGLWindow creation. Default no flags.
   *  \param rederer_flags Flags for the Renderer creation. Default no flags.
   */
  SDLOGLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0) : SDLWindow(title, x, y, width, height, window_flags | SDL_WINDOW_OPENGL, rederer_flags), texStore(std::make_shared<OGLTextureStore>()), modelStore(std::make_shared<OGLModelStore>()), shaderStore(std::make_shared<OGLShaderStore>()){
    createGLContext();
  }

  /** \brief Free resources and destroy the Renderer and the SDLOGLWindow.
   */
  ~SDLOGLWindow() {};

  /** \brief internal OGLTextureStore getter
   */
  std::shared_ptr<OGLTextureStore> getTextureStore() {return (texStore);}

  /** \brief internal OGLTextureStore getter
   */
  std::shared_ptr<OGLModelStore> getModelStore() {return (modelStore);}

  /** \brief internal OGLTextureStore getter
   */
  std::shared_ptr<OGLShaderStore> getShaderStore() {return (shaderStore);}

  /** \brief Swap Open GL buffers.
   */
  void glSwap() {SDL_GL_SwapWindow(getSDL_Window());}

private:

  void createGLContext();

  std::shared_ptr<OGLTextureStore> texStore;
  std::shared_ptr<OGLModelStore> modelStore;
  std::shared_ptr<OGLShaderStore> shaderStore;
};

class ZBEAPI OGLTextureStore {
public:
    OGLTextureStore(const OGLTextureStore&) = delete; //!< Delete copy constructor
    void operator=(const OGLTextureStore&) = delete; //!< Delete assing aperator

    /** \brief Creates a new OGLTextureStore associated to a renderer.
     */
    OGLTextureStore();

    /** \brief Default destructor. Will free all loaded textures.
     */
    ~OGLTextureStore() {};

    /** \brief Creates an empty texture.
     *
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), storeTexture()
     */
    uint64_t createTexture(unsigned weight, unsigned height) {return storeTexture(_createTexture(nullptr, weight, height));}

    /** \brief Load an image to create a texture in this store.
     *
     *  \param url Image file to be loaded.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), storeTexture()
     */
    uint64_t loadImg(const char *url);

    /** \brief Reload an image to an already created texture.
     *
     *  \param url Image file to be reloaded.
     *  \param An id to the texture already created.
     *  \sa loadImg(), storeTexture()
     */
    void reloadImg(uint64_t id, const char *url);

    /** \brief Return a stored texture;
     *  \param An id to the texture already created.
     *  \return a GL texture id.
     *  \sa loadImg(), storeTexture()
     */
    GLuint getTexture(uint64_t id);

private:
  uint64_t storeTexture(const GLuint tex);
  void overwriteTexture(uint64_t index, const GLuint tex);
  GLuint _createTexture(const GLvoid *data, unsigned w, unsigned h);
  std::vector<unsigned char> loadPNG(const char* filename, unsigned &width, unsigned &height);

  std::vector<GLuint> texCollection;  //!< Collection of textures.
  std::mutex m;                       //!< Mutex to avoid race conditions.
};

class ZBEAPI OGLModelStore {
public:
    OGLModelStore(const OGLModelStore&) = delete; //!< Delete copy constructor
    void operator=(const OGLModelStore&) = delete; //!< Delete assing aperator

    OGLModelStore() : modelCollection(), m() {};

    ~OGLModelStore() {};

    uint64_t loadModel(const GLfloat *vertexData, const GLuint *indexData, int vSize ,int iSize);

    std::tuple<GLuint, GLsizei> getModel(uint64_t id);

private:
  uint64_t storeModel(const GLuint vao, const GLsizei nvertex);
  std::vector<std::tuple<GLuint, GLsizei> > modelCollection;  //!< Collection of textures.
  std::mutex m;
};

struct ZBEAPI ShaderDef {
  ShaderDef() : filename(), type() {}
  ShaderDef(std::string filename, GLenum type) : filename(filename), type(type) {}
  std::string filename;
  GLenum type;
};

class ZBEAPI OGLShaderStore {
public:
  OGLShaderStore(const OGLShaderStore&) = delete; //!< Delete copy constructor
  void operator=(const OGLShaderStore&) = delete; //!< Delete assing aperator

  OGLShaderStore() : programCollection(), m() {}

  uint64_t loadShader(std::vector<ShaderDef> shaderDefs);

  GLuint getShader(uint64_t id);

private:
  const std::string readFile(const char* filename);
  void printShaderLog(GLuint shader);
  void printProgramLog(GLuint program);
  void compileShader(GLuint gProgramID, const char* shaderSrc[], GLenum shaderType);
  void linkProgram(GLuint gProgramID);
  uint64_t storeProgram(const GLuint program);

  std::vector<GLuint> programCollection;  //!< Collection of textures.
  std::mutex m;
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLOGLWINDOW_H_
