/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTextSprite.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Batis
 * @brief This define an avatar that can be drawn as text.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_

#include <string>

#include "ZBE/core/entities/avatars/SingleSprite.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn as text.
 */
class ZBEAPI SingleTextSprite : virtual public SingleSprite {
public:
    using Base = SingleSprite;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~SingleTextSprite(){}

    /** \brief Text value for this sprite.
     *  \return the text value
     */
    virtual const std::string& getText() = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_
