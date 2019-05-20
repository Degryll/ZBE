/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcLoaderDmn.h
 * @since 2019-04-03
 * @date 2019-04-03
 * @author Ludo Degryll Batis
 * @brief A Daemon capable of run a RsrcLoader
 */

#ifndef ZBE_DAEMONS_RSRCFOLDERLOADERDMN_H
#define ZBE_DAEMONS_RSRCFOLDERLOADERDMN_H

#include <memory>
#include <vector>
#include <filesystem>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/resources/loaders/RsrcFolderLoader.h"

namespace zbe {

/** \brief DaemonMaster is a Daemon responsible for run others Daemons. This is necessary to build the Daemons tree.
 */
class ZBEAPI RsrcFolderLoaderDmn : public Daemon {
public:

  /** \brief Empty constructor.
   */
  RsrcFolderLoaderDmn() : rsrcFolderLoader(), folderPath() {}

  /** \brief Destructor and the contained Daemons.
   */
  ~RsrcFolderLoaderDmn() {}

  /** \brief It will run all Daemons added to this DaemonMaster.
   */
  void run();

  /** \brief Set the RsrcLoader to be run by this Daemon.
   * \param loader Shared point to the RsrcLoader to be stored and executed.
   */
  void setRsrcFolderLoader(std::shared_ptr<RsrcFolderLoader> loader);

  /** \brief Set the RsrcLoader to be run by this Daemon.
   * \param loader Shared point to the RsrcLoader to be stored and executed.
   */
  void setUrl(std::string folder);

private:
  std::shared_ptr<RsrcFolderLoader> rsrcFolderLoader;
  std::filesystem::path folderPath;
};

}  // namespace zbe

#endif  // ZBE_DAEMONS_RSRCFOLDERLOADERDMN_H
