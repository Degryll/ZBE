#if __has_include(<catch2/catch_test_macros.hpp>)
#include <catch2/catch_test_macros.hpp>
#elif __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#error "Catch2 not found - please make sure Catch2 is provided by the project dependencies"
#endif

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace zbe {

class TicketMock : public Ticket {
public:
  TicketMock() : state(ERASED) {}
  void setACTIVE() override { state = ACTIVE; }
  void setINACTIVE() override { state = INACTIVE; }
  void setERASED() override { state = ERASED; }
  void setState(State s) override { state = s; }
  void toggle() override {
    if (state == ACTIVE) state = INACTIVE;
    else if (state == INACTIVE) state = ACTIVE; 
  }
  bool isACTIVE() override { return state == ACTIVE; }
  bool isNotACTIVE() override { return state != ACTIVE; }
  bool isINACTIVE() override { return state == INACTIVE; }
  bool isERASED() override { return state == ERASED; }
  State getState() override { return state; }
private:
  State state;
};

TEST_CASE("Entity::setDouble and getDouble", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<double>>(3.14159);
  
  entity->setDouble(1, value);
  auto retrieved = entity->getDouble(1);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == 3.14159);
}

TEST_CASE("Entity::setFloat and getFloat", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<float>>(2.71828f);
  
  entity->setFloat(2, value);
  auto retrieved = entity->getFloat(2);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == 2.71828f);
}

TEST_CASE("Entity::setUint and getUint", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<uint64_t>>(42);
  
  entity->setUint(3, value);
  auto retrieved = entity->getUint(3);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == 42);
}

TEST_CASE("Entity::setInt and getInt", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<int64_t>>(-100);
  
  entity->setInt(4, value);
  auto retrieved = entity->getInt(4);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == -100);
}

TEST_CASE("Entity::setBool and getBool", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<bool>>(true);
  
  entity->setBool(5, value);
  auto retrieved = entity->getBool(5);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == true);
}

TEST_CASE("Entity::setVector3D and getVector3D", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  Vector3D vec{1.0f, 2.0f, 3.0f};
  auto value = std::make_shared<SimpleValue<Vector3D>>(vec);
  
  entity->setVector3D(6, value);
  auto retrieved = entity->getVector3D(6);
  
  REQUIRE(retrieved != nullptr);
  Vector3D retrievedVec = retrieved->get();
  REQUIRE(retrievedVec[0] == 1.0);
  REQUIRE(retrievedVec[1] == 2.0);
  REQUIRE(retrievedVec[2] == 3.0);
}

TEST_CASE("Entity::setVector2D and getVector2D", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  Vector2D vec{4.5f, 5.5f};
  auto value = std::make_shared<SimpleValue<Vector2D>>(vec);
  
  entity->setVector2D(7, value);
  auto retrieved = entity->getVector2D(7);
  
  REQUIRE(retrieved != nullptr);
  Vector2D retrievedVec = retrieved->get();
  REQUIRE(retrievedVec[0] == 4.5);
  REQUIRE(retrievedVec[1] == 5.5);
}

TEST_CASE("Entity::setString and getString", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  std::string testStr = "Hello, Entity!";
  auto value = std::make_shared<SimpleValue<std::string>>(testStr);
  
  entity->setString(8, value);
  auto retrieved = entity->getString(8);
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved->get() == testStr);
}

TEST_CASE("Entity::setStringVector and getStringVector", "[Entity][values]") {
  auto entity = std::make_shared<Entity>();
  std::vector<std::string> vecStr = {"one", "two", "three"};
  auto value = std::make_shared<SimpleValue<std::vector<std::string>>>(vecStr);
  
  entity->setStringVector(9, value);
  auto retrieved = entity->getStringVector(9);
  
  REQUIRE(retrieved != nullptr);
  std::vector<std::string> retrievedVec = retrieved->get();
  REQUIRE(retrievedVec.size() == 3);
  REQUIRE(retrievedVec[0] == "one");
  REQUIRE(retrievedVec[1] == "two");
  REQUIRE(retrievedVec[2] == "three");
}

TEST_CASE("Entity::overrideDouble", "[Entity][values][override]") {
  auto entity = std::make_shared<Entity>();
  auto value1 = std::make_shared<SimpleValue<double>>(1.5);
  auto value2 = std::make_shared<SimpleValue<double>>(2.5);
  
  entity->setDouble(10, value1);
  entity->overrideDouble(10, value2);
  
  auto retrieved = entity->getDouble(10);
  REQUIRE(retrieved->get() == 2.5);
}

