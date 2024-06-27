/**
 * Copyright 2016 Batis Degryll Ludo
 * @file NetEventGenerator.h
 * @since 2018-08-16
 * @date 2018-08-16
 * @author Degryll
 * @brief Network event generator.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_NETEVENTGENERATOR_H
#define ZBE_CORE_EVENTS_GENERATORS_NETEVENTGENERATOR_H

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/io/NetBuffer.h"
#include "ZBE/core/io/NetMessage.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/events/handlers/NetHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/NetEvent.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This class ZBEAPI will look for network messages received and creates a net event sending it to the EventStore.
 */
class ZBEAPI NetEventGenerator : virtual public Daemon {
public:
  NetEventGenerator(const NetEventGenerator&) = delete;  //!< Deleted copy constructor.
  void operator=(const NetEventGenerator&) = delete;  //!< Deleted operator.

  /** \brief Default constructor.
   */
  NetEventGenerator(  uint64_t eventId, std::shared_ptr<NetBuffer> netBuffer) : eventId(eventId), netBuffer(netBuffer), contextTime(zbe::SysTime::getInstance()), store(EventStore::getInstance()) {}

  /** \brief Empty destructor.
   */
  ~NetEventGenerator() {}

  /** Will search for input events occurred between initTime and finalTime and send it to the EventStore.
   * \param initTime Time from which events are generated
   * \param endTime Time until the events are generated
   */
  void run() override;

private:
  uint64_t eventId;
  std::shared_ptr<NetBuffer> netBuffer;
  std::shared_ptr<ContextTime> contextTime;
  EventStore &store;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_NETEVENTGENERATOR_H
