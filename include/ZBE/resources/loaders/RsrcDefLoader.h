/**
* Copyright 2015 Batis Degryll Ludo
* @file RsrcDefLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief Interface for classes that loads resource definitions.
*/

#ifndef ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_
#define ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_

#include <filesystem>

namespace zbe {

/** \brief Interface for classes that loads resource definitions.
 */
class ZBEAPI RsrcDefLoader {
public:
 virtual ~RsrcDefLoader(){} //!< Virtual destructor.

 /** \brief Load a resource definition
  *  \param url resource definition file to be loaded.
  *  \param rsrcId Associated resource id
  *  \return An id to the resource definition.
  */
 virtual void loadRsrcDef(const std::filesystem::path& url, uint64_t rsrcId) = 0;

 /** \brief Returns the file extension.
  *  \return The file extension.
  */
 virtual const std::filesystem::path getExtension() = 0;

};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_
