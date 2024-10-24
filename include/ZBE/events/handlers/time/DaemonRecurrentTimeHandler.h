/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonRecurrentTimeHandler.h
 * @since 2017-10-25
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Recurrent Time handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H
#define ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H

#include <cstdint>
#include <memory>

#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Time handler capable of run a daemon.
 */
class ZBEAPI DaemonRecurrentTimeHandler : public TimeHandler {
public:
DaemonRecurrentTimeHandler(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.
void operator=(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.

  /** brief Empty constructor
   */
	DaemonRecurrentTimeHandler() : d(nullptr), teg(nullptr), avatar(nullptr), ticketid(0), period(0) {}

  /** brief Parametrized constructor
   * param daemon Daemon to be executed
   * param teg TimeEventGenerator to use
   * param avatar Avatar that stores the ticket for the timers generated
   * param id Id to identify the ticket to the timer
   * param period repeat time
   */
	DaemonRecurrentTimeHandler(std::shared_ptr<Daemon> daemon, std::shared_ptr<TimeEventGenerator> teg, std::shared_ptr<Avatar> avatar, uint64_t ticketid, uint64_t period) : d(daemon), teg(teg), avatar(avatar), ticketid(ticketid), period(period) {}

  /** brief Set the daemon that will be executed when the timers ends.
   *  param daemon The daemon.
   */
	void setDaemon(std::shared_ptr<Daemon> daemon) {this->d = daemon;}

  /** brief Set the time event generator to handle the timers.
   *  param teg The time event generator.
   */
	void setTimeEventGenerator(std::shared_ptr<TimeEventGenerator> teg) {this->teg = teg;}

  /** brief Set the time avator to use to access entity tickets.
   *  param avatar The avatar.
   */
	void setAvatar(std::shared_ptr<Avatar> avatar) {
	  this->avatar = avatar;
  }

  /** brief Set the avatar that stores the ticket for the timer.
   *  param avatar The avatar.
   *  param ticketid The id used to store the ticket.
   */
	void setTicketId(uint64_t ticketid) {
	  this->ticketid = ticketid;
  }

  /** brief Set the repetition time.
   *  param period The time period until the timers triggers again.
   */
	void setPeriod(uint64_t period) {this->period = period;}


  /** brief Run daemon and re-add the timer.
   *  param time used to calculate next iteration.
   */
	void run(uint64_t /*time*/) override {
    d->run();

    std::shared_ptr<TimeHandler> th = std::make_shared<DaemonRecurrentTimeHandler>(d, teg, avatar, ticketid, period);
    std::shared_ptr<TimerTicket> tt = teg->addRelativeTimer(th, period);
    avatar->replaceTicket(ticketid, tt);
	}

private:
	std::shared_ptr<Daemon> d;
  std::shared_ptr<TimeEventGenerator> teg;
  std::shared_ptr<Avatar> avatar;
	uint64_t ticketid;
	uint64_t period;
};


class DaemonRecurrentTHBldr : public Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>> {
public:
  std::shared_ptr<TimeHandler> operator()(std::shared_ptr<Entity> ent) override {
      //std::shared_ptr<Avatar> avatar = 
      std::shared_ptr<Avatar> avatar = std::make_shared<AwareAvatar>(ent);
      auto drth = std::make_shared<DaemonRecurrentTimeHandler>();
      drth->setAvatar(avatar);
      drth->setTicketId(ticketid);
      drth->setDaemon(d);
      drth->setTimeEventGenerator(teg);
      drth->setPeriod(period);
      return drth;
  }

	void setDaemon(std::shared_ptr<Daemon> daemon) {this->d = daemon;}

	void setTimeEventGenerator(std::shared_ptr<TimeEventGenerator> teg) {this->teg = teg;}

	void setTicketId(uint64_t ticketid) {
	  this->ticketid = ticketid;
  }

  /** brief Set the repetition time.
   *  param period The time period until the timers triggers again.
   */
	void setPeriod(uint64_t period) {this->period = period;}

private:
  std::shared_ptr<Daemon> d;
  std::shared_ptr<TimeEventGenerator> teg;
  uint64_t ticketid;
  uint64_t period;
};

class DaemonRecurrentTHBldrFtry : public Factory {

void create(std::string name, uint64_t) override {
  using namespace std::string_literals;

  std::shared_ptr<DaemonRecurrentTHBldr> drth = std::make_shared<DaemonRecurrentTHBldr>();
  genericRsrc.insert(zbe::factories::functionName_ + name, drth);
  specificRsrc.insert("DaemonRecurrentTHBldrFtry."s + name, drth);
}

void setup(std::string name, uint64_t cfgId) override {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    std::shared_ptr<Daemon> daemon;
    std::shared_ptr<TimeEventGenerator> teg;
    uint64_t ticketid;
    uint64_t period;
    if (j["daemon"].is_string()) {
      std::string dname = j["daemon"].get<std::string>();
      daemon = dmnRsrc.get("Daemon."s + dname);
    } else {
      SysError::setError("DaemonRecurrentTHBldrFtry config for "s + j["daemon"].get<std::string>() + ": must be a string."s);
    }

    if (j["teg"].is_string()) {
      std::string tname = j["teg"].get<std::string>();
      teg = tegRsrc.get("TimeEventGenerator."s + tname);
    } else {
      SysError::setError("DaemonRecurrentTHBldrFtry config for "s + j["timeEventGenerator"].get<std::string>() + ": must be a string."s);
    }

    if (j["period"].is_string()) {
      std::string pname = j["period"].get<std::string>();
      period = uintDict.get(pname);
    } else {
      SysError::setError("DaemonRecurrentTHBldrFtry config for "s + j["period"].get<std::string>() + ": must be a string."s);
    }

    if (j["ticketId"].is_string()) {
      std::string iname = j["ticketId"].get<std::string>();
      ticketid = uintDict.get(iname);
    } else {
      SysError::setError("DaemonRecurrentTHBldrFtry config for "s + j["ticketId"].get<std::string>() + ": must be a string."s);
    }

    auto drthbldr = specificRsrc.get("DaemonRecurrentTHBldrFtry."s + name);
    drthbldr->setDaemon(daemon);
    drthbldr->setTimeEventGenerator(teg);
    drthbldr->setTicketId(ticketid);
    drthbldr->setPeriod(period);

  } else {
    SysError::setError("DaemonRecurrentTHBldrFtry config for "s + name + " not found."s);
  }
}

private:
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<TimeEventGenerator> &tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcStore<Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>> &genericRsrc = RsrcStore<Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<DaemonRecurrentTHBldr> &specificRsrc = RsrcStore<DaemonRecurrentTHBldr>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H
