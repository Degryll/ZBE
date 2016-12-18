/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMobile.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Simple implementation of the Mobile2D interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H

#include "ZBE/archetypes/Mobile.h"

namespace zbe {

template <unsigned s>
class SimpleMobile : public Mobile<s>, public SimplePosition<s> {
  public:
    SimpleMobile() : SimplePosition(), v() {}
    SimpleMobile(std::initializer_list<double> position) : SimplePosition(position), v() {}
    SimpleMobile(Point<s> position) : SimplePosition(position), v() {}
    SimpleMobile(Vector<s> velocity) : SimplePosition(), v(velocity) {}
    SimpleMobile(std::initializer_list<double> position, std::initializer_list<double> velocity) : SimplePosition(position), v(velocity) {}
    SimpleMobile(Point<s> position, std::initializer_list<double> velocity) : SimplePosition(position), v(velocity) {}
    SimpleMobile(Point<s> position, Vector<s> velocity) : SimplePosition(position), v(velocity) {}
    SimpleMobile(std::initializer_list<double> position, Vector<s> velocity) : SimplePosition(position), v(velocity) {}

    void setVelocity(std::initializer_list<double> velocity) {
      if (l.size() != s) {
        SysError::setError("SimpleMobile ERROR: Initializer list size is incorrect.");
        return;
      }

      int i = 0;
      for(auto it = l.begin(); it != l.end(); it++) {
        v[i++] = *it;
      }
    }
    void setVelocity(Vector<s> velocity) {v = velocity;}

    Vector<s>& getVelocity() {return (v);}

  private:
    Vector2D v;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
