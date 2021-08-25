#include "tempmain.h"
#include <cstdint>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <tuple>
#include <utility>
#include <initializer_list>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

struct CollisionData {
  int64_t time{0};
  zbe::Vector3D point{0.0, 0.0, 0.0};
};

struct Sphere {
  zbe::Vector3D center{};
  double radius{};

  friend std::ostream & operator << (std::ostream &out, const Sphere &s)
  {
    out << "Sphere (" << s.center[0] << ", "  << s.center[1] << ", " << s.center[2] << ")" <<  " - " << s.radius;
    return out;
  }
};

struct Box {
  zbe::Vector3D a{};
  zbe::Vector3D b{};

  friend std::ostream & operator << (std::ostream &out, const Box &s)
  {
    out << "Box (" << s.a[0] << ", "  << s.a[1] << ", " << s.a[2] << ") - (" << s.b[0] << ", "  << s.b[1] << ", " << s.b[2] << ")";
    return out;
  }
};

struct Ray {
  zbe::Vector3D point{};
  zbe::Vector3D direction{};

  friend std::ostream & operator << (std::ostream &out, const Ray &s)
  {
    out << "Ray (" << s.point[0] << ", "  << s.point[1] << ", " << s.point[2] << ") - (" << s.direction[0] << ", "  << s.direction[1] << ", " << s.direction[2] << ")";
    return out;
  }
};

template<typename ...Traits>
class Actor;

template<typename Trait>
class Actor<Trait>;

template<typename ...Traits>
class Reactor : public Reactor<Traits>... {
public:
  Reactor(const Reactor& rhs) : Reactor<Traits>(rhs)... {};
  Reactor() : Reactor<Traits>()... {};

  template <typename U>
  void setReaction(std::function<void(U)> reaction) {
    this->Reactor<U>::setReaction(reaction);
  }

  void callActor(Actor<Traits...>*  actor) {
    std::initializer_list<int>{(actor->act((Reactor<Traits>*)this), 0)... };
  }
};

template<typename Trait>
class Reactor<Trait> {
public:
    Reactor(const Reactor& rhs) : reaction(rhs.reaction) {}
    Reactor() : reaction(noReaction) {}

    void setReaction(std::function<void(Trait)> reaction) {
      this->reaction = reaction;
    }
    void react(Trait trait) {
      reaction(trait);
    }
private:
  static void noReaction(Trait) {}
  std::function<void(Trait)> reaction;
};

template<typename ...Traits>
class Actor : public Actor<Traits>... {
public:
  Actor() : Actor<Traits>()... {};
  Actor(std::pair<Traits, std::function<void(void*, Reactor<Traits>*)>>... valFun) : Actor<Traits>(valFun)... {}

  template <typename U>
  const U get() {
    return (this->Actor<U>::get());
  }

  template <typename U>
  void act(Reactor<U>* reactor) {
    this->Actor<U>::act(reactor);
  }

  template <typename U>
  void setTrait(U trait, std::function<void(void*, Reactor<U>*)> sa) {
    this->Actor<U>::setTrait(trait, sa);
  }
};

template<typename Trait>
class Actor<Trait> {
public:
  using subAct = std::function<void(void*, Reactor<Trait>*)>;

  Actor() : sa(noAct), val() {}
  Actor(std::pair<Trait, std::function<void(void*, Reactor<Trait>*)>> valFun) : sa(std::get<1>(valFun)), val(std::get<0>(valFun)) {}

  const Trait get() {
      return val;
  }

  void setTrait(Trait trait, std::function<void(void*, Reactor<Trait>*)> sa) {
    this->val = trait;
    this->sa = sa;
  }

  subAct getAct() {
    return sa;
  }

  void act(Reactor<Trait>* reactor) {
    sa(this, reactor);
  }

protected:
  Actor(Trait val, subAct sa) : sa(sa), val(val) {
  }

  void setAct(subAct sa, void* self) {
    this->sa = sa;
    this->self = self;
  }

private:
  static void noAct(void*, Reactor<Trait>*) {}
  subAct sa;
  Trait val;
};

template<typename Trait>
struct ReactionPrint {
  void operator()(Trait trait){
      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
  }
};

template<typename Trait>
struct EnabledTrait {
  void operator()(void* self, Reactor<Trait>* reactor){
    Actor<Trait>* typedSelf = (Actor<Trait>*)self;
    auto trait = typedSelf->get();
    reactor->react(trait);
  }
};

// ------------------------ WIP 5 END ---------------------------- //

