/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePosition.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Simple implementation of the Position interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H

#include "ZBE/archetypes/Position.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template <unsigned s>
class SimplePosition : public Position<s> {
  public:
    SimplePosition() : p() {}
    SimplePosition(std::initializer_list<double> l) : p(l) {}

    SimplePosition(Point<s> position) : p(position) {}

    virtual ~SimplePosition() {}

    void setPosition(std::initializer_list<double> l) {
      if (l.size() != s) {
        SysError::setError("SimplePosition ERROR: Initializer list size is incorrect.");
        return;
      }

      int i = 0;
      for(auto it = l.begin(); it != l.end(); it++) {
        p[i++] = *it;
      }
    }
    void setPosition(Point<s> position) {p = position;}

    virtual Point<s>& getPosition() {return (p);}

  private:
    Point<s> p;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H
