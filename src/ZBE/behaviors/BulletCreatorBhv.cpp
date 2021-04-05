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

    void BulletCreatorBhvFtry::create(std::string name, uint64_t cfgId){
      using namespace std::string_literals;
      std::shared_ptr<BulletCreatorBhv> bcb = std::shared_ptr<BulletCreatorBhv>(new BulletCreatorBhv);  // std::make_shared<SineOscillator>();
      behaviorStore.insert("Behavior."s + name, bcb);
      bulletCreatorBhvStore.insert("BulletCreatorBhv."s + name, bcb);
    }

    void BulletCreatorBhvFtry::setup(std::string name, uint64_t cfgId){
        using namespace std::string_literals;
        using namespace nlohmann;
        std::shared_ptr<json> cfg = configStore.get(cfgId);

        if(cfg) {
          auto j = *cfg;
          if (!j["creator"].is_string()) {
            SysError::setError("BulletCreatorBhvFtry " + name + " config for creator: "s + j["creator"].get<std::string>() + ": must be a literal double name."s);
            return;
          }

          std::string creatorName = j["creator"].get<std::string>();
          if(!bulletCreatorStore.contains("BulletCreator."s + creatorName)) {
            SysError::setError("BulletCreatorBhvFtry " + name + " config for creator: "s + creatorName + " is not a BulletCreator literal."s);
            return;
          }
          auto bcb = bulletCreatorBhvStore.get("BulletCreatorBhv."s + name);

          auto creator = bulletCreatorStore.get("BulletCreator."s + creatorName);
          bcb->setCreator(creator);
        }
    }

}  // namespace zbe
