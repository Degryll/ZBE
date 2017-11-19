/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Resizable.h
 * @since 2016-12-16
 * @date 2017-01-11
 * @author Batis Degryll Ludo
 * @brief Defines an avatar that can be resized.
 */

#ifndef ZBE_ENTITIES_AVATARS_RESIZABLE_H_
#define ZBE_ENTITIES_AVATARS_RESIZABLE_H_

namespace zbe {

/** \brief Defines an avatar that can be resized.
 */
class Resizable {
  public:
    using Base = void;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Resizable() {}

    /** \brief Sets the size for this Resizable.
     * \param size The desired size
     */
    virtual void setSize(double size) = 0;

    /** \brief Retunrs the size of this Resizable.
     * \return The actual size.
     */
    virtual double getSize() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_RESIZABLE_H_