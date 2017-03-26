/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Generator.h
 * @since 2016-06-05
 * @date 2017-03-26
 * @author Batis Degryll Ludo
 * @brief Store and run multiple Generators events.
 */

#ifndef CORE_EVENTS_GENERATORMASTER_H
#define CORE_EVENTS_GENERATORMASTER_H

#include <cstdint>

#include "ZBE/core/events/generators/Generator.h"

namespace zbe {

/** \brief Store and run multiple Generators events.
 */
class GeneratorMaster : virtual public Generator {
public:
  GeneratorMaster(const GeneratorMaster&) = delete;
  void operator=(const GeneratorMaster&) = delete;

  GeneratorMaster(uint64_t listId ) : gList(ListManager<std::vector<Generator*> >::getInstance().get(listId)) {}

  /** \brief Empty destructor.
   */
  ~GeneratorMaster() {}

  void generate(int64_t initTime, int64_t endTime) {
    for(auto g : (*gList)) {
      g->generate(initTime, endTime);
    }
  }

private:
  std::vector<Generator*>*  gList;
};


}  // namespace zbe

#endif // CORE_EVENTS_GENERATORMASTER_H
