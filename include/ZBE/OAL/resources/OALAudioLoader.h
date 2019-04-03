/**
* Copyright 2012 Batis Degryll Ludo
* @file OALAudioLoader.h
* @since 2019-03-19
* @date 2019-03-19
* @author Batis Degryll Ludo
* @brief RsrcLoader implementation caplable of load ogg files into OAL system.
*/

#ifndef ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_
#define ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_

#include <filesystem>
#include <memory>

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcDefLoader.h"

#include "ZBE/OAL/system/OALAudioStore.h"

namespace zbe {

/** \brief RsrcLoader implementation caplable of load ogg files into OAL system.
*/
class ZBEAPI OALAudioLoader : public RsrcLoader {
public:

 /** \brief Builds an OALAudioLoader from a OALAudioStore
  *  \audioStore OALAudioLoader to use.
  */
 OALAudioLoader(std::shared_ptr<OALAudioStore> audioStore, std::shared_ptr<RsrcDefLoader> audioDefLoader)
   : audioStore(audioStore), audioDefLoader(audioDefLoader) {}

 /** \brief Load an audio file
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath);

 /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
 bool isLoadable(std::filesystem::path extension);

private:

 std::filesystem::path generateDefPath(const std::filesystem::path& p);

 std::shared_ptr<OALAudioStore> audioStore;
 std::shared_ptr<RsrcDefLoader> audioDefLoader;
 static std::filesystem::path ext;

};

}  // namespace zbe

#endif  // ZBE_OAL_RESOURCES_OALAUDIOLOADER_H_
