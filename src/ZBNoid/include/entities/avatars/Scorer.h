/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Scorer.h
 * @since 2017-10-21
 * @date 2017-10-21
 * @author Batis Degryll Ludo
 * @brief Avatar for Zombienoid entities that can score.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_SCORER_H
#define ZBE_EVENTS_HANDLERS_ACTUATORS_SCORER_H


namespace zombienoid {

/** @brief Avatar for Zombienoid entities that can score.
 */
class Scorer {
  public:
      using Base = void;

      virtual ~Scorer(){}

      virtual void setLastScoreTime(int64_t) = 0;
      virtual int64_t getLastScoreTime() = 0;

      virtual void accum() = 0;
      virtual void reset() = 0;
      virtual uint64_t getTotal() = 0;
};

}  // namespace zombienoid

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_SCORER_H
