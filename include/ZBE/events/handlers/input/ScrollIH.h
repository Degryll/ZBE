/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ScrollIH.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_SCROLLIH_H
#define ZBE_EVENTS_HANDLERS_INPUT_SCROLLIH_H

#include <cstdlib>
#include <memory>
#include <vector>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class ScrollIH : public InputHandler {
public:

  /** \brief Constructs a ScrollIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	ScrollIH() : vl(nullptr), vh(nullptr) {}

  /** \brief Constructs a ScrollIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	ScrollIH(std::shared_ptr<zbe::Value<int64_t> > vl, std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) : vl(vl), vh(vh) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setHistorial(std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) {
    this->vh = vh;
  }


  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setView(std::shared_ptr<zbe::Value<int64_t> > vl) {
    this->vl = vl;
  }

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float state) {
	  if (state > 0 && vl->get() > 10ll) {
      vl->set(std::max(10ll, vl->get()-1ll));
    } else  if (state < 0) {
      vl->set(std::min(int64_t(vh->get().size()), vl->get()+1));
    }
	}

private:
  std::shared_ptr<zbe::Value<int64_t> > vl;
  std::shared_ptr<zbe::Value<std::vector<std::string> > > vh;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_SCROLLIH_H
