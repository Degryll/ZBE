#include "tempcleanmain.h"
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

namespace temp {

struct Solid {
  double hardness = 0.0;
  double density = 0.0;

  friend std::ostream & operator << (std::ostream &out, const Solid &s)
  {
    out << "Solid (" << s.hardness << ", "  << s.density << ")";
    return out;
  }
};

struct Alive {
  int life = 1;
  friend std::ostream & operator << (std::ostream &out, const Alive &s)
  {
    out << "Alive (" << s.life << ")";
    return out;
  }
};

struct Furulatrix {
  int level = 10;
  double ratio = 1.0;

  friend std::ostream & operator << (std::ostream &out, const Furulatrix &s)
  {
    out << "Furulatrix (" << s.level << ", "  << s.ratio << ")";
    return out;
  }
};

struct CollisionData {
  int64_t time{0};
  zbe::Vector3D point{0.0, 0.0, 0.0};

  friend std::ostream & operator << (std::ostream &out, const CollisionData &s)
  {
    out << "CollisionData (" << s.time << ", (" << s.point[0] << ", "<< s.point[1] << ", "<< s.point[2] << "))";
    return out;
  }
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

template<typename IData, typename ...Traits>
class Actor;

template<typename IData, typename Trait>
class Actor<IData, Trait>;

template<typename IData, typename ...Traits>
class Reactor : public Reactor<IData, Traits>... {
public:
  Reactor(const Reactor& rhs) : Reactor<IData, Traits>(rhs)... {};
  Reactor() : Reactor<IData, Traits>()... {};

  template <typename U>
  void setReaction(std::function<void(IData, U)> reaction) {
    this->Reactor<IData, U>::setReaction(reaction);
  }

  void callActor(Actor<IData, Traits...>*  actor, IData data) {
    std::initializer_list<int>{(actor->act((Reactor<IData, Traits>*)this, data), 0)... };
  }
};

template<typename IData, typename Trait>
class Reactor<IData, Trait> {
public:
    Reactor(const Reactor& rhs) : reaction(rhs.reaction) {}
    Reactor() : reaction(noReaction) {}

    void setReaction(std::function<void(IData, Trait)> reaction) {
      this->reaction = reaction;
    }
    void react(IData data, Trait trait) {
      reaction(data, trait);
    }
private:
  static void noReaction(IData, Trait) {}
  std::function<void(IData, Trait)> reaction;
};

// TODO añadir typename IData, a tos laos.

template<typename IData, typename ...Traits>
class Actor : public Actor<IData, Traits>... {
public:
  Actor() : Actor<IData, Traits>()... {};
  Actor(std::pair<Traits, std::function<void(void*, Reactor<IData, Traits>*, IData)>>... valFun) : Actor<IData, Traits>(valFun)... {}

  template <typename U>
  const U get() {
    return (this->Actor<IData, U>::get());
  }

  template <typename U>
  void act(Reactor<IData, U>* reactor, IData data) {
    this->Actor<IData, U>::act(reactor, data);
  }

  template <typename U>
  void setTrait(U trait, std::function<void(void*, Reactor<IData, U>*, IData)> sa) {
    this->Actor<IData, U>::setTrait(trait, sa);
  }
};

template<typename IData, typename Trait>
class Actor<IData, Trait> {
public:
  using subAct = std::function<void(void*, Reactor<IData, Trait>*, IData)>;

  Actor() : sa(noAct), val() {}
  Actor(std::pair<Trait, std::function<void(void*, Reactor<IData, Trait>*, IData)>> valFun) : sa(std::get<1>(valFun)), val(std::get<0>(valFun)) {}

  const Trait get() {
      return val;
  }

  void setTrait(Trait trait, std::function<void(void*, Reactor<IData, Trait>*, IData)> sa) {
    this->val = trait;
    this->sa = sa;
  }

  subAct getAct() {
    return sa;
  }

  void act(Reactor<IData, Trait>* reactor, IData data) {
    sa(this, reactor, data);
  }

protected:
  Actor(Trait val, subAct sa) : sa(sa), val(val) {
  }

