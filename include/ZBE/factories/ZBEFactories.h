/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.h
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */

#ifndef ZBE_FACTORIES_ZBEFACTORIES_H_
#define ZBE_FACTORIES_ZBEFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"
#include "ZBE/factories/implementations/entities/avatars/SimpleAnimSprtFtry.h"
#include "ZBE/factories/implementations/entities/avatars/BaseAvatarFtry.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/implementations/CustomAvatars.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/entities/builders/builders.h"

namespace zbe {

/** \brief Daemon capable of load all base factories.
 */
class ZBEAPI ZBEFactories : public Daemon {
public:
  ~ZBEFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    using namespace std::string_literals;
    using AnimList = TicketedForwardList<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> >;
    using AnimDrwr = BehaviorDmnFtry<AnimList, uint64_t, int64_t, double, Vector2D, Vector2D>;

    using ModelList = TicketedForwardList<MAvatar<uint64_t, double, double, Vector3D, Vector3D> >;
    using ModelDrwr = BehaviorDmnFtry<ModelList, uint64_t, double, double, Vector3D, Vector3D>;

    using SimpleSpriteList = TicketedForwardList<MAvatar<uint64_t, Vector2D, Vector2D> >;
    using SimpleSpriteDrwr = BehaviorDmnFtry<SimpleSpriteList, uint64_t, Vector2D, Vector2D>;

    using FloatAvtList = TicketedForwardList<SAvatar<float> >;
    using FloatAvtBhvr = BehaviorDmnFtry<FloatAvtList, float>;

    using V3DAvtList = TicketedForwardList<SAvatar<Vector3D> >;
    using V3DAvtBhvr = BehaviorDmnFtry<V3DAvtList, Vector3D>;

    using ThreeV3DAvtList = TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> >;
    using ThreeV3DAvtBhvr = BehaviorDmnFtry<ThreeV3DAvtList, Vector3D, Vector3D, Vector3D>;

    using PosVel3DAvtList = TicketedForwardList<MAvatar<Vector3D, Vector3D> >;
    using PosVel3DAvtBhvr = BehaviorDmnFtry<PosVel3DAvtList, Vector3D, Vector3D>;

    using TwoV3DAvtList = TicketedForwardList<MAvatar<Vector3D, Vector3D> >;
    using TwoV3DAvtBhvr = BehaviorDmnFtry<TwoV3DAvtList, Vector3D, Vector3D>;

    using LookAtAvtList = TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> >;
    using LookAtAvtBhvr = BehaviorDmnFtry<LookAtAvtList, Vector3D, Vector3D, Vector3D>;

    auto& factories = RsrcStore<Factory>::getInstance();
    for(int i = 0;i<100;i++) {
        factories.insert(std::to_string(i)+"Ftry"s , std::make_shared<SimpleGenericFtry<int> >(factories::listName));
    }
    // Builders
    factories.insert("Drawable2DAvtBldrFtry", std::make_shared<AvatarBldrFtry<uint64_t, int64_t, double, Vector2D, Vector2D>>());
    factories.insert("Drawable3DAvtBldrFtry", std::make_shared<AvatarBldrFtry<uint64_t, double,  double, Vector3D, Vector3D>>());
    factories.insert("DrawableSimple2DAvtBldrFtry", std::make_shared<AvatarBldrFtry<uint64_t, int64_t, double, Vector2D, Vector2D>>());
    factories.insert("V3DAvtBldrFtry", std::make_shared<AvatarBldrFtry<Vector3D> >());
    factories.insert("FloatAvtBldrFtry", std::make_shared<AvatarBldrFtry<float> >());

    factories.insert("TargetToDirAvtBldrFtry", std::make_shared<TargetToDirAvtBldrFtry>());
    factories.insert("PosTargetToPosDirAvtBldrFtry", std::make_shared<PosTargetToPosDirAvtBldrFtry>());
    factories.insert("DerivedCosVelAvtBldrFtry", std::make_shared<DerivedCosVelAvtBldrFtry>());
    factories.insert("DerivedPosMovingSphereAvtBldrFtry", std::make_shared<DerivedPosMovingSphereAvtBldrFtry>());
    factories.insert("LookAtToPitchAvtBldrFtry", std::make_shared<LookAtToPitchAvtBldrFtry>());
    factories.insert("LookAtToYawAvtBldrFtry", std::make_shared<LookAtToYawAvtBldrFtry>());

