/**
 * Copyright 2011 Batis Degryll Ludo
 * @file zbe.h
 * @since 2015-05-16
 * @date 2018-03-27
 * @author Degryll Ludo Batis
 * @brief all zbe container tools.
 */

#ifndef ZBE_CORE_ZBE_H_
#define ZBE_CORE_ZBE_H_

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/tools/containers/containers.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/tools/shared/Value.h"

namespace zbe {

template <typename T>
using TicketedFAE = TicketedForwardList<AE<T> >;  //!< Shortened name for TicketedForwardList<AE<T> >

template <typename ...Avatars>
using TicketedFAEC = TicketedForwardList<AEC<Avatars...> >;  //!< Shortened name for TicketedForwardList<AEC<Avatars...> >

template <typename T>
using JointAE = ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AE<T> > >;  //!< Shortened name for ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AE<T> > >

template <typename ...Avatars>
using JointAEC = ListTicketedJoint<TicketedFAEC<Avatars...>, std::shared_ptr<AEC<Avatars...> > >;  //!< Shortened name for ListTicketedJoint<TicketedFAEC<Avatars...>, std::shared_ptr<AEC<Avatars...> > >

template <typename T>
using RsrcTicketedFAE = ResourceManager<TicketedFAE<T> >;  //!< Shortened name for ResourceManager<TicketedFAE<T> >

template <typename ...Avatars>
using RsrcTicketedFAEC = ResourceManager<TicketedFAEC<Avatars...> >;  //!< Shortened name for ResourceManager<TicketedFAEC<Avatars...> >

template <typename T>
using RsrcJointAE = ResourceManager<JointAE<T> >;  //!< Shortened name for ResourceManager<JointAE<T> >

template <typename ...Avatars>
using RsrcJointAEC = ResourceManager<JointAEC<Avatars...> >;  //!< Shortened name for ResourceManager<JointAEC<Avatars...> >

}  // namespace zbe

#endif  // ZBE_CORE_ZBE_H_
