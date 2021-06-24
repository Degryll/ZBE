#include "tempmain.h"
#include <cstdint>
#include <variant>
#include <vector>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

struct CollisionData {
  int64_t time;
  zbe::Vector3D point;
};

struct Sphere {
  zbe::Vector3D center;
  double radius;
};

struct Box {
  zbe::Vector3D a;
  zbe::Vector3D b;
};

struct Ray {
  zbe::Vector3D point;
  zbe::Vector3D direction;
};

typedef int ReactObject;

template <typename IData>
struct InteractionEvent {
  IData data;
  ReactObject roa;
  ReactObject rob;
};

using CollisionEvent = InteractionEvent<CollisionData>;

template <typename ...Ts>
class Interactioner {
public:
  virtual std::variant<Ts...> getShape() = 0;
  virtual ReactObject getReactObject() = 0;
};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<typename IData, typename Overloaded, typename ...Ts>
class InteractionSelector {
public:
  bool select(std::variant<Ts...> i1, std::variant<Ts...> i2, int64_t timeLimit, IData &data) {
    return std::visit(getOverloaded(), i1, i2, timeLimit, data);
    TODO Esto ^ dice valueless_by_exception. 
  }

  virtual Overloaded getOverloaded() = 0;
};

template <typename IData, typename Overloaded, typename ...Ts>
class Interactionator : public Interactioner<Ts...> {
public:
  std::vector<InteractionEvent<IData>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData>> out;
    long best = timeLimit;
    for(auto iner : *iners) {
      std::variant<Ts...> v = iner->getShape();
      IData data;
      if (selector->select(this->getShape(), iner->getShape(), best, data)) {
        InteractionEvent<IData> ie {data, this->getReactObject(), iner->getReactObject()};
        if(data.time == best) {
          out.push_back(ie);
        } else if(data.time < best) {
          out.clear();
          out.push_back(ie);
        }
      }
    }  // for iners
    return out;
  }

  void setSelector(std::unique_ptr<InteractionSelector<IData, Overloaded, Ts...>> selector) {
    this->selector = std::move(selector);
  }

  void setIners(std::shared_ptr<zbe::TicketedForwardList<Interactioner<Ts...>>> iners) {
    this->iners = iners;
  }

private:
  //  TODO Esto es un tipo abstracto, tiene que ser un unique_ptr
  std::unique_ptr<InteractionSelector<IData, Overloaded, Ts...>> selector;
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<Ts...>>> iners;
};

class SphereSphere {
public:
  bool operator()(Sphere arg1, Sphere arg2, int64_t timelimit, CollisionData &data) {
    data.time = 3.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereBox {
public:
  bool operator()(Sphere arg1, Box arg2, int64_t timelimit, CollisionData &data) {
    data.time = 4.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereRay {
public:
  bool operator()(Sphere arg1, Ray arg2, int64_t timelimit, CollisionData &data) {
    data.time = 5.0;
    data.point = arg1.center;
    return true;
  }
};

using BasePhysicsOverloaded = overloaded<SphereSphere, SphereBox, SphereRay>;

class BasePhysicsSelector : public InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
protected:
  virtual BasePhysicsOverloaded getOverloaded() {
    return BasePhysicsOverloaded {SphereSphere{}, SphereBox{}, SphereRay{}};
  }  // getOverloaded
};

class SampleInteractionator : public Interactionator<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
public:
  std::variant<Sphere, Box, Ray> getShape() {
    return Sphere{{3.0, 7.0, 4.0}, 4.2};
  }

  ReactObject getReactObject() {return 1;}
};

class InteractionerBox : public Interactioner<Sphere, Box, Ray> {
  std::variant<Sphere, Box, Ray> getShape() {
    return Box{{1.0, 2.0}, {3.0, 4.0}};
  }
  ReactObject getReactObject() {return 2;}
};

class InteractionerRay : public Interactioner<Sphere, Box, Ray> {
  std::variant<Sphere, Box, Ray> getShape() {
    return Ray{{1.1, 2.2}, {3.3, 4.4}};
  }
  ReactObject getReactObject() {return 3;}
};

int tempmain (int, char **) {
  // Crear lista
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<Sphere, Box, Ray>>> iners = std::make_shared<zbe::TicketedForwardList<Interactioner<Sphere, Box, Ray>>>();
  // Crear los Interactioner
  auto inerRay1 = std::make_shared<InteractionerRay>();
  auto inerBox1 = std::make_shared<InteractionerBox>();
  auto inerBox2 = std::make_shared<InteractionerBox>();
  // Añadirlos a la lista
  iners->push_front(inerRay1);
  iners->push_front(inerBox1);
  iners->push_front(inerBox2);
  // Crear el selector
  std::unique_ptr<InteractionSelector<CollisionData, overloaded<SphereSphere, SphereBox, SphereRay>, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();
  // Crear el interactionator
  SampleInteractionator inator;
  // Añadir la lista al Interactionator
  inator.setIners(iners);
  // Áñadir el selector al interactionator
  inator.setSelector(std::move(selector));
  // Pedirle los eventos al interactionator
  auto iEs = inator.getCollision(256);
  // Comerse un cachopo

  for(auto& ie: iEs) {
    printf("time: %d, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);
  }

  return 0;
}
