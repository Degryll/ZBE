#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/factories/implementations/tools/graphics/CameraFtry.h"

namespace CameraFtryTest {

TEST(CameraFtryTest, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<json> &configRsrc = RsrcStore<json>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Value<Vector3D> > &vec3DValues = RsrcStore<Value<Vector3D> >::getInstance();
  RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();

  (*cfg)["eyevalue"] = "testEyeVal"s;
  (*cfg)["targetvalue"] = "testTargetvalue"s;
  (*cfg)["upvalue"] = "testUpvalue"s;
  (*cfg)["fov"] = "testFov"s;
  (*cfg)["aspect"] = "testAspect"s;
  (*cfg)["znear"] = "testZnear"s;
  (*cfg)["zfar"] = "testZfar"s;

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  vec3DValues.insert("testEyeVal"s, std::make_shared<zbe::SimpleValue<zbe::Vector3D> >());
  vec3DValues.insert("testTargetvalue"s, std::make_shared<zbe::SimpleValue<zbe::Vector3D> >());
  vec3DValues.insert("testUpvalue"s, std::make_shared<zbe::SimpleValue<zbe::Vector3D> >());

  doubleStore.insert("testFov"s, 1.0f);
  doubleStore.insert("testAspect"s, 1.0f);
  doubleStore.insert("testZnear"s, 1.0f);
  doubleStore.insert("testZfar"s, 1.0f);

  CameraFtry cf;
  cf.create("CameraFtryTestName", cfgId);
  cf.setup("CameraFtryTestName", cfgId);

  uint64_t outId = dict.get("Camera.CameraFtryTestName");
  std::shared_ptr<zbe::Camera> outCam = cameraRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a camera with given name";

  dict.clear();
  configRsrc.clear();
  cameraRsrc.clear();
  vec3DValues.clear();
  doubleStore.clear();

  zbe::SysError::clear();
}

}  // namespace CameraFtryTest
