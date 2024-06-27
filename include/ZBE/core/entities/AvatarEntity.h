/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AvatarEntity.h
 * @since 2017-03-15
 * @date 2018-03-06
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

#include "ZBE/core/system/system.h"

namespace zbe{

/** \brief Forward declaration for use in Covariance_Traits.
 */
template<typename T>
class AvatarEntity;


/** \brief Entity that can be seen as an specific Avatar.
 */
template<typename T>
class AvatarEntity : virtual public Covariance_Traits<AvatarEntity<typename T::Base>,  typename T::Base>::Type {
public:

  /** \brief Virtual destructor
   */
  virtual ~AvatarEntity() {}

  /** \brief Return the Entity's Avatar
   *  \param avatarPtr Direction of the pointer where the avatar will be stored.
   */
  virtual void assignAvatar(T**) = 0;
};

/** \brief Avatar Entity that uses an adaptor to generate de avatar from the entity
 */
template<typename T>
class AvatarEntityAdapted :
            virtual public AvatarEntity<T>,
            public Covariance_Traits<AvatarEntityAdapted<typename T::Base>,  typename T::Base>::Type {
public:

  /** \brief [DEPRECATED?]
   */
  AvatarEntityAdapted() : a() {}

  /** \brief Construct an Avatar Entity given the adaptor.
   */
  AvatarEntityAdapted(std::shared_ptr< Adaptor<T> > adaptor) : a(adaptor) {
    this->template _setAdaptor<typename T::Base>();
  }

  /** \brief Empty Destructor
   */
  virtual ~AvatarEntityAdapted() {}

  /** \brief Return the Entity's Avatar
   *  \param avatarPtr Direction of the pointer where the avatar will be stored.
   */
  void assignAvatar(T** avatarPtr) {
    (*avatarPtr) = a->getAvatar();
  }

  /** \brief Set the adaptor that will be used to retrieve the Entity's Avatar.
   *  \param adaptor The adaptor.
   */
  virtual void setAdaptor(std::shared_ptr< Adaptor<T> > adaptor) {
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

/** \brief Avatar Entity with a fixed avatar
 */
template<typename T>
class AvatarEntityFixed :
                virtual public AvatarEntity<T>,
                virtual public Covariance_Traits<AvatarEntityFixed<typename T::Base>,  typename T::Base>::Type{
public:
  AvatarEntityFixed(const AvatarEntityFixed&) = delete;  //<! Avoid copy
  void operator=(const AvatarEntityFixed&) = delete;  //<! Avoid copy

  /** \brief [DEPRECATED?]
   */
  AvatarEntityFixed() : a(nullptr) { }

  /** \brief Construct an Avatar Entity given the avatar.
   */
  AvatarEntityFixed(T* avatar) : a(avatar) {
    this->template _setAvatar<typename T::Base>();
  }

  /** \brief On destruction, deletes the avatar
   */
  virtual ~AvatarEntityFixed() {
    this->template _deleteAvatar<typename T::Base>();
  }

  /** \brief Return the Entity's Avatar
   *  \param avatarPtr Direction of the pointer where the avatar will be stored.
   */
  void assignAvatar(T** avatarPtr) {
    (*avatarPtr) = a;
  }

  /** \brief Set the avatar that will be returned.
   *  \param avatqar The avatar.
   */
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


/** \brief A container of AvatarEntities. Used to group AvatarEntities.
 */
template <typename T, typename... Bases>
class AvatarEntityContainer : virtual public AvatarEntityContainer<T>,  virtual public AvatarEntityContainer<Bases>... {
public:

  /** \brief Builds an AvatarEntityContainer from an object that inherits all the needed types.
   */
  template<typename U>
  AvatarEntityContainer(U aet) : AvatarEntityContainer<T>(aet), AvatarEntityContainer<Bases>(aet)... {}

  /** \brief Builds an AvatarEntityContainer from a collection of shared_ptrs to all needed AvatarEntity types.
   */
  AvatarEntityContainer(std::shared_ptr<AvatarEntity<T> > aet, std::shared_ptr<AvatarEntity<Bases> >... aes): AvatarEntityContainer<T>(aet), AvatarEntityContainer<Bases>(aes)... {}

  /** \brief Empty Destructor
   */
  ~AvatarEntityContainer() {}
};

/** \brief An Avatar Entity Container of a single avatar type. This type can belong to an avatar hierarchy.
 */
template <typename T>
class AvatarEntityContainer<T> : virtual public AvatarEntityContainer<typename T::Base> {
public:

  /** \brief Builds an AvatarEntityContainer from a pointer to an AvatarEntityContainer of the specific type. This type can belong to an avatar hierarchy.
   */
  AvatarEntityContainer(AvatarEntityContainer<T>* aec) : AvatarEntityContainer<typename T::Base>(aec), aet(aec->get()) {}

  /** \brief Builds an AvatarEntityContainer from a shared_ptr to an AvatarEntityContainer of the specific type. This type can belong to an avatar hierarchy.
   */
  AvatarEntityContainer(std::shared_ptr<AvatarEntityContainer<T> > aec) : AvatarEntityContainer<typename T::Base>(aec), aet(aec->get()) {}

  /** \brief Builds an AvatarEntityContainer from a shared_ptr to an AvatarEntity of the specific type. This type can belong to an avatar hierarchy.
   */
  template <typename U = T>
  AvatarEntityContainer(std::shared_ptr<AvatarEntity<T> > aet, typename std::enable_if<!std::is_void<typename U::Base>::value>::type * = nullptr ) : aet(aet) {
    _setAE(aet);
  }

  /** \brief Builds an AvatarEntityContainer from a shared_ptr to an AvatarEntity of the specific type. This type will be the base type of its hierarchy.
   */
  template <typename U = T>
  AvatarEntityContainer(std::shared_ptr<AvatarEntity<T> > aet, typename std::enable_if<std::is_void<typename U::Base>::value, int>::type * = nullptr) : aet(aet) {}

  /** \brief Empty Destructor
   */
  ~AvatarEntityContainer() {}

  /** \brief Returns the contained AvatarEntity.
   *  \return The AvatarEntity.
   */
  std::shared_ptr<AvatarEntity<T> > const get() {return aet;}

protected:
    AvatarEntityContainer() : aet() {}
    void _setAE(std::shared_ptr<AvatarEntity<T> > _aet) {
        aet = _aet;
        AvatarEntityContainer<typename T::Base>::_setAE(_aet);
    }

private:
  std::shared_ptr<AvatarEntity<T> > aet;
};


/** \brief An Avatar Entity Container of no type. Base case.
 */
template <>
class AvatarEntityContainer<void> {
public:

  AvatarEntityContainer() {}  //<! Empty constructor
  AvatarEntityContainer(AvatarEntityContainer<void>*) {}  //<! Empty constructor
  AvatarEntityContainer(std::shared_ptr<AvatarEntityContainer<void> >) {}  //<! Empty constructor

  /** \brief Empty Destructor
   */
  ~AvatarEntityContainer() {}

protected:
    template<typename T>
    void _setAE(T) {}
};

/** \brief A container of AvatarEntities using weak pointers. Used to group AvatarEntities.
 * It's used when an Avatar, inside an AvatarEntity, stores other AvatarEntities that references to the parent entity.(Avoid shared_ptr circular reference)
 */
template <typename... Bases>
class WeakAvatarEntityContainer : virtual public WeakAvatarEntityContainer<Bases>... {
public:
  /** \brief Builds a WeakAvatarEntityContainer from an object that inherits all the needed types.
   */
  template<typename T>
  WeakAvatarEntityContainer(const T aet): WeakAvatarEntityContainer<Bases>(aet)... {}

  /** \brief Builds a WeakAvatarEntityContainer from a collection of shared_ptrs to all needed AvatarEntity types.
   */
  WeakAvatarEntityContainer(std::weak_ptr<AvatarEntity<Bases> >... aes): WeakAvatarEntityContainer<Bases>(aes)... {}

  /** \brief Empty Destructor
   */
  ~WeakAvatarEntityContainer() {}
};

/** \brief A Weak Avatar Entity Container of a single avatar type. This type can belong to an avatar hierarchy.
 */
template <typename T>
class WeakAvatarEntityContainer<T> : virtual public WeakAvatarEntityContainer<typename T::Base> {
public:

  /** \brief Builds a WeakAvatarEntityContainer from a shared_ptr to a WeakAvatarEntityContainer of the specific type. This type can belong to an avatar hierarchy.
   */
  WeakAvatarEntityContainer(std::shared_ptr<WeakAvatarEntityContainer<T> > waec) : WeakAvatarEntityContainer<typename T::Base>(waec), aet(waec->get()) {}

    /** \brief Builds a WeakAvatarEntityContainer from a shared_ptr to an AvatarEntityContainer of the specific type. This type can belong to an avatar hierarchy.
     */
  WeakAvatarEntityContainer(std::shared_ptr<AvatarEntityContainer<T> > aec) : WeakAvatarEntityContainer<typename T::Base>(aec), aet(aec->get()) {}

  /** \brief Builds a WeakAvatarEntityContainer from a shared_ptr to an AvatarEntity of the specific type. This type can belong to an avatar hierarchy.
   */
  template <typename U = T>
  WeakAvatarEntityContainer(std::weak_ptr<AvatarEntity<T> > aet, typename std::enable_if<!std::is_void<typename U::Base>::value>::type * = nullptr ) : aet(aet) {
    _setAE(aet);
  }

  /** \brief Builds a WeakAvatarEntityContainer from a shared_ptr to an AvatarEntity of the specific type. This type will be the base type of its hierarchy.
   */
  template <typename U = T>
  WeakAvatarEntityContainer(std::weak_ptr<AvatarEntity<T> > aet, typename std::enable_if<std::is_void<typename U::Base>::value, int>::type * = nullptr) : aet(aet) {}

  /** \brief Empty Destructor
   */
  ~WeakAvatarEntityContainer() {}

  /** \brief Returns the contained AvatarEntity.
   *  \return The AvatarEntity.
   */
  std::shared_ptr<AvatarEntity<T> > get() {return aet.lock();}

protected:
    WeakAvatarEntityContainer() : aet() {}
    void _setAE(std::weak_ptr<AvatarEntity<T> > _aet) {
        aet = _aet;
        WeakAvatarEntityContainer<typename T::Base>::_setAE(_aet);
    }
private:
  std::weak_ptr<AvatarEntity<T> > aet;
};

/** \brief A Weak Avatar Entity Container of no type. Base case.
 */
template <>
class WeakAvatarEntityContainer<void> {
protected:
    template<typename T>
    void _setAE(T) {}
public:
  WeakAvatarEntityContainer() {}  //<! Empty constructor
  WeakAvatarEntityContainer(const WeakAvatarEntityContainer<void>&) {}  //<! Empty constructor
  WeakAvatarEntityContainer(WeakAvatarEntityContainer<void>*) {}  //<! Empty constructor
  WeakAvatarEntityContainer(std::shared_ptr<WeakAvatarEntityContainer<void> >) {}  //<! Empty constructor
  WeakAvatarEntityContainer(std::shared_ptr<AvatarEntityContainer<void> >) {}  //<! Empty constructor

  /** \brief Empty Destructor
   */
  ~WeakAvatarEntityContainer() {}

};

/** \brief A helper function that set an adaptor of type "A" in an entity that inherits an undetermined amount of unrelated AvatarEntityAdapted<?>.
 * Avoid the need of an explicit type conversion.
 */
template <typename T, typename A>
void setAdaptor(std::shared_ptr<T> t, std::shared_ptr<zbe::Adaptor<A> > a) {
    std::shared_ptr<zbe::AvatarEntityAdapted<A> > aeaA = t;
    aeaA->setAdaptor(a);
}

/** \brief A helper function that set an avatar of type "A" in an entity that inherits a undetermined amount of unrelated AvatarEntityFixed<?>.
 * Avoid the need of an explicit type conversion.
 */
template <typename T, typename A>
void setAvatar(std::shared_ptr<T> t, A* a) {
    std::shared_ptr<zbe::AvatarEntityFixed<A> > aefA = t;
    aefA->setAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a pointer to an object of type "T" that, at least, inherits from AvatarEntity<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename T, typename A>
void assignAvatar(T* t, A **a) {
    zbe::AvatarEntity<A>* aeA = t;
    aeA->assignAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a shared_ptr to an object of type "T" that, at least, inherits from AvatarEntity<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename T, typename A>
void assignAvatar(std::shared_ptr<T> t, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = t;
    aeA->assignAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a pointer to an object that, at least, inherits from AvatarEntityContainer<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename A>
void assignAvatar(AvatarEntityContainer<A>* aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a shared_ptr to an object that, at least, inherits from AvatarEntityContainer<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename A>
void assignAvatar(std::shared_ptr<AvatarEntityContainer<A> > aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a pointer to an object that, at least, inherits from WeakAvatarEntityContainer<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename A>
void assignAvatar(WeakAvatarEntityContainer<A>* aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

/** \brief A helper function that assings an avatar of type "A" from a shared_ptr to an object that, at least, inherits from WeakAvatarEntityContainer<A>.
 * Avoid the need of an explicit type conversion.
 */
template <typename A>
void assignAvatar(std::shared_ptr<WeakAvatarEntityContainer<A> > aec, A **a) {
    std::shared_ptr<zbe::AvatarEntity<A> > aeA = aec->get();
    aeA->assignAvatar(a);
}

/** \brief A helper function that builds an AvatarEntityContainer<Bases...> from a single shared_ptr to an object that inherits from all needed AvatarEntities.
 * Avoid the need of an explicit type conversion.
 */
template <typename T, typename ...Bases>
void wrapAEC(std::shared_ptr<AvatarEntityContainer<Bases...> >* aec, std::shared_ptr<T> src) {
    *aec = std::make_shared<AvatarEntityContainer<Bases...> >(src);
}

template <typename T>
using AE = AvatarEntity<T>;

template <typename T>
using AEFixed = AvatarEntityFixed<T>;

template <typename T>
using AEAdapted = AvatarEntityAdapted<T>;

template <typename ...Avatars>
using AEC = AvatarEntityContainer<Avatars...>;

template <typename ...Avatars>
using WAEC = WeakAvatarEntityContainer<Avatars...>;

}  // namespace ZBE

#endif  // ZBE_CORE_ENTITIES_AVATARENTITY_H_
