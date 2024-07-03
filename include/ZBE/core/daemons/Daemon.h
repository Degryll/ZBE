/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Daemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Ludo Degryll Batis
 * @brief Define the minimal functions of demons.
 */

#ifndef ZBE_CORE_DAEMONS_DAEMON_H
#define ZBE_CORE_DAEMONS_DAEMON_H


#include <memory>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/tools.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class Daemon {
public:

  /** \brief Do the actual Daemon job.
   */
  virtual void run() = 0;

  /** \brief Destructor.
   */
  virtual ~Daemon() {};
};

class CallDmn : public Daemon {
public:
  CallDmn() : fs() {}
  void run() override {
    for(auto f : fs) {
      (*f)();
    }
  }

  void addFunct(std::shared_ptr<Funct<void>> f) {
    this->fs.push_front(f);
  }

private:
  std::forward_list<std::shared_ptr<Funct<void>>> fs;
};

class CallDmnFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<CallDmn> cdmn = std::make_shared<CallDmn>();
    mainRsrc.insert("Daemon."s + name, cdmn);
    specificRsrc.insert("CallDmn."s + name, cdmn);
  }
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("CallDmnFtry config for "s + name + " not found."s);
      return;
    }
    auto cdmn = specificRsrc.get("CallDmn."s + name);
    auto j = *cfg;

    JSONFactory::loadAllP<Funct<void>>(functRsrc, j, zbe::factories::functionName, "calls"s, "CallDmnFtry"s,        
      [&](std::shared_ptr<Funct<void>> rctbldr) {
        cdmn->addFunct(rctbldr);
        return true;
      }
    );
  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<CallDmn>& specificRsrc = RsrcStore<CallDmn>::getInstance();
  RsrcStore<Funct<void>>& functRsrc = RsrcStore<Funct<void>>::getInstance();
};

template<typename F, typename L>
class FunctOverAvtListDmn : public Daemon {
public:
  void run() override {
    for(auto avt : *l) {
      (*f)(avt);
    }
  }

  void setFunct(std::shared_ptr<F> f) {
    this->f = f;
  }

  void setList(std::shared_ptr<L> l) {
    this->l = l;
  }

private:
  std::shared_ptr<F> f{};
  std::shared_ptr<L> l{};
};

template<typename F, typename L>
class FunctOverAvtListDmnFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<FunctOverAvtListDmn<F,L>> foald = std::make_shared<FunctOverAvtListDmn<F,L>>();
    mainRsrc.insert("Daemon."s + name, foald);
    specificRsrc.insert("FunctOverAvtListDmn."s + name, foald);
  }
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("FunctOverAvtListDmnFtry config for "s + name + " not found."s);
      return;
    }
    auto foald = specificRsrc.get("FunctOverAvtListDmn."s + name);
    auto j = *cfg;

    if(auto funct = JSONFactory::loadParamCfgStoreP<F>(functRsrc, j, zbe::factories::functionName, "function", "FunctOverAvtListDmnFtry"s)) {
      foald->setFunct(*funct);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for function is not an adecuate function name. Either it doesn't exist or type doesn't match"s);
      return;
    }

    if(auto list = JSONFactory::loadParamCfgStoreP<L>(listRsrc, j, zbe::factories::listName, "list", "FunctOverAvtListDmnFtry"s)) {
      foald->setList(*list);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for list is not an adecuate list name. Either it doesn't exist or type doesn't match"s);
      return;
    }
  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<FunctOverAvtListDmn<F,L>>& specificRsrc = RsrcStore<FunctOverAvtListDmn<F,L>>::getInstance();
  RsrcStore<L>& listRsrc = RsrcStore<L>::getInstance();
  RsrcStore<F>& functRsrc = RsrcStore<F>::getInstance();

  //RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};

/** \brief DaemonMaster is a Daemon responsible for run others Daemons. This is necessary to build the Daemons tree.
 */
class ZBEAPI DaemonMaster : public Daemon {
public:

  /** \brief Destructor and the contained Daemons.
   */
  virtual ~DaemonMaster() = default;

  /** \brief It will run all Daemons added to this DaemonMaster.
   */
  void run() override;

  /** \brief Add a Daemon to be run by this Daemon.
   *  The given Daemon will be stored by this Daemon and destroyed with it.
   * \param daemon Pointer to the Daemon desired to be stored and executed.
   * \return void
   *
   */
  std::shared_ptr<Ticket> addDaemon(std::shared_ptr<Daemon> daemon) {
    return daemonList.push_front(daemon);
  }

private:
  TicketedForwardList<Daemon> daemonList{};
};



// /** \brief StatedDaemonMaster is a Daemon responsible for run others Daemons. This is necessary to build the Daemons tree.
//  */
// class ZBEAPI StatedDaemonMaster : public Daemon {
// public:

