/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2016-12-16
 * @date 2017-01-11
 * @author Batis Degryll Ludo
 * @brief This defines an avatar capable of resize a referenced area with given proportions.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASERESIZABLEAREA_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASERESIZABLEAREA_H_

#include "ZBE/entities/avatars/Resizable.h"
#include "ZBE/archetypes/Area.h"


namespace zbe {

/** @brief This defines an avatar capable of resize a referenced area with given proportions.
 */
class BaseResizableArea : virtual public Resizable {
  public:
    BaseResizableArea(const BaseResizableArea&) = delete; //<! Avoid copy
    void operator=(const BaseResizableArea&) = delete; //<! Avoid copy

    /** \brief Virtual destructor.
     */
    virtual ~BaseResizableArea(){}

    /** \brief Builds this BaseResizableArea with a Position.
     */
    BaseResizableArea(Area *area , double wBase , double hBase, double size = 1.0) : a(area), wBase(wBase), hBase(hBase), s(size)  {}

    /** \brief Sets the size for this Resizable.
     * \param size The desired size
     */
    void setSize(double size) {
        s = size;
        a->setWidth(s * wBase);
        a->setHeight(s * hBase);
    }

    /** \brief Retunrs the size of this Resizable.
     * \return The actual size.
     */
    double getSize() {return (s);}

  private:
    Area *a;
    double wBase;
    double hBase;
    double s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASERESIZABLEAREA_H_
