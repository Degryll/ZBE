/**
* Copyright 2015 Batis Degryll Ludo
* @file RsrcLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief Interface for classes that loads resources.
*/

#ifndef ZBE_RESOURCES_LOADERS_RSRCLOADER_H_
#define ZBE_RESOURCES_LOADERS_RSRCLOADER_H_

#include <filesystem>
#include <string>

#include "ZBE/resources/contextnames.h"

namespace zbe {

/** \brief Interface for classes that loads resources.
*/
class ZBEAPI RsrcLoader {
public:

 virtual ~RsrcLoader() {} //!< Virtual destructor.

 /** \brief Load a resource
  *  \param filePath Path to resource file.
  */
 virtual void load(std::filesystem::path filePath) = 0;

 /** \brief Tells if a file extension is loadable.
  *  \param extension resource file extension.
  *  \return True if the extensions is loadable by the given implementation.
  */
 virtual bool isLoadable(std::filesystem::path extension) = 0;
};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_RSRCLOADER_H_
