#include "testing.h"


#include <cstdio>
#include <memory>

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/implementations/CustomAvatars.h"

namespace testing {
const uint64_t velocityIdx = 1;
const uint64_t orientationIdx = 2;
const uint64_t positionIdx = 3;
const uint64_t radsIdx = 4;
const uint64_t sizeIdx = 5;
const uint64_t e1Idx = 6;
const uint64_t e2Idx = 7;

const uint64_t aIdx = 8;
const uint64_t bIdx = 9;
const uint64_t cIdx = 10;

class Triangle3Dto2DCacheBldr : public zbe::Funct<void, std::shared_ptr<zbe::Entity>> {
public:
  void operator()(std::shared_ptr<zbe::Entity> entity) {
    float baseScale = static_cast<float>(entity->getDouble(sizeIdx)->get());
    // Calculate plane
    glm::mat4 mat(1.0);
    glm::vec3 glPos(0.0, 0.0, 0.0);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);
    glm::mat4 m     = glm::scale(glm::mat4(1.0f), glm::vec3(baseScale)) * translate;
    glm::vec3 a = m * glm::vec4(baseT.a.x, baseT.a.y, baseT.a.z, 1.0);
    glm::vec3 b = m * glm::vec4(baseT.b.x, baseT.b.y, baseT.b.z, 1.0);
    glm::vec3 c = m * glm::vec4(baseT.c.x, baseT.c.y, baseT.c.z, 1.0);

    // zbe::Vector3D av3{a.x, a.y, a.z};
    // zbe::Vector3D bv3{b.x, b.y, b.z};
    // zbe::Vector3D cv3{c.x, c.y, c.z};

    zbe::Point3D pa{a.x, a.y, a.z};
    zbe::Point3D pb{b.x, b.y, b.z};
    zbe::Point3D pc{c.x, c.y, c.z};

    zbe::Point3D origin = pa;
    zbe::Vector3D e1 = (pb - origin).normalize();
    zbe::Vector3D aux = (pc - origin);
    zbe::Vector3D norm = cross(aux, e1);
    zbe::Vector3D e2 = cross(e1, norm).normalize();


    // Calculate 2D coords on previous plane

    // zbe::Vector3D ax{1.0, 0.0, 0.0};
    // zbe::Vector3D ay{0.0, 1.0, 0.0};
    // zbe::Vector3D az{0.0, 0.0, 1.0};

    // zbe::Vector3D bx = e1;
    // zbe::Vector3D by = e2;
    // zbe::Vector3D bz = zbe::cross(e1, e2).normalize();

    // ------------- per point ----------- //
    auto aaux = transformPointCoords(e1, e2,/* bz,*/ pa, origin);
    auto baux = transformPointCoords(e1, e2,/* bz,*/ pb, origin);
    auto caux = transformPointCoords(e1, e2,/* bz,*/ pc, origin);
    entity->setVector2D(aIdx, aaux);
    entity->setVector2D(bIdx, baux);
    entity->setVector2D(cIdx, caux);

    auto vaaux = aaux->get();
    auto vbaux = baux->get();
    auto vcaux = caux->get();
    printf("A 3D %lf, %lf, %lf 2D %lf, %lf \n", pa.x, pa.y, pa.z, vaaux.x, vaaux.y);
    printf("B 3D %lf, %lf, %lf 2D %lf, %lf \n", pb.x, pb.y, pb.z, vbaux.x, vbaux.y);
    printf("C 3D %lf, %lf, %lf 2D %lf, %lf \n", pc.x, pc.y, pc.z, vcaux.x, vcaux.y);
  }

  std::shared_ptr<zbe::Value<zbe::Vector2D>> transformPointCoords(zbe::Vector3D bx, zbe::Vector3D by/*, zbe::Vector3D bz*/, zbe::Point3D p, zbe::Point3D origin) {
    zbe::Vector3D pv = zbe::Vector3D{p.x, p.y, p.z};
    zbe::Vector3D ov = zbe::Vector3D{origin.x, origin.y, origin.z};
    double x = (pv - ov) * bx;
    double y = (pv - ov) * by;
    //double z = (pv - ov) * bz;
    zbe::Vector2D newPos2D{x + origin.x, y  - origin.z};
    printf("Origin %lf, %lf, %lf\n", origin.x, origin.y, origin.z);
    return std::make_shared<zbe::SimpleValue<zbe::Vector2D>>(newPos2D);
  }

  void setIdxs(uint64_t aIdx, uint64_t bIdx, uint64_t cIdx, uint64_t sizeIdx) {
    this->aIdx = aIdx;
    this->bIdx = bIdx;
    this->cIdx = cIdx;
    this->sizeIdx = sizeIdx;
  }

  void setBaseTriangle(zbe::Triangle3D baseT) {
    this->baseT = baseT;
  }

private:
  uint64_t aIdx;
  uint64_t bIdx;
  uint64_t cIdx;
  uint64_t sizeIdx;
  zbe::Triangle3D baseT;
};

