#include "gtest/gtest.h"

#include <memory>

#include <forward_list>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Adaptor.h"

// First branch classes

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

// Second branch classes

class DummyAvatarX {
public:
    using Base = void;
  virtual ~DummyAvatarX() {}
  int getValueX() {return (71);}
};

class DummyAvatarY : public DummyAvatarX {
public:
    using Base = DummyAvatarX;
  virtual ~DummyAvatarY() {}
  int getValueY() {return (73);}
};

class DummyAvatarZ : public DummyAvatarY {
public:
    using Base = DummyAvatarY;
  virtual ~DummyAvatarZ() {}
  int getValueZ() {return (24);}
};

// Final classes
class CZAdaptedFixedEntity   : public zbe::AvatarEntityAdapted<DummyAvatarC>, public zbe::AvatarEntityFixed<DummyAvatarZ>   {};
class CZAdaptedAdaptedEntity : public zbe::AvatarEntityAdapted<DummyAvatarC>, public zbe::AvatarEntityAdapted<DummyAvatarZ> {};
class CZFixedFixedEntity     : public zbe::AvatarEntityFixed<DummyAvatarC>,   public zbe::AvatarEntityFixed<DummyAvatarZ>   {};

class DummyAdaptorC : public zbe::Adaptor<DummyAvatarC> {
public:
  DummyAdaptorC(const DummyAdaptorC&) = delete;
  void operator=(const DummyAdaptorC&) = delete;

  DummyAdaptorC() : c(nullptr) {}
  void setAvatar(DummyAvatarC* c) {this->c = c;}
  DummyAvatarC* getAvatar() {return (c);}
private:
  DummyAvatarC* c;
};

class DummyAdaptorZ : public zbe::Adaptor<DummyAvatarZ> {
public:
  DummyAdaptorZ(const DummyAdaptorZ&) = delete;
  void operator=(const DummyAdaptorZ&) = delete;

  DummyAdaptorZ() : z(nullptr) {}
  void setAvatar(DummyAvatarZ* z) {this->z = z;}
  DummyAvatarZ* getAvatar() {return (z);}
private:
  DummyAvatarZ* z;
};

TEST (AvatarEntity, AvatarEntityContainer_usage) {
}

