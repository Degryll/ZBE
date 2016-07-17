#ifndef CORE_DAEMONS_PUNISHERDAEMON_H_INCLUDED
#define CORE_DAEMONS_PUNISHERDAEMON_H_INCLUDED


#include <vector>
#include "./Daemon.h"


namespace zbe {
  /** \brief A Daemon capable of execute a specific Behavior over a list of entities.
   */
  template<typename P, typename L, typename E>
  class PunisherDaemon : public Daemon {
    public:

      /** \brief Build the Daemon with a punish and a .
       * The given Behavior will be stored by this Daemon and destroyed with it. It will be executed when run method is called.
       * \param daemon Pointer to the daemon desired to be stored and executed.
       *
       */
      PunisherDaemon(P * punish, L * entities):punish(punish), entities(entities) {}

      /** \brief Destroys the PunisherDaemon and the contained punisher.
       */
      virtual ~PunisherDaemon();

      /** \brief It will run the Behavior over the entity list.
       */
      void run();

    private:
      P *punish;
      L *entities;
  };


  template<typename P, typename L, typename E>
  PunisherDaemon<P,L,E>::~PunisherDaemon() {
    delete punish;
  }

  template<typename P, typename L, typename E>
  void PunisherDaemon<P,L,E>::run(){
    for(auto it = entities->begin(); it != entities->end(); ++it) {
      punish->apply((*it));
    }
  }

}


#endif // CORE_DAEMONS_PUNISHERDAEMON_H_INCLUDED
