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
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/containers/containers.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/io/Input.h"

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
using RsrcTicketedFAE = RsrcStore<TicketedFAE<T> >;  //!< Shortened name for RsrcStore<TicketedFAE<T> >

template <typename ...Avatars>
using RsrcTicketedFAEC = RsrcStore<TicketedFAEC<Avatars...> >;  //!< Shortened name for RsrcStore<TicketedFAEC<Avatars...> >

template <typename T>
using RsrcJointAE = RsrcStore<JointAE<T> >;  //!< Shortened name for RsrcStore<JointAE<T> >

template <typename ...Avatars>
using RsrcJointAEC = RsrcStore<JointAEC<Avatars...> >;  //!< Shortened name for RsrcStore<JointAEC<Avatars...> >

ZBEAPI void init(RsrcDictionary<ZBE_K>& zbekRsrc = RsrcDictionary<ZBE_K>::getInstance());
}  // namespace zbe

#endif  // ZBE_CORE_ZBE_H_
