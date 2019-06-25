/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokz.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBokz game.
 */

#include "ZBE/core/zbe.h"

int main(int /*argc*/, char** /*argv*/) {
   // using namespace zbe;
   printf("Hello ZandBokz\n");
   //
   // CommonFactories::load();
   //
   // /*CommonListFactories<
   //   int, "listint",
   //   float, "list cosa"
   // >::load();*/
   //
   // GenericExtraFactories<
   //   /*int, "listint",
   //   float, "list cosa",*/
   //   TFAEC<Drawable>, "TFAECDrawable/home/ludo/workspace/ZBE/src/ZandBokz/src/zandbokz.cppsFtry"
   //   >::load();
   //
   // JSONAppLoader appLoader;
   // appLoader.load("data/ZandBokz/app/main.json");
   // auto& dmnRsrcStore = RsrcStore<Daemon>::getInstance();
   // auto mainDaemon = dmnRsrcStore.get("Daemon.Main");
   // mainDaemon.run();
   // return 0;


    // Flujo del juego
      // Llamar a la primera carga de factorias basicas. (CommonFactories)
      // Cargar primera aplicacion: LoadScreen.
        // Devolvera un demonio que cargara lo minimo para:
          // Pintar un pantalla de carga
            // Instanciar pintadores
            // Cargar carpetas de recursos
          // Cargar la siguiente aplicacion.
            // Factoría propias del juego.
            // Instaciar demonios RsrcLoader para segunda aplicacion

      // Cargar segunda aplicacion: Menu.
        // ¿Tenemos factorias para las cosas que crean menus?

      // Cargar segunda aplicacion: juego.

    // Desarrollos necesarios
      // ¿Cambiar factories por general? Necesitamos cargar assets en esa fase.
      // Factorias de ContextTime:SubordinateTime
      // Avatares nuevos: Todos construidos a partir de un Entity.
      // Declarar en CommonFactories factorias para:
        // values X
        // listas V
      // cambiar el campo "lists" del main.json por "containers" e incluir en el factorias de values.
      // ¿Tenemos un demonio vacio?
      // Factorias sistema de menus
      // Factorias BasicPreLoopSDLDaemon/BasicPostLoopSDLDaemon
      // Quizas todas las factorias de entidades iniciales deban dejar tickets de estas en un RsrcStore de tickets.

    // Desarrollos deseados
      // Expandir interfaz de RsrcLoader para poder preguntar estado.
      // * Cada RsrcLoader es responsable de anotar su estado. struct done/total/msgId
      // Añadir descripcion a factoria en json
      // CommonResources incluye recursos por defecto en RsrcStores.
        // Ejemplo: "ContexTime.SysTime" siempre contiene el singleto de SysTime. (Quizás justo este ejemplo sea malo. No podemos jugarnosla a meter SysTime en un shared_ptr)
        // ... pues resulta que SysTime::getInstance() devuelve uns shared_ptr.

    // Chorrandeces
      // La pantalla de carga dice tontas mientras pasan las barras de progreso.
}
