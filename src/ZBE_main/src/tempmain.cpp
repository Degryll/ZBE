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


// -------------------------- WIP 1 ------------------------------ //
/*- Al crear el Interactionator, ya sabes en que tipos estás interesado.
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
*/

// -------------------------- WIP 2 the bad  ------------------------------ //

//template<std::size_t...Is, typename T, typename F>
//void tuple_foreach( std::index_sequence<Is...>, T&& tup, F&& f ) {
//  ( f( std::get<Is>( std::forward<T>(tup) ) ), ... );
//}
//template<typename T, typename F>
//void tuple_foreach( T&& tup, F&& f ) {
//  auto indexes = std::make_index_sequence< std::tuple_size_v< std::decay_t<T> > >{};
//  tuple_foreach( indexes, std::forward<T>(tup), std::forward<F>(f) );
//}
//
//template<std::size_t I>
//using index_t = std::integral_constant<std::size_t, I>;
//template<std::size_t I>
//constexpr index_t<I> index{};
//
//template<std::size_t...Is>
//constexpr std::tuple< index_t<Is>... > make_indexes(std::index_sequence<Is...>){
//  return std::make_tuple(index<Is>...);
//}
//
//template<std::size_t N>
//constexpr auto indexing_tuple = make_indexes(std::make_index_sequence<N>{});
//
//// template<typename V, typename ...Ts>
//// V parse_variant(std::variant<Ts...>& tsVariant)
//// {
////   auto indexes = indexing_tuple<tuple_size_v<V>>;
////   std::optional<V> retval;
////   tuple_foreach(indexes, [&](auto I){ // I is compile time integer
////     if(retval) return;
////     auto p = tsVariant.get<tuple_alternative_t<I>>();
////     if(p) retval.emplace(std::move(*p));
////   });
////   if(!retval) throw ParseError("Can't parse");
////   return std::move(*retval);
//// }
//
//template<typename ...Ts>
//using optional_variant = std::variant<std::monostate, Ts...>;
//
//template<typename V, typename ...Ts>
//optional_variant<Ts...> parse_optional_variant(V& tsVariant)
//{
//  auto indexes = indexing_tuple<std::variant_size_v<V>>;
//  optional_variant<Ts...> retval;
//  tuple_foreach(indexes, [&](auto I){ // I is compile time integer
//    if constexpr ((std::is_same_v<std::variant_alternative_t<I, V>, Ts> || ...)) {
//      if /*constexpr*/ (std::holds_alternative<std::variant_alternative_t<I, V>>(tsVariant)) {
//        retval = std::get<std::variant_alternative_t<I, V>   >(tsVariant);
//      }
//    }
//  });
//  return retval;
//}


// ------------------------ WIP 2 END ---------------------------- //


// -------------------------- WIP 3 the ugly ------------------------------ //

// template<typename T, typename ...Ts>
// class Things : public Things<T>, public Things<Ts...> {
//   template <typename U>
//   U get() {
//     return (this->Things<U>::get());
//   }
// };
//
// template<typename T>
// class Things {
// public:
//   template<typename V = T>
//   V get() {
//       return val;
//   }
// private:
//   T val;
// }

// template<...Ts>
// using Interest = Things<Ts...>;
//
// template<...Ts>
// using Offers = Things<Ts...>;
//
// class ReactorObjectBase {
// public:
//   virtual void resolve(ReactorObjectBase ro) = 0;
// }
//
// template<typename O, typename I>
// class ReactorObject : public ReactorObjectBase {
// public:
//   void resolve(ReactorObjectBase ro) {
//     rsolve((ReactorObject<O,I>) ro);
//   }
//
//   void resolve(ReactorObject<O,I>& ro) {
//       ro.act<O::Bases>(this)...;
//       ro.solve(this);
//   }
//   void solve(ReactorObject<O,I>& ro) {
//       ro.act<O::Bases>(this)...;
//   }
// }
//
// ReactObject<Offers<A, B, C>, Interest<X, Y, Z> > ro;
//
// ReactorObject<Offers<A, B, C>, Interest<X, Y, Z> > rotor;
// ReactionerObject<Offers<A, B, C>, Interest<X, Y, Z> > rotiner;
//
// rotor.resolve(rotiner);
//
// // rotor.solve(rotiner);
// // rotor.act(rotiner);
// // rotiner.act(rotor);
//
// template <typename IData>
// struct InteractionEvent {
//   IData data;
//   ReactorObject rotor;
//   ReactionerObject rotiner;
// };
//
// template<typename T>
// class GeneralCosa {
//   template<typename V = T>
//   void hazCosa(Thing<V> cosa) {
//
//   }
// };
//
// template<typename ...Ts>
// class CoverCosa : public GeneralCosa<Ts>... {
//     void hazCosas(Things<Ts...> cosas) {
//         (this->hazCosa<Ts>(cosas.get<Ts>()), ...);
//     }
// };
//
// class CosaEspecificaA : public CoverCosa<int,double> {
//   // void hazCosa<int>(Thing<int> cosa) {
//   //   printf("Mi cosa tiene un entero %d\n", cosa.get<int>());
//   // }
// };
//
// class CosaEspecificaB : public CoverCosa<int,double> {
//   // void hazCosa<int>(Thing<double> cosa) {
//   //   printf("Mi cosa tiene un double que no le importa a nadie\n");
//   // }
// }
//
// TFL<CoverCosa<int,double>> lista = {a, b}



