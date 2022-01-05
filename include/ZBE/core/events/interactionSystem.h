/**
 * Copyright 2012 Batis Degryll Ludo
 * @file interactionSystem.h
 * @since 2016-08-15
 * @date 2018-03-20
 * @author Degryll Batis Ludo
 * @brief An event caused by input devices.
 */

#ifndef ZBE_CORE_EVENTS_INTERACTIONSYSTEM_H
#define ZBE_CORE_EVENTS_INTERACTIONSYSTEM_H

#include <cstdint>
#include <iostream>
#include <variant>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

namespace zbe {

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
  }

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
    static void noReaction(IData, Trait) {}

    void setReaction(std::function<void(IData, Trait)> reaction) {
      this->reaction = reaction;
    }

    void react(IData data, Trait trait) {
      reaction(data, trait);
    }

    void setPayload(Reactor<IData, Trait> payload) {
      this->reaction = payload.reaction;
    }

    void callActor(Actor<IData, Trait>*  actor, IData data) {
      actor->act(this, data);
    }

private:
  std::function<void(IData, Trait)> reaction;
};

template<typename IData, typename ...Traits>
class Actor : public Actor<IData, Traits>... {
public:
  Actor() : Actor<IData, Traits>()... {};

  // Construtor.... wrapper?
  template <typename ...U>
  Actor(Actor<IData, U...> payload) : Actor<IData, Traits>()...  {
    std::initializer_list<int>{(this->Actor<IData, U>::setPayload(payload) , 0)... };
  }

  Actor(std::function<void(Reactor<IData, Traits>*, IData)>... sa) : Actor<IData, Traits>(sa)... {}

  template <typename U>
  void act(Reactor<IData, U>* reactor, IData data) {
    this->Actor<IData, U>::act(reactor, data);
  }

  template <typename U>
  void setTrait(std::function<void(Reactor<IData, U>*, IData)> sa) {
    this->Actor<IData, U>::setTrait(sa);
  }

  template <typename U>
  void setPayload(Actor<IData, U> payload) {
    this->Actor<IData, U>::setPayload(payload);
  }
};

template<typename IData, typename Trait>
class Actor<IData, Trait> {
public:
  using subAct = std::function<void(Reactor<IData, Trait>*, IData)>;
  static void noAct(Reactor<IData, Trait>*, IData) {}

  Actor() : sa(noAct) {}
  Actor(std::function<void(Reactor<IData, Trait>*, IData)> sa) : sa(sa) {}

  void setTrait(std::function<void(Reactor<IData, Trait>*, IData)> sa) {
    this->sa = sa;
  }

  subAct getAct() {
    return sa;
  }

  void act(Reactor<IData, Trait>* reactor, IData data) {
    sa(reactor, data);
  }

  void setPayload(Actor<IData, Trait> payload) {
    this->sa = payload.sa;
  }

protected:
  //Actor(subAct sa) : sa(sa){  }

  void setAct(subAct sa) {
    this->sa = sa;
  }

private:
  subAct sa;
};

// En algún momento querremos cambiar los tipos del actor o reactor dinámicamente.
// Y por lo tanto cambiara como el resto de objetos reaccionan con nostros y nosotros con ellos
// Esto se puede resolver haciendo este EnabledTrait que dependa de un avatar similar a Reaction Print.
// En función de los datos del avatar, cumpliremos un tipo o no.
// Ejemplo. La bola del zombienoid, por un itme, pasa a no colisionar con los ladrillos.
// Los ladrillos se rompen con la colisión con la bola, pero la bola no está interesada en los ladrillos.
// Su reactor no atiende a los ladrillos.
// ----------------------
// Dado que es esta función la que pasa el valor del trait al reactor,
// no sería necesario que el actor almacenase este valor, sino que podría alamacenarlo esta funcion u objeto callable
// o podría leerla de un avatar.
// Esto eliminaría la necesidad de andar pasando el self.

template<typename IData, typename Trait>
class AvtEnabledTrait {
public:
  AvtEnabledTrait(std::shared_ptr<SAvatar<Trait>> avt) : avt(avt) {}
  void operator()(Reactor<IData, Trait>* reactor, IData data) {
    auto trait = avt->get();
    reactor->react(data, trait);
  }
private:
  std::shared_ptr<SAvatar<Trait>> avt;
};

// Esta implementacion se mantiene como documentacion.
// Revisar
template<typename IData, typename Trait, typename Base, typename ...Bases>
struct ReactionPrint {
  ReactionPrint(std::shared_ptr<zbe::MAvatar<Base, Bases...>> avt) : avt(avt) {}
  void operator() (IData data, Trait trait){
      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
      std::cout << "Interaction data: " << data << std::endl;
      auto val = zbe::AvtUtil::get<2, Base >(avt);
      //auto val = avt->get<1, uint64_t>()->get();
      std::cout << "First avt data: " << val << std::endl;
  }
private:
  std::shared_ptr<zbe::MAvatar<Base, Bases...>> avt;
};

