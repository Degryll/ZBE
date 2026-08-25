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
class ZBEAPI Daemon {
public:

  /** \brief Do the actual Daemon job.
   */
  virtual void run() = 0;

  /** \brief Destructor.
   */
  virtual ~Daemon() = default;
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
DISABLE_DLL_WARN
  std::forward_list<std::shared_ptr<Funct<void>>> fs;
DISABLE_WARNING_POP()
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
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<CallDmn>& specificRsrc = RsrcStore<CallDmn>::getInstance();
  RsrcStore<Funct<void>>& functRsrc = RsrcStore<Funct<void>>::getInstance();
DISABLE_WARNING_POP()
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
DISABLE_DLL_WARN
  std::shared_ptr<F> f{};
  std::shared_ptr<L> l{};
DISABLE_WARNING_POP()
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

    if(auto funct = JSONFactory::StoreLoader<F>::loadParamCfgStoreP(functRsrc, j, zbe::factories::functionName, "function", "FunctOverAvtListDmnFtry"s)) {
      foald->setFunct(*funct);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for function is not an adecuate function name. Either it doesn't exist or type doesn't match"s);
      return;
    }

    if(auto list = JSONFactory::StoreLoader<L>::loadParamCfgStoreP(listRsrc, j, zbe::factories::listName, "list", "FunctOverAvtListDmnFtry"s)) {
      foald->setList(*list);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for list is not an adecuate list name. Either it doesn't exist or type doesn't match"s);
      return;
    }
  }
private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<FunctOverAvtListDmn<F,L>>& specificRsrc = RsrcStore<FunctOverAvtListDmn<F,L>>::getInstance();
  RsrcStore<L>& listRsrc = RsrcStore<L>::getInstance();
  RsrcStore<F>& functRsrc = RsrcStore<F>::getInstance();

  //RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
DISABLE_WARNING_POP()
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
  inline std::shared_ptr<Ticket> addDaemon(std::shared_ptr<Daemon> daemon) {
    return daemonList.push_front(daemon);
  }

private:
DISABLE_DLL_WARN
  TicketedForwardList<Daemon> daemonList{};
DISABLE_WARNING_POP()
};



// /** \brief StatedDaemonMaster is a Daemon responsible for run others Daemons. This is necessary to build the Daemons tree.
//  */
// class StatedDaemonMaster : public Daemon {
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

class ZBEAPI BaseLoopDaemon : virtual public Daemon, virtual public Stoppable {
public:

  /** \brief Builds an empty BaseLoop.
   */
  BaseLoopDaemon() : dPre(nullptr), dFrame(nullptr), keep(true) {}

  /** \brief Constructor.
   * \param pre Pre loop Daemon.
   * \param post Post Loop Daemon.
   * \param frame Frame Daemon.
   * \param common Common Behavior Daemon.
   * \param react React Behavior Daemon.
   * \param draw Drawer daemon.
   */
  BaseLoopDaemon(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> frame, std::shared_ptr<ContextTime> contextTime=zbe::SysTime::getInstance())
    : dPre(pre), dFrame(frame), contextTime(contextTime), keep(true) {}

  /** \brief Destructor.
   */
  virtual ~BaseLoopDaemon() = default;

  /** \brief It will run until stop() is called.
   */
  void run() override {
    keep = true;
    int frame = 0;
    while(keep) {  // Each iteration generates a frame.
      // Pre daemon
      contextTime->update();
      dPre->run();
      dFrame->run();
      SysError::setDebug("--------------- Frame: " + std::to_string(frame) + "---------------");
      frame++;
    }  // while keep
  }

  /** \brief Setter for the Pre-loop daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setPre(std::shared_ptr<Daemon> daemon) {dPre = daemon;}

  /** \brief Setter for the Frame daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   */
  void setFrame(std::shared_ptr<Daemon> daemon) {dFrame = daemon;}

  /** \brief Setter for the context time.
   * \param contextTime Pointer to the context time desired to be used.
   */
  inline void setContextTime(std::shared_ptr<ContextTime> contextTime) {this->contextTime = contextTime;}

  /** \brief Stops current loop.
   */
  inline void stop() override {keep = false;}

private:
DISABLE_DLL_WARN
  std::shared_ptr<Daemon> dPre;
  std::shared_ptr<Daemon> dFrame;
  std::shared_ptr<ContextTime> contextTime;
  bool keep;
DISABLE_WARNING_POP()
};

class BaseLoopDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a BaseLoopDaemonFtry
   *  \param name Name for the created BaseLoopDaemonFtry
   *  \param cfgId BaseLoopDaemonFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto ml = std::make_shared<BaseLoopDaemon>();
    daemonRsrc.insert("Daemon."s + name, ml);
    mainLoopRsrc.insert("BaseLoopDaemon."s + name, ml);
    stoppableRsrc.insert("Stoppable."s + name, ml);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json pre = j["preDaemon"];
      json frame = j["frameDaemon"];
      json cTime = j["contextTime"];

      std::shared_ptr<Daemon> preDm, frameDm;
      std::shared_ptr<ContextTime> ctxTime;

      if ((pre.is_string())
      &&  (frame.is_string())
      &&  (cTime.is_string())) {

        preDm    = daemonRsrc.get("Daemon."s + pre.get<std::string>());
        frameDm  = daemonRsrc.get("Daemon."s + frame.get<std::string>());
        ctxTime  = timeRsrc.get("ContextTime."s + cTime.get<std::string>());

        auto ml = mainLoopRsrc.get("BaseLoopDaemon."s + name);

        ml->setPre(preDm);
        ml->setFrame(frameDm);
        ml->setContextTime(ctxTime);

      } else {
        SysError::setError("Bad config for BaseLoopDaemonFtry"s);
      }   // if pre, frame

    } else {
      SysError::setError("BaseLoopDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<BaseLoopDaemon> &mainLoopRsrc = RsrcStore<BaseLoopDaemon>::getInstance();
  RsrcStore<Stoppable> &stoppableRsrc = RsrcStore<Stoppable>::getInstance();
  RsrcStore<ContextTime> &timeRsrc = RsrcStore<ContextTime>::getInstance();
  EventStore &eventStore = EventStore::getInstance();
};

class ZBEAPI FrameDaemon : virtual public Daemon {
public:
  /** \brief Builds an empty FrameDaemon.
   */
  FrameDaemon() : dPre(nullptr), dPost(nullptr), dTE(nullptr), dCBM(nullptr), dRBM(nullptr), dDM(nullptr),
      contextTime(nullptr), store(nullptr) {}

  /** \brief Constructor.
   * \param pre Pre loop Daemon.
   * \param post Post Loop Daemon.
   * \param event Event genration Daemon.
   * \param common Common Behavior Daemon.
   * \param react React Behavior Daemon.
   * \param draw Drawer daemon.
   */
  FrameDaemon(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> event, std::shared_ptr<Daemon> common, std::shared_ptr<Daemon> react, std::shared_ptr<Daemon> draw, std::shared_ptr<ContextTime> contextTime=zbe::SysTime::getInstance())
    : dPre(pre), dPost(post), dTE(event), dCBM(common), dRBM(react), dDM(draw),
      contextTime(contextTime), store(nullptr) {}

  /** \brief Destructor.
   */
  virtual ~FrameDaemon() = default;

  /** \brief It will run once per frame.
   */
  void run() override {
    // Pre daemon
    contextTime->update();
    dPre->run();
    // SysError::setDebug("FrameDaemon: Frame time: " + std::to_string(contextTime->getFrameTime()) + "ms, Lost time: " + std::to_string(contextTime->getLostTime()) + "ms");
    // Inner loop
    while (contextTime->isFrameRemaining()) {
      // Timed events generator daemon
      // SysError::setDebug("FrameDaemon: Running timed events generator daemon.");
      dTE->run();
      contextTime->setEventTime(store->getTime());
      if (contextTime->isPartialFrame() ) {
        if(contextTime->getCurrentTime() == 0) {
          break;
        }
        // commonBehaviorMaster
        // SysError::setDebug("FrameDaemon: partial:" + std::to_string(contextTime->getCurrentTime()));
        dCBM->run();
        store->manageCurrent();
        // reactBehaviorMaster
        dRBM->run();
      } else {
        // commonBehaviorMaster
        // SysError::setDebug("FrameDaemon: remaining.");
        dCBM->run();
        store->clearStore();
      }
      contextTime->updateInitTime();
    }  // while frame remaining
    // Drawer daemon
    dDM->run();
    // Post daemon
    dPost->run();
  }

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

  /** \brief Setter for the store.
   * \param store Pointer to the EventStore desired to be used.
   */
  void setEventStore(EventStore* store) {this->store = store;}

  /** \brief Setter for the context time.
   * \param contextTime Pointer to the context time desired to be used.
   */
  inline void setContextTime(std::shared_ptr<ContextTime> contextTime) {this->contextTime = contextTime;}

private:
DISABLE_DLL_WARN
  std::shared_ptr<Daemon> dPre;
  std::shared_ptr<Daemon> dPost;
  std::shared_ptr<Daemon> dTE;
  std::shared_ptr<Daemon> dCBM;
  std::shared_ptr<Daemon> dRBM;
  std::shared_ptr<Daemon> dDM;

  std::shared_ptr<ContextTime> contextTime;
  EventStore* store;

DISABLE_WARNING_POP()
};


class FrameDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a FrameDaemonFtry
   *  \param name Name for the created FrameDaemonFtry
   *  \param cfgId FrameDaemonFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto ml = std::make_shared<FrameDaemon>();
    daemonRsrc.insert("Daemon."s + name, ml);
    mainLoopRsrc.insert("FrameDaemon."s + name, ml);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json pre = j["preDaemon"];
      json event = j["eventDaemon"];
      json common = j["commonDaemon"];
      json react = j["reactDaemon"];
      json draw = j["drawDaemon"];
      json post = j["postDaemon"];
      json cTime = j["contextTime"];

      std::shared_ptr<Daemon> preDm, postDm, eventDm, commonDm, reactDm, drawDm;
      std::shared_ptr<ContextTime> ctxTime;

      if ((pre.is_string())
      &&  (event.is_string())
      &&  (common.is_string())
      &&  (react.is_string())
      &&  (draw.is_string())
      &&  (post.is_string())
      &&  (cTime.is_string())) {

        preDm    = daemonRsrc.get("Daemon."s + pre.get<std::string>());
        eventDm  = daemonRsrc.get("Daemon."s + event.get<std::string>());
        commonDm = daemonRsrc.get("Daemon."s + common.get<std::string>());
        reactDm  = daemonRsrc.get("Daemon."s + react.get<std::string>());
        drawDm   = daemonRsrc.get("Daemon."s + draw.get<std::string>());
        postDm   = daemonRsrc.get("Daemon."s + post.get<std::string>());
        ctxTime  = timeRsrc.get("ContextTime."s + cTime.get<std::string>());

        auto ml = mainLoopRsrc.get("FrameDaemon."s + name);

        ml->setPre(preDm);
        ml->setPost(postDm);
        ml->setEvent(eventDm);
        ml->setCommon(commonDm);
        ml->setReact(reactDm);
        ml->setDraw(drawDm);
        ml->setContextTime(ctxTime);
        ml->setEventStore(&eventStore);

      } else {
        SysError::setError("Bad config for FrameDaemonFtry"s);
      }   // if pre, event, common, react, draw, post
    } else {
      SysError::setError("FrameDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<FrameDaemon> &mainLoopRsrc = RsrcStore<FrameDaemon>::getInstance();
  RsrcStore<ContextTime> &timeRsrc = RsrcStore<ContextTime>::getInstance();
  EventStore &eventStore = EventStore::getInstance();
};

/** \brief The Main Loop of the game.
 */
class ZBEAPI SimpleMainLoop : virtual public Daemon, virtual public Stoppable {
public:

  /** \brief Builds an empty MainLoop.
   */
  SimpleMainLoop() : dPre(nullptr), dPost(nullptr), dTE(nullptr), dCBM(nullptr), dRBM(nullptr), dDM(nullptr),
      contextTime(nullptr), store(nullptr), keep(true) {}

  /** \brief Constructor.
   * \param pre Pre loop Daemon.
   * \param post Post Loop Daemon.
   * \param event Event genration Daemon.
   * \param common Common Behavior Daemon.
   * \param react React Behavior Daemon.
   * \param draw Drawer daemon.
   */
  SimpleMainLoop(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> event, std::shared_ptr<Daemon> common, std::shared_ptr<Daemon> react, std::shared_ptr<Daemon> draw, std::shared_ptr<ContextTime> contextTime=zbe::SysTime::getInstance())
    : dPre(pre), dPost(post), dTE(event), dCBM(common), dRBM(react), dDM(draw),
      contextTime(contextTime), store(nullptr), keep(true) {}

  /** \brief Destructor.
   */
  virtual ~SimpleMainLoop() = default;

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

  /** \brief Setter for the store.
   * \param store Pointer to the EventStore desired to be used.
   */
  void setEventStore(EventStore* store) {this->store = store;}

  /** \brief Setter for the context time.
   * \param contextTime Pointer to the context time desired to be used.
   */
  inline void setContextTime(std::shared_ptr<ContextTime> contextTime) {this->contextTime = contextTime;}

  /** \brief Stops current loop.
   */
  inline void stop() override {keep = false;}

private:
DISABLE_DLL_WARN
  std::shared_ptr<Daemon> dPre;
  std::shared_ptr<Daemon> dPost;
  std::shared_ptr<Daemon> dTE;
  std::shared_ptr<Daemon> dCBM;
  std::shared_ptr<Daemon> dRBM;
  std::shared_ptr<Daemon> dDM;

  std::shared_ptr<ContextTime> contextTime;
  EventStore* store;

  bool keep;
DISABLE_WARNING_POP()
};

/** \brief Daemon capable of end a MainLoop
 */
class StopperDaemon : virtual public Daemon {
public:

  /** \brief Builds an empty MainLoopExit.
   */
  StopperDaemon() : stoppable(nullptr), value(nullptr), exitValue(0) {}

  /** \brief Builds a MainLoopExit from its raw data.
   * \param mainLoop main loop to end.
   * \param value Value where exit value will be saved.
   * \param exitValue value to save.
   */
  StopperDaemon(std::shared_ptr<SimpleMainLoop> mainLoop, std::shared_ptr< Value<int64_t> > value, int64_t exitValue)
    : stoppable(mainLoop), value(value), exitValue(exitValue) {}

  /** \brief Virtual destructor.
   */
  ~StopperDaemon() = default;

  void setStoppable(std::shared_ptr<Stoppable> stoppable) {
    this->stoppable = stoppable;
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
    stoppable->stop();
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Stoppable> stoppable;
  std::shared_ptr< Value<int64_t> > value;
  int64_t exitValue;
DISABLE_WARNING_POP()
};

class MainLoopConfigDaemon : virtual public Daemon {
public:
  MainLoopConfigDaemon(std::shared_ptr<BaseLoopDaemon> baseLoop, std::shared_ptr<FrameDaemon> frameLoop) : baseLoop(baseLoop), frameLoop(frameLoop) {}
  MainLoopConfigDaemon() : baseLoop(nullptr), frameLoop(nullptr) {}

  ~MainLoopConfigDaemon() = default;

  void run() override {
    baseLoop->setFrame(frameLoop);
  }

  void setBaseLoop(std::shared_ptr<BaseLoopDaemon> baseLoop) {
    this->baseLoop = baseLoop;
  }

  void setFrameLoop(std::shared_ptr<Daemon> frameLoop) {
    this->frameLoop = frameLoop;
  }
private:
  std::shared_ptr<BaseLoopDaemon> baseLoop;
  std::shared_ptr<Daemon> frameLoop;
};

class MainLoopConfigDaemonFtry : virtual public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto ml = std::make_shared<MainLoopConfigDaemon>();
    daemonRsrc.insert("Daemon."s + name, ml);
    mainLoopConfigRsrc.insert("MainLoopConfigDaemon."s + name, ml);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json baseLoopName = j["baseLoop"];
      json frameDaemonName = j["frameDaemon"];

      if(!baseLoopName.is_string()) {
        SysError::setError("Bad config for MainLoopConfigDaemonFtry - baseLoop."s + name);
        return;
      }
      if(!frameDaemonName.is_string()) {
        SysError::setError("Bad config for MainLoopConfigDaemonFtry - frameDaemon."s + name);
        return;
      }

      auto mlc = mainLoopConfigRsrc.get("MainLoopConfigDaemon."s + name);
      auto baseLoop = baseLoopRsrc.get("BaseLoopDaemon."s + baseLoopName.get<std::string>());
      auto frameLoop = daemonRsrc.get("Daemon."s + frameDaemonName.get<std::string>());
      mlc->setBaseLoop(baseLoop);
      mlc->setFrameLoop(frameLoop);
    } else {
      SysError::setError("MainLoopConfigDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<MainLoopConfigDaemon> &mainLoopConfigRsrc = RsrcStore<MainLoopConfigDaemon>::getInstance();
  RsrcStore<BaseLoopDaemon> &baseLoopRsrc = RsrcStore<BaseLoopDaemon>::getInstance();
};

/** \brief Factory for Main Loop.
 */
class StopperDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a MainLoop.
   *  \param name Name for the created MainLoopFtry
   *  \param cfgId MainLoopFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto ml = std::make_shared<StopperDaemon>();
    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, ml);
    dict.insert("Daemon."s + name, id);
    id = SysIdGenerator::getId();
    stopperDaemonRsrc.insert(id, ml);
    dict.insert("StopperDaemon."s + name, id);
  }
  
  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json mainloopName = j["mainloop"];
      json valueHolderName = j["valueHolder"];
      json outValueName = j["outValue"];
      if(!mainloopName.is_string()) {
        SysError::setError("Bad config for StopperDaemonFtry - mainloop."s + name);
        return;
      }
      if(!valueHolderName.is_string()) {
        SysError::setError("Bad config for StopperDaemonFtry - valueHolder."s + name);
        return;
      }
      //TODO allow to use numbers or strings
      // if(!outValue.is_number()) {
      //   SysError::setError("Bad config for StopperDaemonFtry - outValue."s + name);
      //   return;
      // }
      if(!outValueName.is_string()) {
        SysError::setError("Bad config for StopperDaemonFtry - outValue."s + name);
        return;
      }
      auto mle = stopperDaemonRsrc.get("StopperDaemon."s + name);
      auto ml = stoppableRsrc.get("Stoppable."s + mainloopName.get<std::string>());
      auto valueHolder = valueRsrc.get(valueHolderName.get<std::string>());
      uint64_t value = uintStore.get(outValueName.get<std::string>());
      mle->setStoppable(ml);
      mle->setValue(valueHolder);
      mle->setExitValue(static_cast<int64_t>(value));
    } else {
      SysError::setError("StopperDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Stoppable> &stoppableRsrc = RsrcStore<Stoppable>::getInstance();
  RsrcStore<StopperDaemon> &stopperDaemonRsrc = RsrcStore<StopperDaemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
};

class BasePunisher {
public:
  BasePunisher() {}
  virtual ~BasePunisher() = default;
  virtual std::string getName() = 0;

  virtual std::string getListName() = 0;
};

/** \brief Daemon that applies a "punish" over a list of elements.
 */
template<typename P, typename L>
class PunisherDaemon : public Daemon, public BasePunisher {
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
   void run() override {
    for(auto e : (*list)) {
      punish->apply(e);
    }
  }

  std::string getName() override {
    return name;
  }

  std::string getListName() override {
    return listName;
  }

  void setName(std::string name) {
    this->name = name;
  }

  void setListName(std::string listName) {
    this->listName = listName;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<P> punish;
  std::shared_ptr<L> list;
  std::string name;
  std::string listName;
DISABLE_WARNING_POP()
};

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
  explicit StateMachineDaemon(std::shared_ptr<Value<int64_t> > state) : daemons(), state(state) {}

  /** \brief Destroys the StateMachineDaemon.
   */
  virtual ~StateMachineDaemon() = default;

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
DISABLE_DLL_WARN
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Value<int64_t> > state;
DISABLE_WARNING_POP()
};


/** \brief A Daemon capable of execute an specific sub Daemon depending on
* an state.
*/
class StatedDaemon : public Daemon {
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
  explicit StatedDaemon(std::shared_ptr<Value<int64_t> > state) : daemons(), state(state) {}

  /** \brief Destroys the StateMachineDaemon.
   */
  virtual ~StatedDaemon() = default;

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
DISABLE_DLL_WARN
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Value<int64_t> > state;
DISABLE_WARNING_POP()
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

    if(auto value = JSONFactory::StoreLoader<Value<int64_t>>::loadParamCfgStore(valueIRsrc, j, "value"s, "StatedDaemonFtry"s)) {
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
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<StatedDaemon>& specificRsrc = RsrcStore<StatedDaemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
DISABLE_WARNING_POP()
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

  ConditionalIntDaemon() = default;

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
DISABLE_DLL_WARN
  int64_t condition;
  std::shared_ptr<Value<int64_t> > val;
  std::shared_ptr<Daemon> daemon;
DISABLE_WARNING_POP()
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

    if(auto daemon = JSONFactory::StoreLoader<Daemon>::loadParamCfgStoreP(mainRsrc, j, zbe::factories::daemonName, "daemon", "ConditionalIntDaemonFtry"s)) {
      cid->setDaemon(*daemon);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for daemon is not an adecuate daemon name."s);
      return;
    }

    if(auto value = JSONFactory::StoreLoader<Value<int64_t>>::loadParamCfgStore(valueIRsrc, j, "value"s, "ConditionalIntDaemonFtry"s)) {
      cid->setConditionValue(*value);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for value is not an adecuate value name."s);
      return;
    }

    if(auto condition = JSONFactory::DictLoader<int64_t>::loadParamCfgDict(intStore, j, "condition"s, "ConditionalIntDaemonFtry"s)) {
      cid->setCondition(*condition);
    } else {
      SysError::setError("ConditionalIntDaemonFtry config for condition is not an adecuate int name."s);
      return;
    }

  }
private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ConditionalIntDaemon>& specificRsrc = RsrcStore<ConditionalIntDaemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
DISABLE_WARNING_POP()
};

class BValueTogglerDaemon : public Daemon {
public:
  BValueTogglerDaemon() = default;

  void run() override {
    val->set(!val->get());
  }

  void setValue(std::shared_ptr<Value<bool>> val) {
    this->val = val;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Value<bool>> val;
DISABLE_WARNING_POP()
};

class BValueTogglerDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<BValueTogglerDaemon> bvt = std::make_shared<BValueTogglerDaemon>();
    mainRsrc.insert("Daemon."s + name, bvt);
    specificRsrc.insert("BValueTogglerDaemon."s + name, bvt);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    auto bvt = specificRsrc.get("BValueTogglerDaemon."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("BValueTogglerDaemon " + name + " config for entity must be a string."s);
        return;
      }
      auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
      if (!entity) {
        SysError::setError("BValueTogglerDaemon " + name + " config for entity not found."s);
        return;
      }
      if (!j["valueIdx"].is_string()) {
        SysError::setError("BValueTogglerDaemon " + name + " config for valueIdx must be a string."s);
        return;
      }

      uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());

      auto value = entity->getBool(valueIdx);
      if (!value) {
        SysError::setError("BValueTogglerDaemon " + name + " config for valueIdx not found."s);
        return;
      }
      bvt->setValue(value);
      
    } else {
      SysError::setError("BValueTogglerDaemon config for "s + name + " not found."s);
    }
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<BValueTogglerDaemon>& specificRsrc = RsrcStore<BValueTogglerDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcStore<Value<bool>> &valueBRsrc = RsrcStore<Value<bool>>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
DISABLE_WARNING_POP()
};

