/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ScrollUpIH.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_SCROLLUPIH_H
#define ZBE_EVENTS_HANDLERS_INPUT_SCROLLUPIH_H

#include <cstdlib>
#include <memory>
#include <vector>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class ZBEAPI ScrollUpIH : public InputHandler {
public:

  /** \brief Constructs a ScrollUpIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	ScrollUpIH() : vl(nullptr) {}

  /** \brief Constructs a ScrollUpIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	ScrollUpIH(std::shared_ptr<zbe::Value<int64_t> > vl) : vl(vl) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setView(std::shared_ptr<zbe::Value<int64_t> > vl) {
    this->vl = vl;
  }

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float) {
    vl->set(std::max(0ll, vl->get()-1));
	}

private:
  std::shared_ptr<zbe::Value<int64_t> > vl;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_SCROLLUPIH_H
