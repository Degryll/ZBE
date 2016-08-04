/**
 * Copyright 2015 Batis Degryll Ludo
 * @file DaemonMaster.h
 * @since 2015-05-04
 * @date 2016-08-04
 * @author Ludo
 * @brief A Daemon capable of run other Daemons.
 */

#ifndef CORE_DAEMONS_DAEMONMASTER_H
#define CORE_DAEMONS_DAEMONMASTER_H

#include <memory>
#include <vector>
#include "./Daemon.h"

namespace zbe {

/** \brief DaemonMaster is a Daemon responsible for run others Daemons. This is necessary to build the Daemons tree.
 */
class DaemonMaster : public Daemon {
  public:

    /** \brief Empty constructor.
     */
    DaemonMaster() : daemonList() {}

    /** \brief Destructor and the contained Daemons.
     */
    ~DaemonMaster() {}

    /** \brief It will run all Daemons added to this DaemonMaster.
     */
    void run();

    /** \brief Add a Daemon to be run by this Daemon.
     *  The given Daemon will be stored by this Daemon and destroyed with it.
     * \param daemon Pointer to the Daemon desired to be stored and executed.
     * \return void
     *
     */
    void addDaemon(std::shared_ptr<Daemon> daemon) {daemonList.push_back(daemon);}

  private:
    std::vector<std::shared_ptr<Daemon> > daemonList;
};

}  // namespace zbe

#endif // CORE_DAEMONS_DAEMONMASTER_H