    // Avatars
    factories.insert("Drawable2DAvtFtry", std::make_shared<BaseAvatarFtry<uint64_t, int64_t, double, Vector2D, Vector2D> >());
    factories.insert("Drawable3DAvtFtry", std::make_shared<BaseAvatarFtry<uint64_t, double,  double, Vector3D, Vector3D> >());
    factories.insert("DrawableSimple2DAvtFtry", std::make_shared<BaseAvatarFtry<uint64_t, Vector2D, Vector2D> >());

    factories.insert("FloatAvtFtry", std::make_shared<BaseAvatarFtry<float> >());
    factories.insert("V3DAvtFtry", std::make_shared<BaseAvatarFtry<Vector3D> >());

    factories.insert("TargetToDirAvtFtry", std::make_shared<TargetToDirAvtFtry>());
    factories.insert("PosTargetToPosDirAvtFtry", std::make_shared<PosTargetToPosDirAvtFtry>());
    factories.insert("LookAtToPitchAvtFtry", std::make_shared<LookAtToPitchAvtFtry>());
    factories.insert("LookAtToYawAvtFtry", std::make_shared<LookAtToYawAvtFtry>());
    factories.insert("DerivedCosVelAvtFtry", std::make_shared<DerivedCosVelAvtFtry>());
    factories.insert("DerivedPosMovingSphereAvtFtry", std::make_shared<DerivedPosMovingSphereAvtFtry>());

    // Daemons & List
    factories.insert("DrawerAnimSprtFtry", std::make_shared<AnimDrwr>());
    factories.insert("TFAECAnimSprtFtry" , std::make_shared<SimpleGenericFtry<AnimList> >(factories::listName));

    factories.insert("DrawerModelDaemonFtry", std::make_shared<ModelDrwr>());
    factories.insert("TFAECModelFtry" , std::make_shared<SimpleGenericFtry<ModelList> >(factories::listName));

    factories.insert("SimpleSpriteDrwrDaemonFtry", std::make_shared<SimpleSpriteDrwr>());
    factories.insert("TFAECSimpleSpriteFtry" , std::make_shared<SimpleGenericFtry<SimpleSpriteList> >(factories::listName));

    factories.insert("FloatAvtDaemonFtry", std::make_shared<FloatAvtBhvr>());
    factories.insert("TFAECFloatAvtFtry" , std::make_shared<SimpleGenericFtry<FloatAvtList> >(factories::listName));

    factories.insert("V3DAvtDaemonFtry", std::make_shared<V3DAvtBhvr>());
    factories.insert("TFAECV3DAvtFtry" , std::make_shared<SimpleGenericFtry<V3DAvtList> >(factories::listName));

    factories.insert("ThreeV3DAvtDaemonFtry", std::make_shared<ThreeV3DAvtBhvr>());
    factories.insert("TFAECThreeV3DAvtFtry" , std::make_shared<SimpleGenericFtry<ThreeV3DAvtList> >(factories::listName));

    factories.insert("TwoV3DAvtDaemonFtry", std::make_shared<TwoV3DAvtBhvr>());
    factories.insert("TFAECTwoV3DAvtFtry" , std::make_shared<SimpleGenericFtry<TwoV3DAvtList> >(factories::listName));

    factories.insert("PosVel3DAvtDaemonFtry", std::make_shared<PosVel3DAvtBhvr>());
    factories.insert("TFAECPosVelV3DAvtFtry" , std::make_shared<SimpleGenericFtry<PosVel3DAvtList> >(factories::listName));

    factories.insert("LookAtAvtDaemonFtry", std::make_shared<LookAtAvtBhvr>());
    factories.insert("TFAECLookAtAvtFtry" , std::make_shared<SimpleGenericFtry<LookAtAvtList> >(factories::listName));

    factories.insert("TwoV3DAvtFtry", std::make_shared<BaseAvatarFtry<Vector3D, Vector3D> >());
  }
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_ZBEFACTORIES_H_