TEST (AvatarEntity, Usage) {
    zbe::AvatarEntityAdapted<DummyAvatarC> aeab;
    zbe::AvatarEntityFixed<DummyAvatarC> aefb;

    DummyAvatarC* dacOriginal = new DummyAvatarC();

    std::shared_ptr<DummyAdaptorC> a(new DummyAdaptorC);
    a->setAvatar(dacOriginal);
    aeab.setAdaptor(a);
    aefb.setAvatar(dacOriginal);

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

    EXPECT_EQ(17, dab->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dab->getValueB()) << "Must return 37";

    EXPECT_EQ(17, dac->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dac->getValueB()) << "Must return 37";
    EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    pA_aeb = &aefb;
    pB_aeb = &aefb;
    pC_aeb = &aefb;

    pA_aeb->assignAvatar(&daa);
    pB_aeb->assignAvatar(&dab);
    pC_aeb->assignAvatar(&dac);

    EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

    EXPECT_EQ(17, dab->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dab->getValueB()) << "Must return 37";

    EXPECT_EQ(17, dac->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dac->getValueB()) << "Must return 37";
    EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    // Probably we never use it this way, but we can
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

TEST (AvatarEntity, TwoBranches) {
    DummyAvatarC* originalC = new DummyAvatarC();
    DummyAvatarC* originalC2 = new DummyAvatarC();
    DummyAvatarZ* originalZ = new DummyAvatarZ();
    DummyAvatarZ* originalZ2 = new DummyAvatarZ();
    DummyAvatarZ* originalZ3 = new DummyAvatarZ();

    std::shared_ptr<DummyAdaptorC> ac(new DummyAdaptorC);
    ac->setAvatar(originalC2);

    std::shared_ptr<DummyAdaptorZ> az(new DummyAdaptorZ);
    az->setAvatar(originalZ2);

    CZAdaptedFixedEntity czafe;
    zbe::AvatarEntityAdapted<DummyAvatarC>* aeap = &czafe;
    zbe::AvatarEntityFixed<DummyAvatarZ>*   aefp = &czafe;
    aeap->setAdaptor(ac);
    aefp->setAvatar(originalZ);

    CZAdaptedAdaptedEntity czaae;
    zbe::AvatarEntityAdapted<DummyAvatarC>* aeacp = &czaae;
    zbe::AvatarEntityAdapted<DummyAvatarZ>* aeazp = &czaae;
    aeacp->setAdaptor(ac);
    aeazp->setAdaptor(az);

    CZFixedFixedEntity czffe;
    zbe::AvatarEntityFixed<DummyAvatarC>* aefcp = &czffe;
    zbe::AvatarEntityFixed<DummyAvatarZ>* aefzp = &czffe;
    aefcp->setAvatar(originalC);
    aefzp->setAvatar(originalZ3);

    DummyAvatarA* daa;
    DummyAvatarB* dab;
    DummyAvatarC* dac;
    DummyAvatarX* dax;
    DummyAvatarY* day;
    DummyAvatarZ* daz;

    zbe::AvatarEntity<DummyAvatarA>* pA_aeb;
    zbe::AvatarEntity<DummyAvatarB>* pB_aeb;
    zbe::AvatarEntity<DummyAvatarC>* pC_aeb;
    zbe::AvatarEntity<DummyAvatarX>* pX_aeb;
    zbe::AvatarEntity<DummyAvatarY>* pY_aeb;
    zbe::AvatarEntity<DummyAvatarZ>* pZ_aeb;

    pA_aeb = &czafe;
    pB_aeb = &czafe;
    pC_aeb = &czafe;
    pX_aeb = &czafe;
    pY_aeb = &czafe;
    pZ_aeb = &czafe;

    pA_aeb->assignAvatar(&daa);
    pB_aeb->assignAvatar(&dab);
    pC_aeb->assignAvatar(&dac);
    pX_aeb->assignAvatar(&dax);
    pY_aeb->assignAvatar(&day);
    pZ_aeb->assignAvatar(&daz);

    EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

    EXPECT_EQ(17, dab->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dab->getValueB()) << "Must return 37";

    EXPECT_EQ(17, dac->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dac->getValueB()) << "Must return 37";
    EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    EXPECT_EQ(71, dax->getValueX()) << "Must return 71";

    EXPECT_EQ(71, day->getValueX()) << "Must return 71";
    EXPECT_EQ(73, day->getValueY()) << "Must return 73";

    EXPECT_EQ(71, daz->getValueX()) << "Must return 71";
    EXPECT_EQ(73, daz->getValueY()) << "Must return 73";
    EXPECT_EQ(24, daz->getValueZ()) << "Must return 24";

    pA_aeb = &czaae;
    pB_aeb = &czaae;
    pC_aeb = &czaae;
    pX_aeb = &czaae;
    pY_aeb = &czaae;
    pZ_aeb = &czaae;

    pA_aeb->assignAvatar(&daa);
    pB_aeb->assignAvatar(&dab);
    pC_aeb->assignAvatar(&dac);
    pX_aeb->assignAvatar(&dax);
    pY_aeb->assignAvatar(&day);
    pZ_aeb->assignAvatar(&daz);

    EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

    EXPECT_EQ(17, dab->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dab->getValueB()) << "Must return 37";

    EXPECT_EQ(17, dac->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dac->getValueB()) << "Must return 37";
    EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    EXPECT_EQ(71, dax->getValueX()) << "Must return 71";

    EXPECT_EQ(71, day->getValueX()) << "Must return 71";
    EXPECT_EQ(73, day->getValueY()) << "Must return 73";

    EXPECT_EQ(71, daz->getValueX()) << "Must return 71";
    EXPECT_EQ(73, daz->getValueY()) << "Must return 73";
    EXPECT_EQ(24, daz->getValueZ()) << "Must return 24";

    pA_aeb = &czffe;
    pB_aeb = &czffe;
    pC_aeb = &czffe;
    pX_aeb = &czffe;
    pY_aeb = &czffe;
    pZ_aeb = &czffe;

    pA_aeb->assignAvatar(&daa);
    pB_aeb->assignAvatar(&dab);
    pC_aeb->assignAvatar(&dac);
    pX_aeb->assignAvatar(&dax);
    pY_aeb->assignAvatar(&day);
    pZ_aeb->assignAvatar(&daz);

    EXPECT_EQ(17, daa->getValueA()) << "Must return 17";

    EXPECT_EQ(17, dab->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dab->getValueB()) << "Must return 37";

    EXPECT_EQ(17, dac->getValueA()) << "Must return 17";
    EXPECT_EQ(37, dac->getValueB()) << "Must return 37";
    EXPECT_EQ(42, dac->getValueC()) << "Must return 42";

    EXPECT_EQ(71, dax->getValueX()) << "Must return 71";

    EXPECT_EQ(71, day->getValueX()) << "Must return 71";
    EXPECT_EQ(73, day->getValueY()) << "Must return 73";

    EXPECT_EQ(71, daz->getValueX()) << "Must return 71";
    EXPECT_EQ(73, daz->getValueY()) << "Must return 73";
    EXPECT_EQ(24, daz->getValueZ()) << "Must return 24";
}