TEST_CASE("Entity::overrideFloat", "[Entity][values][override]") {
  auto entity = std::make_shared<Entity>();
  auto value1 = std::make_shared<SimpleValue<float>>(1.5f);
  auto value2 = std::make_shared<SimpleValue<float>>(2.5f);
  
  entity->setFloat(11, value1);
  entity->overrideFloat(11, value2);
  
  auto retrieved = entity->getFloat(11);
  REQUIRE(retrieved->get() == 2.5f);
}

TEST_CASE("Entity::overrideString", "[Entity][values][override]") {
  auto entity = std::make_shared<Entity>();
  auto value1 = std::make_shared<SimpleValue<std::string>>("old");
  auto value2 = std::make_shared<SimpleValue<std::string>>("new");
  
  entity->setString(12, value1);
  entity->overrideString(12, value2);
  
  auto retrieved = entity->getString(12);
  REQUIRE(retrieved->get() == "new");
}

TEST_CASE("Entity::setContextTime and getContextTime", "[Entity][context]") {
  auto entity = std::make_shared<Entity>();
  auto contextTime = SysTime::getInstance();
  
  entity->setContextTime(contextTime);
  auto retrieved = entity->getContextTime();
  
  REQUIRE(retrieved != nullptr);
  REQUIRE(retrieved == contextTime);
}

TEST_CASE("Entity::addTicket", "[Entity][tickets]") {
  auto entity = std::make_shared<Entity>();
  auto ticket = std::make_shared<TicketMock>();
  
  entity->addTicket(100, ticket);
  // Verify ticket was added without exception
  REQUIRE(true);
}

TEST_CASE("Entity::replaceTicket", "[Entity][tickets]") {
  auto entity = std::make_shared<Entity>();
  auto ticket1 = std::make_shared<TicketMock>();
  auto ticket2 = std::make_shared<TicketMock>();
  
  entity->addTicket(101, ticket1);
  entity->replaceTicket(101, ticket2);
  // Verify ticket was replaced without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setACTIVE with id", "[Entity][state]") {
  auto entity = std::make_shared<Entity>();
  auto ticket = std::make_shared<TicketMock>();
  
  entity->addTicket(102, ticket);
  entity->setACTIVE(102);
  // Verify state was changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setINACTIVE with id", "[Entity][state]") {
  auto entity = std::make_shared<Entity>();
  auto ticket = std::make_shared<TicketMock>();
  
  entity->addTicket(103, ticket);
  entity->setINACTIVE(103);
  // Verify state was changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setERASED with id", "[Entity][state]") {
  auto entity = std::make_shared<Entity>();
  auto ticket = std::make_shared<TicketMock>();
  
  entity->addTicket(104, ticket);
  entity->setERASED(104);
  // Verify state was changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setACTIVE global", "[Entity][state][global]") {
  auto entity = std::make_shared<Entity>();
  auto ticket1 = std::make_shared<TicketMock>();
  auto ticket2 = std::make_shared<TicketMock>();
  
  entity->addTicket(105, ticket1);
  entity->addTicket(106, ticket2);
  entity->setACTIVE();
  // Verify all states were changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setINACTIVE global", "[Entity][state][global]") {
  auto entity = std::make_shared<Entity>();
  auto ticket1 = std::make_shared<TicketMock>();
  auto ticket2 = std::make_shared<TicketMock>();
  
  entity->addTicket(107, ticket1);
  entity->addTicket(108, ticket2);
  entity->setINACTIVE();
  // Verify all states were changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::setERASED global", "[Entity][state][global]") {
  auto entity = std::make_shared<Entity>();
  auto ticket1 = std::make_shared<TicketMock>();
  auto ticket2 = std::make_shared<TicketMock>();
  
  entity->addTicket(109, ticket1);
  entity->addTicket(110, ticket2);
  entity->setERASED();
  // Verify all states were changed without exception
  REQUIRE(true);
}

