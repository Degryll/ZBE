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

#include "ZBE/core/system/system.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"

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
  static void noAct(Reactor<IData, Trait>*, IData) {}
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

template <typename IData, typename ActorType, typename ReactorType, typename Overloaded, typename ...Shapes>
class Interactionator : public Interactioner<ActorType, ReactorType, Shapes...> {
public:
  Interactionator(std::shared_ptr<Shape<Shapes...>> shape, uint64_t id) : Interactioner<ActorType, ReactorType, Shapes...>(shape), id(id), selector(), iners() {}
  Interactionator(std::shared_ptr<Shape<Shapes...>> shape, uint64_t id, ActorType actor, ReactorType reactor) : Interactioner<ActorType, ReactorType, Shapes...>(shape, actor, reactor), id(id), selector(), iners() {}

  std::vector<InteractionEvent<IData, ActorType, ReactorType>> getCollision(int64_t timeLimit) {
    std::vector<InteractionEvent<IData, ActorType, ReactorType>> out;
    std::variant<int64_t> vbest = timeLimit;
    for(auto iner : *iners) {
      //Shape<Shapes...> v = iner->getShape();
      std::variant<IData> vdata;
      if (selector->select(this->getShape(), iner->getShape(), vbest, vdata)) {
        IData data = std::get<IData>(vdata);
        int64_t best = std::get<int64_t>(vbest);
        InteractionEvent<IData, ActorType, ReactorType> iea(id, best, data, this->getActor(), iner->getReactor());
        InteractionEvent<IData, ActorType, ReactorType> ieb(id, best, data, iner->getActor(), this->getReactor());
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
  uint64_t id;
  std::unique_ptr<InteractionSelector<IData, Overloaded, Shapes...>> selector{};
  std::shared_ptr<zbe::TicketedForwardList<Interactioner<ActorType, ReactorType, Shapes...>>> iners{};
};

template <typename InteractionatorType>
class InteractionEventGenerator : virtual public Daemon {
public:

  InteractionEventGenerator() : ators(), contextTime(), es(EventStore::getInstance()) {}

  void setInteractionList(std::shared_ptr<zbe::TicketedForwardList<InteractionatorType>> ators) {
    this->ators = ators;
  }

  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

  void run() {
    int64_t totalTime = contextTime->getRemainTime();

    for(auto iator : (*ators)) {
      auto iel = iator->getCollision(totalTime);
      for(auto event : iel) {
        this->es.storeEvent(event);
      }
    }
  }

private:
  std::shared_ptr<zbe::TicketedForwardList<InteractionatorType>> ators{};
  std::shared_ptr<ContextTime> contextTime;
  EventStore& es; //!< The Event Store.
};


}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONSYSTEM_H
