/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonSelectorAtor.h
 * @since 2018-04-02
 * @date 2018-04-02
 * @author Ludo
 * @brief Actuator that stores daemons and is able to call of them depending on
 * the value of the received Stated.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_DAEMONSELECTORACTUATOR_H_
#define ZBE_EVENTS_HANDLERS_ACTUATORS_DAEMONSELECTORACTUATOR_H_

#include <memory>
#include <unordered_map>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Actuator that stores daemons and is able to call one of them depending on
* the value of the received Stated.
*/
template <typename T, typename R>
class DaemonSelectorAlienAtor: public zbe::Actuator<WeakAvatarEntityContainer<T>, R> {
public:
  /** \brief Builds a DaemonSelectorAlienAtor with the default daemon.
   *
   */
  DaemonSelectorActuator(std::shared_ptr<Daemon> defDaemon) : daemons(), defDaemon(defDaemon) {}

  /** \brief call a daemon depending on the value of the received Stated.
   *  \param ro not used.
   */
  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<zbe::Stated> > ro) {
    zbe::Stated * s;
    ro->get()->assignAvatar(&s);
    int64_t state = s->getState();
    if(daemons.find(state) != daemons.end()) {
      daemons[state]->run();
    } else {
      defDaemon->run();
    }
  }

  /** \brief Set the daemon to use for an state
   *  \param state State for which daemon will be executed.
   *  \param daemon The Daemon.
   */
  void setDaemon(int64_t state, std::shared_ptr<Daemon> daemon){
    daemons[state] = daemon;
  }

  /** \brief Set the daemon to use for as default.
   *  \param daemon The Daemon.
   */
  void setDefault(std::shared_ptr<Daemon> daemon){
    defDaemon = daemon;
  }

private:
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Daemon> defDaemon;
};


/** \brief Actuator that stores daemons and is able to call one of them depending on
* the value of the own Stated when interacts with a given reactor type.
*/
template <typename T, typename R>
class DaemonSelectorSelfAtor: public zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R> {
public:
  /** \brief Builds a DaemonSelectorAlienAtor with the default daemon.
   *
   */
  DaemonSelectorActuator(std::shared_ptr<Daemon> defDaemon) : daemons(), defDaemon(defDaemon) {}

  /** \brief call a daemon depending on the value of the received Stated.
   *  \param ro not used.
   */
  void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<T> > ro) {
    zbe::Stated * s;
    zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R>::getCollisioner()->get()->assignAvatar(&s);
    int64_t state = s->getState();
    if(daemons.find(state) != daemons.end()) {
      daemons[state]->run();
    } else {
      defDaemon->run();
    }
  }

  /** \brief Set the daemon to use for an state
   *  \param state State for which daemon will be executed.
   *  \param daemon The Daemon.
   */
  void setDaemon(int64_t state, std::shared_ptr<Daemon> daemon){
    daemons[state] = daemon;
  }

  /** \brief Set the daemon to use for as default.
   *  \param daemon The Daemon.
   */
  void setDefault(std::shared_ptr<Daemon> daemon){
    defDaemon = daemon;
  }

private:
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Daemon> defDaemon;
};

/** \brief Actuator that stores daemons and is able to call one of them depending on
* the value of the own Stated when interacts with any reactor type.
*/
template <typename R>
class DaemonSelectorSelfAnyAtor: public zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R> {
public:
  /** \brief Builds a DaemonSelectorAlienAtor with the default daemon.
   *
   */
  DaemonSelectorActuator(std::shared_ptr<Daemon> defDaemon) : daemons(), defDaemon(defDaemon) {}

  /** \brief call a daemon depending on the value of the received Stated.
   *  \param ro not used.
   */
  void act() {
    zbe::Stated * s;
    zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R>::getCollisioner()->get()->assignAvatar(&s);
    int64_t state = s->getState();
    if(daemons.find(state) != daemons.end()) {
      daemons[state]->run();
    } else {
      defDaemon->run();
    }
  }

  /** \brief Set the daemon to use for an state
   *  \param state State for which daemon will be executed.
   *  \param daemon The Daemon.
   */
  void setDaemon(int64_t state, std::shared_ptr<Daemon> daemon){
    daemons[state] = daemon;
  }

  /** \brief Set the daemon to use for as default.
   *  \param daemon The Daemon.
   */
  void setDefault(std::shared_ptr<Daemon> daemon){
    defDaemon = daemon;
  }

private:
  std::unordered_map<int64_t, std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Daemon> defDaemon;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTUATORS_DAEMONSELECTORACTUATOR_H_
