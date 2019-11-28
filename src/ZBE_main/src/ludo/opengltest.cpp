#include "ludo/opengltest.h"

#include <unordered_map>

namespace ludo {

const float PI = 3.14159f;
const float TO_RADS = PI/180.0f;

std::vector<uint64_t> loadGraphics(std::shared_ptr<zbe::SDLOGLWindow> window) {
  //std::vector<std::tuple<GLuint, GLsizei> > indexes(2);
  std::vector<uint64_t> indexes(2);
  GLfloat vertexData[] = {
           // front
           -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
           // back
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
           // left
           -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
           -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
           -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
           // right
           0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
           0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
           0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
           0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
           0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
           0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
           // top
           -0.5f, 0.5f,  0.5f, 0.0f, 0.0f,
            0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
           -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
           -0.5f, 0.5f,  0.5f, 0.0f, 0.0f,
           // bottom
           -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
           -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f, 0.0f, 0.0f};

  GLuint indexData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

  GLfloat vertexData2[] = {
          -5.5f, -0.5f,  5.5f, 0.0f, 0.0f,
           5.5f, -0.5f,  5.5f, 1.0f, 0.0f,
           5.5f, -0.5f, -5.5f, 1.0f, 1.0f,
           5.5f, -0.5f, -5.5f, 1.0f, 1.0f,
          -5.5f, -0.5f, -5.5f, 0.0f, 1.0f,
          -5.5f, -0.5f,  5.5f, 0.0f, 0.0f};

  //uint64_t index;
  indexes[0] = window->getModelStore()->loadModel(vertexData, indexData, 36, 36);
  //indexes[0] = window->getModelStore()->getModel(index);
  indexes[1] = window->getModelStore()->loadModel(vertexData2, indexData, 6, 6);
  //indexes[1] = window->getModelStore()->getModel(index);

  return indexes;
}

void setFrustum(GLfloat *projection, float left, float right, float bottom, float top, float near, float far) {
    projection[0] = 2 * near / (right - left);
    projection[2] = (right + left) / (right - left);
    projection[5] = 2 * near / (top - bottom);
    projection[6] = (top + bottom) / (top - bottom);
    projection[10] = -(far + near) / (far - near);
    projection[11] = -(2 * far * near) / (far - near);
    projection[14] = -1;
    projection[15] = 0;
}

void set_perspective(GLfloat *projection, float fov, float aspect, float znear, float zfar) {
  float tangent = tan(TO_RADS * (fov / 2.0));
  float height = znear * tangent;
  float width = height * aspect;
  setFrustum(projection, -width, width, -height, height, znear, zfar);
}

std::vector<GLfloat> traspose(std::vector<GLfloat> viewMat){
    std::vector<GLfloat> v(16);
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        v[i * 4 + j] = viewMat[j * 4 + i];
      }
    }
    return v;
}

