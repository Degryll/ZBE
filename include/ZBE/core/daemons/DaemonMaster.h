/**
 * Copyright 2015 Batis Degryll Ludo
 * @file DaemonMaster.h
 * @since 2015-05-04
 * @date 2015-12-09
 * @author Ludo
 * @brief A Daemon capable of run other Daemons.
 */

#ifndef CORE_DAEMONS_DAEMONMASTER_H
#define CORE_DAEMONS_DAEMONMASTER_H

#include <vector>
#include "./Daemon.h"

namespace zbe {
  /** \brief DaemonMaster is a Daemon responsible for run others Daemons. This necessary to build the Daemons tree.
   */
  class DaemonMaster : public Daemon {
    public:

      /** \brief Constructor of the DaemonsMaster class.
       *  No params.
       */
      DaemonMaster();

      /** \brief Destroy the DaemonMaster
       */
      virtual ~DaemonMaster();

      /** \brief It will execute al Daemons added to this DaemonMaster
       *
       * \return void
       *
       */
      void run();

      /** \brief Add a Daemon to be executed by this Daemon.
       *  The given Daemon will be stored by this Daemon and destroyed with it. It will be executed when run method is called.
       * \param daemon Daemon* the daemon desired to be stored and executed.
       * \return void
       *
       */
      void addDaemon(Daemon * daemon);

    private:
      std::vector<Daemon*> * daemonList;
  };
}

#endif // CORE_DAEMONS_DAEMONMASTER_H
