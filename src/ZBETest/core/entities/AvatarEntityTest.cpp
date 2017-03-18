#include "gtest/gtest.h"

#include <memory>

#include <forward_list>

#include "ZBE/core/entities/adaptorentities/AvatarEntity.h"
#include "ZBE/core/entities/adaptors/Adaptor.h"

class DummyAvatarA {
public:
	using Base = void;
  virtual ~DummyAvatarA() {}
  virtual int getValue() = 0;
};

class DummyAvatarB : public DummyAvatarA {
public:
	using Base = DummyAvatarA;
  virtual ~DummyAvatarB() {}
  virtual int getValue() {return (37);}
};

class DummyAvatarC : public DummyAvatarB {
public:
	using Base = DummyAvatarB;
  virtual ~DummyAvatarC() {}
  int getValue() {return (42);}
};

class DummyAdaptor : public zbe::Adaptor<DummyAvatarC> {
public:
  DummyAdaptor(const DummyAdaptor&) = delete;
  void operator=(const DummyAdaptor&) = delete;

  DummyAdaptor() : c(nullptr) {}
  void setAvatar(DummyAvatarC* c) {this->c = c;}
  DummyAvatarC* getAvatar() {return (c);}
private:
  DummyAvatarC* c;
};

TEST (AvatarEntity, AvatarEntity) {
    zbe::AvatarEntityAdapted<DummyAvatarC> aeab;
    zbe::AvatarEntityFixed<DummyAvatarC> aefb;

  	DummyAvatarC* b(new DummyAvatarC);

    std::shared_ptr<DummyAdaptor> a(new DummyAdaptor);
    a->setAvatar(b);
    aeab.setAdaptor(a);
    aefb.setAvatar(b);

    std::forward_list<zbe::AvatarEntity<DummyAvatarA>*> DAList;

    DAList.push_front(&aeab);
    DAList.push_front(&aefb);

  	auto it = DAList.begin();

    EXPECT_EQ(42, (*it)->getAvatar()->getValue()) << "Must return 42";

  	it++;

  	EXPECT_EQ(42, (*it)->getAvatar()->getValue()) << "Must return 42";
}

