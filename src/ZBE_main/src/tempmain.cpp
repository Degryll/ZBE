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

namespace temp {
/*

Bola: Movil, Vivo y Rompe

N ladrillos: Vivo, Solido

Bordes: Solido

Pozo: Mata.

---------------



*/

struct Movil {
  zbe::Vector3D v;

  friend std::ostream & operator << (std::ostream &out, const Movil &s)
  {
    out << "Movil (" << s.v[0] << ", "<< s.v[1] << ", "<< s.v[2] << ")";
    return out;
  }
};

struct Vivo {
  int vidas;

  friend std::ostream & operator << (std::ostream &out, const Vivo &s)
  {
    out << "Vivo (" << s.vidas << ")";
    return out;
  }
};

struct Solido {
  friend std::ostream & operator << (std::ostream &out, const Solido &s)
  {
    out << "Solido";
    return out;
  }
};

struct Mata {
  friend std::ostream & operator << (std::ostream &out, const Mata &s)
  {
    out << "Mata";
    return out;
  }
};

struct Rompe {
  friend std::ostream & operator << (std::ostream &out, const Rompe &s)
  {
    out << "Rompe";
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
  Reactor() : Reactor<IData, Traits>()... {};
  Reactor(const Reactor& rhs) : Reactor<IData, Traits>(rhs)... {};

  template <typename ...U>
  Reactor(Reactor<IData, U...> payload) : Reactor<IData, Traits>()... {
    std::initializer_list<int>{(this->Reactor<IData, U>::setPayload(payload) , 0)... };
  };

  template <typename U>
  void setReaction(std::function<void(IData, U)> reaction) {
    this->Reactor<IData, U>::setReaction(reaction);
  }

  template <typename U>
  void setPayload(Reactor<IData, U> payload) {
    this->Reactor<IData, U>::setPayload(payload);
  }

  void callActor(Actor<IData, Traits...>*  actor, IData data) {
    std::initializer_list<int>{(actor->act((Reactor<IData, Traits>*)this, data), 0)... };
  }
};

template<typename IData, typename Trait>
class Reactor<IData, Trait> {
public:
    Reactor() : reaction(noReaction) {}
    Reactor(const Reactor& rhs) : reaction(rhs.reaction) {}

    void setReaction(std::function<void(IData, Trait)> reaction) {
      this->reaction = reaction;
    }
    void react(IData data, Trait trait) {
      reaction(data, trait);
    }

    void setPayload(Reactor<IData, Trait> payload) {
      this->reaction = payload.reaction;
    }

private:
  static void noReaction(IData, Trait) {}
  std::function<void(IData, Trait)> reaction;
};

// template<typename IData>
// class Reactor<IData, void> {
// public:
//     Reactor() : reaction(noReaction) {}
//
// private:
//   static void noReaction(IData, Trait) {}
//   std::function<void(IData, Trait)> reaction;
// };

// TODO añadir typename IData, a tos laos.

template<typename IData, typename ...Traits>
class Actor : public Actor<IData, Traits>... {
public:
  Actor() : Actor<IData, Traits>()... {};

  // Construtor.... wrapper?
  template <typename ...U>
  Actor(Actor<IData, U...> payload) : Actor<IData, Traits>()...  {
    std::initializer_list<int>{(this->Actor<IData, U>::setPayload(payload) , 0)... };
  };

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

