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

namespace zbe {

/** \brief Calls the daemons and daemon masters that makes magic possible 0_0.
 */
class MainLoop {
  public:

    /** \brief Empty constructor.
     */
    MainLoop(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> timedEventsDaemon, std::shared_ptr<Daemon> commonBehaviorMaster, std::shared_ptr<Daemon> reactBehaviorMaster) :
                dPre(pre),
                dPost(post),
                dTE(timedEventsDaemon),
                dCBM(commonBehaviorMaster),
                dRBM(reactBehaviorMaster){}

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
    void setTEDaemon(std::shared_ptr<Daemon> daemon) {dTE = daemon;}

    /** \brief Setter for the Common Behavior Daemon Master.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setCommonBehaviorMaster(std::shared_ptr<Daemon> daemon) {dCBM = daemon;}

    /** \brief Setter for the React Behavior Daemon Master.
     * \param daemon Pointer to the Daemon desired to be used.
     * \return void
     *
     */
    void setReactBehaviorMaster(std::shared_ptr<Daemon> daemon) {dRBM = daemon;}

  private:
    std::shared_ptr<Daemon>  dPre;
    std::shared_ptr<Daemon>  dPost;
    std::shared_ptr<Daemon>  dTE;
    std::shared_ptr<Daemon>  dCBM;
    std::shared_ptr<Daemon>  dRBM;
};


}  // namespace zbe

#endif // CORE_DAEMONS_DAEMONMASTER_H
