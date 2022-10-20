#include "testing.h"


#include <cstdio>
#include "ZBE/core/tools/math/collisions/intersections.h"


namespace testing {

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

int testingmain(int, char** ) {
  caso1Esfera();
  caso1Cilindro();
  
  return 0;
}

} //namespace Ludo
