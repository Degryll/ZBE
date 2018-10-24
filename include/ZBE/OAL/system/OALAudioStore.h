/**
 * Copyright 2018 Batis Degryll Ludo
 * @file OALAudioStore.h
 *
 * @since 2018-08-19
 * @date 2018-08-19
 * @author Degryll Ludo
 * @brief A store for audio samples.
 */

#ifndef ZBE_OAL_SYSTEM_OALAUDIOSTORE_H_
#define ZBE_OAL_SYSTEM_OALAUDIOSTORE_H_

#include <cstdint>
#include <vector>

#include <mutex>

#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/OAL/tools/OALUtils.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/**
 * @brief A store for audio samples.
 */
class ZBEAPI OALAudioStore {
public:
    OALAudioStore(const OALAudioStore&) = delete; //!< Delete copy constructor
    void operator=(const OALAudioStore&) = delete; //!< Delete assing aperator

    /** \brief Creates a new OALAudioStore.
     */
    OALAudioStore();

    /** \brief Default destructor. Will free all loaded textures.
     */
    virtual ~OALAudioStore();

    /** \brief Load an audio from a file.
     *
     *  \param url Audio file to be loaded.
     *  \return An id to the audio loaded.
     *  \sa reloadAudio()
     */
    uint64_t loadAudio(const char *url);

    /** \brief Reload an audio to an already created texture.
     *
     *  \param url Audio file to be reloaded.
     *  \param id An id to the audio already created.
     *  \sa loadAudio()
     */
    uint64_t reloadAudio(const char *url, uint64_t id);

    /** \brief Return a stored audio;
     *  \param id An id to the audio already created.
     *  \return an OAL buffer id.
     *  \sa loadImg(), storeTexture()
     */
    ALuint getAudio(uint64_t id);

private:

    bool checkErrors(const char *job);
    void logOALError(const char *job, std::string error);

    ALuint _loadAudio(const char *url);

    //void _loadAudio(const char *url);
    std::vector<ALuint> audioCollection;  //!< Collection of textures.
    std::mutex m;                             //!< Mutex to avoid race conditions.

};

}  // namespace zbe

#endif  // ZBE_OAL_SYSTEM_OALAUDIOSTORE_H_