class ParametricTicketToggleDaemon : public Daemon {
public:
  ParametricTicketToggleDaemon() : negate(false) {}

  void run() override {
    bool active = val->get();
    if (negate) {
      active = !active;
    }

    if (active) {
      ticket->setACTIVE();
    } else {
      ticket->setINACTIVE();
    }
  }

  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->ticket = ticket;
  }

  void setValue(std::shared_ptr<Value<bool>> val) {
    this->val = val;
  }

  void setNegate(bool negate) {
    this->negate = negate;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Ticket> ticket;
  std::shared_ptr<Value<bool>> val;
  bool negate;
DISABLE_WARNING_POP()
};

class ParametricTicketToggleDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ParametricTicketToggleDaemon> pttd = std::make_shared<ParametricTicketToggleDaemon>();
    mainRsrc.insert("Daemon."s + name, pttd);
    specificRsrc.insert("ParametricTicketToggleDaemon."s + name, pttd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    auto pttd = specificRsrc.get("ParametricTicketToggleDaemon."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for entity must be a string."s);
        return;
      }
      auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
      if (!entity) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for entity not found."s);
        return;
      }
      if (!j["valueIdx"].is_string()) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for valueIdx must be a string."s);
        return;
      }

      uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());
      auto value = entity->getBool(valueIdx);
      if (!value) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for valueIdx not found."s);
        return;
      }

      if (!j["ticket"].is_string()) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for ticket must be a string."s);
        return;
      }

      std::string ticketName = j["ticket"].get<std::string>();
      auto ticket = ticketRsrc.get(ticketName);
      if (!ticket) {
        SysError::setError("ParametricTicketToggleDaemon " + name + " config for ticket not found."s);
        return;
      }

      bool negate = false;
      if (j.contains("negate") && j["negate"].is_boolean()) {
        negate = j["negate"].get<bool>();
      }

      pttd->setValue(value);
      pttd->setTicket(ticket);
      pttd->setNegate(negate);
    } else {
      SysError::setError("ParametricTicketToggleDaemon config for "s + name + " not found."s);
    }
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ParametricTicketToggleDaemon>& specificRsrc = RsrcStore<ParametricTicketToggleDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcStore<Ticket>& ticketRsrc = RsrcStore<Ticket>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
DISABLE_WARNING_POP()
};

