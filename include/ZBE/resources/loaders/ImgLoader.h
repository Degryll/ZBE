/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImgLoader.h
 * @since 2018-04-19
 * @date 2018-04-19
 * @author Batis Degryll Ludo
 * @brief Interface for classes that loads images. It will return an identifier
 * of the loaded image.
 */

#ifndef ZBE_RESOURCES_LOADERS_IMGLOADER_H_
#define ZBE_RESOURCES_LOADERS_IMGLOADER_H_

#include <experimental/filesystem>

namespace zbe {

/** \brief Interface for classes that loads images. It will return an identifier
 */
class ImgLoader {
public:
  virtual ~ImgLoader(){} //!< Virtual destructor.

  /** \brief Load an image
   *  \param filePath Path to image file.
   *  \return An id to the image loaded.
   */
  virtual uint64_t loadImg(std::experimental::filesystem::path filePath);

  /** \brief Tells if a file extension is loadable.
   *  \param extension Image file extension.
   *  \return True if the extensions is loadable by the given implementation.
   */
  virtual bool isLoadable(std::experimental::filesystem::path extension);

};

}  // namespace zbe

#endif  // ZBE_RESOURCES_LOADERS_IMGLOADER_H_