template<typename IData, typename Trait, typename Base>
struct ReactionPrint<IData, Trait, Base> {
  ReactionPrint(std::shared_ptr<zbe::SAvatar<Base>> avt) : avt(avt) {}
  void operator() (IData data, Trait trait){
      std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
      std::cout << "Interaction data: " << data << std::endl;
      auto val = zbe::AvtUtil::get<1, Base >(avt);
      std::cout << "First avt data: " << val << std::endl;
  }
private:
  std::shared_ptr<zbe::SAvatar<Base>> avt;
};


template<typename ...Shapes>
class Shape {
public:
  virtual ~Shape() = default;
  virtual std::variant<std::shared_ptr<Shapes>...> getShape() = 0;
};

template <typename IData, typename ActorType, typename ReactorType>
struct InteractionEvent : public Event {
  InteractionEvent(uint64_t id, uint64_t time, IData data, ActorType actor, ReactorType reactor) : Event(id, time), data(data), actor(actor), reactor(reactor) {}
  IData data;
  ActorType actor;
  ReactorType reactor;
  void manage() {
    reactor.callActor(&actor, data);
  }
};

template <typename S, typename ...Shapes>
class AvtShape : public zbe::Shape<Shapes...> {
public:
  AvtShape(std::shared_ptr<SAvatar<S>> avt) : avt(avt) {};
  std::variant<std::shared_ptr<Shapes>...> getShape() {
    return avt->get();
  };
private:
  std::shared_ptr<SAvatar<S>> avt;
};

template<typename ActorType, typename ReactorType, typename ...Shapes>
class Interactioner {
public:
  Interactioner(std::shared_ptr<Shape<Shapes...>> shape) : shape(shape), actor(), reactor() {}
  Interactioner(std::shared_ptr<Shape<Shapes...>> shape, ActorType actor, ReactorType reactor) : shape(shape), actor(actor), reactor(reactor) {}

  std::shared_ptr<Shape<Shapes...>> getShape()   {return shape;}
  ActorType        getActor()   {return actor;}
  ReactorType      getReactor() {return reactor;}

  void setShape(std::shared_ptr<Shape<Shapes...>> shape) {
    this->shape = shape;
  }

  template<typename U>
  void setActor(U actor) {
    this->actor = ActorType(actor);
  }

  template<typename U>
  void setReactor(U actor) {
    this->reactor = ReactorType(actor);
  }

private:
  std::shared_ptr<Shape<Shapes...>> shape;
  ActorType actor;
  ReactorType reactor;
};

/* Sample interaction selector implementation

class RayRay {
public:
  bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Ray> , int64_t , CollisionData &data) {
    printf("RayRay\n");fflush(stdout);
    data.time = 5;
    data.point = zbe::Vector3D{4.0,2.0,0.0};
    return true;
  }
};

using BasePhysicsOverloaded = zbe::overloaded<SphereSphere, SphereBox, SphereRay, BoxSphere, BoxBox, BoxRay, RaySphere, RayBox, RayRay>;

class BasePhysicsSelector : public zbe::InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray> {
public:
  virtual ~BasePhysicsSelector() = default;
protected:
  virtual BasePhysicsOverloaded getOverloaded() {
    return BasePhysicsOverloaded {SphereSphere{}, SphereBox{}, SphereRay{}, BoxSphere{}, BoxBox{}, BoxRay{}, RaySphere{}, RayBox{}, RayRay{}};
  }  // getOverloaded
};

*/

template<class... Shapes> struct overloaded : Shapes... { using Shapes::operator()...; };
template<class... Shapes> overloaded(Shapes...) -> overloaded<Shapes...>;

template<typename IData, typename Overloaded, typename ...Shapes>
class InteractionSelector {
public:
  virtual ~InteractionSelector() = default;
  bool select(std::shared_ptr<Shape<Shapes...>> i1, std::shared_ptr<Shape<Shapes...>> i2, std::variant<int64_t> timeLimit, std::variant<IData>& data) {
    return std::visit(getOverloaded(), i1->getShape(), i2->getShape(), timeLimit, data);
  }

  virtual Overloaded getOverloaded() = 0;
};

template <typename IS, typename O, typename ...F>
class BaseSelector : public IS {
public:
  virtual ~BaseSelector() = default;
protected:
  virtual O getOverloaded() {
    return O{F{}...};
  }  // getOverloaded
};

template <typename ActorType, typename ReactorType, typename ...Shapes>
class Interactionator : public Interactioner<ActorType, ReactorType, Shapes...> {
public:
  Interactionator(std::shared_ptr<Shape<Shapes...>> shape) : Interactioner<ActorType, ReactorType, Shapes...>(shape), iners() {}
  Interactionator(std::shared_ptr<Shape<Shapes...>> shape, ActorType actor, ReactorType reactor) : Interactioner<ActorType, ReactorType, Shapes...>(shape, actor, reactor), iners() {}

  void setIners(std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> iners) {
    this->iners = iners;
  }

  std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> getIners() {
    return this->iners;
  }

private:
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> iners{};
};

