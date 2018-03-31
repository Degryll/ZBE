/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Scorer.h
 * @since 2017-10-21
 * @date 2017-10-21
 * @author Batis Degryll Ludo
 * @brief Avatar for Zombienoid entities that can score.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_SIMPLESCORER_H
#define ZBE_EVENTS_HANDLERS_ACTUATORS_SIMPLESCORER_H

#include "entities/avatars/Scorer.h"

namespace zombienoid {

/** @brief Avatar for Zombienoid entities that can score.
 */
class SimpleScorer : virtual public Scorer{
  public:

      SimpleScorer() : t(0), total(0) {}

      void setLastScoreTime(int64_t time) {t = time;}
      int64_t getLastScoreTime() {return t;}

      void accum() {total++;};
      void reset() {total = 0;};
      uint64_t getTotal() {return total;};
  private:

    int64_t t;
    uint64_t total;
};

}  // namespace zombienoid

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_SIMPLESCORER_H
