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


// -------------------------- WIP ------------------------------ //
- Al crear el Interactionator, ya sabes en que tipos estás interesado.
Es más en la lista de interactioners sabes que cada interactioner, al menos, cumple uno de los tipos que te interesan.
Como sabes que interactioners participan, tambien sabes que tipos de los que tu eres interesan a los interationers.

Si el interactionators está interesado en los tipos A, B, C, sabemos que cualquiera de los interactioners cumple uno de estos tipos y como maximo los 3. Se puede guardar esta información en un std::Array.


template<typename IDatat, typename T, typename ...Ts>
void react(ReactObject2<Ts...> r1, IData iData, (*)f(ReactObject2<T>, IData)) {
  if contexpr std::is_one_of<T, Ts...> {
    f(r1, id);
  }
}

template<typename IData, typename T>
class ReactObjectCallback {
  setCallback(f1);
  (*)f(ReactObject2<T>, IData) getCallback();
}

template<typename IData, typename ...Ts>
class ReactObject2 : ReactObjectCallback<IData, Ts...>{
  template<typename ...Us>
  void solve(ReactObject2<Us...> r1, IData iData) {

    std::initializer_list<int>{ (react<IData, Ts, Us>(r1, id, ), 0)... };

    std::initializer_list<int>{ (react<IData, Us>(r1, id, getCallback<IData, Ts...>()), 0)... };

    if contexpr std::is_one_of<Bounceable, Us...> {
      fb1(r1, id);
    }
    if contexpr std::is_one_of<Hitable, Us...> {
      fb2(r1, id);
    }
    if contexpr std::is_one_of<Movible, Us...> {
      fb2(r1, id);
    }
  }
}


Ball : Bounce -> Hitables
Brick: Hitable, Bombizer -> Bounce, Explotables

class Ball : public RO<>


class Ball : RO<Bounceable, Hitable, Movible> {
  Ball() {
    setCallback<Bounceable>(f1);
    setCallback<Hitable>(f2);
    setCallback<Movible>(f3);
  }
};

class Ball : Soy<Sphere>, DoyA<Bounceable, Hitable, Movible>, ReciboDe<Hitable> {

};

class Ball : Soy<Sphere>, DoyA<Bounceable, Hitable, Movible>, ReciboDe<Hitable> {

};

class Ball : RO<Sphere, Bounceable, Hitable, Movible> {
  Ball() {
    setCallback<Bounceable>(f1);
    setCallback<Hitable>(f2);
    setCallback<Movible>(f3);
  }
};

struct IE {
  InteractionData id;
  RO a;
  RO b;
};

struct IE {
  InteractionData id;
  RO<I<Hitable>,O<Bounceable, Katacrokerer1>> a;
  RO<I<Bounceable>, o<Hitable> > b;
};



template<typename ...Ts>
class Interest {}
template<typename ...Ts>
class Offers {}

template<typename F, typename O, typename I, typename ...Is>
class RO : public RO<F, O, Is...> {
  template<typename F2, typename I2, typename ...Us>
  std::enable_if<>
  void solve(ReactObject2<F2, Us..., I2> r1, IData iData) {
    if contexpr std::is_one_of<I, US> ..
};


template<...Ts>
class Things : public Ts... {

}

Things::Bases

template<...Ts>
using Interest = Things<Ts...>;

template<...Ts>
using Offers = Things<Ts...>;

template<typename F, typename O, typename I>
class RO {

}

class Brick : RO<Form<Box>, Interest<Bounceables, Explotables>, Hitable, Bombizer> {

};


// ------------------------ WIP END ---------------------------- //


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
  bool select(std::variant<Ts...> i1, std::variant<Ts...> i2, std::variant<int64_t> timeLimit, std::variant<IData>& data) {
    return std::visit(getOverloaded(), i1, i2, timeLimit, data);
  }

  virtual Overloaded getOverloaded() = 0;
};