/** \brief Daemon that toggles a Ticket using internal state.
 */
class TicketToggleDaemon : public Daemon {
public:
  TicketToggleDaemon() : active(false) {}

  void run() override {
    active = !active;
    if (active) {
      ticket->setACTIVE();
    } else {
      ticket->setINACTIVE();
    }
  }

  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->ticket = ticket;
  }

  void setInitialState(bool active) {
    this->active = active;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Ticket> ticket;
  bool active;
DISABLE_WARNING_POP()
};

class TicketToggleDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<TicketToggleDaemon> ttd = std::make_shared<TicketToggleDaemon>();
    mainRsrc.insert("Daemon."s + name, ttd);
    specificRsrc.insert("TicketToggleDaemon."s + name, ttd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    auto ttd = specificRsrc.get("TicketToggleDaemon."s + name);
    if(cfg) {
      auto j = *cfg;

      if (!j["ticket"].is_string()) {
        SysError::setError("TicketToggleDaemon " + name + " config for ticket must be a string."s);
        return;
      }
      std::string ticketName = j["ticket"].get<std::string>();
      auto ticket = ticketRsrc.get(ticketName);
      if (!ticket) {
        SysError::setError("TicketToggleDaemon " + name + " config for ticket not found."s);
        return;
      }
      ttd->setTicket(ticket);

      bool initialState = false;
      if (j.contains("initialState") && j["initialState"].is_boolean()) {
        initialState = j["initialState"].get<bool>();
      }
      ttd->setInitialState(initialState);
    } else {
      SysError::setError("TicketToggleDaemon config for "s + name + " not found."s);
    }
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<TicketToggleDaemon>& specificRsrc = RsrcStore<TicketToggleDaemon>::getInstance();
  RsrcStore<Ticket>& ticketRsrc = RsrcStore<Ticket>::getInstance();
DISABLE_WARNING_POP()
};

