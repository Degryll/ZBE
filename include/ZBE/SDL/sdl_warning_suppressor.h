// sdl_warnings_suppressor.h

#ifndef ZBE_SDL_WARN_SUPPRESS_H
#define ZBE_SDL_WARN_SUPPRESS_H

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wold-style-cast"
        // Añade aquí otros warnings específicos de GCC/Clang que quieras suprimir
    #elif defined(_MSC_VER)
        #pragma warning(push)
        #pragma warning(disable: 4244) // Ejemplo de warning de MSVC (conversión de tipos)
        // Añade aquí otros warnings específicos de MSVC que quieras suprimir
    #endif

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
    #include <SDL_ttf.h>
    #include <SDL_net.h>

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #elif defined(_MSC_VER)
        #pragma warning(pop)
    #endif

#endif //ZBE_SDL_WARN_SUPPRESS_H
