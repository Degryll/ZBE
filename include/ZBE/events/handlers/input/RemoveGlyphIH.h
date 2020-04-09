/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RemoveGlyphIH.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_REMOVEGLYPHIH_H
#define ZBE_EVENTS_HANDLERS_INPUT_REMOVEGLYPHIH_H

#include <memory>
#include <string>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class ZBEAPI RemoveGlyphIH : public InputHandler {
public:

  /** \brief Constructs a RemoveGlyphIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	RemoveGlyphIH() : vc(nullptr) {}

  /** \brief Constructs a RemoveGlyphIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	RemoveGlyphIH(std::shared_ptr<zbe::Value<std::string> > vc) : vc(vc) {}

	/** \brief set the Daemon to be called.
	 *  \param daemon The Daemon.
	 */
  void setDaemon(std::shared_ptr<zbe::Value<std::string> > vc){
		this->vc = vc;
	}

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float) {
    while(1) {
      if (vc->get().size()==0) {
        break;
      }
      if ((vc->get().back() & 0x80) == 0x00) {
        /* One byte */
        vc->get().pop_back();
        break;
      }
      if ((vc->get().back() & 0xC0) == 0x80) {
        /* Byte from the multibyte sequence */
        vc->get().pop_back();
      }
      if ((vc->get().back() & 0xC0) == 0xC0) {
        /* First byte of multibyte sequence */
        vc->get().pop_back();
        break;
      }
    }  // while(1)
	}

private:
	  std::shared_ptr<zbe::Value<std::string> > vc;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_REMOVEGLYPHIH_H