template <typename IData, typename ...Traits>
struct InteractionEvent {
  IData data;
  Actor<Traits...> actor;
  Reactor<Traits...> reactor;
  void manage() {
    reactor.callActor(&actor);
  }
};

template <typename ...Ts>
class Interactioner {
public:
  virtual ~Interactioner() = default;
  virtual std::variant<Ts...> getShape() = 0;
  virtual Actor<Ts...> getActor() = 0;
  virtual Reactor<Ts...> getReactor() = 0;
};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<typename IData, typename Overloaded, typename ...Ts>
class InteractionSelector {
public:
  virtual ~InteractionSelector() = default;
  bool select(std::variant<Ts...> i1, std::variant<Ts...> i2, std::variant<int64_t> timeLimit, std::variant<IData>& data) {
    return std::visit(getOverloaded(), i1, i2, timeLimit, data);
  }

  virtual Overloaded getOverloaded() = 0;
};

template <typename IData, typename Overloaded, typename ...Ts>
class Interactionator : public Interactioner<Ts...> {
public:
  std::vector<InteractionEvent<IData, Ts...>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData, Ts...>> out;
    std::variant<int64_t> vbest = timeLimit;
    for(auto iner : *iners) {
      std::variant<Ts...> v = iner->getShape();
      std::variant<IData> vdata;
      if (selector->select(this->getShape(), iner->getShape(), vbest, vdata)) {
        IData data = std::get<IData>(vdata);
        int64_t best = std::get<int64_t>(vbest);
        InteractionEvent<IData, Ts...> iea {data, this->getActor(), iner->getReactor()};
        InteractionEvent<IData, Ts...> ieb {data, iner->getActor(), this->getReactor()};
printf("best: %ld, data.time: %ld\n", best, data.time);
        if(data.time == best) {
          out.push_back(iea);
          out.push_back(ieb);
        } else if(data.time < best) {
          vbest = data.time;
          out.clear();
          out.push_back(iea);
          out.push_back(ieb);
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
  std::unique_ptr<InteractionSelector<IData, Overloaded, Ts...>> selector{};
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<Ts...>>> iners{};
};

class SphereSphere {
public:
  bool operator()(Sphere arg1, Sphere , int64_t , CollisionData &data) {
    printf("SphereSphere\n");fflush(stdout);
    data.time = 3.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereBox {
public:
  bool operator()(Sphere arg1, Box , int64_t , CollisionData &data) {
    printf("SphereBox\n");fflush(stdout);
    data.time = 4.0;
    data.point = arg1.center;
    return true;
  }
};

class SphereRay {
public:
  bool operator()(Sphere arg1, Ray , int64_t , CollisionData &data) {
    printf("SphereRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = arg1.center;
    return true;
  }
};

class BoxSphere {
public:
  bool operator()(Box , Sphere , int64_t , CollisionData &data) {
    printf("BoxSphere\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0, 2.0, 0.0};
    return true;
  }
};

class BoxBox {
public:
  bool operator()(Box , Box , int64_t , CollisionData &data) {
    printf("BoxBox\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class BoxRay {
public:
  bool operator()(Box , Ray , int64_t , CollisionData &data) {
    printf("BoxRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RaySphere {
public:
  bool operator()(Ray , Sphere , int64_t , CollisionData &data) {
    printf("RaySphere\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RayBox {
public:
  bool operator()(Ray , Box , int64_t , CollisionData &data) {
    printf("RayBox\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

class RayRay {
public:
  bool operator()(Ray , Ray , int64_t , CollisionData &data) {
    printf("RayRay\n");fflush(stdout);
    data.time = 5.0;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

using BasePhysicsOverloaded = overloaded<SphereSphere, SphereBox, SphereRay, BoxSphere, BoxBox, BoxRay, RaySphere, RayBox, RayRay>;

class BasePhysicsSelector : public InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
public:
  virtual ~BasePhysicsSelector() = default;
protected:
  virtual BasePhysicsOverloaded getOverloaded() {
    return BasePhysicsOverloaded {SphereSphere{}, SphereBox{}, SphereRay{}, BoxSphere{}, BoxBox{}, BoxRay{}, RaySphere{}, RayBox{}, RayRay{}};
  }  // getOverloaded
};

// TODO aquí hay dos clases iguales, por si no lo has notao.
class CustomInteractioner : public Interactioner<Sphere, Box, Ray> {
public:
  CustomInteractioner(std::variant<Sphere, Box, Ray> shape, Actor<Sphere, Box, Ray> actor, Reactor<Sphere, Box, Ray> reactor) :shape(shape), actor(actor), reactor(reactor) {}

  std::variant<Sphere, Box, Ray> getShape() {
    return shape;
  }

  Actor<Sphere, Box, Ray> getActor() {return actor;}

  Reactor<Sphere, Box, Ray> getReactor() {return reactor;}

private:
  std::variant<Sphere, Box, Ray> shape;
  Actor<Sphere, Box, Ray> actor;
  Reactor<Sphere, Box, Ray> reactor;
};


class CustomSampleInteractionator : public Interactionator<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>  {
public:

  CustomSampleInteractionator(std::variant<Sphere, Box, Ray> shape, Actor<Sphere, Box, Ray> actor, Reactor<Sphere, Box, Ray> reactor) :shape(shape), actor(actor), reactor(reactor) {}

  std::variant<Sphere, Box, Ray> getShape() {
    return shape;
  }

  Actor<Sphere, Box, Ray> getActor() {return actor;}

  Reactor<Sphere, Box, Ray> getReactor() {return reactor;}

private:
  std::variant<Sphere, Box, Ray> shape;
  Actor<Sphere, Box, Ray> actor;
  Reactor<Sphere, Box, Ray> reactor;
};

int tempcleanmain (int, char **) {

  // Crear lista
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<Sphere, Box, Ray>>> iners = std::make_shared<zbe::TicketedForwardList<Interactioner<Sphere, Box, Ray>>>();


  // Actors y Reactors

  Reactor<Sphere, Box, Ray> reactor;
  reactor.setReaction<Sphere>(ReactionPrint<Sphere>());
  reactor.setReaction<Box>(ReactionPrint<Box>());
  reactor.setReaction<Ray>(ReactionPrint<Ray>());

  Actor<Sphere, Box, Ray> actorRay1;
  actorRay1.setTrait<Ray>(Ray{{1.1, 2.2, 0.0}, {3.3, 4.4, 0.0}}, EnabledTrait<Ray>());

  Actor<Sphere, Box, Ray> actorBox1;
  actorBox1.setTrait<Box>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, EnabledTrait<Box>());

  Actor<Sphere, Box, Ray> actorBox2;
  actorBox2.setTrait<Box>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, EnabledTrait<Box>());

  Actor<Sphere, Box, Ray> actorSphere1;
  actorSphere1.setTrait<Sphere>(Sphere{{3.0, 7.0, 4.0}, 4.2}, EnabledTrait<Sphere>());

  // Crear los Interactioner
  // Reconstruir
  auto inerRay1 = std::make_shared<CustomInteractioner>(Ray{{1.1, 2.2, 0.0}, {3.3, 4.4, 0.0}}, actorRay1, reactor);
  auto inerBox1 = std::make_shared<CustomInteractioner>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, actorBox1, reactor);
  auto inerBox2 = std::make_shared<CustomInteractioner>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, actorBox2, reactor);
  // hasta aquí

  // Añadirlos a la lista
  iners->push_front(inerRay1);
  iners->push_front(inerBox1);
  iners->push_front(inerBox2);
  // Crear el selector
  std::unique_ptr<InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();

  // Crear el interactionator
  // Reconstruir
  CustomSampleInteractionator inator(Sphere{{3.0, 7.0, 4.0}, 4.2}, actorSphere1, reactor);
  // hasta aquí

  // Añadir la lista al Interactionator
  inator.setIners(iners);
  // Áñadir el selector al interactionator
  inator.setSelector(std::move(selector));
  // Pedirle los eventos al interactionator
  auto iEs = inator.getCollision(256);
  // Comerse un cachopo

  for(auto& ie: iEs) {
    // Aquí tenemos que meter lo de después
    printf("time: %lld, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);fflush(stdout);
    ie.manage();
  }

  // lo de después
  // Actor<int, double, long, float>* nicolasCage = new Actor<int, double, long, float>();
  // nicolasCage->setTrait<double>(0.75, EnabledTrait<double>());
  // nicolasCage->setTrait<int>(327, EnabledTrait<int>());
  //
  // Reactor<int, double, long, float> reactor;
  // reactor.setReaction<int>(ReactionPrint<int>());
  // reactor.setReaction<double>(ReactionPrint<double>());
  // reactor.setReaction<long>(ReactionPrint<long>());
  // reactor.setReaction<float>(ReactionPrint<float>());

  // reactor.callActor(nicolasCage);

  return 0;
}
