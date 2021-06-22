#include "tempmain.h"
#include <cstdint>
#include "ZBE/core/tools/math/Vector.h"
#include <variant>

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

template <typename IData, typename ...Ts>
class Interactionator : public Interactioner<IData, Ts...> {
public:
  std::vector<InteractionEvent<IData>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData>> out;
    long best = timeLimit;
    for(auto iner : iners) {
      std::variant<Ts...> v = iner->getShape();
      IData data = selector.select(this->getShape(), iner.getShape, best);
      InteractionEvent<IData> ie {data, this->getReactorObject(), iner->getReactObject()}
      if(data.time == best) {
        out.push_back(ie);
      } else if(data.time < best) {
        out.clear();
        out.push_back(ie);
      }
    }
  }

  void setSelector(InteractionSelector<IData, Ts...> selector) {
    this->selector = selector;
  }

  void setIners(TicketedForwardList<std::shared_ptr<Interactioner<Ts...>>> iners) {
    this->iners = iners;
  }

private:
  InteractionSelector<IData, Ts...> selector;
  TicketedForwardList<std::shared_ptr<Interactioner<Ts...>>> iners;
};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<typename IData, typename ...Ts>
class InteractionSelector {
public:
  bool select(std::variant<Ts...> i1, std::variant<Ts...> i2, int64_t timeLimit, IData &data) {
    return std::visit(getOverloaded(), i1, i2, timeLimit, data);
  }

  virtual overloaded<Ts...> getOverloaded() = 0;
};


class BasePhysicsSelector : public InteractionSelector<CollisionData, Sphere, Box, Ray> {
protected:
  overloaded<...Ts> getOverloaded() {
    return overloaded {
         [](Sphere arg1, Sphere arg2, int64_t timelimit, CollisionData &data) {data.time = 3.0; data.point = arg1.center; return true;},
         [](Sphere arg1, Box arg2, int64_t timelimit, CollisionData &data) {data.time = 4.0; data.point = arg1.center; return true;},
         [](Sphere arg1, Ray arg2, int64_t timelimit, CollisionData &data) {data.time = 5.0; data.point = arg1.center; return true;}
    };
  }  // getOverloaded
};


class SampleInteractionator : public Interactionator<CollisionData, Sphere, Box, Ray> {
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
  TicketedForwardList<std::shared_ptr<Interactioner<Sphere, Box, Ray>>> iners;
  // Crear los Interactioner
  auto inerRay1 = std::make_shared<InteractionerRay>();
  auto inerBox1 = std::make_shared<InteractionerBox>();
  auto inerBox2 = std::make_shared<InteractionerBox>();
  // Añadirlos a la lista
  iners.push_back(inerRay1);
  iners.push_back(inerBox1);
  iners.push_back(inerBox2);
  // Crear el selector
  BasePhysicsSelector selector;
  // Crear el interactionator
  SampleInteractionator inator;
  // Añadir la lista al Interactionator
  inator.setIners(iners);
  // Áñadir el selector al interactionator
  inator.setSelector(selector);
  // Pedirle los eventos al interactionator
  auto iEs = inator.getCollision(256);
  // Comerse un cachopo

  for( ie: iEs) {
    printf("time: %d, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);
  }

  return 0;
}
