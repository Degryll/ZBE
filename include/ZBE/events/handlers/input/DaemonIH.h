/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonIH.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
#define ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H


#include <memory>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class ZBEAPI DaemonIH : public InputHandler {
public:

  /** \brief Constructs a DaemonIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	DaemonIH() : d(nullptr), value(1.0f) {}

  /** \brief Constructs a DaemonIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	DaemonIH(std::shared_ptr<Daemon> daemon):d(daemon), value(1.0f)  {}

	/** \brief set the Daemon to be called.
	 *  \param daemon The Daemon.
	 */
  void setDaemon(std::shared_ptr<Daemon> daemon) {
		this->d = daemon;
	}

	/** \brief set the Daemon to be called.
	 *  \param daemon The Daemon.
	 */
  void setValue(float value) {
		this->value = value;
	}

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float inval) override {
		if (almost_equal(inval, value)) {
    	d->run();
		}
	}

private:
	std::shared_ptr<Daemon> d;
	float value;
};

/** \brief Input handler capable of run a daemon.
 */
template<typename T>
class ZBEAPI ConditionalDaemonIH : public InputHandler {
public:

  /** \brief Constructs a DaemonIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	ConditionalDaemonIH() : d(nullptr), value(1.0f), cValue(nullptr), cExpected() {}

  /** \brief Constructs a DaemonIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	ConditionalDaemonIH(std::shared_ptr<Daemon> daemon):d(daemon), value(1.0f), cValue(nullptr), cExpected() {}

	/** \brief set the Daemon to be called.
	 *  \param daemon The Daemon.
	 */
  void setDaemon(std::shared_ptr<Daemon> daemon) {
		this->d = daemon;
	}

	/** \brief set the Daemon to be called.
	 *  \param daemon The Daemon.
	 */
  void setValue(float value) {
		this->value = value;
	}

	/** \brief set the conditial Value<T> and the expected value.
	 *  \param cValue The Value<T> that will be checked.
	 *  \param cValue The expected value that will run the damon.
	 */
  void setCondition(std::shared_ptr<Value<T>> cValue, T cExpected, bool equal) {
		this->cValue = cValue;
		this->cExpected = cExpected;
		this->equal = equal;
	}

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float inval) override {
		if (!(cValue->get() == cExpected) == equal) {
    	return;
		}
		if (almost_equal(inval, value)) {
    	d->run();
		}
	}

private:
	std::shared_ptr<Daemon> d;
	float value;
	std::shared_ptr<Value<T>> cValue;
	T cExpected;
	bool equal;
};

/** \brief Input handler capable of run another input handler if a condition is fullfilled.
 */
template<typename T>
class ZBEAPI ConditionalCompositeIH : public InputHandler {
public:

  /** \brief Constructs a DaemonIH from a daemon.
 	 *  \param daemon daemon to be executed.
	 */
	ConditionalCompositeIH() : ih(nullptr), cValue(nullptr), cExpected() {}

  /** \brief Constructs a DaemonIH from a daemon.
	 *  \param daemon daemon to be executed.
	 */
	ConditionalCompositeIH(std::shared_ptr<InputHandler> ih): ih(ih), cValue(nullptr), cExpected() {}

	/** \brief set the InputHandler to be called.
	 *  \param ih The InputHandler.
	 */
  void setInputHandler(std::shared_ptr<InputHandler> ih) {
		this->ih = ih;
	}

	/** \brief set the conditial Value<T> and the expected value.
	 *  \param cValue The Value<T> that will be checked.
	 *  \param cValue The expected value that will run the damon.
	 */
  void setCondition(std::shared_ptr<Value<T>> cValue, T cExpected, bool equal) {
		this->cValue = cValue;
		this->cExpected = cExpected;
		this->equal = equal;
	}

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t key, float inval) override {
		if (!(cValue->get() == cExpected) == equal) {
    		return;
		}
		ih->run(key, inval);
	}

private:
	std::shared_ptr<InputHandler> ih;
	std::shared_ptr<Value<T>> cValue;
	T cExpected;
	bool equal;
};
}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