class ParametricCTXTimePauseDaemon : public Daemon {
public:
  ParametricCTXTimePauseDaemon() : negate(false) {}

  void run() override {
    bool isPaused = paused->get();
    if (negate) {
      SysError::setDebug("Negado");
      isPaused = !isPaused;
    }

    if (isPaused) {
      SysError::setDebug("Y pausando");
      ctxTime->pause();
    } else {
      SysError::setDebug("Y despausando");
      ctxTime->resume(0);
    }
    // paused->set(!paused->get());
  }

  void setContextTime(std::shared_ptr<ContextTime> ctxTime) {
    this->ctxTime = ctxTime;
  }

  void setParentTime(std::shared_ptr<ContextTime> parentTime) {
    this->parentTime = parentTime;
  }

  void setValue(std::shared_ptr<Value<bool>> paused) {
    this->paused = paused;
  }

  void setNegate(bool negate) {
    this->negate = negate;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<ContextTime> ctxTime;
  std::shared_ptr<ContextTime> parentTime;
  std::shared_ptr<Value<bool>> paused;
  bool negate;
DISABLE_WARNING_POP()
};

class ParametricCTXTimePauseDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ParametricCTXTimePauseDaemon> pctpd = std::make_shared<ParametricCTXTimePauseDaemon>();
    mainRsrc.insert("Daemon."s + name, pctpd);
    specificRsrc.insert("ParametricCTXTimePauseDaemon."s + name, pctpd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    auto pctpd = specificRsrc.get("ParametricCTXTimePauseDaemon."s + name);
    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for entity must be a string."s);
        return;
      }
      auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
      if (!entity) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for entity not found."s);
        return;
      }
      if (!j["valueIdx"].is_string()) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for valueIdx must be a string."s);
        return;
      }

      uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());
      auto value = entity->getBool(valueIdx);
      if (!value) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for valueIdx not found."s);
        return;
      }

      if (!j["contextTime"].is_string()) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for contextTime must be a string."s);
        return;
      }

      std::string ctxTimeName = j["contextTime"].get<std::string>();
      auto ctxTime = ctxTimeRsrc.get("ContextTime."s + ctxTimeName);
      if (!ctxTime) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for contextTime not found."s);
        return;
      }

      if (!j["parentTime"].is_string()) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for parentTime must be a string."s);
        return;
      }

      std::string parentTimeName = j["parentTime"].get<std::string>();
      auto parentTime = ctxTimeRsrc.get("ContextTime."s + parentTimeName);
      if (!parentTime) {
        SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for parentTime not found."s);
        return;
      }

      bool negate = false;
      if (j.contains("negate")) {
        if(j["negate"].is_boolean()) {
          negate = j["negate"].get<bool>();
        } else {
          SysError::setError("ParametricCTXTimePauseDaemon " + name + " config for negate must be a boolean."s);
        }
      }

      pctpd->setValue(value);
      pctpd->setContextTime(ctxTime);
      pctpd->setParentTime(parentTime);
      pctpd->setNegate(negate);
    } else {
      SysError::setError("ParametricCTXTimePauseDaemon config for "s + name + " not found."s);
    }
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ParametricCTXTimePauseDaemon>& specificRsrc = RsrcStore<ParametricCTXTimePauseDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcStore<ContextTime>& ctxTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
DISABLE_WARNING_POP()
};

