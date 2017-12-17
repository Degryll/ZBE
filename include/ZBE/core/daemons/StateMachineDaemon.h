/**
 * Copyright 2015 Batis Degryll Ludo
 * @file StateMachineDaemon.h
 * @since 2015-05-04
 * @date 2017-01-13
 * @author Degryll Ludo
 * @brief A Daemon capable of execute an specific sub Daemon depending on
 * an state.
 */

#ifndef CORE_DAEMONS_STATEMACHINEDAEMON_H_
#define CORE_DAEMONS_STATEMACHINEDAEMON_H_

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
      StateMachineDaemon(std::shared_ptr<Value<int64_t> > state, unsigned initialSize) : state(state), daemons(initialSize) {}

      /** \brief Destroys the StateMachineDaemon.
       */
      virtual ~StateMachineDaemon() {}

      void setDaemon(unsigned state, std::shared_ptr<Daemon> daemon) {
        if(state >= daemons.size) {
          daemons.resize(state+1);
        }
        daemons[state]= daemon;
      }

      /** \brief It will run the contained daemons while "state" is positive.
       */
      void run();

    private:
      std::std::vector<std::shared_ptr<Daemon> > daemons;
      std::shared_ptr<Value<int64_t> > state;
  };

  void StateMachineDaemon::run(){
    while(state->getValue()>=0) {
      daemons[state->getValue()]->run();
    }
  }
}  // namespace zbe



#endif // CORE_DAEMONS_STATEMACHINEDAEMON_H_
