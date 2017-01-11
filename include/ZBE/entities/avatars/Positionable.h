/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2016-12-16
 * @date 2017-01-11
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that can be posicioned.
 */

#ifndef ZBE_ENTITIES_AVATARS_POSITIONABLE_H_
#define ZBE_ENTITIES_AVATARS_POSITIONABLE_H_


namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <unsigned s>
class Positionable {
  public:
    virtual ~Positionable() {}

    virtual void setPosition(std::initializer_list<double> l) = 0;
    virtual void setPosition(Point<s> position) = 0;

    virtual Point<s>& getPosition() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_POSITIONABLE_H_
