/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticket.h
 * @since 2015/02/15
 * @date 2017/05/15
 * @author Degryll Ludo
 * @brief Ticket that a container gives to a contained item to mark itself as active, inactive or erased.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_
#define ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_

#include <memory>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Ticket to send to and entities so it can mark itself as active, inactive or erase in the related list.
 */
class ZBEAPI Ticket {
public:

  virtual ~Ticket() {}

  virtual void setACTIVE() = 0;    //!< Set the state as ACTIVE.
  virtual void setINACTIVE() = 0;  //!< Set the state as INACTIVE.
  virtual void setERASED() = 0;    //!< Set the state as ERASED.

  virtual bool isACTIVE() = 0;     //!< True if state is ACTIVE.
  virtual bool isNotACTIVE() = 0;  //!< True if state is not ACTIVE, either INACTIVE or ERASED.
  virtual bool isINACTIVE() = 0;   //!< True if state is INACTIVE.
  virtual bool isERASED() = 0;     //!< True if state is ERASED.

protected:
  enum State{ACTIVE,INACTIVE,ERASED};  //!< The different states.

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_