void caso1Esfera() {
  using namespace zbe;
  std::cout << "caso1Esfera:" << std::endl;
  NSphere<3> sphere{{-10.0,0.0,0.0},1.0};
  Vector<3> sVelocity{1.0,0.0,0.0};
  Triangle<3> triangle{{0.0,0.0,0.0},{10.0,0.0,10.0},{10.0,0.0,-10.0}};
  Vector<3> tVelocity{0.0,0.0,0.0};
  int64_t time = 6553600;
  Point<3> point{42.0,42.0,42.0};
  Vector<3> normal{37.0,37.0,37.0};
  intersectionMovingNSphereOutsideMovingNTriangle<3>(sphere, sVelocity, triangle, tVelocity, time, point, normal);
  std::cout << "Punto:" << point.x << ","  << point.y << ","  << point.z << std::endl;
  std::cout << "Normal:" << normal.x << ","  << normal.y << ","  << normal.z << std::endl;
  std::cout << "Tiempo:" << time << std::endl;
  //TODO: Está devolviendo un valor incorrecto para point.x en colisión con esfera
}

void caso1Cilindro() {
  using namespace zbe;
  std::cout << "caso1Cilindro:" << std::endl;
  NSphere<3> sphere{{-10.0,0.0,0.0},1.0};
  Vector<3> sVelocity{1.0,0.0,0.0};
  Triangle<3> triangle{{10.0,0.0,0.0},{0.0,0.0,10.0},{0.0,0.0,-10.0}};
  Vector<3> tVelocity{0.0,0.0,0.0};
  int64_t time = 6553600;
  Point<3> point{42.0,42.0,42.0};
  Vector<3> normal{37.0,37.0,37.0};
  intersectionMovingNSphereOutsideMovingNTriangle<3>(sphere, sVelocity, triangle, tVelocity, time, point, normal);
  std::cout << "Punto:" << point.x << ","  << point.y << ","  << point.z << std::endl;
  std::cout << "Normal:" << normal.x << ","  << normal.y << ","  << normal.z << std::endl;
  std::cout << "Tiempo:" << time << std::endl;
  // TODO aqui estamos depurando
  // Lo mismo toca cambiar todo a printf, que el tbar nos sale feo.
}

void ray2DRay2DCasoHorizontalDiagonal() {
  using namespace zbe;
  std::cout << "ray2DRay2DCasoHorizontalDiagonal" << std::endl;
  Ray2D r1(Point2D{49.0, 49.0}, Vector2D{100.0, 0.0});
  Ray2D r2(Point2D{100.0, 0.0}, Vector2D{-200.0, 200.0});
  int64_t time = 2048;
  Point2D point;
  Vector2D normal;
  intersectionMovingRay2DRay2D(r1, r2, time, point, normal);
  std::cout << "Point:" << point.x << "," << point.y << std::endl;
  std::cout << "-----------------------" << std::endl;
}

void ray2DRay2DCasoVerticalDiagonal() {
  using namespace zbe;
  std::cout << "ray2DRay2DCasoVerticalDiagonal" << std::endl;
  Ray2D r1(Point2D{49.0, 49.0}, Vector2D{0.0, 100.0});
  Ray2D r2(Point2D{100.0, 0.0}, Vector2D{-200.0, 200.0});
  int64_t time = 2048;
  Point2D point;
  Vector2D normal;
  intersectionMovingRay2DRay2D(r1, r2, time, point, normal);
  std::cout << "Point:" << point.x << "," << point.y << std::endl;
  std::cout << "-----------------------" << std::endl;
}

void ray2DRay2DCasoDiagonalDiagonal() {
  using namespace zbe;
  std::cout << "ray2DRay2DCasoDiagonalDiagonal" << std::endl;
  Ray2D r1(Point2D{49.0, 49.0}, Vector2D{100.0, 100.0});
  Ray2D r2(Point2D{100.0, 0.0}, Vector2D{-200.0, 200.0});
  int64_t time = 2048;
  Point2D point;
  Vector2D normal;
  intersectionMovingRay2DRay2D(r1, r2, time, point, normal);
  std::cout << "Point:" << point.x << "," << point.y << std::endl;
  std::cout << "-----------------------" << std::endl;
}

void ray2DRay2DCasoHorizontalVertical() {
  using namespace zbe;
  std::cout << "ray2DRay2DCasoHorizontalVertical" << std::endl;
  Ray2D r1(Point2D{49.0, 50.0}, Vector2D{100.0, 0.0});
  Ray2D r2(Point2D{100.0, 0.0}, Vector2D{0.0, 100.0});
  int64_t time = 2048;
  Point2D point;
  Vector2D normal;
  intersectionMovingRay2DRay2D(r1, r2, time, point, normal);
  std::cout << "Point:" << point.x << "," << point.y << std::endl;
  std::cout << "-----------------------" << std::endl;
}

