/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BulletCreatorBhv.cpp
 * @since 2021-03-16
 * @date 2021-03-16
 * @author Degryll Ludo Batis
 * @brief BulletCreatorBhv given avatar.
 */

#include "ZBE/behaviors/BulletCreatorBhv.h"

namespace zbe {
    void BulletCreatorBhv::apply(std::shared_ptr<MAvatar<Vector3D, Vector3D> > avatar) {
      auto pos = avatar->get<1, Vector3D>()->get();
      auto dir = avatar->get<2, Vector3D>()->get();

      creator->operator()(pos, dir);
    }
}  // namespace zbe
