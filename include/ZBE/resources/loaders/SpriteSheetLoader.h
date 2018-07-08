/**
 * Copyright 2015 Batis Degryll Ludo
 * @file SpriteSheetLoader.h
 * @since 2018-07-05
 * @date 2018-07-05
 * @author Batis Degryll Ludo
 * @brief Interface for classes that loads SpriteSheets. It will return an identifier
 * of the loaded SpriteSheet.
 */

#ifndef ZBE_RESOURCES_LOADERS_SPRITESHEETLOADER_H_
#define ZBE_RESOURCES_LOADERS_SPRITESHEETLOADER_H_

#include <filesystem>

namespace zbe {

/** \brief Interface for classes that loads SpriteSheets. It will return an identifier
 */
class SpriteSheetLoader {
public:
  virtual ~SpriteSheetLoader() {} //!< Virtual destructor.

  /** \brief Load an SpriteSheet
   *  \param filePath Path to SpriteSheet file.
   *  \return An id to the SpriteSheet loaded.
   */
  virtual uint64_t loadSpriteSheet(std::filesystem::path filePath) = 0;

  /** \brief Returns the file extension.
   *  \return The file extension.
   */
  virtual const std::filesystem::path getExtension() = 0;

};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_SPRITESHEETLOADER_H_
