/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2016-04-27
 * @author Ludo
 * @brief Imput reader using sdl.
 */

#ifndef SDLINPUTREADER_H
#define SDLINPUTREADER_H

#include "../InputReader.h"
#include <SDL2/SDL.h>
#include <map>

namespace zbe {
/** \brief Manage intput from keyboard/mouse using SDL
 */
class SDLInputReader : public InputReader {
  private:
    /** \brief Private empty constructor
     */
    SDLInputReader():changedIds(0), states(0){}

  public:
    /** \brief Returns singleton instance for SDLInputReader
     */
    static SDLInputReader * getInstance();

    /** \brief Set the input data.
     */
    void setInputStatus(std::list<uint32_t>* changedIds, std::map<uint32_t, float>* states);

    inline std::list<uint32_t>* changes() {return changedIds;}

    float getStatus(uint32_t keyid);

  private:
    std::list<uint32_t>* changedIds;
    std::map<uint32_t, float>* states;
};

} // namespace zbe
#endif // SDLINPUTREADER_H
