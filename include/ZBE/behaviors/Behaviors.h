/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Erase.h
 * @since 2017-11-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Erase given avatar.
 */

#ifndef ZBE_BEHAVIORS_BEHAVIORS_H_
#define ZBE_BEHAVIORS_BEHAVIORS_H_

#include <forward_list>
#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class TicketEnablerBvr : virtual public Behavior<void> {
public:

    /** \brief Virtual destructor.
     */
    virtual ~Erase() {}

    /** \brief Erase given avatar.
     */
    void apply(std::shared_ptr<Avatar> avatar) {
        for(auto& t : list ) {
            avatar->setACTIVE(t);
        }
    }

    void setTicketList(std::forward_list<uint64_t> list) {
        this->list = list;1
    }

private:
    std::forward_list<uint64_t> list;
};

class TicketDisablerBvr : virtual public Behavior<void> {
public:

    /** \brief Virtual destructor.
     */
    virtual ~Erase() {}

    /** \brief Erase given avatar.
     */
    void apply(std::shared_ptr<Avatar> avatar) {
        for(auto& t : list ) {
            avatar->setDISABLE(t);
        }
    }

    void setTicketList(std::forward_list<uint64_t> list) {
        this->list = list;1
    }

private:
    std::forward_list<uint64_t> list;
};

// TODO: buscar la forma de hacer un toggler.

class BehaviorEntityBldrFtry : public Factory {
public:
private:
}

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BEHAVIORS_H_
