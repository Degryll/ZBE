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
    using VoidAvtList = TicketedForwardList<Avatar>;
    using VoidAvtBhvr = BehaviorDmnFtry<VoidAvtList, void>;

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

    using LookAtAvtList = TicketedForwardList<MAvatar<uint64_t, double, Vector3D, Vector3D, Vector3D> >;
    using LookAtAvtBhvr = BehaviorDmnFtry<LookAtAvtList, uint64_t, double, Vector3D, Vector3D, Vector3D>;

    using M3DOn2DAvtList = TicketedForwardList<MAvatar<Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D> >;
    using M3DOn2DAvtBhvr = BehaviorDmnFtry<M3DOn2DAvtList, Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D>;

    auto& factories = RsrcStore<Factory>::getInstance();
    for(int i = 0;i<100;i++) {
        factories.insert(std::to_string(i)+"Ftry"s , std::make_shared<SimpleGenericFtry<int> >(factories::listName));
    }
    // Builders
    factories.insert("Drawable2DAvtBldrFtry", std::make_shared<MAvatarBldrFtry<uint64_t, int64_t, double, Vector2D, Vector2D>>());
    factories.insert("Drawable3DAvtBldrFtry", std::make_shared<MAvatarBldrFtry<uint64_t, double,  double, Vector3D, Vector3D>>());
    factories.insert("DrawableLookAtAvtBldrFtry", std::make_shared<MAvatarBldrFtry<uint64_t, double,  Vector3D, Vector3D, Vector3D>>());
    factories.insert("DrawableSimple2DAvtBldrFtry", std::make_shared<MAvatarBldrFtry<uint64_t, int64_t, double, Vector2D, Vector2D>>());
    factories.insert("V3DAvtBldrFtry", std::make_shared<SAvatarBldrFtry<Vector3D> >());
    factories.insert("TwoV3DAvtBldrFtry", std::make_shared<MAvatarBldrFtry<Vector3D, Vector3D> >());
    factories.insert("FloatAvtBldrFtry", std::make_shared<SAvatarBldrFtry<float> >());
    factories.insert("VoidAvtBldrFtry", std::make_shared<AvatarBldrFtry>());

    factories.insert("TargetToDirAvtBldrFtry", std::make_shared<TargetToDirAvtBldrFtry>());
    factories.insert("PosTargetToPosDirAvtBldrFtry", std::make_shared<PosTargetToPosDirAvtBldrFtry>());
    factories.insert("PosUpwardsTargetToPosUpwardsDirAvtBldrFtry", std::make_shared<PosUpwardsTargetToPosUpwardsDirAvtBldrFtry>());
    factories.insert("PosUpwardsTargetToPosUpwardsDirAvtFtry", std::make_shared<PosUpwardsTargetToPosUpwardsDirAvtFtry>());
    factories.insert("DerivedCosVelAvtBldrFtry", std::make_shared<DerivedCosVelAvtBldrFtry>());
    factories.insert("DerivedPosMovingSphereAvtBldrFtry", std::make_shared<DerivedPosMovingSphereAvtBldrFtry>());
    factories.insert("DerivedPosMovingSphereAvtShapeBldrFtry", std::make_shared<DerivedPosMovingSphereAvtShapeBldrFtry>());
    factories.insert("LookAtToPitchAvtBldrFtry", std::make_shared<LookAtToPitchAvtBldrFtry>());
    factories.insert("LookAtToYawAvtBldrFtry", std::make_shared<LookAtToYawAvtBldrFtry>());
    factories.insert("3DOn2DAvtBldrFtry", std::make_shared<MDynamicAvatarBldrFtry<Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D> >());
    //factories.insert("MovingSphereAvtBldrFtry", std::make_shared<MovingSphereAvtBldrFtry>());
    factories.insert("MovingSphereAvtShapeBldrFtry", std::make_shared<MovingSphereAvtShapeBldrFtry>());
    factories.insert("MovingTriangle3DAvtShapeBldrFtry", std::make_shared<MovingTriangle3DAvtShapeBldrFtry>());
    factories.insert("MovingTriangle3DRscAvtShapeBldrFtry", std::make_shared<MovingTriangle3DRscAvtShapeBldrFtry>());

    factories.insert("MovingPoint2DShapeAvtBldrFtry", std::make_shared<MovingPoint2DShapeAvtBldrFtry>());
    factories.insert("Triangle2DShapeAvtBldrFtry", std::make_shared<Triangle2DShapeAvtBldrFtry>());

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

    factories.insert("VoidBvrDmnFtry", std::make_shared<VoidAvtBhvr>());
    factories.insert("TFAEVoidFtry" , std::make_shared<SimpleGenericFtry<VoidAvtList> >(factories::listName));

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

    factories.insert("3DOn2DAvtDaemonFtry", std::make_shared<M3DOn2DAvtBhvr>());
    factories.insert("TFAEC3DOn2DAvtFtry" , std::make_shared<SimpleGenericFtry<M3DOn2DAvtList> >(factories::listName));

    factories.insert("TwoV3DAvtFtry", std::make_shared<BaseAvatarFtry<Vector3D, Vector3D> >());

  }
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_ZBEFACTORIES_H_
