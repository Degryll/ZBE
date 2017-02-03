/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobileAPO.h
 * @since 2017-01-30
 * @date 2017-01-30
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H
#define ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H

#include "ZBE/archetypes/implementations/SimpleWideMobile.h"
#include "ZBE/archetypes/ActivePhysicalObject.h"

namespace zbe {

template <unsigned s>
class SimpleWideMobileAPO : public SimpleWideMobile<s>, public ActivePhysicalObject {
  public:
    SimpleWideMobileAPO(uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(std::initializer_list<int64_t> position, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(Point<s> position, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(Vector<s> velocity, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(velocity ,width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(std::initializer_list<int64_t> position, std::initializer_list<int64_t> velocity, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, velocity, width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(Point<s> position, std::initializer_list<int64_t> velocity, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, velocity, width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(Point<s> position, Vector<s> velocity, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, velocity, width), ActivePhysicalObject(actuatorsList, collisionablesList) {}
    SimpleWideMobileAPO(std::initializer_list<int64_t> position, Vector<s> velocity, uint64_t width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWideMobile<s>(position, velocity ,width), ActivePhysicalObject(actuatorsList, collisionablesList) {}

    virtual ~SimpleWideMobileAPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H
