#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/factories/implementations/events/handlers/input/InputToValueFtry.h"

namespace InputToValueFtryTest {

TEST(InputToValueFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto &inputRsrc = RsrcStore<InputHandler>::getInstance();
  auto &itvRsrc = RsrcStore<InputToValue>::getInstance();
  auto &valueDRsrc = RsrcStore<Value<double> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg) = {{"value", "outValue"}};

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto outValue = std::make_shared<SimpleValue<double> >(0.0f);

  valueDRsrc.insert("ValueD."s + "outValue"s, outValue);

  InputToValueFtry itvf;
  itvf.create("InputToValueFtryTestName", cfgId);
  itvf.setup("InputToValueFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("InputHandler.InputToValueFtryTestName");
  uint64_t outRealId = dict.get("InputToValue.InputToValueFtryTestName");

  ASSERT_NE(0, outId) << "Must create a InputHandler with given name";
  ASSERT_NE(0, outRealId) << "Must create a InputToValue with given name";

  auto outHnd = inputRsrc.get(outId);

  EXPECT_EQ(outValue->get(), 0.0f) << "Initially value is zero";

  outHnd->run(1, 75.0f);

  EXPECT_EQ(outValue->get(), 75.0f) << "Value must have a valid content after run";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finaly no errors.";

  dict.clear();
  configRsrc.clear();
  inputRsrc.clear();
  itvRsrc.clear();
  valueDRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
