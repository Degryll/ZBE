/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BulletCreatorBhv.h
 * @since 2021-03-16
 * @date 2021-03-16
 * @author Degryll Ludo Batis
 * @brief BulletCreatorBhv given avatar.
 */

#ifndef ZBE_BEHAVIORS_BULLETCREATORBHV_H_
#define ZBE_BEHAVIORS_BULLETCREATORBHV_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/creators/BulletCreator.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI BulletCreatorBhvFtry;

/** \brief BulletCreatorBhv given avatar.
 */
class BulletCreatorBhv : virtual public Behavior<Vector3D, Vector3D> {
public:
  friend class BulletCreatorBhvFtry;

  BulletCreatorBhv(std::shared_ptr<BulletCreator> creator) : creator(creator) {}

  /** \brief Virtual destructor.
   */
  virtual ~BulletCreatorBhv() = default;

  void setSpeed(double speed, uint64_t idx) {
    creator->setSpeed(speed, idx);
  }

  void setGid(uint64_t gid, uint64_t idx) {
    creator->setGid(gid, idx);
  }

  void setRotation(double rotation, uint64_t idx) {
    creator->setRotation(rotation, idx);
  }

  void setScale(double scale, uint64_t idx) {
    creator->setScale(scale, idx);
  }

  void setPositionId(uint64_t idx) {
    creator->setPositionId(idx);
  }

  void setDirectionId(uint64_t idx) {
    creator->setDirectionId(idx);
  }

  void setGraphicList(std::vector<std::pair<std::string, uint64_t>> graphicList) {
    creator->setGraphicList(graphicList);
  }

  void setBehaviorList(std::vector<std::pair<std::string, uint64_t>> behaviorList) {
    creator->setBehaviorList(behaviorList);
  }

  /** \brief BulletCreatorBhv given avatar.
   */
  void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D> > avatar);

private:

  BulletCreatorBhv() : creator() {};

  void setCreator(std::shared_ptr<BulletCreator> creator) {
    this->creator = creator;
  }

  std::shared_ptr<BulletCreator> creator;
};

class ZBEAPI BulletCreatorBhvFtry : virtual public Factory  {
public:
  void create(std::string name, uint64_t);

  void setup(std::string name, uint64_t cfgId);
private:
  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<Vector3D, Vector3D>>& behaviorStore = RsrcStore<Behavior<Vector3D, Vector3D>>::getInstance();
  RsrcStore<BulletCreatorBhv>& bulletCreatorBhvStore = RsrcStore<BulletCreatorBhv>::getInstance();
  RsrcStore<BulletCreator>& bulletCreatorStore = RsrcStore<BulletCreator>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BULLETCREATORBHV_H_
