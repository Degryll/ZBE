/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandler.h
 * @since 2021-04-08
 * @date 2021-04-08
 * @author Batis Degrill Ludo
 * @brief Time handler capable of erase an entity.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_ENTITYERASER_H
#define ZBE_EVENTS_HANDLERS_TIME_ENTITYERASER_H

#include <cstdint>
#include <memory>

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"


namespace zbe {

class EntityEraser : public TimeHandler {
  public:
	EntityEraser(const EntityEraser&) = delete; //!< Avoid copy.
	void operator=(const EntityEraser&) = delete; //!< Avoid copy.

    /** brief Empty constructor
     */
  	EntityEraser() = default;

    /** brief Parametrized constructor
     * param entity Entity to be erased
     */
  	EntityEraser(std::shared_ptr<Entity> entity): e(entity){}

  	void setEntity(std::shared_ptr<Entity> entity) {e = entity;}

    /** brief Erases entity
     *  param time not used
     */
  	void run(uint64_t) {
        e->setERASED();
  	}

  private:
    std::shared_ptr<zbe::Entity> e;
};

/** \brief Factory for EntityEraser.
 */
class EntityEraserFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;

    std::shared_ptr<EntityEraser> te = std::make_shared<EntityEraser>();
    timeStore.insert("TimeHandler."s + name, te);
    timeEraserStore.insert("EntityEraser."s + name, te);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (j["entity"].is_string()) {
        std::string ename = j["entity"].get<std::string>();
        std::shared_ptr<Entity> entity = entityStore.get("Entity."s + ename);
        auto te = timeEraserStore.get("EntityEraser."s + name);
        te->setEntity(entity);

      } else {
        SysError::setError("EntityEraserFtry config for "s + j["entity"].get<std::string>() + ": must be a string."s);
      }
    } else {
      SysError::setError("EntityEraserFtry config for "s + name + " not found."s);
    }
  }


private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Entity> &entityStore = RsrcStore<Entity>::getInstance();
  RsrcStore<TimeHandler> &timeStore = RsrcStore<TimeHandler>::getInstance();
  RsrcStore<EntityEraser> &timeEraserStore = RsrcStore<EntityEraser>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_ENTITYERASER_H