// -------------------

// template<typename T, typename ...Ts>
// class Things : public Things<T>, public Things<Ts...> {
//   template <typename U>
//   U get() {
//     return (this->Things<U>::get());
//   }
// };
//
// template<typename T>
// class Things {
// public:
//   template<typename V = T>
//   virtual void act(Waiter<V> a) {
//   }
//
//   template<typename V = T>
//   V get() {
//       return val;
//   }
// private:
//   T val;
// };
//
// class B : public CoverCosa<int, double, long, float>,  RealCosa<int>{
//   template<>
//   void act(Waiter<int> a) {
//     a.react(this.get<int>());
//   }
// };
//
// class C : public CoverCosa<int, double, long, float> {
//   template<>
//   void act(Waiter<double> a) {
//     a.react(this.get<double>());
//   }
//   template<>
//   void act(Waiter<double> a) {
//     a.react(this.get<long>());
//   }
// };
//
// class A : public Waiter<int, double, long, float> {
//   void react(int cosa) {
//     printf("int\n");
//   }
//   void react(double cosa) {
//     printf("double\n");
//   }
//   void react(long cosa) {
//     printf("long\n");
//   }
//   void react(float cosa) {
//     printf("float\n");
//   }
// }
//
// A<int, double, long, float>
//
// B<int>
// C<double, long>
//
// X = warper<int,double, long, float>(B);
// Z = wraper<int,double, long, float>(C);
//
// // A reacciona POR DEFECTO a todos los tipos.
// A.hazCosas(X); -> print int64_t
// A.hazCosas(Z); -> print double, print long
// -----------------------------------------------


// template<typename T, typename ...Ts>
// class Things : public Things<T>, public Things<Ts...> {
//   template <typename U>
//   U get() {
//     return (this->Things<U>::get());
//   }
// };
//
// template<typename T>
// class Things {
// public:
//   template<typename V = T>
//   virtual void act(Waiter<V> a) {
//   }
//
//   template<typename V = T>
//   V get() {
//       return val;
//   }
// private:
//   T val;
// };

template<typename T, typename ...Ts>
class Things;

template<typename T>
class Things<T>;

template<typename ...Ts>
class Waiter : public Waiter<Ts>... {
public:
  void hazCosas(Things<Ts...>*  cosas) {
    //std::initializer_list<int>{ (reactor->act(std::shared_ptr<WeakAvatarEntityContainer<Bases> >(rObject)), 0)... };
      std::initializer_list<int>{(cosas->act((Waiter<Ts>*)this), 0)... };
    //(this->hazCosa<Ts>(cosas.get<Ts>()), ...);
  }
};

template<typename T>
class Waiter<T> {
public:
    virtual void react(T) = 0;
};

template<typename T, typename ...Ts>
class Things : public Things<T>, public Things<Ts...> {
public:
  Things(T val, Ts... vals) : Things<T>(val), Things<Ts...>(vals...) {}

  template <typename U>
  U get() {
    return (this->Things<U>::get());
  }

  template <typename U>
  void act(Waiter<U>* w) {
    printf("NONAINO\n");fflush(stdout);
    this->Things<U>::act(w);
  }
};

template<typename T>
class Things<T> {
public:
  Things() : val(), sa(&noAct) {}
  Things(T val) : val(val), sa(&noAct) {}

  template<typename V = T>
  V get() {
      return val;
  }

  void act(Waiter<T>* w) {
    printf("MIDNAI\n");fflush(stdout);
    sa(this, w);
  }
protected:
  using subAct = void (*)(void*, Waiter<T>*);
  void setAct(subAct sa) {
    this->sa = sa;
  }

private:
  static void noAct(void*, Waiter<T>*) {printf("NONAI\n");fflush(stdout);}
  subAct sa;
  T val;
};

class A : public Waiter<int, double, long, float> {
public:
  virtual void react(int val) {
    printf("int %d\n", val);fflush(stdout);
  }
  virtual void react(double val) {
    printf("double %lf\n", val);fflush(stdout);
  }
  virtual void react(long val) {
    printf("long %d\n", val);fflush(stdout);
  }
  virtual void react(float val) {
    printf("float %f\n", val);fflush(stdout);
  }
};

class BThing : public Things<int, double, long, float> {
public:
  BThing(int val) : Things<int, double, long, float>(val,0.0,0l,0.0f) {
    this->Things<int>::setAct(&actI);
  }
  static void actI(void* self, Waiter<int>* w) {
    printf("DALE B int\n");fflush(stdout);
    w->react(((BThing*)self)->get<int>());
  }
};

class CThing : public Things<int, double, long, float> {
public:
  CThing(double dval, long lval) : Things<int, double, long, float>(0,dval,lval,0.0f) {
    this->Things<double>::setAct(&actD);
    this->Things<long>::setAct(&actL);
  }

