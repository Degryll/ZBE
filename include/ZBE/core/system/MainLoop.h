/**
 * Copyright 2015 Batis Degryll Ludo
 * @file MainLoop.h
 * @since 2017-05-09
 * @date 2017-05-09
 * @author Batis
 * @brief The Main Loop of the game.
 */

#ifndef CORE_SYSTEM_MAINLOOP_H
#define CORE_SYSTEM_MAINLOOP_H

#include <memory>
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/BassicCommonBehaviorMaster.h"
#include "ZBE/core/daemons/BassicPreLoopDaemon.h"
#include "ZBE/core/daemons/BassicPostLoopSDLDaemon.h"
#include "ZBE/core/daemons/BassicReactBehaviorMaster.h"
#include "ZBE/core/daemons/BassicTimedEventsDaemon.h"

namespace zbe {

/** \brief The Main Loop of the game.
 */
class MainLoop {
  public:

    /** \brief Constructor.
     * \param Pre loop Daemon.
     * \param Post Loop Daemon.
     * \param Timed Events Daemon.
     * \param Common Behavior Daemon Master.
     * \param React Behavior Daemon Master.
     */
    MainLoop(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> event, std::shared_ptr<Daemon> common, std::shared_ptr<Daemon> react) :
                dPre(pre),
                dPost(post),
                dTE(event),
                dCBM(common),
                dRBM(react){}

    /** \brief Destructor.
     */
    ~MainLoop() {}

    /** \brief It will run the main loop.
     */
    void loop();

    /** \brief Setter for the Pre-loop daemon.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setPre(std::shared_ptr<Daemon> daemon) {dPre = daemon;}

    /** \brief Setter for the Post-loop daemon.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setPost(std::shared_ptr<Daemon> daemon) {dPost = daemon;}

    /** \brief Setter for the Timed Events daemon.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setEvent(std::shared_ptr<Daemon> daemon) {dTE = daemon;}

    /** \brief Setter for the Common Behavior Daemon Master.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setCommon(std::shared_ptr<Daemon> daemon) {dCBM = daemon;}

    /** \brief Setter for the React Behavior Daemon Master.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setReact(std::shared_ptr<Daemon> daemon) {dRBM = daemon;}

  private:
    std::shared_ptr<Daemon>  dPre;
    std::shared_ptr<Daemon>  dPost;
    std::shared_ptr<Daemon>  dTE;
    std::shared_ptr<Daemon>  dCBM;
    std::shared_ptr<Daemon>  dRBM;
};


}  // namespace zbe

#endif // CORE_DAEMONS_DAEMONMASTER_H
