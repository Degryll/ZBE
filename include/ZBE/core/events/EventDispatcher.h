/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventDispatcher.h
 * @since 2016-08-15
 * @date 2016-08-15
 * @author Degryll
 * @brief Definitions of child events and the Event dispatcher.
 */

#ifndef CORE_EVENTS_EVENTDISPATCHER_H
#define CORE_EVENTS_EVENTDISPATCHER_H

#include "ZBE/core/events/Event.h"
#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

class CollisionEvent2D;
class TimeEvent;
class InputEvent;

/** \brief Send the event to the right handler.
 */
class EventDispatcher {
  public:
    /** \brief Using the Visitor pattern select the correct handler to use depending on the types of the event.
     *  \param param1 The event.
     */
    inline void select(Event& param) {
      param.accept(*this);
    }

    /** \brief Event handler for CollisionEvent2D.
     *  \param param1 A CollisionEvent2D event.
     */
    inline void visit(CollisionEvent2D& param);

    /** \brief Event handler for TimeEvent.
     *  \param param1 A TimeEvent event.
     */
    inline void visit(TimeEvent& param);

    /** \brief Event handler for InputEvent.
     *  \param param1 A InputEvent event.
     */
    inline void visit(InputEvent& param);
};

// Every child event must define a accept function
// This macro is used to avoid repeated code
#define DERIVEDEVENT \
  void accept(EventDispatcher &visitor) { \
    visitor.visit(*this); \
  } \

/** \brief Has the information needed to resolve a collision.
 */
class CollisionEvent2D : public Event {
  public:
    DERIVEDEVENT

    /** \brief Copy Constructor.
     */
    CollisionEvent2D(const CollisionEvent2D& rhs) : Event(rhs), a(rhs.a), b(rhs.b), p(rhs.p) {}

    /** \brief Parametrized Constructor.
    *
    * \param id Represents the global id of this event.
    * \param time Exact moment in which it occurred
    * \param entityA The first entity involved in the collision.
    * \param entityB The second entity involved in the collision.
    * \param point Point of collision.
    */
    CollisionEvent2D(uint64_t id, uint64_t time, CollisionerEntity *entityA, CollisionerEntity *entityB, Point2D point) : Event(id, time), a(entityA), b(entityB), p(point) {}

    /** \brief Empty destructor.
    */
    virtual ~CollisionEvent2D() {};

    /** \brief Copy Operator.
     */
    CollisionEvent2D& operator=(const CollisionEvent2D& rhs) {
      Event::operator=(rhs);
      a = rhs.a;
      b = rhs.b;
      p = rhs.p;
      return (*this);
    }

    /** \brief Get the first entity involved in the collision.
    * \return The first entity involved in the collision.
    */
    inline CollisionerEntity* getEntityA() {return (a);}

    /** \brief Get the second entity involved in the collision.
    * \return The second entity involved in the collision.
    */
    inline CollisionerEntity* getEntityB() {return (b);}

    /** \brief Get the point of collision.
    * \return The point of collision.
    */
    inline Point2D getPoint() {return (p);}

  private:
    CollisionerEntity *a;  //!< First entitie involved.
    CollisionerEntity *b;  //!< Second entitie involved.
    Point2D p;             //!< Point of collision.
};

/** \brief An event caused by time.
 */
class TimeEvent : public Event {
  public:
    DERIVEDEVENT

    /** \brief Basic constructor
     *
     * \param id Represents the global id of this event.
     * \param time Exact moment in which it occurred
     * \param timerId Id of timer that generate this event.
     *
     */
    TimeEvent(uint64_t id, uint64_t time, uint64_t timerId):Event(id,time),timerId(timerId) {}

    ~TimeEvent() {}

    /** \brief Get timerId from the timer that generates this event.
    *
    * \return The identifyer of the timer.
    *
    */
    uint64_t getTimerId() {
        return timerId;
    }

  private:
    uint64_t timerId;
};

/** \brief An event caused by input devices.
 */
class InputEvent : public Event {
  public:
    //DERIVEDEVENT
    void accept(EventDispatcher &visitor) {
      visitor.visit(*this);
    }

    /** \brief Builds an InputEvent with the status and id of the associated input.
     *
     * \param id Represents the global id of this event.
     * \param time Exact moment in which it occurred
     * \param key Id of the input related with this event.
     * \param state The state of the related input as a value in the range (-1.0 .. +1.0).
     *
     */
    InputEvent(uint64_t id, uint64_t time, uint32_t key, float state):Event(id,time), key(key),state(state) {}

    ~InputEvent() {}

    /** \brief Get the id of the key related with this event.
    * \return An integer that identifies the key.
    */
    inline uint32_t getKey() {
        return key;
    }

    /** \brief Get the state of the related key as a value in the range (-1.0 .. +1.0).
    * \return An float representing the state.
    */
    inline float getState() {
        return state;
    }

  private:
    uint32_t key;
    float state;
};

//void EventDispatcher::visit(CollisionEvent2D& param) {
void EventDispatcher::visit(CollisionEvent2D&) {
  // Call event handler for CollisionEvent2D
}

//void EventDispatcher::visit(TimeEvent& param) {
void EventDispatcher::visit(TimeEvent&) {
  // Call event handler for TimeEvent
}

//void EventDispatcher::visit(InputEvent& param) {
void EventDispatcher::visit(InputEvent&) {
  // Call event handler for InputEvent
}

}  // namespace zbe

#endif // CORE_EVENTS_EVENTDISPATCHER_H