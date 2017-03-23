/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideBouncingMobileAPO.h
 * @since 2017-03-20
 * @date 2017-03-20
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity, a width and the ability to accumulate normals.
 */

#ifndef ZBE_ARCHETYPES_SIMPLEWIDEBOUNCINGMOBILEAPO_H
#define ZBE_ARCHETYPES_SIMPLEWIDEBOUNCINGMOBILEAPO_H

#include "ZBE/archetypes/implementations/SimpleWideMobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleBouncing.h"

namespace zbe {

template <unsigned s>
class SimpleWideBouncingAPO : public SimpleBouncing<s>, public SimpleWideMobileAPO<s> {
  public:
    SimpleWideBouncingAPO(double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(width, actuatorsList, collisionablesList) {}
    SimpleWideBouncingAPO(std::initializer_list<double> position, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(Point<s> position, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(velocity, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, velocity, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(Point<s> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, velocity, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(Point<s> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, velocity, width, actuatorsList, collisionablesList){}
    SimpleWideBouncingAPO(std::initializer_list<double> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobileAPO<s>(position, velocity, width, actuatorsList, collisionablesList){}

    virtual ~SimpleWideBouncingAPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_SIMPLEWIDEBOUNCINGMOBILEAPO_H
