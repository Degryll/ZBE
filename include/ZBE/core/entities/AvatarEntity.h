/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AvatarEntity.h
 * @since 2017-03-15
 * @date 2017-03-15
 * @author Batis Degryll Ludo
 * @brief Entity that can be seen as an specific Avatar.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARENTITY_H_
#define ZBE_CORE_ENTITIES_AVATARENTITY_H_

#include <iostream>

#include <memory>
#include <type_traits>
#include <typeinfo>

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/entities/Adaptor.h"

namespace zbe{

template<typename T>
class AvatarEntity;

template<typename T>
class AvatarEntity : virtual public Covariance_Traits<AvatarEntity<typename T::Base>,  typename T::Base>::Type {
public:
  virtual ~AvatarEntity(){}
  virtual void assignAvatar(T**) = 0;
};

template<typename T>
class AvatarEntityAdapted :
            virtual public AvatarEntity<T>,
            public Covariance_Traits<AvatarEntityAdapted<typename T::Base>,  typename T::Base>::Type {
public:
  AvatarEntityAdapted() : a() {}
  AvatarEntityAdapted(std::shared_ptr< Adaptor<T> > adaptor) : a(adaptor) {
    this->template _setAdaptor<typename T::Base>();
  }
  virtual ~AvatarEntityAdapted(){}
  void assignAvatar(T** avatarPtr) {
    (*avatarPtr) = a->getAvatar();
  }

  virtual void setAdaptor(std::shared_ptr< Adaptor<T> > adaptor){
    this->a = adaptor;
    this->template _setAdaptor<typename T::Base>();
  }

private:

  template <typename B>
  void _setAdaptor() {_setAdaptor(TypeGimmick<B>());}

  template<typename B>
  void _setAdaptor(TypeGimmick<B>) {AvatarEntityAdapted<B>::setAdaptor(a);}

  void _setAdaptor(TypeGimmick<void>) {}

  std::shared_ptr< Adaptor<T> > a;
};

template<typename T>
class AvatarEntityFixed :
                virtual public AvatarEntity<T>,
                virtual public Covariance_Traits<AvatarEntityFixed<typename T::Base>,  typename T::Base>::Type{
public:
  AvatarEntityFixed(const AvatarEntityFixed&) = delete;
  void operator=(const AvatarEntityFixed&) = delete;

  AvatarEntityFixed() : a(nullptr) { }
  AvatarEntityFixed(T* avatar) : a(avatar) {
    this->template _setAvatar<typename T::Base>();
  }

  virtual ~AvatarEntityFixed(){
    this->template _deleteAvatar<typename T::Base>();
  }

  void assignAvatar(T** avatarPtr) {
    (*avatarPtr) = a;
  }

  void setAvatar(T* avatar) {
    this->template _deleteAvatar<typename T::Base>();
    this->a = avatar;
    this->template _setAvatar<typename T::Base>();
  }

private:

  template <typename B>
  void _setAvatar() {_setAvatar(TypeGimmick<B>());}

  template<typename B>
  void _setAvatar(TypeGimmick<B>) {AvatarEntityFixed<B>::setAvatar(a);}

  void _setAvatar(TypeGimmick<void>) {}

  template <typename B>
  void _deleteAvatar() {_deleteAvatar(TypeGimmick<B>());}

  template<typename B>
  void _deleteAvatar(TypeGimmick<B>) {}

  void _deleteAvatar(TypeGimmick<void>) {delete a;}

  T* a = nullptr;
};

template <typename T, typename A>
void setAdaptor(std::shared_ptr<T> t, std::shared_ptr<zbe::Adaptor<A> > a) {
    std::shared_ptr<zbe::AvatarEntityAdapted<A> > aeaA = t;
    aeaA->setAdaptor(a);
}

template <typename T, typename A>
void setAvatar(std::shared_ptr<T> t, A* a) {
    std::shared_ptr<zbe::AvatarEntityFixed<A> > aefA = t;
    aefA->setAvatar(a);
}

/** \brief Agroupation of an undetermined number of types
 */
template <typename... Bases>
class AvatarEntityContainer : public AvatarEntityContainer<Bases>... {
public:
  template<typename T>
  AvatarEntityContainer(T aet): AvatarEntityContainer<Bases>(aet)... {}

  ~AvatarEntityContainer(){}
};

template <typename T>
class AvatarEntityContainer<T> {
public:
  //AvatarEntityContainer<T>(const AvatarEntityContainer<T>&) = delete;
  //void operator=(const AvatarEntityContainer<T>&) = delete;

  AvatarEntityContainer(AvatarEntityContainer<T>* aec): aet(aec->get()){}
  //AvatarEntityContainer(AvatarEntity<T>* aet): aet(aet){}
  AvatarEntityContainer(std::shared_ptr<AvatarEntityContainer<T> > aec): aet(aec->get()){}
  AvatarEntityContainer(std::shared_ptr<AvatarEntity<T> > aet): aet(aet){}

  ~AvatarEntityContainer(){}

  std::shared_ptr<AvatarEntity<T> > get() {return aet;}

private:
  std::shared_ptr<AvatarEntity<T> > aet;
};

template <>
class AvatarEntityContainer<void> {
public:
  AvatarEntityContainer() {}
  ~AvatarEntityContainer(){}

};

template <typename T, typename A>
void assignAvatar(T* t, A **a) {
    zbe::AvatarEntity<A>* aeA = t;
    aeA->assignAvatar(a);
}

template <typename T, typename A>
void assignAvatar(std::shared_ptr<T> t, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = t;
    aeA->assignAvatar(a);
}

template <typename A>
void assignAvatar(AvatarEntityContainer<A>* aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

template <typename A>
void assignAvatar(std::shared_ptr<AvatarEntityContainer<A> > aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

//template <typename ...A>
//class Avatarable {
//public:
//    using AECBases = AvatarEntityContainer<A...>;
//    Avatarable(AvatarEntity<A>*... a) : aec(a...){}
//    const AECBases& getAvatarEntityContainer(){
//        return aec;
//    }
//private:
//    AvatarEntityContainer<A...> aec;
//};

template <typename T, typename ...Bases>
void wrapAEC(std::shared_ptr<AvatarEntityContainer<Bases...> >* aec, std::shared_ptr<T> src) {
    *aec = std::make_shared<AvatarEntityContainer<Bases...> >(src);
}


}  // namespace ZBE

#endif  // ZBE_CORE_ENTITIES_AVATARENTITY_H_