  static void actD(void* self, Waiter<double>* w) {
    printf("DALE C double\n");fflush(stdout);
    w->react(((CThing*)self)->get<double>());
  }

  static void actL(void* self, Waiter<long>* w) {
    printf("DALE C long\n");fflush(stdout);
    w->react(((CThing*)self)->get<long>());
  }
};

// -------------------
//
// Se proponen dos sisteman de resolución de interacciones:
// - Maestro/Esclavo (Actual).
// - Todos contra todos.

// ------------------------ WIP 3 END ---------------------------- //
// ------------------------ WIP 4 The good ---------------------------- //

// class ReactObjectDeVerdaDeLaGuena {};
//
// template <typename ...Ts>
// class ReactObjectCocreto : public ReactObjectDeVerdaDeLaGuena, public ReactObjectCocreto<Ts>... {};
//
// template <typename T>
// class ReactObjectCocreto<T> {
// public:
//   T get() {return val;}
//
//   T val;
// };
//
// // What you need is dynamic_cast. In its pointer form, it will return a null pointer if the cast cannot be performed:
// //
// // if( Moveable* moveable_john = dynamic_cast< Moveable* >( &John ) )
// // {
// //     // do something with moveable_john
// // }
//
// class A : public ReactObjectCocreto<int, double> {
// public:
//   void react(ReactObjectDeVerdaDeLaGuena *b) {
//
//     if (ReactObjectCocreto<float>* bfloat = dynamic_cast<ReactObjectCocreto<float>*>(b)) {
//       printf("Float: %f\n", bflot->get());
//     } else if (ReactObjectCocreto<long>* blong = dynamic_cast<ReactObjectCocreto<long>*>(b)) {
//       printf("Long: %ld\n", blong->get());
//     }
//   }
// };
//
// class B : public ReactObjectCocreto<float, long> {
// public:
//   void react(ReactObjectDeVerdaDeLaGuena *b) {
//     if (ReactObjectCocreto<int>* bint = dynamic_cast<ReactObjectCocreto<int>*>(b)) {
//       printf("Int: %d\n", bint->get());
//     } else if (ReactObjectCocreto<double>* bdouble = dynamic_cast<ReactObjectCocreto<double>*>(b)) {
//       printf("Double: %lf\n", bdouble->get());
//     }
//   }
// };
//
// struct WIP4A {
//     virtual ~WIP4A() {}
//     virtual void print() {
//       printf("Soy A.\n");
//     }
// };
//
// struct WIP4B : WIP4A {
//   virtual void print() {
//     printf("Soy B.\n");
//   }
//   int get() {return 42;}
// };
//
// struct WIP4C : WIP4A {
//   virtual void print() {
//     printf("Soy C.\n");
//   }
//   double get() {return 4.2;}
// };

// ------------------------ WIP 4 END ---------------------------- //
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
//  optional_variant<Sphere, Ray> a = Sphere{};
//  optional_variant<Sphere, Box, Ray> b = parse_optional_variant<optional_variant<Sphere, Ray>, Sphere, Box, Ray>(a);
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
    printf("time: %lld, point: %lf, %lf, %lf\n", ie.data.time, ie.data.point.x, ie.data.point.y, ie.data.point.z);fflush(stdout);
  }

  printf("WIP 3\n");fflush(stdout);

  A* a = new A();
  BThing* b = new BThing{42};
  CThing* c = new CThing{42.0, 7};

  a->hazCosas(b);
  a->hazCosas(c);

  // printf("WIP 4\n");fflush(stdout);
  //
  // A *a = new A;
  // B *b = new B;
  //
  // printf("A react to B...\n");fflush(stdout);
  // a->react(b);
  //
  // printf("B react to A...\n");fflush(stdout);
  // b->react(a);
  //
  // std::unordered_map<std::type_index, std::string> type_names;
  //
  // type_names[std::type_index(typeid(int))] = "int";
  // type_names[std::type_index(typeid(double))] = "double";
  // type_names[std::type_index(typeid(WIP4A))] = "A";
  // type_names[std::type_index(typeid(WIP4B))] = "B";
  // type_names[std::type_index(typeid(WIP4C))] = "C";
  //
  // int i;
  // double d;
  // WIP4A a;
  //
  // // note that we're storing pointer to type A
  // std::unique_ptr<WIP4A> b(new WIP4B);
  // std::unique_ptr<WIP4A> c(new WIP4C);
  //
  // std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
  // std::cout << "d is " << type_names[std::type_index(typeid(d))] << '\n';
  // std::cout << "a is " << type_names[std::type_index(typeid(a))] << '\n';
  // std::cout << "*b is " << type_names[std::type_index(typeid(*b))] << '\n';
  // std::cout << "*c is " << type_names[std::type_index(typeid(*c))] << '\n';
  //
  // b->print();
  // c->print();
  //
  // WIP4B* bb = dynamic_cast<WIP4B*>(b.get());
  // WIP4C* cc = dynamic_cast<WIP4C*>(c.get());
  // i = bb->get();
  // printf("i: %d\n", i);
  // d = cc->get();
  // printf("d: %lf\n", d);

  return 0;
}
