/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDL_Window.cpp
 * @since 2015-05-30
 * @date 2018-03-28
 * @author Degryll Ludo Batis
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include <fstream>
#include "lodepng.h"

namespace zbe {

const GLuint V_POS = 0;
const GLuint VT_POS = 1;

//----- SDLOGLWindow -----//

  void GLAPIENTRY
MessageCallback( GLenum ,//source,
                 GLenum type,
                 GLuint ,//id,
                 GLenum severity,
                 GLsizei ,//length,
                 const GLchar* message,
                 const void* )//userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void SDLOGLWindow::createGLContext() {
  SDL_GLContext gContext = SDL_GL_CreateContext(getSDL_Window());
  if( gContext == NULL ) {
     SysError::setError(std::string("ERROR: SDL could not create an OGL context. SDL ERROR: ") + SDL_GetError());
  }
  //Use OpenGL 3.1 core
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, ZBE_GL_MAJOR_VERSION );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, ZBE_GL_MINOR_VERSION );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


  SDL_GL_SetSwapInterval(0);

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if( glewError != GLEW_OK ) {
    SysError::setError(std::string("ERROR: Error initializing GLEW: ") + std::string((char*)glewGetErrorString( glewError )));
  }

// During init, enable debug output
glEnable              ( GL_DEBUG_OUTPUT );
glDebugMessageCallback( MessageCallback, 0 );

  //glEnable(GL_TEXTURE_2D);printf("Pista a 0x%x\n", glGetError()); fflush(stdout);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glCullFace(GL_FRONT_AND_BACK);
}

//----- OGLTextureStore -----//

OGLTextureStore::OGLTextureStore() : texCollection(), m() {
  const unsigned deftex[16] = {255, 128, 255, 255,
                                 0,   0,   0, 255,
                               255, 128, 255, 255,
                                 0,   0,   0, 255};
  texCollection.push_back(_createTexture(deftex, 2, 2));
}

uint64_t OGLTextureStore::loadImg(const char *url) {
  unsigned w, h;
  std::vector<unsigned char> data = loadPNG(url, w, h);
  return storeTexture(_createTexture(&data[0], w, h));
}

void OGLTextureStore::reloadImg(uint64_t id, const char *url) {
  unsigned w, h;
  std::vector<unsigned char> data = loadPNG(url, w, h);
  return overwriteTexture(id, _createTexture(&data[0], w, h));
}

GLuint OGLTextureStore::getTexture(uint64_t id) {
  if(texCollection.size() <= id) {
    zbe::SysError::setError(std::string("ERROR: trying to get a non existing texture."));
    return (0);
  }
  return texCollection[id];
}

//----- OGLTextureStore : private -----//


uint64_t OGLTextureStore::storeTexture(const GLuint tex) {
  uint64_t index;
  m.lock();
    texCollection.push_back(tex);
    index = texCollection.size() - 1;
  m.unlock();
  return (index);
}

void OGLTextureStore::overwriteTexture(uint64_t index, const GLuint tex) {
  m.lock();
    if(texCollection.size()> index) {
      texCollection[index] = tex;
    } else {
      zbe::SysError::setError(std::string("ERROR: trying to overwrite a non existing texture: "));
    }
  m.unlock();
}

GLuint OGLTextureStore::_createTexture(const GLvoid *data, unsigned w, unsigned h) {
  m.lock();
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  m.unlock();
  return texture;
}

std::vector<unsigned char> OGLTextureStore::loadPNG(const char* filename, unsigned &width, unsigned &height) {
  std::vector<unsigned char> image;
  unsigned error = lodepng::decode(image, width, height, filename);
  if(error != 0)  {
    zbe::SysError::setError(std::string("ERROR: lodepng could not load the texture: ") + lodepng_error_text(error));
  }
  return image;
}

//----- OGLModelStore -----//