//   /** \brief Destructor and the contained Daemons.
//    */
//   ~StatedDaemonMaster() = default;

//   /** \brief It will run all Daemons added to this StatedDaemonMaster.
//    */
//   void run() override;

//   /** \brief Add a Daemon to be run by this Daemon.
//    * \param value The value that contains the state that decides what daemon to run
//    * \return void
//    */
//   void setValue(std::shared_ptr< Value<int64_t> > value) {
//     this->state = value;
//   }

//   /** \brief Add a Daemon to be run by this Daemon.
//    *  The given Daemon will be stored by this Daemon and destroyed with it.
//    * \param stated state associated to the given daemon.
//    * \param daemon Pointer to the Daemon desired to be stored and executed.
//    * \return void
//    *
//    */
//   std::shared_ptr<Ticket> addDaemon(uint64_t state, std::shared_ptr<Daemon> daemon) {
//     return daemonList.push_front(daemon);
//   }

// private:
//   TicketedForwardList<Daemon> daemonList;
//   std::shared_ptr< Value<int64_t> > state;

// };


/** \brief The Main Loop of the game.
 */
class ZBEAPI MainLoop : virtual public Daemon {
public:

  /** \brief Builds an empty MainLoop.
   */
  MainLoop() : dPre(nullptr), dPost(nullptr), dTE(nullptr), dCBM(nullptr), dRBM(nullptr), dDM(nullptr),
      contextTime(nullptr), store(zbe::EventStore::getInstance()), keep(true) {}

  /** \brief Constructor.
   * \param pre Pre loop Daemon.
   * \param post Post Loop Daemon.
   * \param event Event genration Daemon.
   * \param common Common Behavior Daemon.
   * \param react React Behavior Daemon.
   * \param draw Drawer daemon.
   */
  MainLoop(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> event, std::shared_ptr<Daemon> common, std::shared_ptr<Daemon> react, std::shared_ptr<Daemon> draw, std::shared_ptr<ContextTime> contextTime=zbe::SysTime::getInstance())
    : dPre(pre), dPost(post), dTE(event), dCBM(common), dRBM(react), dDM(draw),
      contextTime(contextTime), store(zbe::EventStore::getInstance()), keep(true) {}

  /** \brief Destructor.
   */
  virtual ~MainLoop() = default;

  /** \brief It will run until stop() is called.
   *  For each frame it will:
   *    execute "pre" daemon (usually do nothing): mean to prepare the frame.
   *    while there is frame time remaining:
   *      execute "event" daemon: mean to generate "timed" events.
   *      if there are events:
   *        execute "common" daemon: mean to run entity behaviors until first event
   *        call event management
   *        execute "react" daemon: mean to run event related entity behaviors
   *      if there are no events:
   *        execute "common" daemon: mean to run entity behaviors until frame end
   *      update frame time remaining
   *    execute "draw" daemon: mean to draw game entities
   *    execute "post" daemon (usually do nothing): mean to clean up the frame.
   *  \sa stop(), EventStore::manage()
   */
  void run() override;

  /** \brief Setter for the Pre-loop daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setPre(std::shared_ptr<Daemon> daemon) {dPre = daemon;}

  /** \brief Setter for the Post-loop daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setPost(std::shared_ptr<Daemon> daemon) {dPost = daemon;}

  /** \brief Setter for the Timed Events daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setEvent(std::shared_ptr<Daemon> daemon) {dTE = daemon;}

  /** \brief Setter for the Common Behavior Daemon Master.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setCommon(std::shared_ptr<Daemon> daemon) {dCBM = daemon;}

  /** \brief Setter for the React Behavior Daemon Master.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setReact(std::shared_ptr<Daemon> daemon) {dRBM = daemon;}

  /** \brief Setter for the Drawlo  Master.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setDraw(std::shared_ptr<Daemon> daemon) {dDM = daemon;}

  /** \brief Setter for the context time.
   * \param contextTime Pointer to the context time desired to be used.
   */
  void setContextTime(std::shared_ptr<ContextTime> contextTime) {this->contextTime = contextTime;}

  /** \brief Stops current loop.
   */
  void stop() {keep = false;}

private:
  std::shared_ptr<Daemon> dPre;
  std::shared_ptr<Daemon> dPost;
  std::shared_ptr<Daemon> dTE;
  std::shared_ptr<Daemon> dCBM;
  std::shared_ptr<Daemon> dRBM;
  std::shared_ptr<Daemon> dDM;

  std::shared_ptr<ContextTime> contextTime;
  zbe::EventStore &store;

  bool keep;

};

/** \brief Daemon capable of end a MainLoop
 */
