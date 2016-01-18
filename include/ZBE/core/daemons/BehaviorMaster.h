/**
 * Copyright 2015 Batis Degryll Ludo
 * @file BehaviorMaster.h
 * @since 2015-05-04
 * @date 2015-12-18
 * @author Ludo
 * @brief A Daemon capable of run Behaviors.
 */

#ifndef CORE_DAEMONS_BEHAVIORMASTER_H
#define CORE_DAEMONS_BEHAVIORMASTER_H

#include <vector>
#include "./Daemon.h"
#include "../behaviors/Behavior.h"


namespace zbe {
  template<typename T>
  /** \brief A Daemon capable of execute a specific Behavior over a list of entities.
   */
  class BehaviorMaster : public Daemon {
    public:

      /** \brief Build the Daemon with a Behavior.
       * The given Behavior will be stored by this Daemon and destroyed with it. It will be executed when run method is called.
       * \param daemon Behavior* the daemon desired to be stored and executed.
       *
       */
      BehaviorMaster(Behavior<T> * behavior, std::vector<T*> * entities);

      /** \brief Destroys the BehaviorMaster and the contained Behavior
       *
       * \return virtual
       *
       */
      virtual ~BehaviorMaster();

      /** \brief It will execute al Behaviors added to this DaemonMaster
       *
       * \return void
       *
       */
      void run();

    private:
      Behavior<T> * behavior;
      std::vector<T*> * entities;
  };

template<typename T>
BehaviorMaster<T>::BehaviorMaster(Behavior<T> * behavior, std::vector<T*> * entities):behavior(behavior), entities(entities) {
}

template<typename T>
BehaviorMaster<T>::~BehaviorMaster() {
    delete behavior;
}

template<typename T>
void BehaviorMaster<T>::run(){
  for(auto it = entities->begin(); it < entities->end(); ++it) {
    behavior->behave((*it));
  }
}
}

#endif // CORE_DAEMONS_BEHAVIORMASTER_H
