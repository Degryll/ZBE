/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AvatarCreator.h
 * @since 2017-11-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Erase given avatar.
 */

#ifndef ZBE_BEHAVIORS_AVATARCREATOR_H_
#define ZBE_BEHAVIORS_AVATARCREATOR_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Erase given avatar.
 */
template<typename T, typename ...Ts>
class AvatarCreator : virtual public Behavior<T, Ts...> {
  public:
    AvatarCreator(std::array<uint64_t, sizeof...(Ts) + 1> attribs, std::array<uint64_t, sizeof...(Ts) + 1> ids lists) : attribs(attribs), lists(lists) {}
    /*
    * Recibir indices de:
    Atributos
    Lista (RsrcStore de la lista correspondiente)
    */

    /** \brief Virtual destructor.
     */
    virtual ~AvatarCreator() {}

    /** \brief Erase given avatar.
     */
    void apply(std::shared_ptr<Avatar> avatar) {
      MAvatar a<T, Ts...>(attribs);
      for (auto lid : lists) {
        auto l = rsrclists.get(lid);
        l->insert(a);
      }
    }

  private:
    std::array<uint64_t, sizeof...(Ts) + 1> attribs;
    std::array<uint64_t, sizeof...(Ts) + 1> lists;
    RsrcStore<TicketedForwardList<Avatar> > rsrclists = RsrcStore<TicketedForwardList<Avatar> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_AVATARCREATOR_H_
