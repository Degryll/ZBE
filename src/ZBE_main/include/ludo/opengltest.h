#ifndef LUDO_OPENGLTEST_H_
#define LUDO_OPENGLTEST_H_

#include <cstdio>
#include <ctime>
#include <fstream>
#include <memory>
#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/tools/graphics/Camera.h"

//#include "ZBE/entities/avatars/implementations/SimpleSingleModel.h"
#include "ZBE/entities/avatars/SingleModel.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/OGL/graphics/implementations/OGLModelSheets.h"
#include "ZBE/OGL/drawers/OGLModelSheetDrawer.h"
#include "ZBE/OGL/daemons/OGLPreDrawer.h"
#include "ZBE/OGL/daemons/OGLPostDraw.h"


namespace ludo {

std::vector<uint64_t> loadGraphics(std::shared_ptr<zbe::SDLOGLWindow> window);

void setFrustum(GLfloat *projection, float left, float right, float bottom, float top, float near, float far);

void set_perspective(GLfloat *projection, float fov, float aspect, float znear, float zfar);

std::vector<GLfloat> traspose(std::vector<GLfloat> viewMat);

int opengltest(int argc, char** argv);

}  // namespace ludo

#endif  // LUDO_OPENGLTEST_H_