class ZBEAPI MainLoopExit : virtual public Daemon {
public:

  /** \brief Builds an empty MainLoopExit.
   */
  MainLoopExit() : mainLoop(nullptr), value(nullptr), exitValue(0) {}

  /** \brief Builds a MainLoopExit from its raw data.
   * \param mainLoop main loop to end.
   * \param value Value where exit value will be saved.
   * \param exitValue value to save.
   */
  MainLoopExit(std::shared_ptr<MainLoop> mainLoop, std::shared_ptr< Value<int64_t> > value, int64_t exitValue)
    : mainLoop(mainLoop), value(value), exitValue(exitValue) {}

  /** \brief Virtual destructor.
   */
  ~MainLoopExit() {}

  void setMainLoop(std::shared_ptr<MainLoop> mainLoop) {
    this->mainLoop = mainLoop;
  }

  void setValue(std::shared_ptr< Value<int64_t> > value) {
    this->value = value;
  }

  void setExitValue(int64_t exitValue) {
    this->exitValue = exitValue;
  }

  /** \brief End MainLoop and save given value.
   */
  void run() override {
    value->set(exitValue);
    mainLoop->stop();
  }

private:
  std::shared_ptr<MainLoop> mainLoop;
  std::shared_ptr< Value<int64_t> > value;
  int64_t exitValue;
};

/** \brief Daemon that applies a "punish" over a list of elements.
 */
template<typename P, typename L>
class PunisherDaemon : public Daemon {
public:

  PunisherDaemon(const PunisherDaemon&) = delete; //!< Avoid copy.
  void operator=(const PunisherDaemon&) = delete; //!< Avoid copy.

  /** \brief Builds an empty Punisher Daemon.
   *
   */
  PunisherDaemon() : punish(nullptr), list(nullptr) {}

  /** \brief Build the Daemon with a punish and a list id.
   * The given Behavior will be stored by this Daemon and destroyed with it. It will be executed when run method is called.
   * \param daemon Pointer to the daemon desired to be stored and executed.
   *
   */
  PunisherDaemon(std::shared_ptr<P> punish, std::shared_ptr<L> list) : punish(punish), list(list) {}

  /** \brief Destroys the PunisherDaemon and the contained punisher.
   */
  virtual ~PunisherDaemon() = default;

  void setPunish(std::shared_ptr<P> punish) {
    this->punish = punish;
  }

  void setList(std::shared_ptr<L> list) {
    this->list = list;
  }

  /** \brief It will run the Behavior over the entity list.
   */
  void run() override;

private:
  std::shared_ptr<P> punish;
  std::shared_ptr<L> list;
};

template<typename P, typename L>
void PunisherDaemon<P, L>::run() {
  for(auto e : (*list)) {
    punish->apply(e);
  }
}

/** \brief Punishers that applies Behaviors over a list of entities.
*/
template<typename L, typename ...E>
using BehaviorDaemon = PunisherDaemon<Behavior<E...>, L>;

/** \brief A Daemon capable of execute an specific sub Daemon depending on
* an state.
*/
class ZBEAPI StateMachineDaemon : public Daemon {
public:

  StateMachineDaemon(const StateMachineDaemon&) = delete;
  void operator=(const StateMachineDaemon&) = delete;

  /** \brief Builds an empty StateMachineDaemon.
   */
  StateMachineDaemon() : daemons(), state(nullptr) {}

  /** \brief Build the Daemon with the value used to select the state
   * and an initial state amount.
   *
   */
  StateMachineDaemon(std::shared_ptr<Value<int64_t> > state) : daemons(), state(state) {}

  /** \brief Destroys the StateMachineDaemon.
   */
  virtual ~StateMachineDaemon() {}

  /** \brief Sets the Daemon to use for a given state.
   * |param state desired state
   * |param daemon Daemon daemon to run
   */
  void setDaemon(int64_t state, std::shared_ptr<Daemon> daemon) {
    daemons[state]= daemon;
  }

  /** \brief Sets the Value<int64_t> where the state will be found.
   * |param state state container.
   */
  void setStateValue(std::shared_ptr<Value<int64_t> > state) {
    this->state = state;
  }

  /** \brief It will run the contained daemons while "state" is positive.
   */
  void run() override;

private:
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Value<int64_t> > state;
};


/** \brief A Daemon capable of execute an specific sub Daemon depending on
* an state.
*/
class ZBEAPI StatedDaemon : public Daemon {
public:

  StatedDaemon(const StateMachineDaemon&) = delete;
  void operator=(const StateMachineDaemon&) = delete;

  /** \brief Builds an empty StatedDaemon.
   */
  StatedDaemon() : daemons(), state(nullptr) {}

