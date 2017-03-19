#include "gtest/gtest.h"

#include <memory>

#include <forward_list>

#include "ZBE/core/entities/adaptorentities/AvatarEntity.h"
#include "ZBE/core/entities/adaptors/Adaptor.h"

class DummyAvatarA {
public:
	using Base = void;
  virtual ~DummyAvatarA() {}
  int getValueA() {return (17);}
};

class DummyAvatarB : public DummyAvatarA {
public:
	using Base = DummyAvatarA;
  virtual ~DummyAvatarB() {}
  int getValueB() {return (37);}
};

class DummyAvatarC : public DummyAvatarB {
public:
	using Base = DummyAvatarB;
  virtual ~DummyAvatarC() {}
  int getValueC() {return (42);}
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

  	DummyAvatarC dacOriginal;

    std::shared_ptr<DummyAdaptor> a(new DummyAdaptor);
    a->setAvatar(&dacOriginal);
    aeab.setAdaptor(a);
    aefb.setAvatar(&dacOriginal);

    std::forward_list<zbe::AvatarEntity<DummyAvatarA>*> DAList;

    DAList.push_front(&aeab);
    DAList.push_front(&aefb);

  	auto it = DAList.begin();

  	DummyAvatarA* daa;
  	DummyAvatarB* dab;
  	DummyAvatarC* dac;

  	(*it)->assignAvatar(&daa);

    EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

  	it++;
		(*it)->assignAvatar(&daa);
  	EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

    zbe::AvatarEntity<DummyAvatarA>* pA_aeb = &aeab;
  	zbe::AvatarEntity<DummyAvatarB>* pB_aeb = &aeab;
  	zbe::AvatarEntity<DummyAvatarC>* pC_aeb = &aeab;

  	pA_aeb->assignAvatar(&daa);
    pB_aeb->assignAvatar(&dab);
    pC_aeb->assignAvatar(&dac);
  	EXPECT_EQ(17, daa->getValueA()) << "Must return 17";
  	EXPECT_EQ(37, dab->getValueB()) << "Must return 37";
  	EXPECT_EQ(42, dac->getValueC()) << "Must return 42";


    zbe::AvatarEntityAdapted<DummyAvatarA>* pA_aeab = &aeab;
  	zbe::AvatarEntityAdapted<DummyAvatarB>* pB_aeab = &aeab;
  	zbe::AvatarEntityAdapted<DummyAvatarC>* pC_aeab = &aeab;

  	pA_aeab->assignAvatar(&daa);
    pB_aeab->assignAvatar(&dab);
    pC_aeab->assignAvatar(&dac);
  	EXPECT_EQ(17, daa->getValueA()) << "Must return 17";
  	EXPECT_EQ(37, dab->getValueB()) << "Must return 37";
  	EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    zbe::AvatarEntityFixed<DummyAvatarA>* pA_aefb = &aefb;
  	zbe::AvatarEntityFixed<DummyAvatarB>* pB_aefb = &aefb;
  	zbe::AvatarEntityFixed<DummyAvatarC>* pC_aefb = &aefb;

  	pA_aefb->assignAvatar(&daa);
    pB_aefb->assignAvatar(&dab);
    pC_aefb->assignAvatar(&dac);
  	EXPECT_EQ(17, daa->getValueA()) << "Must return 17";
  	EXPECT_EQ(37, dab->getValueB()) << "Must return 37";
  	EXPECT_EQ(42, dac->getValueC()) << "Must return 42";
}
