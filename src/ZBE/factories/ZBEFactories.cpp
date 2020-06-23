/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.cpp
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */

#include "ZBE/factories/ZBEFactories.h"

#include "ZBE/factories/implementations/GenericFtry.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"

#include "ZBE/factories/implementations/entities/avatars/SimpleAnimSprtFtry.h"
#include "ZBE/factories/implementations/entities/avatars/BaseAvatarFtry.h"


namespace zbe {

void ZBEFactories::load() {
  static const char listName[] = "List";

  auto& factories = RsrcStore<Factory>::getInstance();
  using AnimList = TicketedForwardList<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> >;

  using AnimDrwr = BehaviorDmnFtry<AnimList, uint64_t, int64_t, double, Vector2D, Vector2D>;

  factories.insert("SpriteAvtFtry", std::make_shared<BaseAvatarFtry<uint64_t, int64_t, double, Vector2D, Vector2D> >());

  factories.insert("DrawerAnimSprtFtry", std::make_shared<AnimDrwr>());
  factories.insert("TFAECAnimSprtFtry" , std::make_shared<SimpleGenericFtry<AnimList> >(listName));
  //factories.insert("SimpleAnimSprtFtry", std::make_shared<AnimFtry>());
}

}  // namespace zbe