  void setAct(subAct sa, void* self) {
    this->sa = sa;
    this->self = self;
  }

private:
  static void noAct(void*, Reactor<IData, Trait>*, IData) {}
  subAct sa;
  Trait val;
};

template<typename IData, typename Trait>
struct ReactionPrint {
  void operator() (IData data, Trait trait){
      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
      std::cout << "Interaction data: " << data << std::endl;
  }
};

template<typename IData, typename Trait>
struct EnabledTrait {
  void operator()(void* self, Reactor<IData, Trait>* reactor, IData data) {
    Actor<IData, Trait>* typedSelf = (Actor<IData, Trait>*)self;
    auto trait = typedSelf->get();
    reactor->react(data, trait);
  }
};

// ------------------------ WIP 5 END ---------------------------- //

template <typename IData, typename ActorType, typename ReactorType>
struct InteractionEvent {
  IData data;
  ActorType actor;
  ReactorType reactor;
  void manage() {
    reactor.callActor(&actor, data);
  }
};

template <typename ActorType, typename ReactorType, typename ...Ts>
class Interactioner {
public:
  virtual ~Interactioner() = default;
  virtual std::variant<Ts...> getShape() = 0;
  virtual ActorType getActor() = 0;
  virtual ReactorType getReactor() = 0;
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

template <typename IData, typename ActorType, typename ReactorType, typename Overloaded, typename ...Ts>
class Interactionator : public Interactioner<ActorType, ReactorType, Ts...> {
public:
  std::vector<InteractionEvent<IData, ActorType, ReactorType>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData, ActorType, ReactorType>> out;
    std::variant<int64_t> vbest = timeLimit;
    for(auto iner : *iners) {
      std::variant<Ts...> v = iner->getShape();
      std::variant<IData> vdata;
      if (selector->select(this->getShape(), iner->getShape(), vbest, vdata)) {
        IData data = std::get<IData>(vdata);
        int64_t best = std::get<int64_t>(vbest);
        InteractionEvent<IData, ActorType, ReactorType> iea {data, this->getActor(), iner->getReactor()};
        InteractionEvent<IData, ActorType, ReactorType> ieb {data, iner->getActor(), this->getReactor()};
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

  void setIners(std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Ts...>>> iners) {
    this->iners = iners;
  }

private:
  //  TODO Esto es un tipo abstracto, tiene que ser un unique_ptr
  std::unique_ptr<InteractionSelector<IData, Overloaded, Ts...>> selector{};
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Ts...>>> iners{};
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

template<typename ActorType, typename ReactorType>
class CustomInteractioner : public Interactioner<ActorType, ReactorType, Sphere, Box, Ray> {
public:
  CustomInteractioner(std::variant<Sphere, Box, Ray> shape, ActorType actor, ReactorType reactor) :shape(shape), actor(actor), reactor(reactor) {}

  std::variant<Sphere, Box, Ray> getShape() {
    return shape;
  }

  ActorType getActor() {return actor;}

  ReactorType getReactor() {return reactor;}

private:
  std::variant<Sphere, Box, Ray> shape;
  ActorType actor;
  ReactorType reactor;
};


template<typename ActorType, typename ReactorType>
class CustomSampleInteractionator : public Interactionator<CollisionData, ActorType, ReactorType, BasePhysicsOverloaded, Sphere, Box, Ray>  {
public:

  CustomSampleInteractionator(std::variant<Sphere, Box, Ray> shape, ActorType actor, ReactorType reactor) :shape(shape), actor(actor), reactor(reactor) {}

  std::variant<Sphere, Box, Ray> getShape() {
    return shape;
  }

  ActorType getActor() {return actor;}

  ReactorType getReactor() {return reactor;}

private:
  std::variant<Sphere, Box, Ray> shape;
  ActorType actor;
  ReactorType reactor;
};

int tempmain (int, char **) {
  using CustomActor = Actor<CollisionData, Solid, Alive, Furulatrix>;
  using CustomReactor = Reactor<CollisionData, Solid, Alive, Furulatrix>;

  // Crear lista
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<CustomActor, CustomReactor, Sphere, Box, Ray>>> iners = std::make_shared<zbe::TicketedForwardList<Interactioner<CustomActor, CustomReactor, Sphere, Box, Ray>>>();


  // Actors y Reactors

  CustomReactor reactor;
  reactor.setReaction<Solid>(ReactionPrint<CollisionData, Solid>());
  reactor.setReaction<Alive>(ReactionPrint<CollisionData, Alive>());
  reactor.setReaction<Furulatrix>(ReactionPrint<CollisionData, Furulatrix>());

  CustomActor actor1;
  actor1.setTrait<Solid>(Solid{1.0,0.5}, EnabledTrait<CollisionData, Solid>());

  CustomActor actor2;
  actor2.setTrait<Alive>(Alive{1}, EnabledTrait<CollisionData, Alive>());

  CustomActor actor3;
  actor3.setTrait<Solid>(Solid{7.0,0.5}, EnabledTrait<CollisionData, Solid>());

  CustomActor actor4;
  actor4.setTrait<Furulatrix>(Furulatrix{}, EnabledTrait<CollisionData, Furulatrix>());

  // Crear los Interactioner
  // Reconstruir
  auto inerRay1 = std::make_shared<CustomInteractioner<CustomActor, CustomReactor>>(Ray{{1.1, 2.2, 0.0}, {3.3, 4.4, 0.0}}, actor1, reactor);
  auto inerBox1 = std::make_shared<CustomInteractioner<CustomActor, CustomReactor>>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, actor2, reactor);
  auto inerBox2 = std::make_shared<CustomInteractioner<CustomActor, CustomReactor>>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}}, actor3, reactor);
  // hasta aquí

  // Añadirlos a la lista
  iners->push_front(inerRay1);
  iners->push_front(inerBox1);
  iners->push_front(inerBox2);
  // Crear el selector
  std::unique_ptr<InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();

  // Crear el interactionator
  // Reconstruir
  CustomSampleInteractionator inator(Sphere{{3.0, 7.0, 4.0}, 4.2}, actor4, reactor);
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
}
