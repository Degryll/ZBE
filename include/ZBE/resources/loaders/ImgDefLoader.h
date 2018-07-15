// TODO filesystem
///**
// * Copyright 2015 Batis Degryll Ludo
// * @file ImgDefLoader.h
// * @since 2018-04-19
// * @date 2018-04-19
// * @author Batis Degryll Ludo
// * @brief Interface for classes that loads image definitions. It will return an identifier
// * of the loaded image definition.
// */
//
//#ifndef ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_
//#define ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_
//
//#include <filesystem>
//
//namespace zbe {
//
// /** \brief Interface for classes that loads image definitions. It will return an identifier
//  */
//class ImgDefLoader {
//public:
//  virtual ~ImgDefLoader(){} //!< Virtual destructor.
//
//  /** \brief Load an image definition
//   *  \param url Image definition file to be loaded.
//   *  \param imgId Associated image id
//   *  \return An id to the image definition.
//   */
//  virtual void loadImgDef(const std::filesystem::path& url, uint64_t imgId) = 0;
//
//  /** \brief Returns the file extension.
//   *  \return The file extension.
//   */
//  virtual const std::filesystem::path getExtension() = 0;
//
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_RESOURCES_LOADERS_IMGDEFLOADER_H_
