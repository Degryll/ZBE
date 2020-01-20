#include "gtest/gtest.h"

#include <cstdint>
#include <memory>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/TicketedElement.h"

#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

namespace BaseAvatarTest {

TEST(BaseAvatar, Usage) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";

  std::shared_ptr<zbe::_Entity<double, uint64_t, int64_t> > e = std::make_shared<zbe::_Entity<double, uint64_t, int64_t> >();
  std::shared_ptr<zbe::Value<double> >  vald1 = std::make_shared<zbe::SimpleValue<double> >(0.0);
  std::shared_ptr<zbe::Value<double> >  vald2 = std::make_shared<zbe::SimpleValue<double> >(1.0);
  std::shared_ptr<zbe::Value<uint64_t> >  valu1 = std::make_shared<zbe::SimpleValue<uint64_t> >(42);
  std::shared_ptr<zbe::Value<uint64_t> >  valu2 = std::make_shared<zbe::SimpleValue<uint64_t> >(37);
  std::shared_ptr<zbe::Value<int64_t> >  vali1 = std::make_shared<zbe::SimpleValue<int64_t> >(-1);
  std::shared_ptr<zbe::Value<int64_t> >  vali2 = std::make_shared<zbe::SimpleValue<int64_t> >(3);

//  e->setDouble(0, vald1);
//  e->setDouble(1, vald2);
//
//  e->setUint(0, valu1);
//  e->setUint(1, valu2);
//
//  e->setInt(0, vali1);
//  e->setInt(1, vali2);

  e->set<double>(0, vald1);
  e->set<double>(1, vald2);

  e->set<uint64_t>(0, valu1);
  e->set<uint64_t>(1, valu2);

  e->set<int64_t>(0, vali1);
  e->set<int64_t>(1, vali2);

  EXPECT_DOUBLE_EQ(0.0,  e->get<double>(0)->get()) << "First double value is 0.0.";
  EXPECT_DOUBLE_EQ(1.0,  e->get<double>(1)->get()) << "Second double value is 1.0";
  EXPECT_EQ(42, e->get<uint64_t>(0)->get()) << "First uint value is 42.";
  EXPECT_EQ(37, e->get<uint64_t>(1)->get()) << "Second uint value is 37";
  EXPECT_EQ(-1, e->get<int64_t>(0)->get()) << "First int value is -1.";
  EXPECT_EQ(3, e->get<int64_t>(1)->get()) << "Second int value is 3";

  std::shared_ptr<zbe::_Avatar<1, double> > ba1 = std::make_shared<zbe::_BaseAvatar<1, double> >(e, 1);
  //zbe::_BaseAvatar<1, double> ba1(e, 1);
  auto d1 = ba1->get<1, double>();
  d1->set(0.1);

  EXPECT_DOUBLE_EQ(0.1,  e->get<double>(1)->get()) << "Second double value now is 0.1.";
  std::shared_ptr<zbe::_Avatar<3, double, uint64_t, uint64_t> > ba3 = std::make_shared<zbe::_BaseAvatar<3, double, uint64_t, uint64_t> >(e, std::array<uint64_t, 3>({1, 1, 0}));
  //zbe::_BaseAvatar<3, double, uint64_t, uint64_t> ba3(e, {1, 1, 0});
//  auto d3 = ba3._BaseAvatar<3, double>::get();
  std::shared_ptr<zbe::Value<double> > d3 = ba3->get<3, double>();
  d3->set(4.2);
  std::shared_ptr<zbe::Value<uint64_t> > u1 = ba3->get<2, uint64_t>();
  u1->set(73);
//  std::shared_ptr<zbe::Value<uint64_t> > u0 = ba3->get<1, uint64_t>();
//  u0->set(24);

  EXPECT_DOUBLE_EQ(4.2,  e->get<double>(1)->get()) << "Second double value now is 4.2.";
  EXPECT_EQ(24, e->get<uint64_t>(0)->get()) << "First uint value now is 24.";
  EXPECT_EQ(73, e->get<uint64_t>(1)->get()) << "Second uint value now is 73";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No error ocurred.";

  zbe::SysError::clear();
}

}  // namespace EntityTest
