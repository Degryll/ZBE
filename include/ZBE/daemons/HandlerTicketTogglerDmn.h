/**
 * Copyright 2015 Batis Degryll Ludo
 * @file OnceDaemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo
 * @brief Daemon that applies a "punish" over a list of elements.
 */

#ifndef ZBE_CORE_DAEMONS_HANDLER_TICKET_TOGGLER_DMN_H_
#define ZBE_CORE_DAEMONS_HANDLER_TICKET_TOGGLER_DMN_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class HandlerTicketTogglerDmn : public Daemon {
public:

  virtual ~HandlerTicketTogglerDmn() = default;

  void addTicket(std::shared_ptr<HandlerTicket> ticket) {
    tickets.push_back(ticket);
  }

  void setState( bool state) {
    this->active = state;
  }

  /** \brief It will run the Daemons and deactivate it.
   */
  void run() override {
    if (this->active) {
      for(auto t : tickets) {
        t->setActive();
      }
    } else {
      for(auto t : tickets) {
        t->setInactive();
      }
    }
    this->active = !this->active;
  }

private:
DISABLE_DLL_WARN
  std::vector<std::shared_ptr<HandlerTicket> > tickets;
  bool active = false;
DISABLE_WARNING_POP()
};

class HandlerTicketTogglerDmnFtry : public Factory {
public:

  /** \brief Creates a OnceDaemon from a file.
   *  \param name Name for the created OnceDaemon.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<HandlerTicketTogglerDmn> od = std::make_shared<HandlerTicketTogglerDmn>();
    handlerTicketTogglerDmnStore.insert("HandlerTicketTogglerDmn."s + name, od);
    daemonStore.insert("Daemon."s + name, od);
  }

  /** \brief Set-up a HandlerTicketTogglerDmn.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto httd = handlerTicketTogglerDmnStore.get("HandlerTicketTogglerDmn."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["tickets"].is_array()) {
        SysError::setError("HandlerTicketTogglerDmn " + name + " config for tickets must be an array."s);
        return;
      }

      json tickets = j["tickets"];
      for (auto ticket : tickets) {
        if (ticket.is_string()) {
          auto handlerTicket = ticketStore.get("HandlerTicket."s + ticket.get<std::string>());
          if (handlerTicket) {
            httd->addTicket(handlerTicket);
          } else {
            SysError::setError("HandlerTicketTogglerDmn config for "s + name + " has a ticket that was not found."s);
          }
        }
      }

    } else {
      SysError::setError("HandlerTicketTogglerDmn config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<HandlerTicketTogglerDmn>& handlerTicketTogglerDmnStore = RsrcStore<HandlerTicketTogglerDmn>::getInstance();
  RsrcStore<HandlerTicket>& ticketStore = RsrcStore<HandlerTicket>::getInstance();
};


class ParametricHandlerTicketTogglerDmn : public Daemon {
public:

  virtual ~ParametricHandlerTicketTogglerDmn() = default;

  void addTicket(std::shared_ptr<HandlerTicket> ticket) {
    tickets.push_back(ticket);
  }

  void setState(std::shared_ptr<Value<bool>> active) {
    this->active = active;
  }

  /** \brief It will run the Daemons and deactivate it.
   */
  void run() override {
    if (this->active->get()) {
      for(auto t : tickets) {
        t->setActive();
      }
    } else {
      for(auto t : tickets) {
        t->setInactive();
      }
    }
  }

private:
DISABLE_DLL_WARN
  std::vector<std::shared_ptr<HandlerTicket> > tickets;
  std::shared_ptr<Value<bool>> active;
DISABLE_WARNING_POP()
};

class ParametricHandlerTicketTogglerDmnFtry : public Factory {
public:

  /** \brief Creates a OnceDaemon from a file.
   *  \param name Name for the created OnceDaemon.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<ParametricHandlerTicketTogglerDmn> od = std::make_shared<ParametricHandlerTicketTogglerDmn>();
    parametricHandlerTicketTogglerDmnStore.insert("ParametricHandlerTicketTogglerDmn."s + name, od);
    daemonStore.insert("Daemon."s + name, od);
  }

  /** \brief Set-up a HandlerTicketTogglerDmn.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto httd = parametricHandlerTicketTogglerDmnStore.get("ParametricHandlerTicketTogglerDmn."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["tickets"].is_array()) {
        SysError::setError("ParametricHandlerTicketTogglerDmn " + name + " config for tickets must be an array."s);
        return;
      }

      json tickets = j["tickets"];
      for (auto ticket : tickets) {
        if (ticket.is_string()) {
          auto handlerTicket = ticketStore.get("HandlerTicket."s + ticket.get<std::string>());
          if (handlerTicket) {
            httd->addTicket(handlerTicket);
          } else {
            SysError::setError("ParametricHandlerTicketTogglerDmn config for "s + name + " has a ticket that was not found."s);
          }
        }
      }
      if (!j["entity"].is_string()) {
        SysError::setError("ParametricHandlerTicketTogglerDmn " + name + " config for entity must be a string."s);
        return;
      }
      auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
      if (!entity) {
        SysError::setError("ParametricHandlerTicketTogglerDmn " + name + " config for entity not found."s);
        return;
      }
      if (!j["valueIdx"].is_string()) {
        SysError::setError("ParametricHandlerTicketTogglerDmn " + name + " config for valueIdx must be a string."s);
        return;
      }

      uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());

      auto value = entity->getBool(valueIdx);
      if (!value) {
        SysError::setError("ParametricHandlerTicketTogglerDmn " + name + " config for valueIdx not found."s);
        return;
      }
      httd->setState(value);
      
    } else {
      SysError::setError("ParametricHandlerTicketTogglerDmn config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<ParametricHandlerTicketTogglerDmn>& parametricHandlerTicketTogglerDmnStore = RsrcStore<ParametricHandlerTicketTogglerDmn>::getInstance();
  RsrcStore<HandlerTicket>& ticketStore = RsrcStore<HandlerTicket>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
};


class HandlerTicketActivatorDmn : public Daemon {
public:

  virtual ~HandlerTicketActivatorDmn() = default;

  void addTicket(std::shared_ptr<HandlerTicket> ticket) {
    tickets.push_back(ticket);
  }

  /** \brief It will run the Daemons and deactivate it.
   */
  void run() override {
    for(auto t : tickets) {
      t->setActive();
    }
  }

private:
DISABLE_DLL_WARN
  std::vector<std::shared_ptr<HandlerTicket> > tickets;
DISABLE_WARNING_POP()
};

