#include "tempmain.h"
//#include <cstdint>
//#include <variant>
//#include <vector>
//#include <type_traits>
//#include <optional>
//#include <tuple>
//#include <utility>
//#include <initializer_list>
//#include <unordered_map>
//#include <typeindex>
//#include <typeinfo>
//#include <iostream>
//#include <string>
//#include <functional>
//
//#include "ZBE/core/tools/math/Vector.h"
//#include "ZBE/core/tools/containers/TicketedForwardList.h"
//#include "ZBE/core/entities/avatars/Avatar.h"
//#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
//#include "ZBE/core/entities/Entity.h"
//#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
//#include "ZBE/core/events/interactionSystem.h"

namespace temp {

//class Vivo {
//public:
//  Vivo(int vidas) : vidas(vidas) {}
//
//  int getVidas() {
//    return this->vidas;
//  }
//
//  friend std::ostream & operator << (std::ostream &out, std::shared_ptr<Vivo> s) {
//    out << "Vivo (" << s->getVidas() << ")";
//    return out;
//  }
//private:
//  int vidas;
//};
//
//class Solido {
//public:
//  friend std::ostream & operator << (std::ostream &out, const Solido&)
//  {
//    out << "Solido";
//    return out;
//  }
//};
//
//class Mata {
//public:
//  friend std::ostream & operator << (std::ostream &out, const Mata&)
//  {
//    out << "Mata";
//    return out;
//  }
//};
//
//class Rompe {
//public:
//  friend std::ostream & operator << (std::ostream &out, const Rompe&)
//  {
//    out << "Rompe";
//    return out;
//  }
//};
//
//template<typename Trait>
//class SimpleTraitAvt : public zbe::SAvatar<Trait>, zbe::AvatarImp {
//public:
//    SimpleTraitAvt(std::shared_ptr<zbe::Entity> entity) {
//      setupEntity(entity);
//    }
//
//    void setupEntity(std::shared_ptr<zbe::Entity> entity) {
//      AvatarImp::setupEntity(entity);
//      zbe::_Avatar<1, Trait>::setup(&getTrait, &setTrait, (void*)this);
//    }
//
//    static std::shared_ptr<zbe::Value<Trait>> getTrait(void*) {
//      return std::make_shared<zbe::SimpleValue<Trait>>(Trait());
//    }
//
//    static void setTrait(void*, Trait) {}
//
//    std::shared_ptr<zbe::Entity> getEntity() {
//      assert(false);
//    }
//};
//
//struct CollisionData {
//  int64_t time{0};
//  zbe::Vector3D point{0.0, 0.0, 0.0};
//
//  friend std::ostream & operator << (std::ostream &out, const CollisionData &s)
//  {
//    out << "CollisionData (" << s.time << ", (" << s.point[0] << ", "<< s.point[1] << ", "<< s.point[2] << "))";
//    return out;
//  }
//};
//
//class Sphere {
//public:
//  virtual ~Sphere() = default;
//
//  virtual zbe::Vector3D getCenter() = 0;
//  virtual double getRadius() = 0;
//
//  friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Sphere> s)  {
//    auto center = s->getCenter();
//    auto radius = s->getRadius();
//    out << "Sphere (" << center[0] << ", "  << center[1] << ", " << center[2] << ")" <<  " - " << radius;
//    return out;
//  }
//};
//
//class AvtSphere : public Sphere {
//public:
//  AvtSphere(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> avt) : avt(avt) {}
//
//  double getRadius() {
//    return zbe::AvtUtil::get<1, double>(avt)->get();
//  }
//
//  zbe::Vector3D getCenter() {
//    return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
//  }
//
//private:
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> avt;
//  //zbe::Vector3D center{};
//  //double radius{};
//};
//
//class Box {
//public:
//  virtual ~Box() = default;
//  virtual zbe::Vector3D getA() = 0;
//  virtual zbe::Vector3D getB() = 0;
//
//  friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Box> &s) {
//    auto a = s->getA();
//    auto b = s->getB();
//    out << "Box (" << a[0] << ", "  << a[1] << ", " << a[2] << ") - (" << b[0] << ", "  << b[1] << ", " << b[2] << ")";
//    return out;
//  }
//};
//
//class AvtBox : public Box {
//public:
//  AvtBox(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt) : avt(avt) {}
//
//  zbe::Vector3D getA() {
//    return zbe::AvtUtil::get<1, zbe::Vector3D>(avt)->get();
//  }
//
//  zbe::Vector3D getB() {
//    return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
//  }
//private:
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt;
//};
//
//class Ray {
//public:
//  virtual ~Ray() = default;
//  virtual zbe::Vector3D getPoint() = 0;
//  virtual zbe::Vector3D getDirection() = 0;
//
//  friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Ray> &s)  {
//    auto point = s->getPoint();
//    auto direction = s->getDirection();
//    out << "Ray (" << point[0] << ", "  << point[1] << ", " << point[2] << ") - (" << direction[0] << ", "  << direction[1] << ", " << direction[2] << ")";
//    return out;
//  }
//};
//
//class AvtRay : public Ray {
//public:
//  AvtRay(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt) : avt(avt) {}
//  zbe::Vector3D getPoint() {
//    return zbe::AvtUtil::get<1, zbe::Vector3D>(avt)->get();
//  }
//  zbe::Vector3D getDirection() {
//    return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
//  }
//private:
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt;
//};
//
//template <typename S, typename ...Ss>
//class SimpleShape : public zbe::Shape<Ss...> {
//public:
//  SimpleShape(std::shared_ptr<S> s) : s(s) {};
//  std::variant<std::shared_ptr<Ss>...> getShape() {
//    return s;
//  };
//private:
//  std::shared_ptr<S> s;
//};
//
//class SphereSphere {
//public:
//  bool operator()(std::shared_ptr<Sphere> arg1, std::shared_ptr<Sphere> arg2, int64_t , CollisionData &data) {
//    printf("SphereSphere\n");fflush(stdout);
//    data.time = 3;
//    data.point = arg1->getCenter() + arg2->getCenter();
//    return true;
//  }
//};
//
//class SphereBox {
//public:
//  bool operator()(std::shared_ptr<Sphere>, std::shared_ptr<Box> arg2, int64_t , CollisionData &data) {
//    printf("SphereBox\n");fflush(stdout);
//    data.time = 4;
//    data.point = arg2->getA();
//    return true;
//  }
//};
//
//class SphereRay {
//public:
//  bool operator()(std::shared_ptr<Sphere> arg1, std::shared_ptr<Ray> , int64_t , CollisionData &data) {
//    printf("SphereRay\n");fflush(stdout);
//    data.time = 5;
//    data.point = arg1->getCenter();
//    return true;
//  }
//};
//
//class BoxSphere {
//public:
//  bool operator()(std::shared_ptr<Box> , std::shared_ptr<Sphere> , int64_t , CollisionData &data) {
//    printf("BoxSphere\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0, 2.0, 0.0};
//    return true;
//  }
//};
//
//class BoxBox {
//public:
//  bool operator()(std::shared_ptr<Box> , std::shared_ptr<Box> , int64_t , CollisionData &data) {
//    printf("BoxBox\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0,2.0,0.0};
//    return true;
//  }
//};
//
//class BoxRay {
//public:
//  bool operator()(std::shared_ptr<Box> , std::shared_ptr<Ray> , int64_t , CollisionData &data) {
//    printf("BoxRay\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0,2.0,0.0};
//    return true;
//  }
//};
//
//class RaySphere {
//public:
//  bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Sphere> , int64_t , CollisionData &data) {
//    printf("RaySphere\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0,2.0,0.0};
//    return true;
//  }
//};
//
//class RayBox {
//public:
//  bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Box> , int64_t , CollisionData &data) {
//    printf("RayBox\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0,2.0,0.0};
//    return true;
//  }
//};
//
//class RayRay {
//public:
//  bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Ray> , int64_t , CollisionData &data) {
//    printf("RayRay\n");fflush(stdout);
//    data.time = 5;
//    data.point = zbe::Vector3D{4.0,2.0,0.0};
//    return true;
//  }
//};
//
//
//// Habría que dejar documentado como se construye esto en alguna parte del core
//using BasePhysicsOverloaded = zbe::overloaded<SphereSphere, SphereBox, SphereRay, BoxSphere, BoxBox, BoxRay, RaySphere, RayBox, RayRay>;
//
//class BasePhysicsSelector : public zbe::InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
//public:
//  virtual ~BasePhysicsSelector() = default;
//protected:
//  virtual BasePhysicsOverloaded getOverloaded() {
//    return BasePhysicsOverloaded {SphereSphere{}, SphereBox{}, SphereRay{}, BoxSphere{}, BoxBox{}, BoxRay{}, RaySphere{}, RayBox{}, RayRay{}};
//  }  // getOverloaded
//};
//
//template<typename IData, typename Trait, typename Base, typename ...Bases>
//struct ReactionPrint {
//  ReactionPrint(std::shared_ptr<zbe::MAvatar<Base, Bases...>> avt) : avt(avt) {}
//  void operator() (IData data, Trait trait){
//      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
//      std::cout << "Interaction data: " << data << std::endl;
//      auto val = zbe::AvtUtil::get<2, Base >(avt);
//      //auto val = avt->get<1, uint64_t>()->get();
//      std::cout << "First avt data: " << val << std::endl;
//  }
//private:
//  std::shared_ptr<zbe::MAvatar<Base, Bases...>> avt;
//};
//
//template<typename IData, typename Trait, typename Base>
//struct ReactionPrint<IData, Trait, Base> {
//  ReactionPrint(std::shared_ptr<zbe::SAvatar<Base>> avt) : avt(avt) {}
//  void operator() (IData data, Trait trait){
//      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
//      std::cout << "Interaction data: " << data << std::endl;
//      auto val = zbe::AvtUtil::get<1, Base >(avt);
//      std::cout << "First avt data: " << val << std::endl;
//  }
//private:
//  std::shared_ptr<zbe::SAvatar<Base>> avt;
//};
//
//template<typename IData, typename Trait>
//class AvtEnabledTrait {
//public:
//  AvtEnabledTrait(std::shared_ptr<zbe::SAvatar<Trait>> avt) : avt(avt) {}
//  void operator()(zbe::Reactor<IData, Trait>* reactor, IData data) {
//    auto trait = avt->get()->get();
//    reactor->react(data, trait);
//  }
//private:
//  std::shared_ptr<zbe::SAvatar<Trait>> avt;
//};
//
//class MockedContextTime : public zbe::ContextTime {
//public:
//
//  MockedContextTime(uint64_t fixedTime = 0) : fixedTime(fixedTime) {}
//
//  std::shared_ptr<ContextTime> clone() {
//    return std::make_shared<MockedContextTime>(fixedTime);
//  };
//
//  void setFixedTime(uint64_t fixedTime) { this->fixedTime = fixedTime;}
//
//  uint64_t getFixedTime() { return fixedTime;}
//
//private:
//  uint64_t fixedTime;
//
//  uint64_t _getTotalTime() {
//    return fixedTime;
//  }
//
//  uint64_t _getInitTime() {
//    return endT;
//  }
//
//};

int tempmain (int, char **) {
//  std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();
//
//  // std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avtRay
//  // std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avtBox
//  // std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> avtSphere
//
//  // Reaction values & indexes
//  std::shared_ptr<zbe::Value<uint64_t>> valuint = std::make_shared<zbe::SimpleValue<uint64_t>>(8);
//  std::shared_ptr<zbe::Value<double>> valdouble1 = std::make_shared<zbe::SimpleValue<double>>(12.6);
//  ent->setDouble(0, valdouble1);
//  ent->setUint(0, valuint);
//  std::array<uint64_t, 2> lreaction{ {0, 0} };
//
//
//  // Shape values & indexes
//
//  std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec13 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 1.0,  2.0,  3.0});
//  std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec46 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 4.0,  5.0,  6.0});
//  std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec79 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 7.0,  8.0,  9.0});
//  std::shared_ptr<zbe::Value<zbe::Vector3D>> valVecAC = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{10.0, 11.0, 12.0});
//  std::shared_ptr<zbe::Value<zbe::Vector3D>> valVecDF = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{13.0, 14.0, 15.0});
//  std::shared_ptr<zbe::Value<double>> valdouble2 = std::make_shared<zbe::SimpleValue<double>>(16);
//
//  ent->setDouble(1, valdouble2);
//  ent->setVector3D(0, valVec13);
//  ent->setVector3D(1, valVec46);
//  ent->setVector3D(2, valVec79);
//  ent->setVector3D(3, valVecAC);
//  ent->setVector3D(4, valVecDF);
//
//  std::array<uint64_t, 2> lSphere{ {0, 1} };
//  std::array<uint64_t, 2> lSphere2{ {4, 1} };
//  std::array<uint64_t, 2> lBox{ {1, 2} };
//  std::array<uint64_t, 2> lRay{ {3, 4} };
//
//  std::shared_ptr<zbe::MAvatar<uint64_t, double>> reactionAvt = std::make_shared<zbe::MBaseAvatar<uint64_t, double>>(ent, lreaction);
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> shapeSphereAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, double>>(ent, lSphere);
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> shapeSphereAvt2 = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, double>>(ent, lSphere2);
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> shapeBoxAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, zbe::Vector3D>>(ent, lBox);
//  std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> shapeRayAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, zbe::Vector3D>>(ent, lRay);
//
//  std::shared_ptr<Sphere> avtSphere1 = std::make_shared<AvtSphere>(shapeSphereAvt);
//  std::shared_ptr<Sphere> avtSphere2 = std::make_shared<AvtSphere>(shapeSphereAvt2);
//  std::shared_ptr<Box> avtBox = std::make_shared<AvtBox>(shapeBoxAvt);
//  std::shared_ptr<Ray> avtRay = std::make_shared<AvtRay>(shapeRayAvt);
//
//  auto sphereShape1 = std::make_shared<SimpleShape<Sphere, Sphere, Box, Ray>>(avtSphere1);
//  auto sphereShape2 = std::make_shared<SimpleShape<Sphere, Sphere, Box, Ray>>(avtSphere2);
//
//  auto boxShape = std::make_shared<SimpleShape<Box, Sphere, Box, Ray>>(avtBox);
//  auto rayShape = std::make_shared<SimpleShape<Ray, Sphere, Box, Ray>>(avtRay);
//
//  // TODO construir funciones que sustituyen a esto.
//  // using ActorBola = Actor<CollisionData, Rompe>;
//  // using ActorLadrillo = Actor<CollisionData, Solido>;
//  // using ActorBorde = Actor<CollisionData, Solido>;
//  // using ActorPozo = Actor<CollisionData, Mata>;
//
//  //using ReactorBola = Reactor<CollisionData, Solido, Mata>;
//  //using ReactorLadrillo = Reactor<CollisionData, Rompe>;
//  //using ReactorBorde = Reactor<CollisionData>; // Parece que no es necesario
//
//  //using CustomShape = zbe::Shape<Sphere, Box, Ray>;
//  using CustomActor = zbe::Actor<CollisionData, Vivo, Solido, Mata, Rompe>;
//  using CustomReactor = zbe::Reactor<CollisionData, Vivo, Solido, Mata, Rompe>;
//
//  using CustomInteractioner = zbe::Interactioner<CustomActor, CustomReactor, Sphere, Box, Ray>;
//  using CustomInteractionator = zbe::Interactionator<CustomActor, CustomReactor, Sphere, Box, Ray>;
//
//  // Crear lista
//  std::shared_ptr<zbe::TicketedForwardList<CustomInteractioner>> iners = std::make_shared<zbe::TicketedForwardList<CustomInteractioner>>();
//  std::shared_ptr<zbe::TicketedForwardList<CustomInteractionator>> ators = std::make_shared<zbe::TicketedForwardList<CustomInteractionator>>();
//
//  //
//  CustomActor caBola;
//  caBola.setTrait<Rompe>(AvtEnabledTrait<CollisionData, Rompe>(std::make_shared<SimpleTraitAvt<Rompe>>(ent)));
//  CustomActor caLadrillo;
//  caLadrillo.setTrait<Solido>(AvtEnabledTrait<CollisionData, Solido>(std::make_shared<SimpleTraitAvt<Solido>>(ent)));
//  CustomActor caBorde;
//  caBorde.setTrait<Solido>(AvtEnabledTrait<CollisionData, Solido>(std::make_shared<SimpleTraitAvt<Solido>>(ent)));
//  CustomActor caPozo;
//  caPozo.setTrait<Mata>(AvtEnabledTrait<CollisionData, Mata>(std::make_shared<SimpleTraitAvt<Mata>>(ent)));
//
//  CustomReactor crBola;
//  crBola.setReaction<Solido>(ReactionPrint<CollisionData, Solido, uint64_t, double>(reactionAvt));
//  crBola.setReaction<Mata>(ReactionPrint<CollisionData, Mata, uint64_t, double>(reactionAvt));
//
//  CustomReactor crLadrillo;
//  crLadrillo.setReaction<Rompe>(ReactionPrint<CollisionData, Rompe, uint64_t, double>(reactionAvt));
//
//  CustomReactor crBorde;
//  CustomReactor crPozo;
//
//  auto inerLadrilloRedondo = std::make_shared<CustomInteractioner>(sphereShape2, caLadrillo, crLadrillo);
//  auto inerLadrilloCuadrao = std::make_shared<CustomInteractioner>(boxShape, caLadrillo, crLadrillo);
//  auto inerBordeCasiCuadrao = std::make_shared<CustomInteractioner>(boxShape, caBorde, crBorde);
//  auto inerPozoNoRedondo = std::make_shared<CustomInteractioner>(boxShape, caPozo, crPozo);
//
//  // auto inerBox3 = std::make_shared<CustomInteractioner>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}});
//  // inerBox3.setActor(actor3);
//  // inerBox3.setReactor(reactor);
//
//
//  // hasta aquí
//
//  // Añadirlos a la lista
//  iners->push_front(inerLadrilloRedondo);
//  iners->push_front(inerLadrilloCuadrao);
//  iners->push_front(inerBordeCasiCuadrao);
//  iners->push_front(inerPozoNoRedondo);
//  // Crear el selector
//  std::unique_ptr<zbe::InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();
//
//  // Crear el interactionator
//  // Reconstruir
//  //std::shared_ptr<Sphere> avtSphere = std::make_shared<AvtSphere>(shapeSphereAvt);
//  //std::variant<std::shared_ptr<Sphere>, std::shared_ptr<Box>, std::shared_ptr<Ray>> varAvtSphere = avtSphere;
//  auto inatorBolaEsferica = std::make_shared<CustomInteractionator>(sphereShape1, caBola, crBola);
//
//  // Añadir la lista al Interactionator
//  inatorBolaEsferica->setIners(iners);
//  // Pedirle los eventos al interactionator
//  ators->push_front(inatorBolaEsferica);
//  // auto iEs = inatorBolaEsferica.getCollision(256);
//  // // Comerse un cachopo
//  //
//  // for(auto& ie: iEs) {
//  //   // Aquí tenemos que meter lo de después
//  //   printf("time: %ld, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);fflush(stdout);
//  //   ie.manage();
//  // }
//  auto timeMock = std::make_shared<MockedContextTime>(256);
//
//  zbe::InteractionEventGenerator<BasePhysicsOverloaded, CollisionData, CustomActor, CustomReactor, Sphere, Box, Ray> generator(7);
//  generator.setAtorList(ators);
//  generator.setContextTime(timeMock);
//  generator.setSelector(std::move(selector));
//  generator.run();
//  zbe::EventStore::getInstance().manageCurrent();
  return 0;
}

}  // namespace zbe
