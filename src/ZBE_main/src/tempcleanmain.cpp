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
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace tempclean {

  class Movil {
  public:
    virtual zbe::Vector3D getVel() = 0;

    friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Movil> s) {
      auto v = s->getVel();
      out << "Movil (" << v[0] << ", "<< v[1] << ", "<< v[2] << ")";
      return out;
    }
  };

  class AvtMovil : public Movil {
  public:
    AvtMovil(std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt) : avt(avt) {}

    zbe::Vector3D getVel() {
      return zbe::AvtUtil::get<1, zbe::Vector3D>(avt)->get();
    }

  private:
    std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt;
  };

  class Vivo {
  public:
    virtual int getVidas() = 0;

    friend std::ostream & operator << (std::ostream &out, std::shared_ptr<Vivo> s) {
      out << "Vivo (" << s->getVidas() << ")";
      return out;
    }

  };

  class AvtVivo : public Vivo {
  public:
    AvtVivo(std::shared_ptr<zbe::SAvatar<int>> avt) : avt(avt) {}

    int getVidas() {
      return zbe::AvtUtil::get<1, int>(avt)->get();
    }

  private:
    std::shared_ptr<zbe::SAvatar<int>> avt;
  };

  class Solido {
    friend std::ostream & operator << (std::ostream &out, const Solido &s)
    {
      out << "Solido";
      return out;
    }
  };

  class Mata {
    friend std::ostream & operator << (std::ostream &out, const Mata &s)
    {
      out << "Mata";
      return out;
    }
  };

  class Rompe {
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

  class Sphere {
  public:

    virtual zbe::Vector3D getCenter() = 0;
    virtual double getRadius() = 0;

    friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Sphere> s)  {
      auto center = s->getCenter();
      auto radius = s->getRadius();
      out << "Sphere (" << center[0] << ", "  << center[1] << ", " << center[2] << ")" <<  " - " << radius;
      return out;
    }
  };

  class AvtSphere : public Sphere {
  public:
    AvtSphere(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> avt) : avt(avt) {}

    double getRadius() {
      return zbe::AvtUtil::get<1, double>(avt)->get();
    }

    zbe::Vector3D getCenter() {
      return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
    }

  private:
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> avt;
    //zbe::Vector3D center{};
    //double radius{};
  };

  class Box {
  public:
    virtual zbe::Vector3D getA() = 0;
    virtual zbe::Vector3D getB() = 0;

    friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Box> &s) {
      auto a = s->getA();
      auto b = s->getB();
      out << "Box (" << a[0] << ", "  << a[1] << ", " << a[2] << ") - (" << b[0] << ", "  << b[1] << ", " << b[2] << ")";
      return out;
    }
  };

  class AvtBox : public Box {
  public:
    AvtBox(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt) : avt(avt) {}

    zbe::Vector3D getA() {
      return zbe::AvtUtil::get<1, zbe::Vector3D>(avt)->get();
    }

    zbe::Vector3D getB() {
      return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
    }
  private:
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt;
  };

  class Ray {
  public:
    virtual zbe::Vector3D getPoint() = 0;
    virtual zbe::Vector3D getDirection() = 0;

    friend std::ostream & operator << (std::ostream &out, const std::shared_ptr<Ray> &s)  {
      auto point = s->getPoint();
      auto direction = s->getDirection();
      out << "Ray (" << point[0] << ", "  << point[1] << ", " << point[2] << ") - (" << direction[0] << ", "  << direction[1] << ", " << direction[2] << ")";
      return out;
    }
  };

  class AvtRay : public Ray {
  public:
    AvtRay(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt) : avt(avt) {}
    zbe::Vector3D getPoint() {
      return zbe::AvtUtil::get<1, zbe::Vector3D>(avt)->get();
    }
    zbe::Vector3D getDirection() {
      return zbe::AvtUtil::get<2, zbe::Vector3D>(avt)->get();
    }
  private:
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt;
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
    }

    template <typename U>
    void setReaction(std::function<void(IData, std::shared_ptr<U>)> reaction) {
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

      void setReaction(std::function<void(IData, std::shared_ptr<Trait>)> reaction) {
        this->reaction = reaction;
      }
      void react(IData data, std::shared_ptr<Trait> trait) {
        reaction(data, trait);
      }

      void setPayload(Reactor<IData, Trait> payload) {
        this->reaction = payload.reaction;
      }

  private:
    static void noReaction(IData, std::shared_ptr<Trait>) {}
    std::function<void(IData, std::shared_ptr<Trait>)> reaction;
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


  template<typename IData, typename ...Traits>
  class Actor : public Actor<IData, Traits>... {
  public:
    Actor() : Actor<IData, Traits>()... {};

    // Construtor.... wrapper?
    template <typename ...U>
    Actor(Actor<IData, U...> payload) : Actor<IData, Traits>()...  {
      std::initializer_list<int>{(this->Actor<IData, U>::setPayload(payload) , 0)... };
    }

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
    void setTrait(std::shared_ptr<U> trait, std::function<void(void*, Reactor<IData, U>*, IData)> sa) {
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
    Actor(std::pair<std::shared_ptr<Trait>, std::function<void(void*, Reactor<IData, Trait>*, IData)>> valFun) : sa(std::get<1>(valFun)), val(std::get<0>(valFun)) {}

    const std::shared_ptr<Trait> get() {
        return val;
    }

    void setTrait(std::shared_ptr<Trait> trait, std::function<void(void*, Reactor<IData, Trait>*, IData)> sa) {
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
    Actor(std::shared_ptr<Trait> val, subAct sa) : sa(sa), val(val) {
    }

    void setAct(subAct sa, void* self) {
      this->sa = sa;
      this->self = self;
    }

  private:
    static void noAct(void*, Reactor<IData, Trait>*, IData) {}
    subAct sa;
    std::shared_ptr<Trait> val;
  };

  // TODO reactionPrintBuilder->buildReaction(act);

  template<typename IData, typename Trait, typename Base, typename ...Bases>
  struct ReactionPrint {
    ReactionPrint(std::shared_ptr<zbe::MAvatar<Base, Bases...>> avt) : avt(avt) {}
    void operator() (IData data, std::shared_ptr<Trait> trait){
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
    void operator() (IData data, std::shared_ptr<Trait> trait){
        std::cout << "Typeid name: " << typeid(trait).name() << " With value " << trait << std::endl;
        std::cout << "Interaction data: " << data << std::endl;
        auto val = zbe::AvtUtil::get<1, Base >(avt);
        std::cout << "First avt data: " << val << std::endl;
    }
  private:
    std::shared_ptr<zbe::SAvatar<Base>> avt;
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
    Interactioner(std::variant<std::shared_ptr<Shapes>...> shape) :shape(shape), actor(), reactor() {}
    Interactioner(std::variant<std::shared_ptr<Shapes>...> shape, ActorType actor, ReactorType reactor) :shape(shape), actor(actor), reactor(reactor) {}

    std::variant<std::shared_ptr<Shapes>...> getShape() {
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
    std::variant<std::shared_ptr<Shapes>...> shape;
    ActorType actor;
    ReactorType reactor;
  };

  template<class... Shapes> struct overloaded : Shapes... { using Shapes::operator()...; };
  template<class... Shapes> overloaded(Shapes...) -> overloaded<Shapes...>;

  template<typename IData, typename Overloaded, typename ...Shapes>
  class InteractionSelector {
  public:
    virtual ~InteractionSelector() = default;
    bool select(std::variant<std::shared_ptr<Shapes>...> i1, std::variant<std::shared_ptr<Shapes>...> i2, std::variant<int64_t> timeLimit, std::variant<IData>& data) {
      return std::visit(getOverloaded(), i1, i2, timeLimit, data);
    }

    virtual Overloaded getOverloaded() = 0;
  };

  template <typename IData, typename ActorType, typename ReactorType, typename Overloaded, typename ...Shapes>
  class Interactionator : public Interactioner<ActorType, ReactorType, Shapes...> {
  public:
    Interactionator(std::variant<std::shared_ptr<Shapes>...> shape) : Interactioner<ActorType, ReactorType, std::shared_ptr<Shapes>...>(shape) {}
    Interactionator(std::variant<std::shared_ptr<Shapes>...> shape, ActorType actor, ReactorType reactor) : Interactioner<ActorType, ReactorType, Shapes...>(shape, actor, reactor) {}

    std::vector<InteractionEvent<IData, ActorType, ReactorType>> getCollision(int64_t timeLimit) {
      std::vector<InteractionEvent<IData, ActorType, ReactorType>> out;
      std::variant<int64_t> vbest = timeLimit;
      for(auto iner : *iners) {
        std::variant<std::shared_ptr<Shapes>...> v = iner->getShape();
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
    bool operator()(std::shared_ptr<Sphere> arg1, std::shared_ptr<Sphere> arg2, int64_t , CollisionData &data) {
      printf("SphereSphere\n");fflush(stdout);
      data.time = 3.0;
      data.point = arg1->getCenter() + arg2->getCenter();
      return true;
    }
  };

  class SphereBox {
  public:
    bool operator()(std::shared_ptr<Sphere>, std::shared_ptr<Box> arg2, int64_t , CollisionData &data) {
      printf("SphereBox\n");fflush(stdout);
      data.time = 4.0;
      data.point = arg2->getA();
      return true;
    }
  };

  class SphereRay {
  public:
    bool operator()(std::shared_ptr<Sphere> arg1, std::shared_ptr<Ray> , int64_t , CollisionData &data) {
      printf("SphereRay\n");fflush(stdout);
      data.time = 5.0;
      data.point = arg1->getCenter();
      return true;
    }
  };

  class BoxSphere {
  public:
    bool operator()(std::shared_ptr<Box> , std::shared_ptr<Sphere> , int64_t , CollisionData &data) {
      printf("BoxSphere\n");fflush(stdout);
      data.time = 5.0;
      data.point = zbe::Vector3D{4.0, 2.0, 0.0};
      return true;
    }
  };

  class BoxBox {
  public:
    bool operator()(std::shared_ptr<Box> , std::shared_ptr<Box> , int64_t , CollisionData &data) {
      printf("BoxBox\n");fflush(stdout);
      data.time = 5.0;
      data.point = zbe::Vector3D{4.0,2.0,0.0};
      return true;
    }
  };

  class BoxRay {
  public:
    bool operator()(std::shared_ptr<Box> , std::shared_ptr<Ray> , int64_t , CollisionData &data) {
      printf("BoxRay\n");fflush(stdout);
      data.time = 5.0;
      data.point = zbe::Vector3D{4.0,2.0,0.0};
      return true;
    }
  };

  class RaySphere {
  public:
    bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Sphere> , int64_t , CollisionData &data) {
      printf("RaySphere\n");fflush(stdout);
      data.time = 5.0;
      data.point = zbe::Vector3D{4.0,2.0,0.0};
      return true;
    }
  };

  class RayBox {
  public:
    bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Box> , int64_t , CollisionData &data) {
      printf("RayBox\n");fflush(stdout);
      data.time = 5.0;
      data.point = zbe::Vector3D{4.0,2.0,0.0};
      return true;
    }
  };

  class RayRay {
  public:
    bool operator()(std::shared_ptr<Ray> , std::shared_ptr<Ray> , int64_t , CollisionData &data) {
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

  int tempcleanmain (int, char **) {
    std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();

    // Reaction values & indexes
    std::shared_ptr<zbe::Value<uint64_t>> valuint = std::make_shared<zbe::SimpleValue<uint64_t>>(8);
    std::shared_ptr<zbe::Value<double>> valdouble1 = std::make_shared<zbe::SimpleValue<double>>(12.6);
    ent->setDouble(0, valdouble1);
    ent->setUint(0, valuint);
    std::array<uint64_t, 2> lreaction{ {0, 0} };

    // Shape values & indexes
    std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec13 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 1.0,  2.0,  3.0});
    std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec46 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 4.0,  5.0,  6.0});
    std::shared_ptr<zbe::Value<zbe::Vector3D>> valVec79 = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{ 7.0,  8.0,  9.0});
    std::shared_ptr<zbe::Value<zbe::Vector3D>> valVecAC = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{10.0, 11.0, 12.0});
    std::shared_ptr<zbe::Value<zbe::Vector3D>> valVecDF = std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(zbe::Vector3D{13.0, 14.0, 15.0});
    std::shared_ptr<zbe::Value<double>> valdouble2 = std::make_shared<zbe::SimpleValue<double>>(16);

    ent->setDouble(1, valdouble2);
    ent->setVector3D(0, valVec13);
    ent->setVector3D(1, valVec46);
    ent->setVector3D(2, valVec79);
    ent->setVector3D(3, valVecAC);
    ent->setVector3D(4, valVecDF);

    std::array<uint64_t, 2> lSphere{ {0, 1} };
    std::array<uint64_t, 2> lSphere2{ {4, 1} };
    std::array<uint64_t, 2> lBox{ {1, 2} };
    std::array<uint64_t, 2> lRay{ {3, 4} };

    std::shared_ptr<zbe::MAvatar<uint64_t, double>> reactionAvt = std::make_shared<zbe::MBaseAvatar<uint64_t, double>>(ent, lreaction);
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> shapeSphereAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, double>>(ent, lSphere);
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, double>> shapeSphereAvt2 = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, double>>(ent, lSphere2);
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> shapeBoxAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, zbe::Vector3D>>(ent, lBox);
    std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> shapeRayAvt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, zbe::Vector3D>>(ent, lRay);


    // TODO hacer pruebas con tipos con avatar (Vivo o Movil)
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

    ActorBola aBola;
    aBola.setTrait(std::make_shared<Rompe>(), EnabledTrait<CollisionData, Rompe>());

    ActorLadrillo aLadrillo;
    aLadrillo.setTrait(std::make_shared<Solido>(), EnabledTrait<CollisionData, Solido>());

    ActorBorde aBorde;
    aBorde.setTrait(std::make_shared<Solido>(), EnabledTrait<CollisionData, Solido>());

    ActorPozo aPozo;
    aPozo.setTrait(std::make_shared<Mata>(), EnabledTrait<CollisionData, Mata>());

    WholeActor waBola(aBola);
    WholeActor waLadrillo(aLadrillo);
    WholeActor waBorde(aBorde);
    WholeActor waPozo(aPozo);

    ReactorBola rBola;
    rBola.setReaction<Solido>(ReactionPrint<CollisionData, Solido, uint64_t, double>(reactionAvt));
    rBola.setReaction<Mata>(ReactionPrint<CollisionData, Mata, uint64_t, double>(reactionAvt));

    ReactorLadrillo rLadrillo;
    rLadrillo.setReaction(ReactionPrint<CollisionData, Rompe, uint64_t, double>(reactionAvt));

    Wholereactor wrBola(rBola);
    Wholereactor wrLadrillo(rLadrillo);
    Wholereactor wrBorde;
    Wholereactor wrPozo;

    // Crear los Interactioner
    // Reconstruir
    //auto inerBolaEsferica = std::make_shared<WholeInteractioner>(Ray{{1.1, 2.2, 0.0}, {3.3, 4.4, 0.0}}, actor1, reactor);
    auto inerLadrilloRedondo = std::make_shared<WholeInteractioner>(std::make_shared<AvtSphere>(shapeSphereAvt2), waLadrillo, wrLadrillo);
    auto inerLadrilloCuadrao = std::make_shared<WholeInteractioner>(std::make_shared<AvtBox>(shapeBoxAvt), waLadrillo, wrLadrillo);
    auto inerBordeCasiCuadrao = std::make_shared<WholeInteractioner>(std::make_shared<AvtBox>(shapeBoxAvt), waBorde, wrBorde);
    auto inerPozoNoRedondo = std::make_shared<WholeInteractioner>(std::make_shared<AvtBox>(shapeBoxAvt), waPozo, wrPozo);

    // auto inerBox3 = std::make_shared<WholeInteractioner>(Box{{1.0, 2.0, 0.0}, {3.0, 4.0, 0.0}});
    // inerBox3.setActor(actor3);
    // inerBox3.setReactor(reactor);


    // hasta aquí

    // Añadirlos a la lista
    iners->push_front(inerLadrilloRedondo);
    iners->push_front(inerLadrilloCuadrao);
    iners->push_front(inerBordeCasiCuadrao);
    iners->push_front(inerPozoNoRedondo);
    // Crear el selector
    std::unique_ptr<InteractionSelector<CollisionData, BasePhysicsOverloaded, Sphere, Box, Ray>> selector = std::make_unique<BasePhysicsSelector>();

    // Crear el interactionator
    // Reconstruir
    std::shared_ptr<Sphere> avtSphere = std::make_shared<AvtSphere>(shapeSphereAvt);
    std::variant<std::shared_ptr<Sphere>, std::shared_ptr<Box>, std::shared_ptr<Ray>> varAvtSphere = avtSphere;
    WholeInteractionator inatorBolaEsferica(varAvtSphere, waBola, wrBola);
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

  // TODO:
  // Hacer Actor/Reactor/Shape saquen su información de un avatar

  // Blahblah
  //TODO:
  //  InteractionEventGenerator
  //  Pieza que va a recibir un Avatar<...>
  //
  //PENSAR EN ESTO:
  //  Avatar<Vector3D, Vector3D> avt;
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
}