class HandlerTicketDeactivatorDmn : public Daemon {
public:

  virtual ~HandlerTicketDeactivatorDmn() = default;

  void addTicket(std::shared_ptr<HandlerTicket> ticket) {
    tickets.push_back(ticket);
  }

  /** \brief It will run the Daemons and deactivate it.
   */
  void run() override {
    for(auto t : tickets) {
      t->setInactive();
    }
  }

private:
DISABLE_DLL_WARN
  std::vector<std::shared_ptr<HandlerTicket> > tickets;
DISABLE_WARNING_POP()
};

class HandlerTicketActivatorDmnFtry : public Factory {
public: 

  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<HandlerTicketActivatorDmn> htad = std::make_shared<HandlerTicketActivatorDmn>();
    handlerTicketActivatorDmnStore.insert("HandlerTicketActivatorDmn."s + name, htad);
    daemonStore.insert("Daemon."s + name, htad);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto htad = handlerTicketActivatorDmnStore.get("HandlerTicketActivatorDmn."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["tickets"].is_array()) {
        SysError::setError("HandlerTicketActivatorDmn " + name + " config for tickets must be an array."s);
        return;
      }

      json tickets = j["tickets"];
      for (auto ticket : tickets) {
        if (ticket.is_string()) {
          auto handlerTicket = ticketStore.get("HandlerTicket."s + ticket.get<std::string>());
          if (handlerTicket) {
            htad->addTicket(handlerTicket);
          } else {
            SysError::setError("HandlerTicketActivatorDmn config for "s + name + " has a ticket that was not found."s);
          }
        }
      }

    } else {
      SysError::setError("HandlerTicketActivatorDmn config for "s + name + " not found."s);
    }
  }
private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<HandlerTicketActivatorDmn>& handlerTicketActivatorDmnStore = RsrcStore<HandlerTicketActivatorDmn>::getInstance();
  RsrcStore<HandlerTicket>& ticketStore = RsrcStore<HandlerTicket>::getInstance();
}; 


class HandlerTicketDeactivatorDmnFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<HandlerTicketDeactivatorDmn> htdad = std::make_shared<HandlerTicketDeactivatorDmn>();
    handlerTicketDeactivatorDmnStore.insert("HandlerTicketDeactivatorDmn."s + name, htdad);
    daemonStore.insert("Daemon."s + name, htdad);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto htdad = handlerTicketDeactivatorDmnStore.get("HandlerTicketDeactivatorDmn."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["tickets"].is_array()) {
        SysError::setError("HandlerTicketDeactivatorDmn " + name + " config for tickets must be an array."s);
        return;
      }

      json tickets = j["tickets"];
      for (auto ticket : tickets) {
        if (ticket.is_string()) {
          auto handlerTicket = ticketStore.get("HandlerTicket."s + ticket.get<std::string>());
          if (handlerTicket) {
            htdad->addTicket(handlerTicket);
          } else {
            SysError::setError("HandlerTicketDeactivatorDmn config for "s + name + " has a ticket that was not found."s);
          }
        }
      }

    } else {
      SysError::setError("HandlerTicketDeactivatorDmn config for "s + name + " not found."s);
    }
  }
private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<HandlerTicketDeactivatorDmn>& handlerTicketDeactivatorDmnStore = RsrcStore<HandlerTicketDeactivatorDmn>::getInstance();
  RsrcStore<HandlerTicket>& ticketStore = RsrcStore<HandlerTicket>::getInstance();
}; 


// TODO: Crear un toggler como HandlerTicketTogglerDmn pero que use un Value de una entidad.
// Usando ese toggler, haremos que el menú se haga visitble, o no, según el estado de ese value.

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_HANDLER_TICKET_TOGGLER_DMN_H_
