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
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f
  };

  GLuint indexData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

  GLfloat vertexData2[] = {
    -5.5f, -0.5f,  5.5f, 0.0f, 0.0f,
    5.5f, -0.5f,  5.5f, 1.0f, 0.0f,
    5.5f, -0.5f, -5.5f, 1.0f, 1.0f,
    5.5f, -0.5f, -5.5f, 1.0f, 1.0f,
    -5.5f, -0.5f, -5.5f, 0.0f, 1.0f,
    -5.5f, -0.5f,  5.5f, 0.0f, 0.0f
  };

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

std::vector<GLfloat> traspose(std::vector<GLfloat> viewMat) {
  std::vector<GLfloat> v(16);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      v[i * 4 + j] = viewMat[j * 4 + i];
    }
  }
  return v;
}

int opengltest(int, char** ) {
  using namespace zbe;
  printf("unordere double: %ld\n", sizeof(std::unordered_map<uint64_t, std::shared_ptr<Value<double> > >));
  printf("unordere char: %ld\n", sizeof(std::unordered_map<uint64_t, std::shared_ptr<Value<char> > >));
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


  // std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar
  RsrcStore<OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsModel = RsrcStore<OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >::getInstance();

  uint64_t modelId1 = SysIdGenerator::getId();
  uint64_t modelId2 = SysIdGenerator::getId();

  rsModel.insert(modelId1, modelSheet1);
  rsModel.insert(modelId2, modelSheet2);

  Vector3D position({0.0f, 0.0f, 0.0f});
  Vector3D orientation({1.0f, 1.0f, 1.0f});
  double angle = 0.0f;
  double scale1 = 1.0f;
  double scale2 = 1.0f;

  // SimpleSingleModel* sm1 = new SimpleSingleModel(position, orientation, angle, scale1, modelId1);
  // SimpleSingleModel* sm2 = new SimpleSingleModel(position, orientation, angle, scale2, modelId2);

  // std::shared_ptr<AvatarEntityContainer<SingleModel> > aecSm1 = std::make_shared<AvatarEntityContainer<SingleModel> >(std::make_shared<AvatarEntityFixed<SingleModel> >(sm1));
  // std::shared_ptr<AvatarEntityContainer<SingleModel> > aecSm2 = std::make_shared<AvatarEntityContainer<SingleModel> >(std::make_shared<AvatarEntityFixed<SingleModel> >(sm2));

  std::shared_ptr<Entity> ent1 = std::make_shared<Entity>();
  std::shared_ptr<Entity> ent2 = std::make_shared<Entity>();

  std::shared_ptr<Value<Vector3D> > pV1 = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<Vector3D> > oV1 = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<double> > scaleV1 = std::make_shared<SimpleValue<double> >(0);
  std::shared_ptr<Value<double> > angleV1 = std::make_shared<SimpleValue<double> >(0);
  std::shared_ptr<Value<uint64_t> > modelIdV1 = std::make_shared<SimpleValue<uint64_t> >(modelId1);
  ent1->setVector3D(1, pV1);
  ent1->setVector3D(2, oV1);
  ent1->setDouble(1, angleV1);
  ent1->setDouble(2, scaleV1);
  ent1->setUint(1, modelIdV1);

  std::shared_ptr<Value<Vector3D> > pV2 = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<Vector3D> > oV2 = std::make_shared<SimpleValue<Vector3D> >();
  std::shared_ptr<Value<double> > scaleV2 = std::make_shared<SimpleValue<double> >(0);
  std::shared_ptr<Value<double> > angleV2 = std::make_shared<SimpleValue<double> >(0);
  std::shared_ptr<Value<uint64_t> > modelIdV2 = std::make_shared<SimpleValue<uint64_t> >(modelId2);
  ent2->setVector3D(1, pV2);
  ent2->setVector3D(2, oV2);
  ent2->setDouble(1, angleV2);
  ent2->setDouble(2, scaleV2);
  ent2->setUint(1, modelIdV2);

  std::array<uint64_t, 5> a1{ {1, 2, 1, 2, 1} };
  std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar1 = std::make_shared<MBaseAvatar<uint64_t, double, double, Vector3D, Vector3D> >(ent1, a1);

  std::array<uint64_t, 5> a2{ {1, 2, 1, 2, 1} };
  std::shared_ptr<MAvatar<uint64_t, double, double, Vector3D, Vector3D> > avatar2 = std::make_shared<MBaseAvatar<uint64_t, double, double, Vector3D, Vector3D> >(ent2, a2);

  OGLPreDrawer preDraw(window, shaderId, cam);
  OGLPostDraw posDraw(window);

  auto draw = std::make_shared<OGLModelSheetDrawer<5, uint64_t, double, double, Vector3D, Vector3D> >(window, shaderId);

  if(SysError::getNErrors()>0) {
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
    if ( currentTime - lastTime >= CLOCKS_PER_SEC ) {
      printf("%f ms/frame (%d FPS)\n", 1000.0/double(nframes*CLOCKS_PER_SEC), nframes);
      nframes = 0;
      lastTime += CLOCKS_PER_SEC;
    }

    cam->lookAt(Vector3D({sin(a) * 5.0f, cos(a*4) * 1.0f + 2.0f, cos(a) * 5.0f}), Vector3D({cos(a), 0.0f, cos(a)}), Vector3D({0.0f, 1.0f, 0.0f}));
    cam->set_perspective(90.0 + (30.0*sin(2*a)), 1.0, 1.0, 50.0);

    scale1 = 1.0f + 0.5*cos(a);
    scale2 = 1.0f + 0.7*sin(a);

    position = {0.0f, 0.0f, 0.0f};
    orientation = {0.0f, 0.0f, 1.0f};
    angle = 0.0f;
    pV1->set(position);
    oV1->set(orientation);
    scaleV1->set(scale1);
    angleV1->set(angle);

    position = {cos(a*5) * 1.0f, sin(a) * 1.0f, 0.0f};
    orientation = {1.0f, sin(a) * 1.0f, 0.0f};
    angle = TO_RADS * 360.0f * (a/5);

    pV2->set(position);
    oV2->set(orientation);
    angleV2->set(angle);
    scaleV2->set(scale2);


    glClearColor(cos(a/100.0), 0.2f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    preDraw.run();
    draw->apply(avatar1);
    draw->apply(avatar2);
    posDraw.run();
  }

  return 0;
}

} //namespace Ludo
