/**
 * Copyright 2015 Batis Degryll Ludo
 * @file PunisherDaemon.h
 * @since 2015-05-04
 * @date 2017-01-13
 * @author Degryll Ludo
 * @brief Define the minimal functions of demons.
 */

#ifndef CORE_DAEMONS_PUNISHERDAEMON_H_
#define CORE_DAEMONS_PUNISHERDAEMON_H_

#include <vector>
#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/containers/ResourceManager.h"


namespace zbe {
  /** \brief A Daemon capable of execute a specific Behavior over a list of entities.
   */
  template<typename P, typename L>
  class PunisherDaemon : public Daemon {
    public:

      PunisherDaemon(const PunisherDaemon&) = delete;
      void operator=(const PunisherDaemon&) = delete;

      /** \brief Build the Daemon with a punish and a .
       * The given Behavior will be stored by this Daemon and destroyed with it. It will be executed when run method is called.
       * \param daemon Pointer to the daemon desired to be stored and executed.
       *
       */
      PunisherDaemon(std::shared_ptr<P> punish, uint64_t listId) : punish(punish), eList( ResourceManager<L>::getInstance().get(listId) ) {}

      /** \brief Destroys the PunisherDaemon and the contained punisher.
       */
      virtual ~PunisherDaemon() {}

      /** \brief It will run the Behavior over the entity list.
       */
      void run();

    private:
      std::shared_ptr<P> punish;
      std::shared_ptr<L> eList;
  };

  template<typename P, typename L>
  void PunisherDaemon<P, L>::run(){
    for(auto e : (*eList)) {
      punish->apply(e);
    }
  }
}  // namespace zbe



#endif // CORE_DAEMONS_PUNISHERDAEMON_H_
