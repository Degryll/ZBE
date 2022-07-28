/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLFactories.h
 * @since 2020-09-14
 * @date 2020-09-14
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all OGL factories.
 */

#ifndef ZBE_OAL_FACTORIES_OALFACTORIES_H_
#define ZBE_OAL_FACTORIES_OALFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/OAL/players/Sound3DOALPlayer.h"
#include "ZBE/OAL/resources/OALAudioLoader.h"
#include "ZBE/JSON/resources/JSONAudioDefLoader.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI OALFactories : public Daemon {
public:
  ~OALFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load() {
    using OALList = TicketedForwardList<MAvatar<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D> >;
    using OALDrwr = BehaviorDmnFtry<OALList, uint64_t, uint64_t, uint64_t, Vector3D, Vector3D>;

    auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("Sound3DOALPlayerFtry", std::make_shared<Sound3DOALPlayerFtry>());
    factories.insert("OALAudioLoaderFtry", std::make_shared<OALAudioLoaderFtry>());
    factories.insert("OALudioStoreFtry", std::make_shared<SimpleGenericFtry<OALAudioStore>>("OALAudioStore"));
    factories.insert("JSONAudioDefLoaderFtry", std::make_shared<GenericFtry<RsrcDefLoader, JSONAudioDefLoader>>("RsrcDefLoader", "JSONAudioDefLoader"));
    factories.insert("OALAvatarBuilder", std::make_shared<AvatarBldrFtry<uint64_t, uint64_t, uint64_t, Vector3D, Vector3D>>());

    factories.insert("OALPlayerDaemon", std::make_shared<OALDrwr>());
    factories.insert("TFOALAvtFtry", std::make_shared<SimpleGenericFtry<OALList> >(factories::listName));

    // Demonio y lista de avatares para el demonio.
    // Crear avatar al vuelo para una entidad en un evento.

    // Se va a asociar un nuevo builder al click que crea las castañas.
    // Así, de momento, tendremos sonidos cuando hagamos click.
  }

};

}  // namespace zbe

#endif  // ZBE_OGL_FACTORIES_OGLFACTORIES_H_