  template <typename U>
  void setPayload(Actor<IData, U> payload) {
    this->Actor<IData, U>::setPayload(payload);
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

  void setPayload(Actor<IData, Trait> payload) {
    this->sa = payload.sa;
    this->val = payload.val;
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

template<typename ActorType, typename ReactorType, typename ...Shapes>
class Interactioner {
public:
  Interactioner(std::variant<Shapes...> shape) :shape(shape), actor(), reactor() {}
  Interactioner(std::variant<Shapes...> shape, ActorType actor, ReactorType reactor) :shape(shape), actor(actor), reactor(reactor) {}

  std::variant<Shapes...> getShape() {
    return shape;
  }

  ActorType getActor() {return actor;}

  ReactorType getReactor() {return reactor;}

  template<typename U>
  void setActor(U actor) {
    this->actor = ActorType(actor);
  }

  template<typename U>
  void setReactor(U actor) {
    this->reactor = ReactorType(actor);
  }

private:
  std::variant<Shapes...> shape;
  ActorType actor;
  ReactorType reactor;
};

template<class... Shapes> struct overloaded : Shapes... { using Shapes::operator()...; };
template<class... Shapes> overloaded(Shapes...) -> overloaded<Shapes...>;

template<typename IData, typename Overloaded, typename ...Shapes>
class InteractionSelector {
public:
  virtual ~InteractionSelector() = default;
  bool select(std::variant<Shapes...> i1, std::variant<Shapes...> i2, std::variant<int64_t> timeLimit, std::variant<IData>& data) {
    return std::visit(getOverloaded(), i1, i2, timeLimit, data);
  }

  virtual Overloaded getOverloaded() = 0;
};

template <typename IData, typename ActorType, typename ReactorType, typename Overloaded, typename ...Shapes>
class Interactionator : public Interactioner<ActorType, ReactorType, Shapes...> {
public:
  Interactionator(std::variant<Shapes...> shape) : Interactioner<ActorType, ReactorType, Shapes...>(shape) {}
  Interactionator(std::variant<Shapes...> shape, ActorType actor, ReactorType reactor) : Interactioner<ActorType, ReactorType, Shapes...>(shape, actor, reactor) {}

  std::vector<InteractionEvent<IData, ActorType, ReactorType>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData, ActorType, ReactorType>> out;
    std::variant<int64_t> vbest = timeLimit;
    for(auto iner : *iners) {
      std::variant<Shapes...> v = iner->getShape();
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

  void setSelector(std::unique_ptr<InteractionSelector<IData, Overloaded, Shapes...>> selector) {
    this->selector = std::move(selector);
  }

  void setIners(std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> iners) {
    this->iners = iners;
  }

private:
  //  TODO Esto es un tipo abstracto, tiene que ser un unique_ptr
  std::unique_ptr<InteractionSelector<IData, Overloaded, Shapes...>> selector{};
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> iners{};
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
  bool operator()(Sphere, Box arg2, int64_t , CollisionData &data) {
    printf("SphereBox\n");fflush(stdout);
    data.time = 4.0;
    data.point = arg2.a;
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

int tempmain (int, char **) {

  // Esto por si solo no se puede
  // Hace falta un wrapper
  using ActorBola = Actor<CollisionData, Rompe>;
  using ActorLadrillo = Actor<CollisionData, Solido>;
  using ActorBorde = Actor<CollisionData, Solido>;
  using ActorPozo = Actor<CollisionData, Mata>;

  // using ActorMarkRuffalo = Actor<CollisionData, Mata, Rompe>;

  using ReactorBola = Reactor<CollisionData, Solido, Mata>;
  using ReactorLadrillo = Reactor<CollisionData, Rompe>;
  //using ReactorBorde = Reactor<CollisionData>; // Parece que no es necesario

  using WholeActor = Actor<CollisionData, Vivo, Solido, Mata, Rompe>;
  using Wholereactor = Reactor<CollisionData, Vivo, Solido, Mata, Rompe>;

  using WholeInteractioner = Interactioner<WholeActor, Wholereactor, Sphere, Box, Ray>;
  using WholeInteractionator = Interactionator<CollisionData, WholeActor, Wholereactor, BasePhysicsOverloaded, Sphere, Box, Ray>;

  // Crear lista
  std::shared_ptr<zbe::TicketedForwardList<WholeInteractioner>> iners = std::make_shared<zbe::TicketedForwardList<WholeInteractioner>>();


  // Actors y Reactors

  // Futurible InteractionAvatar<Avatar<A,B,C>,CollisionData, Rompe, Casca, LoQuesea>

  //################ TODO construir actors y reactors de distintos tipos y meterlos en los whole iners y ators.

  ActorBola aBola;
  aBola.setTrait(Rompe{}, EnabledTrait<CollisionData, Rompe>());

  ActorLadrillo aLadrillo;
  aLadrillo.setTrait(Solido{}, EnabledTrait<CollisionData, Solido>());

  ActorBorde aBorde;
  aBorde.setTrait(Solido{}, EnabledTrait<CollisionData, Solido>());

  ActorPozo aPozo;
  aPozo.setTrait(Mata{}, EnabledTrait<CollisionData, Mata>());

  WholeActor waBola(aBola);
  WholeActor waLadrillo(aLadrillo);
  WholeActor waBorde(aBorde);
  WholeActor waPozo(aPozo);

  ReactorBola rBola;
  rBola.setReaction<Solido>(ReactionPrint<CollisionData, Solido>());
  rBola.setReaction<Mata>(ReactionPrint<CollisionData, Mata>());

  ReactorLadrillo rLadrillo;
  rLadrillo.setReaction(ReactionPrint<CollisionData, Rompe>());

  Wholereactor wrBola(rBola);
  Wholereactor wrLadrillo(rLadrillo);
  Wholereactor wrBorde;
  Wholereactor wrPozo;

  // Crear los Interactioner
  // Reconstruir
  //auto inerBolaEsferica = std::make_shared<WholeInteractioner>(Ray{{1.1, 2.2, 0.0}, {3.3, 4.4, 0.0}}, actor1, reactor);
  auto inerLadrilloCuadrao = std::make_shared<WholeInteractioner>(Box{{-0.1, -0.1, 0.0}, {0.1, 0.1, 0.0}}, waLadrillo, wrLadrillo);
  auto inerBordeCasiCuadrao = std::make_shared<WholeInteractioner>(Box{{-1.0, -1.0, 0.0}, {1.0, 1.0, 0.0}}, waBorde, wrBorde);
  auto inerPozoNoRedondo = std::make_shared<WholeInteractioner>(Box{{-1.0, -0.9, 0.0}, {-1.0, -1.0, 0.0}}, waPozo, wrPozo);

  // auto inerBox3 = std::make_shared<WholeInteractioner>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}});
  // inerBox3.setActor(actor3);
  // inerBox3.setReactor(reactor);


  // hasta aquí

  // Añadirlos a la lista
  iners->push_front(inerLadrilloCuadrao);
  iners->push_front(inerBordeCasiCuadrao);
  iners->push_front(inerPozoNoRedondo);
  // Crear el selector
  std::unique_ptr<InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();

  // Crear el interactionator
  // Reconstruir
  WholeInteractionator inatorBolaEsferica(Sphere{{0.0, -0.5, 0.0}, 0.1}, waBola, wrBola);
  // hasta aquí

  // Añadir la lista al Interactionator
  inatorBolaEsferica.setIners(iners);
  // Áñadir el selector al interactionator
  inatorBolaEsferica.setSelector(std::move(selector));
  // Pedirle los eventos al interactionator
  auto iEs = inatorBolaEsferica.getCollision(256);
  // Comerse un cachopo

  for(auto& ie: iEs) {
    // Aquí tenemos que meter lo de después
    printf("time: %lld, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);fflush(stdout);
    ie.manage();
  }

//TODO:
//  InteractionEventGenerator
//  Pieza que va a recibir un Avatar<...>
//
//PENSAR EN ESTO:
//  Avatar<Vecto3D, Vecto3D> avt;
//  Interactioner<ActorType, ReactorType, Sphere, Box, Ray>;
//  ReactionPrint<CollisionData, Solido>()


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

}  // namespace zbe