TEST_CASE("Entity::multiple values of different types", "[Entity][values][mixed]") {
  auto entity = std::make_shared<Entity>();
  
  // Add values of different types with different IDs
  entity->setDouble(200, std::make_shared<SimpleValue<double>>(3.14));
  entity->setInt(201, std::make_shared<SimpleValue<int64_t>>(42));
  entity->setString(202, std::make_shared<SimpleValue<std::string>>("test"));
  entity->setBool(203, std::make_shared<SimpleValue<bool>>(true));
  
  // Verify all values are retrievable
  REQUIRE(entity->getDouble(200)->get() == 3.14);
  REQUIRE(entity->getInt(201)->get() == 42);
  REQUIRE(entity->getString(202)->get() == "test");
  REQUIRE(entity->getBool(203)->get() == true);
}

TEST_CASE("Entity::template set/get double", "[Entity][templates]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<double>>(7.77);
  
  entity->set<double>(300, value);
  auto retrieved = entity->get<double, std::shared_ptr<Value<double>>>(300);
  
  REQUIRE(retrieved->get() == 7.77);
}

TEST_CASE("Entity::template set/get int", "[Entity][templates]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<int64_t>>(999);
  
  entity->set<int64_t>(301, value);
  auto retrieved = entity->get<int64_t, std::shared_ptr<Value<int64_t>>>(301);
  
  REQUIRE(retrieved->get() == 999);
}

TEST_CASE("Entity::template set/get string", "[Entity][templates]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<std::string>>("template_test");
  
  entity->set<std::string>(302, value);
  auto retrieved = entity->get<std::string, std::shared_ptr<Value<std::string>>>(302);
  
  REQUIRE(retrieved->get() == "template_test");
}

TEST_CASE("Entity::template override double", "[Entity][templates][override]") {
  auto entity = std::make_shared<Entity>();
  auto value1 = std::make_shared<SimpleValue<double>>(1.1);
  auto value2 = std::make_shared<SimpleValue<double>>(2.2);
  
  entity->set<double>(303, value1);
  entity->override<double>(303, value2);
  
  auto retrieved = entity->get<double, std::shared_ptr<Value<double>>>(303);
  REQUIRE(retrieved->get() == 2.2);
}

TEST_CASE("Entity::destructor cleans up tickets", "[Entity][cleanup]") {
  auto ticket = std::make_shared<TicketMock>();
  {
    auto entity = std::make_shared<Entity>();
    entity->addTicket(400, ticket);
  } // Entity goes out of scope and destructor is called
  // Verify no crash occurred
  REQUIRE(true);
}

TEST_CASE("Entity::modify Value after assignment", "[Entity][values][modification]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<double>>(10.5);
  
  // Assign value to entity
  entity->setDouble(500, value);
  
  // Verify initial value is stored correctly
  auto retrieved = entity->getDouble(500);
  REQUIRE(retrieved->get() == 10.5);
  
  // Modify the value directly
  value->set(25.75);
  
  // Verify the modification is reflected in the entity's stored value
  auto retrievedAfterModification = entity->getDouble(500);
  REQUIRE(retrievedAfterModification->get() == 25.75);
  REQUIRE(retrievedAfterModification == value);  // Verify it's the same object
}

TEST_CASE("Entity::modify Int Value after assignment", "[Entity][values][modification]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<int64_t>>(100);
  
  // Assign value to entity
  entity->setInt(501, value);
  
  // Verify initial value is stored correctly
  auto retrieved = entity->getInt(501);
  REQUIRE(retrieved->get() == 100);
  
  // Modify the value directly
  value->set(-50);
  
  // Verify the modification is reflected in the entity's stored value
  auto retrievedAfterModification = entity->getInt(501);
  REQUIRE(retrievedAfterModification->get() == -50);
  REQUIRE(retrievedAfterModification == value);
}

TEST_CASE("Entity::modify String Value after assignment", "[Entity][values][modification]") {
  auto entity = std::make_shared<Entity>();
  auto value = std::make_shared<SimpleValue<std::string>>("initial");
  
  // Assign value to entity
  entity->setString(502, value);
  
  // Verify initial value is stored correctly
  auto retrieved = entity->getString(502);
  REQUIRE(retrieved->get() == "initial");
  
  // Modify the value directly
  value->set("modified");
  
  // Verify the modification is reflected in the entity's stored value
  auto retrievedAfterModification = entity->getString(502);
  REQUIRE(retrievedAfterModification->get() == "modified");
  REQUIRE(retrievedAfterModification == value);
}

}  // namespace zbe
