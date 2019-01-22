#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/factories/implementations/events/handlers/input/BroadcastIHFtry.h"

namespace BroadcastIHFtryTest {

class DummyHandler : virtual public zbe::InputHandler {
public:
    DummyHandler() {}

    virtual void run(uint32_t key, float state) {
      called = true;
      this->state = state;
      this->key = key;
    }

    float state = 0.0f;
    uint32_t key = 0;
    bool called = false;
};

TEST(BroadcastIHFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto &inputRsrc = RsrcStore<InputHandler>::getInstance();
  auto &bihRsrc = RsrcStore<BroadcastIH>::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["handlers"] = json::array({"ih1", "ih2", "ih3"});

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto ih1 = std::make_shared<DummyHandler>();
  auto ih2 = std::make_shared<DummyHandler>();
  auto ih3 = std::make_shared<DummyHandler>();

  inputRsrc.insert("InputHandler."s + "ih1", ih1);
  inputRsrc.insert("InputHandler."s + "ih2", ih2);
  inputRsrc.insert("InputHandler."s + "ih3", ih3);

  BroadcastIHFtry bcihf;
  bcihf.create("BroadcastIHFtryTestName", cfgId);
  bcihf.setup("BroadcastIHFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("InputHandler.BroadcastIHFtryTestName");
  uint64_t outRealId = dict.get("BroadcastIH.BroadcastIHFtryTestName");

  ASSERT_NE(0, outId) << "Must create a InputHandler with given name";
  ASSERT_NE(0, outRealId) << "Must create a BroadcastIH with given name";

  auto outHnd = inputRsrc.get(outId);

  outHnd->run(1, 0.5f);

  EXPECT_EQ(ih1->state,0.5f) << "New state must match";
  EXPECT_EQ(ih2->state,0.5f) << "New state must match";
  EXPECT_EQ(ih3->state,0.5f) << "New state must match";

  EXPECT_EQ(ih1->key, 1) << "Key must match";
  EXPECT_EQ(ih2->key, 1) << "Key must match";
  EXPECT_EQ(ih3->key, 1) << "Key must match";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finaly no errors.";

  dict.clear();
  configRsrc.clear();
  inputRsrc.clear();
  bihRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