class ValueBoolSelectorDaemon : public Daemon {
public:
  ValueBoolSelectorDaemon() = default;

  void run() override {
    if(val->get()) {
      SysError::setDebug("######################## Running true");
      trueDaemon->run();
    } else {
      SysError::setDebug("######################## Running false");
      falseDaemon->run();
    }
  }

  void setValue(std::shared_ptr<Value<bool>> val) {
    this->val = val;
  }

  void setTrueDaemon(std::shared_ptr<Daemon> daemon) {
    this->trueDaemon = daemon;
  }

  void setFalseDaemon(std::shared_ptr<Daemon> daemon) {
    this->falseDaemon = daemon;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Value<bool>> val;
  std::shared_ptr<Daemon> trueDaemon;
  std::shared_ptr<Daemon> falseDaemon;
DISABLE_WARNING_POP()
};

class ValueBoolSelectorDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ValueBoolSelectorDaemon> vbstd = std::make_shared<ValueBoolSelectorDaemon>();
    mainRsrc.insert("Daemon."s + name, vbstd);
    specificRsrc.insert("ValueBoolSelectorDaemon."s + name, vbstd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto vbstd = specificRsrc.get("ValueBoolSelectorDaemon."s + name);

    if(!cfg) {
      SysError::setError("ValueBoolSelectorDaemonFtry config for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;
    if(!j["entity"].is_string()) {
      SysError::setError("ValueBoolSelectorDaemonFtry config for entity must be a string."s);
      return;
    }

    auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
    if(!entity) {
      SysError::setError("ValueBoolSelectorDaemonFtry config for entity not found."s);
      return;
    }

    if(!j["valueIdx"].is_string()) {
      SysError::setError("ValueBoolSelectorDaemonFtry config for valueIdx must be a string."s);
      return;
    }

    uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());
    auto value = entity->getBool(valueIdx);
    if(!value) {
      SysError::setError("ValueBoolSelectorDaemonFtry config for valueIdx not found."s);
      return;
    }

    if(auto trueDaemon = JSONFactory::StoreLoader<Daemon>::loadParamCfgStoreP(mainRsrc, j, zbe::factories::daemonName, "trueDaemon", "ValueBoolSelectorDaemonFtry"s)) {
      vbstd->setTrueDaemon(*trueDaemon);
    } else {
      SysError::setError("ValueBoolSelectorDaemonFtry config for trueDaemon is not an adecuate daemon name."s);
      return;
    }

    if(auto falseDaemon = JSONFactory::StoreLoader<Daemon>::loadParamCfgStoreP(mainRsrc, j, zbe::factories::daemonName, "falseDaemon", "ValueBoolSelectorDaemonFtry"s)) {
      vbstd->setFalseDaemon(*falseDaemon);
    } else {
      SysError::setError("ValueBoolSelectorDaemonFtry config for falseDaemon is not an adecuate daemon name."s);
      return;
    }

    vbstd->setValue(value);
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ValueBoolSelectorDaemon>& specificRsrc = RsrcStore<ValueBoolSelectorDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
DISABLE_WARNING_POP()
};

class ValueIntSelectorDaemon : public Daemon {
public:
  ValueIntSelectorDaemon() = default;

  void run() override {
    auto current = val->get();
    auto it = daemons.find(current);
    if(it != daemons.end() && it->second) {
      it->second->run();
    } else if(defaultDaemon) {
      defaultDaemon->run();
    }
  }

  void setValue(std::shared_ptr<Value<int64_t>> val) {
    this->val = val;
  }

  void setDaemon(int64_t value, std::shared_ptr<Daemon> daemon) {
    daemons[value] = daemon;
  }

  void setDefaultDaemon(std::shared_ptr<Daemon> daemon) {
    defaultDaemon = daemon;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<Value<int64_t>> val;
  std::unordered_map<int64_t, std::shared_ptr<Daemon>> daemons;
  std::shared_ptr<Daemon> defaultDaemon;
DISABLE_WARNING_POP()
};

class ValueIntSelectorDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<ValueIntSelectorDaemon> vistd = std::make_shared<ValueIntSelectorDaemon>();
    mainRsrc.insert("Daemon."s + name, vistd);
    specificRsrc.insert("ValueIntSelectorDaemon."s + name, vistd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto vistd = specificRsrc.get("ValueIntSelectorDaemon."s + name);

    if(!cfg) {
      SysError::setError("ValueIntSelectorDaemonFtry config for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;
    if(!j["entity"].is_string()) {
      SysError::setError("ValueIntSelectorDaemonFtry config for entity must be a string."s);
      return;
    }

    auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
    if(!entity) {
      SysError::setError("ValueIntSelectorDaemonFtry config for entity not found."s);
      return;
    }

    if(!j["valueIdx"].is_string()) {
      SysError::setError("ValueIntSelectorDaemonFtry config for valueIdx must be a string."s);
      return;
    }

    uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());
    auto value = entity->getInt(valueIdx);
    if(!value) {
      SysError::setError("ValueIntSelectorDaemonFtry config for valueIdx not found."s);
      return;
    }

    if(!j["daemons"].is_object()) {
      SysError::setError("ValueIntSelectorDaemonFtry config for daemons must be an object."s);
      return;
    }

    if(!JSONFactory::loadAllIndexedRev<Daemon, int64_t>(mainRsrc, intStore, j, zbe::factories::daemonName, "daemons"s, "ValueIntSelectorDaemonFtry"s,
      [&](int64_t idx, std::shared_ptr<Daemon> daemon) {
        vistd->setDaemon(idx, daemon);
        return true;
      })) {
      return;
    }

    if(auto defaultDaemon = JSONFactory::StoreLoader<Daemon>::loadParamCfgStoreP(mainRsrc, j, zbe::factories::daemonName, "defaultDaemon", "ValueIntSelectorDaemonFtry"s)) {
      vistd->setDefaultDaemon(*defaultDaemon);
    } else {
      SysError::setError("ValueIntSelectorDaemonFtry config for defaultDaemon is not an adecuate daemon name."s);
      return;
    }

    vistd->setValue(value);
  }

private:
DISABLE_DLL_WARN
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ValueIntSelectorDaemon>& specificRsrc = RsrcStore<ValueIntSelectorDaemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_DAEMON_H
