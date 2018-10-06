/**
 * Copyright 2011 Batis Degryll Ludo
 * @file RsrcStore.h
 * @since 2016/03/31
 * @date 2016/08/04
 * @author Degryll
 * @brief A class that relates an id with a resource.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_RSRCSTORE_H_
#define ZBE_CORE_TOOLS_CONTAINERS_RSRCSTORE_H_

#include <memory>

#include <map>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/system/SysIdGenerator.h"

namespace zbe {

/** \brief A class that relates an id with a resource.
 */
template <typename T>
class RsrcStore {
  public:
    RsrcStore(RsrcStore const&)    = delete;  //!< Needed for singleton.
    void operator=(RsrcStore const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the RsrcStore.
     */
    static RsrcStore& getInstance() {
      static RsrcStore<T> instance;
      return (instance);
    }

    /** \brief Associates a resource with an id.
     *  \param id Id to identify the resource.
     *  \param resource The resource.
     */
    void insert(uint64_t id, std::shared_ptr<T> resource) {
      auto it = l.find(id);
      if (it != l.end()) {
        SysError::setError("Id already in use.");
        return;
      } else if (id == 0) {
        SysError::setError("Using zero as id is potentialy dangerous");
      }
      l[id] = resource;
    }

    /** \brief Associates a resource with a name.
     *  \param name Name to identify the resource.
     *  \param resource The resource.
     */
    void insert(std::string name, std::shared_ptr<T> resource) {
      uint64_t id = SysIdGenerator::getId();
      dict.insert(name, id);
      this->insert(id, resource);
    }

    /** \brief Returns the resource identify by the id.
     *  \param id Id to identify the resource.
     *  \return The resource.
     */
    std::shared_ptr<T> get(uint64_t id);

    /** \brief Returns the resource identify by the name.
     *  \param name Name to identify the resource.
     *  \return The resource.
     */
    std::shared_ptr<T> get(std::string name) {
      uint64_t id = dict.get(name);
      return (this->get(id));
    }

    /** \brief Clear the container.
    */
    void clear() {
      l.clear();
    }

  private:
    RsrcStore() : l() {};  //!< Needed for singleton.

    std::map<uint64_t, std::shared_ptr<T> > l;  //!< Map that associates resources with ids.
    NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();  //!< Nuevo, maho y reshulón-----------------
};

template <typename T>
std::shared_ptr<T> RsrcStore<T>::get(uint64_t id) {
  auto it = l.find(id);
  if (it == l.end()) {
    SysError::setError("Resource not found.");
    return (std::shared_ptr<T>());
  } else {
    return (it->second);
  }
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_RSRCSTORE_H_
