/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ResourceManager.h
 * @since 2016/03/31
 * @date 2016/08/04
 * @author Degryll
 * @brief A class that relates an id with a resource.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_RESOURCEMANAGER_H_
#define ZBE_CORE_TOOLS_CONTAINERS_RESOURCEMANAGER_H_

#include <memory>

#include <map>

#include "ZBE/core/system/SysError.h"

namespace zbe {

/** \brief A class that relates an id with a resource.
 */
template <typename T>
class ResourceManager {
  public:
    ResourceManager(ResourceManager const&)    = delete;  //!< Needed for singleton.
    void operator=(ResourceManager const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the ResourceManager.
     */
    static ResourceManager& getInstance() {
      static ResourceManager<T> instance;
      return (instance);
    }

    /** \brief Associates a resource with an id.
     *  \param id Id to identify the resource.
     *  \param resource The resource.
     */
    void insert(uint64_t id, std::shared_ptr<T> resource) {l[id] = resource;}

    /** \brief Returns the resource identify by the id.
     *  \param id Id to identify the resource.
     *  \return The resource.
     */
    std::shared_ptr<T> get(uint64_t id);

  private:
    ResourceManager() : l() {};  //!< Needed for singleton.

    std::map<uint64_t, std::shared_ptr<T> > l;  //!< Map that associates resources with ids.
};

template <typename T>
std::shared_ptr<T> ResourceManager<T>::get(uint64_t id) {
  auto it = l.find(id);
  if (it == l.end()) {
    SysError::setError("List not found.");
    return (std::shared_ptr<T>());
  } else {
    return (it->second);
  }
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_RESOURCEMANAGER_H_
