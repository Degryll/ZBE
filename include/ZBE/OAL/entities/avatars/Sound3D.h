/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sound3D.h
 * @since 2018-08-22
 * @date 2018-08-22
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that produces sound.
 */

#ifndef ZBE_OAL_ENTITIES_AVATARS_SOUND3D_H_
#define ZBE_OAL_ENTITIES_AVATARS_SOUND3D_H_

#include <cstdint>
#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This defines an avatar that produces sound.
 */
class Sound3D {
public:
  using Base = void;//!< inheritance info

  enum State { NEW = 0, PLAYING = 1, STOPPED = 2};

  Sound3D(int64_t audioId) : audioId(audioId), s(NEW), src() {}

  /** \brief Virtual destructor.
   */
  virtual ~Sound3D() {
    alDeleteSources(1, &src);
  }

  /** \brief Setter for the state
   *  \param state The integer value for the state.
   */
  void setSource(ALuint source) {
    src = source;
    s = PLAYING;
  }

  /** \brief Getter for the position.
  *  \return Emisor position.
  */
  virtual Point3D getPosition() = 0;

  /** \brief Getter for the velocity.
  *  \return Emisor velocity.
  */
  virtual Vector3D getVelocity() = 0;

  /** \brief Getter for the audio id.
  *  \return The audio id.
  */
  int64_t getAudioId() {
    return (audioId);
  }

  /** \brief Getter for the OpenAL audio source id.
  *  \return Id of the audio source.
  */
  ALuint getSource() {
    return (src);
  }

  /** \brief Tells if current sound is new (No buffer assigned)
  *  \return true if sound is new. False otherwise
  */
  bool isNew() {
    return (s == NEW);
  }

  /** \brief Tells if current sound is playing
  *  \return true if sound is playing. False otherwise
  */
  bool isPlaying() {
    return (s == PLAYING);
  }

  /** \brief Tells if current sound is ended
  *  \return true if sound is ended. False otherwise
  */
  bool isStopped() {
    return (s == STOPPED);
  }

  /** \brief Tells if current sound is playing
  */
  virtual void stop() = 0;

protected:

  /** \brief Setter for the state
   *  \param state The integer value for the state.
   */
  void setState(State state) {
    s = state;
  }

  /** \brief Getter for the state.
  *  \return Playing state (NEW, PLAYING, END).
  */
  State getState() {
    return (s);
  }

private:
  int64_t audioId;
  State s;
  ALuint src;
};

}  // namespace zbe

#endif  // ZBE_OAL_ENTITIES_AVATARS_SOUND3D_H_