void ray2DRay2DCasoVerticalHorizontal() {
  using namespace zbe;
  std::cout << "ray2DRay2DCasoVerticalHorizontal" << std::endl;
  Ray2D r1(Point2D{50.0, 49.0}, Vector2D{0.0, 100.0});
  Ray2D r2(Point2D{0.0, 100.0}, Vector2D{100.0, 0.0});
  int64_t time = 2048;
  Point2D point;
  Vector2D normal;
  intersectionMovingRay2DRay2D(r1, r2, time, point, normal);
  std::cout << "Point:" << point.x << "," << point.y << std::endl;
  std::cout << "-----------------------" << std::endl;
}

void configureEntity(std::shared_ptr<zbe::Entity> ent, zbe::Triangle3D& baseT) {
    using namespace zbe;
    ent->setVector3D(orientationIdx, std::make_shared<SimpleValue<Vector3D> >(Vector3D{1.0, 0.0, 0.0}));
    ent->setVector3D(velocityIdx, std::make_shared<SimpleValue<Vector3D> >(Vector3D{0.0, 0.0, 0.0}));
    ent->setVector3D(positionIdx, std::make_shared<SimpleValue<Vector3D> >(Vector3D{0.0, 0.0, 0.0}));
    ent->setDouble(radsIdx, std::make_shared<SimpleValue<double> >(0.0));
    ent->setDouble(sizeIdx, std::make_shared<SimpleValue<double> >(100.0));
    ent->setContextTime(zbe::SysTime::getInstance());
    ent->setVector3D(e1Idx, std::make_shared<SimpleValue<Vector3D> >());
    ent->setVector3D(e2Idx, std::make_shared<SimpleValue<Vector3D> >());
    baseT.a = Point3D({-1.0, 0.0, 1.0});
    baseT.b = Point3D({1.0, 0.0, 1.0});
    baseT.c = Point3D({-1.0, 0.0, -1.0});


/*
A 3D -1.0, 0.0, 1.0
B 3D 1.0, 0.0, 1.0
C 3D -1.0, 0.0, -1.0
*/
}

void movingTriangle3DRscAvtTest(std::shared_ptr<zbe::Entity> ent, zbe::Triangle3D& baseT) {
  using namespace zbe;
  MovingTriangle3DRscAvt mt3dra;

  mt3dra.setupEntity(ent, velocityIdx, orientationIdx, positionIdx, radsIdx, sizeIdx, e1Idx, e2Idx);
  mt3dra.setBaseTriangle(baseT);
  std::shared_ptr<Value<MovingTriangle3D> > mTriangle = mt3dra.getTriangle(&mt3dra);
  auto outputTriangle = mTriangle->get().getShape();
  auto e1 = ent->getVector3D(e1Idx)->get();
  auto e2 = ent->getVector3D(e2Idx)->get();
  std::cout << "movingTriangle3DRscAvtTest e1: " << e1.x << "," << e1.y << "," << e1.z << std::endl;
  std::cout << "movingTriangle3DRscAvtTest e2: " << e2.x << "," << e2.y << "," << e2.z << std::endl;
}

void triangle3Dto2DCacheBldrTest(std::shared_ptr<zbe::Entity> ent, zbe::Triangle3D& baseT) {
  Triangle3Dto2DCacheBldr t3dt2dcb;
  t3dt2dcb.setIdxs(aIdx, bIdx, cIdx, sizeIdx);
  t3dt2dcb.setBaseTriangle(baseT);
  t3dt2dcb(ent);
  auto a = ent->getVector2D(aIdx)->get();
  auto b = ent->getVector2D(bIdx)->get();
  auto c = ent->getVector2D(cIdx)->get();
  std::cout << "triangle3Dto2DCacheBldrTest a: " << a.x << "," << a.y << std::endl;;
  std::cout << "triangle3Dto2DCacheBldrTest b: " << b.x << "," << b.y << std::endl;;
  std::cout << "triangle3Dto2DCacheBldrTest c: " << c.x << "," << c.y << std::endl;;
}

int testingmain(int, char** ) {
  using namespace zbe;
  caso1Esfera();
  caso1Cilindro();
  ray2DRay2DCasoHorizontalDiagonal();
  ray2DRay2DCasoVerticalDiagonal();
  ray2DRay2DCasoDiagonalDiagonal();
  ray2DRay2DCasoHorizontalVertical();
  ray2DRay2DCasoVerticalHorizontal();

  std::shared_ptr<Entity> entity = std::make_shared<Entity>();
  Triangle3D baseT;
  configureEntity(entity, baseT);
  movingTriangle3DRscAvtTest(entity, baseT);
  triangle3Dto2DCacheBldrTest(entity, baseT);
  return 0;
}

} //namespace Ludo
