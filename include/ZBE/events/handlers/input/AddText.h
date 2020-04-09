/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AddText.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_ADDTEXT_H_
#define ZBE_EVENTS_HANDLERS_ADDTEXT_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/events/handlers/TextHandler.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Handler that stores input value to a Value<double>
 */
class AddText : public TextHandler {
public:
  AddText(const AddText&) = delete; //!< Deleted copy constructor.
  void operator=(const AddText&) = delete; //!< Deleted operator.

  /** brief Empty constructor
   */
  AddText() : vh(nullptr), vc(nullptr), vl(nullptr) {}

  /** brief Parametrized constructor
    * param value where to store input.
   */
  AddText(std::shared_ptr<zbe::Value<std::string> > vc, std::shared_ptr<zbe::Value<int64_t> > vl, std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) : vh(vh), vc(vc), vl(vl) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setHistorial(std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) {
    this->vh = vh;
  }

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setCommand(std::shared_ptr<zbe::Value<std::string> > vc) {
    this->vc = vc;
  }

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setView(std::shared_ptr<zbe::Value<int64_t> > vl) {
    this->vl = vl;
  }

  /** brief stores input value to the value.
    * param status value from input.
   */
  void run(std::string text) {
    if (SDL_strlen(text.c_str()) == 0 || text.c_str()[0] == '\n') return;
    vc->set(vc->get() + text);
    vl->set(vh->get().size());
  }


private:
  std::shared_ptr<zbe::Value<std::vector<std::string> > > vh;
  std::shared_ptr<zbe::Value<std::string> > vc;
  std::shared_ptr<zbe::Value<int64_t> > vl;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ADDTEXT_H_