template <typename IData, typename Overloaded, typename ...Ts>
class Interactionator : public Interactioner<Ts...> {
public:
  std::vector<InteractionEvent<IData>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData>> out;
    std::variant<int64_t> vbest = timeLimit;
    for(auto iner : *iners) {
      std::variant<Ts...> v = iner->getShape();
      std::variant<IData> vdata;
      if (selector->select(this->getShape(), iner->getShape(), vbest, vdata)) {
        IData data = std::get<IData>(vdata);
        int64_t best = std::get<int64_t>(vbest);
        InteractionEvent<IData> ie {data, this->getReactObject(), iner->getReactObject()};
printf("best: %lld, data.time: %lld\n", best, data.time);
        if(data.time == best) {
          out.push_back(ie);
        } else if(data.time < best) {
          vbest = data.time;
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
    printf("SphereSphere\n");fflush(stdout);
    data.time = 3.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereBox {
public:
  bool operator()(Sphere arg1, Box arg2, int64_t timelimit, CollisionData &data) {
    printf("SphereBox\n");fflush(stdout);
    data.time = 4.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereRay {
public:
  bool operator()(Sphere arg1, Ray arg2, int64_t timelimit, CollisionData &data) {
    printf("SphereRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = arg1.center;
    return true;
  }
};

class BoxSphere {
public:
  bool operator()(Box arg1, Sphere arg2, int64_t timelimit, CollisionData &data) {
    printf("BoxSphere\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0, 2.0, 0.0};
    return true;
  }
};

class BoxBox {
public:
  bool operator()(Box arg1, Box arg2, int64_t timelimit, CollisionData &data) {
    printf("BoxBox\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class BoxRay {
public:
  bool operator()(Box arg1, Ray arg2, int64_t timelimit, CollisionData &data) {
    printf("BoxRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RaySphere {
public:
  bool operator()(Ray arg1, Sphere arg2, int64_t timelimit, CollisionData &data) {
    printf("RaySphere\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RayBox {
public:
  bool operator()(Ray arg1, Box arg2, int64_t timelimit, CollisionData &data) {
    printf("RayBox\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RayRay {
public:
  bool operator()(Ray arg1, Ray arg2, int64_t timelimit, CollisionData &data) {
    printf("RayRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

using BasePhysicsOverloaded = overloaded<SphereSphere, SphereBox, SphereRay, BoxSphere, BoxBox, BoxRay, RaySphere, RayBox, RayRay>;

class BasePhysicsSelector : public InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
protected:
  virtual BasePhysicsOverloaded getOverloaded() {
    return BasePhysicsOverloaded {SphereSphere{}, SphereBox{}, SphereRay{}, BoxSphere{}, BoxBox{}, BoxRay{}, RaySphere{}, RayBox{}, RayRay{}};
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

// struct Gato {
//   int vidas = 7;
//   bool pelo = true;
//   bool hidraulico = false;
// };
//
// struct Perro {
//   int dientes = 42;
//   bool pelo = true;
//   bool entusiasmo = true;
// };
//
// struct Canario {
//   bool pico = true;
//   float vidas = 0.2;
//   bool plumas = true;
// };
//
// using Animal = std::variant<Gato, Perro, Canario>;
// // template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// // template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
//
// struct VisitPackage
// {
//     void operator()(Gato& g, int& r) { printf("gato\n"); r = g.vidas;}
//     void operator()(Perro& p, int& r) { printf("perro\n"); r = p.dientes;}
//     void operator()(Canario& c, int& r) { printf("canario\n"); r = static_cast<int>(c.vidas);}
// };


int tempmain (int, char **) {

  // std::vector<Animal> animales {Gato{}, Perro{}, Gato{}, Canario{}};
  // std::variant<int> resultado;
  //
  // for(auto& a: animales) {
  //   std::visit(VisitPackage(), a, resultado);
  //   printf("Resultao %d\n", std::get<int>(resultado));
  // }

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
  std::unique_ptr<InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();
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