int opengltest(int, char** ) {
  using namespace zbe;
  printf("unordere double: %d\n", sizeof(std::unordered_map<uint64_t, std::shared_ptr<Value<double> > >));
  printf("unordere char: %d\n", sizeof(std::unordered_map<uint64_t, std::shared_ptr<Value<char> > >));
   std::shared_ptr<SDLOGLWindow> window = std::make_shared<SDLOGLWindow>("Veamos", 1000, 1000);

   // GLfloat projection[] = {
   //   0.0f, 0.0f, 0.0f, 0.0f,
   //   0.0f, 0.0f, 0.0f, 0.0f,
   //   0.0f, 0.0f, 0.0f, 0.0f,
   //   0.0f, 0.0f, 0.0f, 0.0f
   // };
   //
   // std::vector<GLfloat> viewMatRaw {
   //   1.0f, 0.0f, 0.0f, 0.0f,
   //   0.0f, 1.0f, 0.0f, 0.0f,
   //   0.0f, 0.0f, 1.0f, -5.0f,
   //   0.0f, 0.0f, 0.0f, 1.0f
   // };

   // glm::mat4 auxViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   // GLfloat* viewMat = glm::value_ptr(auxViewMat);
   // for(auto val : viewMatRaw) {
   //   printf("%f, ", val);
   // }
   // printf("\n------------------------------\n");
   // std::vector<GLfloat> viewMat = traspose(viewMatRaw);
   // for(auto val : viewMat) {
   //   printf("%f, ", val);
   // }
   printf("\n------------------------------\n");
   glm::mat4 auxViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   GLfloat* viewMat1 = glm::value_ptr(auxViewMat);
   std::vector<GLfloat> viewMatGenerated = std::vector<GLfloat>(viewMat1, viewMat1 + 16);
   for(auto val : viewMatGenerated) {
     printf("%f, ", val);
   }

   std::shared_ptr<Camera> cam = std::make_shared<Camera>();

   cam->set_perspective(120.0, 1.0, 1.0, 50.0);

   float a = 0.0f;

   std::vector<uint64_t> models = loadGraphics(window);

   std::vector<ShaderDef> shaderDefs;

   shaderDefs.push_back(ShaderDef("data/shaders/working/test_001.vs", GL_VERTEX_SHADER));
   shaderDefs.push_back(ShaderDef("data/shaders/working/test_001.fs", GL_FRAGMENT_SHADER));

   uint64_t shaderId = window->getShaderStore()->loadShader(shaderDefs);

   uint64_t cubeTex = window->getTextureStore()->loadImg("data/images/ludo/arrow_r_000_512.png");
   uint64_t floorTex = window->getTextureStore()->loadImg("data/images/ludo/orb_001_512.png");

   //std::shared_ptr<std::vector<GLfloat> > projectionV = std::make_shared<std::vector<GLfloat> >(projection, projection + (sizeof(projection)/sizeof(GLfloat)));
   //std::shared_ptr<std::vector<GLfloat> > viewV = std::make_shared<std::vector<GLfloat> >(viewMatGenerated);

   std::shared_ptr<SingleModelOGLModelSheet> modelSheet1 = std::make_shared<SingleModelOGLModelSheet>(window, models[1], floorTex);
   std::shared_ptr<SingleModelOGLModelSheet> modelSheet2 = std::make_shared<SingleModelOGLModelSheet>(window, models[0], cubeTex);

   RsrcStore<OGLModelSheet<SingleModel> >& rsModel = RsrcStore<OGLModelSheet<SingleModel> >::getInstance();

   uint64_t modelId1 = SysIdGenerator::getId();
   uint64_t modelId2 = SysIdGenerator::getId();

   rsModel.insert(modelId1, modelSheet1);
   rsModel.insert(modelId2, modelSheet2);

   Point3D position({0.0f, 0.0f, 0.0f});
   Vector3D orientation({1.0f, 1.0f, 1.0f});
   float angle = 0.0f;
   float scale1 = 1.0f;
   float scale2 = 1.0f;

   SimpleSingleModel* sm1 = new SimpleSingleModel(position, orientation, angle, scale1, modelId1);
   SimpleSingleModel* sm2 = new SimpleSingleModel(position, orientation, angle, scale2, modelId2);

   std::shared_ptr<AvatarEntityContainer<SingleModel> > aecSm1 = std::make_shared<AvatarEntityContainer<SingleModel> >(std::make_shared<AvatarEntityFixed<SingleModel> >(sm1));
   std::shared_ptr<AvatarEntityContainer<SingleModel> > aecSm2 = std::make_shared<AvatarEntityContainer<SingleModel> >(std::make_shared<AvatarEntityFixed<SingleModel> >(sm2));

   OGLPreDrawer preDraw(window, shaderId, cam);
   OGLPostDraw posDraw(window);

   OGLModelSheetDrawer<SingleModel> draw(window, shaderId);

   if(SysError::getNErrors()>0){
     printf("Postion!: %s\n", SysError::getFirstErrorString().c_str());
   } else {
     printf("Good\n");
   }


  clock_t currentTime, lastTime = CLOCKS_PER_SEC;
  int nframes = 0;
  while(true) {
     a += 0.0001f;


     currentTime = clock();
     nframes++;
     if ( currentTime - lastTime >= CLOCKS_PER_SEC ){
         printf("%f ms/frame (%d FPS)\n", 1000.0/double(nframes*CLOCKS_PER_SEC), nframes);
         nframes = 0;
         lastTime += CLOCKS_PER_SEC;
     }

     cam->lookAt(Vector3D({sin(a) * 5.0f, cos(a*4) * 1.0f + 2.0f, cos(a) * 5.0f}), Vector3D({cos(a), 0.0f, cos(a)}), Vector3D({0.0f, 1.0f, 0.0f}));

     //position = {cos(a)*60.0f, sin(a)*60.0f, 30.0f};
     position = {0.0f, 0.0f, 0.0f};
     orientation = {0.0f, 0.0f, 1.0f};
     angle = 0.0f;
     //sm1->setPosition(position);
     //sm1->setOrientation(orientation);
     //sm1->setAngle(angle);
     //position = {cos(a*5) * 1.0f, sin(a) * 1.0f, 0.0f};
     orientation = {1.0f, sin(a) * 1.0f, 0.0f};
     angle = TO_RADS * 360.0f * (a/5);
     //angle = TO_RADS * 45.0f ;
     //sm2->setPosition(position);
     sm2->setOrientation(orientation);
     sm2->setAngle(angle);

     glClearColor(cos(a), 0.2f, 0.5f, 0.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     preDraw.run();
     draw.apply(aecSm1);
     draw.apply(aecSm2);
     posDraw.run();

     window->glSwap();
//    window->present();
  }

  delete sm1;
  delete sm2;

  return 0;
}

} //namespace Ludo