template <typename Overloaded, typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionEventGenerator : virtual public Daemon {
public:

  InteractionEventGenerator(uint64_t id = 0) : id(id), ators(), contextTime(), es(EventStore::getInstance()) {}

  void setAtorList(std::shared_ptr<zbe::TicketedForwardList<Interactionator<ActorType, ReactorType, Shapes...>>> ators) {
    this->ators = ators;
  }

  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

  void run() {
    int64_t totalTime = contextTime->getRemainTime();

    for(auto iator : (*ators)) {
      getCollision(iator, totalTime);
    }
  }

  void setSelector(std::unique_ptr<InteractionSelector<IData, Overloaded, Shapes...>> selector) {
    this->selector = std::move(selector);
  }

  void setEventId(uint64_t id) {
    this->id = id;
  }

private:
  void getCollision(std::shared_ptr<Interactionator<ActorType, ReactorType, Shapes...>> ator, int64_t timeLimit) {
    std::vector<InteractionEvent<IData, ActorType, ReactorType>> out;
    std::variant<int64_t> vbest = timeLimit;
    auto iners = ator->getIners();
    for(auto iner : *iners) {
      std::variant<IData> vdata;
      if (selector->select(ator->getShape(), iner->getShape(), vbest, vdata)) {
        IData data = std::get<IData>(vdata);
        int64_t best = data.time;
        vbest = best;
        std::cout << "InteractionEG time: " << best << std::endl;
        auto iea = new InteractionEvent<IData, ActorType, ReactorType>(id, best, data, ator->getActor(), iner->getReactor());
        auto ieb = new InteractionEvent<IData, ActorType, ReactorType>(id, best, data, iner->getActor(), ator->getReactor());
        this->es.storeEvent(iea);
        this->es.storeEvent(ieb);
      }
    }  // for iners
  }
  uint64_t id;
  std::unique_ptr<InteractionSelector<IData, Overloaded, Shapes...>> selector{};

  std::shared_ptr<zbe::TicketedForwardList<Interactionator<ActorType, ReactorType, Shapes...>>> ators{};
  std::shared_ptr<ContextTime> contextTime;
  EventStore& es; //!< The Event Store.
};


template <typename Selector, typename Overloaded, typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionEventGeneratorFtry : virtual public Factory  {
public:
  using IEG = InteractionEventGenerator<Overloaded, IData, ActorType, ReactorType, Shapes...>;
  using ATOR = Interactionator<ActorType, ReactorType, Shapes...>;

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<IEG> ieg = std::shared_ptr<IEG>(new IEG);  // std::make_shared<SineOscillator>();
    daemonStore.insert("Daemon."s + name, ieg);
    iegStore.insert("InteractionEventGenerator."s + name, ieg);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["eventId"].is_string()) {
        SysError::setError("InteractionEventGeneratorFtry config for eventId: "s + j["eventId"].get<std::string>() + ": must be a literal int name."s);
        return;
      }

      if (!j["interactionators"].is_string()) {
        SysError::setError("InteractionEventGeneratorFtry config for interactionators: "s + j["interactionators"].get<std::string>() + ": must be an interactionators list name."s);
        return;
      }

      if (!j["contextTime"].is_string()) {
        SysError::setError("InteractionEventGeneratorFtry config for contextTime: "s + j["contextTime"].get<std::string>() + ": must be a contextTime name."s);
        return;
      }

      std::string eventIdName = j["eventId"].get<std::string>();
      if(!intStore.contains(eventIdName)) {
        SysError::setError("InteractionEventGeneratorFtry config for eventId: "s + eventIdName + " is not a int64_t literal."s);
        return;
      }
      int64_t eventId = intStore.get(eventIdName);

      std::string interactionatorsName = j["interactionators"].get<std::string>();
      if(!atorListStore.contains(interactionatorsName)) {
        SysError::setError("InteractionEventGeneratorFtry config for eventId: "s + interactionatorsName + " is not a interactionators lsit name."s);
        return;
      }
      auto ators = atorListStore.get("InteractionEventGenerator."s + interactionatorsName);

      std::string contextTimeName = j["contextTime"].get<std::string>();
      if(!timeStore.contains(contextTimeName)) {
        SysError::setError("InteractionEventGeneratorFtry config for contextTime: "s + contextTimeName + " is not a context time name."s);
        return;
      }
      auto contextTime = timeStore.get(eventIdName);

      auto ieg = iegStore.get("InteractionEventGenerator."s + name);

      ieg->setEventId(eventId);
      ieg->setAtorList(ators);
      ieg->setContextTime(contextTime);

      std::unique_ptr<Selector> selector = std::make_unique<Selector>();
      ieg->setSelector(std::move(selector));

    } else {
      SysError::setError("InteractionEventGeneratorFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ContextTime> &timeStore = RsrcStore<ContextTime>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<IEG>& iegStore = RsrcStore<IEG>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<zbe::TicketedForwardList<ATOR>>& atorListStore = RsrcStore<zbe::TicketedForwardList<ATOR>>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONSYSTEM_H