uint64_t OGLModelStore::loadModel(const GLfloat *vertexData, const GLuint *indexData, int vSize ,int iSize) {
  GLuint vbo = 0;
  GLuint ibo = 0;
  GLuint vao = 0;

  //Create VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Create VBO
  glGenBuffers( 1, &vbo);
  glBindBuffer( GL_ARRAY_BUFFER, vbo);
  // (3 + 2) * vSize : (pos + tex) * nvertex
  glBufferData( GL_ARRAY_BUFFER, (3 + 2) * vSize * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

  glEnableVertexAttribArray(V_POS);
  glEnableVertexAttribArray(VT_POS);
  glVertexAttribPointer(V_POS, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(GLfloat), NULL );
  glVertexAttribPointer(VT_POS, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

  //Create IBO
  glGenBuffers( 1, &ibo);
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indexData, GL_STATIC_DRAW );

  glBindVertexArray(0);

  return storeModel(vao, iSize);
}

std::tuple<GLuint, GLsizei> OGLModelStore::getModel(uint64_t id) {
  if(modelCollection.size() <= id) {
    zbe::SysError::setError(std::string("ERROR: trying to get a non existing model."));
    return std::tuple<GLuint, GLsizei>();
  }
  return modelCollection[id];
}

//----- OGLModelStore : private -----//

uint64_t OGLModelStore::storeModel(const GLuint vao, const GLsizei nvertex) {
  uint64_t index;
  m.lock();
    modelCollection.push_back(std::tuple<GLuint, GLsizei>(vao, nvertex));
    index = modelCollection.size() - 1;
  m.unlock();
  return (index);
}

//----- OGLShaderStore -----//

uint64_t OGLShaderStore::loadShader(std::vector<ShaderDef> shaderDefs) {

  GLuint gProgramID = glCreateProgram();

  glBindAttribLocation(gProgramID, V_POS, "pos" );
  glBindAttribLocation(gProgramID, VT_POS, "texCoord" );

  for(ShaderDef sd : shaderDefs){
    std::string content = readFile(sd.filename.c_str());
    const char* c_content = content.c_str();
    compileShader(gProgramID, &(c_content), sd.type);
  }

  linkProgram(gProgramID);
  return storeProgram(gProgramID);
}

GLuint OGLShaderStore::getShader(uint64_t id) {
  if(programCollection.size() <= id) {
    zbe::SysError::setError(std::string("ERROR: trying to get a non existing shader."));
    return (0);
  }
  return programCollection[id];
}

//----- OGLShaderStore : private-----//

const std::string OGLShaderStore::readFile(const char* filename) {
    std::string content;
    std::ifstream fileStream(filename, std::ios::in);

    if(!fileStream.is_open()) {
        zbe::SysError::setError(std::string("Could not read file ") + std::string(filename) + std::string(". File does not exist."));
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();

    return content;
}

void OGLShaderStore::printProgramLog(GLuint /*program*/) {
  //TODO use logger
  // if( glIsProgram( program ) ) {
  //     int infoLogLength = 0;
  //     int maxLength = infoLogLength;
  //     glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
  //     char* infoLog = new char[ maxLength ];
  //     glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
  //     if( infoLogLength > 0 ) { printf( "%s\n", infoLog );}
  //     delete[] infoLog;
  // } else {
  //     printf( "Name %d is not a program\n", program );
  // }
}

void OGLShaderStore::printShaderLog(GLuint /*shader*/) {
  //TODO use logger
  // if( glIsShader( shader ) ) {
  //     int infoLogLength = 0;
  //     int maxLength = infoLogLength;
  //     glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
  //     char* infoLog = new char[ maxLength ];
  //     glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
  //     if( infoLogLength > 0 ){ printf( "%s\n", infoLog );}
  //     delete[] infoLog;
  // } else {
  //     printf( "Name %d is not a shader\n", shader );
  // }
}

void OGLShaderStore::linkProgram(GLuint gProgramID) {
  glLinkProgram(gProgramID);
  GLint programSuccess = GL_TRUE;
  glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess );
  if( programSuccess != GL_TRUE ) {
    zbe::SysError::setError(std::string("Error linking program."));
    printProgramLog(gProgramID);
  }
}

void OGLShaderStore::compileShader(GLuint gProgramID, const char* shaderSrc[], GLenum shaderType ) {
  GLuint shader = glCreateShader(shaderType);

  glShaderSource(shader, 1, shaderSrc, NULL);
  glCompileShader(shader );

  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &vShaderCompiled);
  if(vShaderCompiled != GL_TRUE) {
    zbe::SysError::setError(std::string("Unable to compile shader."));
    printShaderLog( shader );
  } else {
    glAttachShader(gProgramID, shader);
  }
}

uint64_t OGLShaderStore::storeProgram(const GLuint program) {
  uint64_t index;
  m.lock();
    programCollection.push_back(program);
    index = programCollection.size() - 1;
  m.unlock();
  return (index);
}

//----- OGLShaderStore : private -----//

}  // namespace zbe
