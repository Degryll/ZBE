/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMainLoop.cpp
 * @since 2018-03-27
 * @date 2018-03-27
 * @author Batis Degryll Ludo
 * @brief Daemon that executes a main game loop.
 */

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

void SimpleMainLoop::run() {

  keep = true;
  while(keep) {  // Each iteration generates a frame.
    // Pre daemon
    contextTime->update();
    dPre->run();

    // Inner loop
    while (contextTime->isFrameRemaining()) {
      // Timed events generator daemon
      dTE->run();
      contextTime->setEventTime(store->getTime());
      if (contextTime->isPartialFrame()) {
        // commonBehaviorMaster
        dCBM->run();
        store->manageCurrent();
        // reactBehaviorMaster
        dRBM->run();
      } else {
        // commonBehaviorMaster
        dCBM->run();
        store->clearStore();
      }
      contextTime->updateInitTime();
    }  // while frame remaining
    // Drawer daemon
    dDM->run();
    // Post daemon
    dPost->run();
    // end
  }  // while keep
}

// TODO Hay que construir un MainLoop en dos capas.
// La primera capa tiene el bucle "infinito" y está, presumiblemente, asociado al tiempo "DEFAULT".
// Eejecuta su propio demonio "pre" para eventos donde se generarán los eventos de entrada. (Que no tiene sentido que se pausen)
// Llamará a otro demonio que ejecutará todo lo que, actualmente, se hace dentro de un frame.
// Hay que tener en cuenta que estas llamadas:
// contextTime->update();
// dPre->run();
// se ejecutarán tanto en el la primera capa como en la intera.
// El system time debe estar protegido para que no que puede llamar a su update mas de una vez por frame.
// Para ello podría disponer de un método que permita espeficicar cuando ha acabado un frame y que el mismo se bloquee internamente
// Solo permitirá un update hasta que ese método de fin de frame sea llamado de nuevo.
// De esto modo todos los tiempos subordinados podrán actualizarse sin afectar al los tiempos del padre.
// --- OPCION B --- <--- VAMOS A HACER ESTA.
// Si el subordinate time no llama al update del padre, la primera capa del main loop lo llamará.
// Después cada frame hijo llamará al update de su propio subordinate time y este se refrescará con los tiempos del padre.
// Con esto evitamos tener que proteger al system time ya que a su update solo lo llamará el bucle superior.
// Esto tiene una implicación: El frame siempre tiene que tener un tiempo subordinado y NUNCA podrá usar el DEFAULT
// EXTRA
// ¿Quizás debamos permitir que la factoría del demonio de frame cree directamente el tiempo subordinado?
// O le pasas el parent para que cree el subordinado o le pasas el tiempo que debe usar (QUE NUNCA DEBE SER EL DEFAULT)

}  // namespace zbe
