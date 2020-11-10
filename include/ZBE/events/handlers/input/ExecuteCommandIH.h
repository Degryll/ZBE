/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ExecuteCommandIH.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_EXECUTECOMMANDIH_H
#define ZBE_EVENTS_HANDLERS_INPUT_EXECUTECOMMANDIH_H

#include <cstdlib>
#include <memory>
#include <vector>
#include <string>

#include <chaiscript/chaiscript.hpp>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class ExecuteCommandIH : public InputHandler {
public:

  /** \brief Constructs a ExecuteCommandIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	ExecuteCommandIH() : chai(nullptr), vc(nullptr), vl(nullptr), vh(nullptr) {}

  /** \brief Constructs a ExecuteCommandIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	ExecuteCommandIH(std::shared_ptr<chaiscript::ChaiScript> chai, std::shared_ptr<zbe::Value<std::string> > vc, std::shared_ptr<zbe::Value<int64_t> > vl, std::shared_ptr<zbe::Value<std::vector<std::string> > > vh) : chai(chai), vc(vc), vl(vl), vh(vh) {}

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

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float state) {
	  if (state) {
      std::string text = vc->get();
      std::string prefix("chai ");
      if (!text.compare(0, prefix.size(), prefix)) {
        chai->eval(text.substr(prefix.size()).c_str());
      }
      std::string file("file ");
      if (!text.compare(0, file.size(), file)) {
        std::string content = get_file_contents(text.substr(file.size()).c_str());
        chai->eval(content);
      }
      vh->get().push_back(text);
      vc->get().clear();
      vl->set(vl->get() + 1);
	  }
	}

private:
  std::string get_file_contents(const char *filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
      std::string contents;
      in.seekg(0, std::ios::end);
      contents.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&contents[0], contents.size());
      in.close();
      return(contents);
    } else {
			// TODO Use System & logger
      printf("Fichero %s no encontrado.\n", filename);
      return ("");
    }

  }

  std::shared_ptr<chaiscript::ChaiScript> chai;
  std::shared_ptr<zbe::Value<std::string> > vc;
  std::shared_ptr<zbe::Value<int64_t> > vl;
  std::shared_ptr<zbe::Value<std::vector<std::string> > > vh;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_EXECUTECOMMANDIH_H
