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

#include <SDL2/SDL.h>
#include <map>

#include "ZBE/core/io/InputReader.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {
/** \brief Manage intput from keyboard/mouse using SDL
 */
class SDLInputReader : public InputReader {

  public:
    /** \brief Returns singleton instance for SDLInputReader
     */
    static SDLInputReader & getInstance(){
      static SDLInputReader instance;
      return instance;
    }

    /** \brief Set the input data.
     */
    void setInputStatus(std::list<uint32_t>* changedIds, std::map<uint32_t, float>* states, std::map<uint32_t, uint64_t>* times);

    inline std::list<uint32_t>* changes() {return changedIds;}

    float getStatus(uint32_t keyid);

    uint64_t getTime(uint32_t keyid);

  private:
    /** \brief Private empty constructor
     */
    SDLInputReader():changedIds(0), states(0), times(0){}

    std::list<uint32_t>* changedIds;
    std::map<uint32_t, float>* states;
    std::map<uint32_t, uint64_t>* times;
};

} // namespace zbe
#endif // SDLINPUTREADER_H
