/**
 * Copyright 2015 Batis Degryll Ludo
 * @file MainLoop.h
 * @since 2017-05-09
 * @date 2018-03-21
 * @author Batis, Degryll, Ludo
 * @brief The Main Loop of the game.
 */

#ifndef ZBE_CORE_DAEMONS_MAINLOOP_H
#define ZBE_CORE_DAEMONS_MAINLOOP_H

#include <memory>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief The Main Loop of the game.
 */
class ZBEAPI MainLoop : virtual public Daemon {
public:

  /** \brief Constructor.
   * \param pre Pre loop Daemon.
   * \param post Post Loop Daemon.
   * \param event Event genration Daemon.
   * \param common Common Behavior Daemon.
   * \param react React Behavior Daemon.
   * \param draw Drawer daemon.
   */
  MainLoop(std::shared_ptr<Daemon> pre, std::shared_ptr<Daemon> post, std::shared_ptr<Daemon> event, std::shared_ptr<Daemon> common, std::shared_ptr<Daemon> react, std::shared_ptr<Daemon> draw, std::shared_ptr<ContextTime> contextTime=zbe::SysTime::getInstance())
    : dPre(pre), dPost(post), dTE(event), dCBM(common), dRBM(react), dDM(draw),
      contextTime(contextTime), store(zbe::EventStore::getInstance()), keep(true) {}

  /** \brief Destructor.
   */
  ~MainLoop() {}

  /** \brief It will run until stop() is called.
   *  For each frame it will:
   *    execute "pre" daemon (usually do nothing): mean to prepare the frame.
   *    while there is frame time remaining:
   *      execute "event" daemon: mean to generate "timed" events.
   *      if there are events:
   *        execute "common" daemon: mean to run entity behaviors until first event
   *        call event management
   *        execute "react" daemon: mean to run event related entity behaviors
   *      if there are no events:
   *        execute "common" daemon: mean to run entity behaviors until frame end
   *      update frame time remaining
   *    execute "draw" daemon: mean to draw game entities
   *    execute "post" daemon (usually do nothing): mean to clean up the frame.
   *  \sa stop(), EventStore::manage()
   */
  void run();

  /** \brief Setter for the Pre-loop daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return void
   */
  void setPre(std::shared_ptr<Daemon> daemon) {dPre = daemon;}

  /** \brief Setter for the Post-loop daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return void
   */
  void setPost(std::shared_ptr<Daemon> daemon) {dPost = daemon;}

  /** \brief Setter for the Timed Events daemon.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return void
   */
  void setEvent(std::shared_ptr<Daemon> daemon) {dTE = daemon;}

  /** \brief Setter for the Common Behavior Daemon Master.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return voidsince
   */
  void setCommon(std::shared_ptr<Daemon> daemon) {dCBM = daemon;}

  /** \brief Setter for the React Behavior Daemon Master.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return void
   */
  void setReact(std::shared_ptr<Daemon> daemon) {dRBM = daemon;}

  /** \brief Setter for the Drawlo  Master.
   * \param daemon Pointer to the Daemon desired to be used.
   * \return void
   */
  void setDraw(std::shared_ptr<Daemon> daemon) {dDM = daemon;}

  /** \brief Stops current loop.
   */
  void stop() {keep = false;}

private:
  std::shared_ptr<Daemon> dPre;
  std::shared_ptr<Daemon> dPost;
  std::shared_ptr<Daemon> dTE;
  std::shared_ptr<Daemon> dCBM;
  std::shared_ptr<Daemon> dRBM;
  std::shared_ptr<Daemon> dDM;

  std::shared_ptr<ContextTime> contextTime;
  zbe::EventStore &store;

  bool keep;

};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_MAINLOOP_H