  /** \brief Build the Daemon with the value used to select the state
   * and an initial state amount.
   *
   */
  StatedDaemon(std::shared_ptr<Value<int64_t> > state) : daemons(), state(state) {}

  /** \brief Destroys the StateMachineDaemon.
   */
  virtual ~StatedDaemon() {}

  /** \brief Sets the Daemon to use for a given state.
   * |param state desired state
   * |param daemon Daemon daemon to run
   */
  void setDaemon(int64_t state, std::shared_ptr<Daemon> daemon) {
    daemons[state]= daemon;
  }

  /** \brief Sets the Value<int64_t> where the state will be found.
   * |param state state container.
   */
  void setStateValue(std::shared_ptr<Value<int64_t> > state) {
    this->state = state;
  }

  /** \brief It will run the contained daemons while "state" is positive.
   */
  void run() override {
    int64_t s = state->get();
    auto it = daemons.find(s);
    if(it != daemons.end()) {
      it->second->run();
    }
  }

private:
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Value<int64_t> > state;
};

class StatedDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<StatedDaemon> smd = std::make_shared<StatedDaemon>();
    mainRsrc.insert("Daemon."s + name, smd);
    specificRsrc.insert("StatedDaemon."s + name, smd);
  }
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("StatedDaemonFtry config for "s + name + " not found."s);
      return;
    }
    auto j = *cfg;
    auto smd = specificRsrc.get("StatedDaemon."s + name);

    if(auto value = JSONFactory::loadParamCfgStore<Value<int64_t>>(valueIRsrc, j, "value"s, "StatedDaemonFtry"s)) {
      smd->setStateValue(*value);
    } else {
      SysError::setError("StatedDaemonFtry config for value is not an adecuate value name."s);
      return;
    }

    JSONFactory::loadAllIndexedRev<Daemon, int64_t>(mainRsrc, intDict, j, zbe::factories::daemonName, "daemons"s, "StatedDaemonFtry"s,
    [&](int64_t idx, std::shared_ptr<Daemon> dmn) {
      smd->setDaemon(idx, dmn);
      return true;
    });

  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<StatedDaemon>& specificRsrc = RsrcStore<StatedDaemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
};

/** \brief Daemon that does nothing.
 */
class VoidDaemon : public Daemon {
public:

  /** \brief Do nothing.
   */
  void run() override {}
};

/** \brief Daemon that does nothing.
 */
class ConditionalIntDaemon : public Daemon {
public:

  /** \brief Do nothing.
   */
  void run() override {
    if(val->get() == condition) {
      daemon->run();
    }
  }

  /** \brief Sets the expected condition to run the underlying daemon.
   * |param condition The expected condition value.
   */
  void setCondition(int64_t condition) {
    this->condition = condition;
  }

  /** \brief Sets the Value<int64_t> where the state will be found.
   * |param val Condition container.
   */
  void setConditionValue(std::shared_ptr<Value<int64_t> > val) {
    this->val = val;
  }

  /** \brief Sets the Daemon to be executed if the condtion is fullfiled.
   * |param daemon The daemon.
   */
  void setDaemon(std::shared_ptr<Daemon> daemon) {
    this->daemon = daemon;
  }

private:

  int64_t condition;
  std::shared_ptr<Value<int64_t> > val;
  std::shared_ptr<Daemon> daemon;

};

class ConditionalIntDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ConditionalIntDaemon> cid = std::make_shared<ConditionalIntDaemon>();
    mainRsrc.insert("Daemon."s + name, cid);
    specificRsrc.insert("ConditionalIntDaemon."s + name, cid);
  }
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("ConditionalIntDaemonFtry config for "s + name + " not found."s);
      return;
    }
    auto cid = specificRsrc.get("ConditionalIntDaemon."s + name);
    auto j = *cfg;

    if(auto daemon = JSONFactory::loadParamCfgStoreP<Daemon>(mainRsrc, j, zbe::factories::daemonName, "daemon", "ConditionalIntDaemonFtry"s)) {
      cid->setDaemon(*daemon);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for daemon is not an adecuate daemon name."s);
      return;
    }

    if(auto value = JSONFactory::loadParamCfgStore<Value<int64_t>>(valueIRsrc, j, "value"s, "ConditionalIntDaemonFtry"s)) {
      cid->setConditionValue(*value);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for value is not an adecuate value name."s);
      return;
    }

    if(auto condition = JSONFactory::loadParamCfgDict<int64_t>(intStore, j, "condition"s, "ConditionalIntDaemonFtry"s)) {
      cid->setCondition(*condition);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for condition is not an adecuate int name."s);
      return;
    }

  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ConditionalIntDaemon>& specificRsrc = RsrcStore<ConditionalIntDaemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_DAEMON_H
