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

#include <memory>

#include "ZBE/core/entities/adaptors/Adaptor.h"

namespace zbe{

template<typename T>
class AvatarEntity;

template<typename T>
struct AvatarEntity_Traits {
  virtual ~AvatarEntity_Traits(){}
  using Type = AvatarEntity<T>;
};

template<>
struct AvatarEntity_Traits<void> {
  virtual ~AvatarEntity_Traits() {}
  struct Type {virtual ~Type() {}};
};

template<typename T>
class AvatarEntity : virtual public AvatarEntity_Traits<typename T::Base>::Type {
public:
  virtual ~AvatarEntity(){}
  virtual T* getAvatar() = 0;
};

template<typename T>
class AvatarEntityAdapted : virtual public AvatarEntity<T> {
public:
  AvatarEntityAdapted() : a() {}
  virtual ~AvatarEntityAdapted(){}
  virtual T* getAvatar() {
  	return (a->getAvatar());
  }

  virtual void setAdaptor(std::shared_ptr< Adaptor<T> > adaptor) {this->a = adaptor;}

private:
  std::shared_ptr< Adaptor<T> > a;
};

template<typename T>
class AvatarEntityFixed : virtual public AvatarEntity<T> {
public:
  virtual ~AvatarEntityFixed(){}
  virtual T* getAvatar() {return (a);}
  virtual void setAvatar(T* avatar) {this->a = avatar;}

private:
  T* a = nullptr;
};

}  // namespace ZBE

#endif  // ZBE_CORE_ENTITIES_AVATARENTITY_H_
