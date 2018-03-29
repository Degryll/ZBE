/**
 * Copyright 2015 Batis Degryll Ludo
 * @file StateMachineDaemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief A Daemon capable of execute an specific sub Daemon depending on
 * an state.
 */

#ifndef ZBE_CORE_DAEMONS_STATEMACHINEDAEMON_H_
#define ZBE_CORE_DAEMONS_STATEMACHINEDAEMON_H_

#include <vector>
#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/shared/Value.h"


namespace zbe {
/** \brief A Daemon capable of execute an specific sub Daemon depending on
* an state.
*/
class StateMachineDaemon : public Daemon {
public:

  StateMachineDaemon(const StateMachineDaemon&) = delete;
  void operator=(const StateMachineDaemon&) = delete;

  /** \brief Build the Daemon with the value used to select the state
   * and an initial state amount.
   *
   */
  StateMachineDaemon(std::shared_ptr<Value<int64_t> > state, unsigned initialSize) : daemons(initialSize), state(state) {}

  /** \brief Destroys the StateMachineDaemon.
   */
  virtual ~StateMachineDaemon() {}

  /** \brief Sets the Daemon to use for a given state.
   * |param state desired state
   * |param daemon Daemon daemon to run
   */
  void setDaemon(unsigned state, std::shared_ptr<Daemon> daemon) {
    if(state >= daemons.size()) {
      daemons.resize(state+1);
    }
    daemons[state]= daemon;
  }

  /** \brief It will run the contained daemons while "state" is positive.
   */
  void run();

private:
  std::vector<std::shared_ptr<Daemon> > daemons;
  std::shared_ptr<Value<int64_t> > state;
  };

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_STATEMACHINEDAEMON_H_
