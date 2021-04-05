/**
 * Copyright 2011 Batis Degryll Ludo
 * @file RsrcDictionary.h
 * @since 2018-04-16
 * @date 2018-04-16
 * @author Degryll Ludo Batis
 * @brief
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_RSRCDICTIONARY_H_
#define ZBE_CORE_TOOLS_CONTAINERS_RSRCDICTIONARY_H_

#include <memory>
#include <string>
#include <map>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A class that translate a name to a globaly accesible resource id.
 */
template<typename T>
class ZBEAPI RsrcDictionary {
  public:
    RsrcDictionary(RsrcDictionary const&)    = delete;  //!< Needed for singleton.
    void operator=(RsrcDictionary const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the RsrcDictionary.
     */
    static RsrcDictionary& getInstance() {
      static RsrcDictionary instance;
      return (instance);
    }

    /** \brief Associates a string with an id.
     *  \param name Name to identify the resource.
     *  \param id Id of the resource in the adecuate store.
     *  \sa get(string name)
     */
    void insert(std::string name, T rsrc) {
      auto it = l.find(name);
      if (it != l.end()) {
        SysError::setError("Name " + name + " already in use.");
        return;
      }
      l[name] = rsrc;
    }

    /** \brief Returns the resource named "name".
     *  \param name Name to identify the resource.
     *  \return The resource.
     *  \sa insert
     */
    T get(std::string name) {
      auto it = l.find(name);
      if (it == l.end()) {
        SysError::setError("Resource id not found:" + name);
        return T();
      } else {
        return (it->second);
      }
    }

    /** \brief Removes an entry and returns its value.
     *  \param name of the entry.
     *  \return The entry value.
     */
    T remove(std::string name) {
      auto it = l.find(name);
      if (it == l.end()) {
        SysError::setError("Resource id not found:" + name);
        return (T());
      } else {
        auto aux = it->second;
        l.erase(it);
        return (aux);
      }
    }

    /** \brief Returns true if a resource named "name" exist in this dictionary. False otherwise.
     *  \param name Name to identify the resource.
     *  \return True if a resource named "name" exist in this dictionary. False otherwise.
     *  \sa get
     */
    bool contains(std::string name) {
      auto it = l.find(name);
      return (it != l.end());
    }

    /** \brief Clear the container.
     */
    void clear() {
      l.clear();
    }

  private:
    RsrcDictionary() : l() {};  //!< Needed for singleton.

    std::map<std::string, T> l;  //!< Map that associates resources with ids.
};

using NameRsrcDictionary = RsrcDictionary<uint64_t>;

/** \brief A class ZBEAPI that translate a local resource id to a globaly accesible resource id.
 */
class ZBEAPI IdRsrcDictionary {
  public:
    IdRsrcDictionary(IdRsrcDictionary const&)    = delete;  //!< Needed for singleton.
    void operator=(IdRsrcDictionary const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the IdRsrcDictionary.
     */
    static IdRsrcDictionary& getInstance() {
      static IdRsrcDictionary instance;
      return (instance);
    }

    /** \brief Associates a string with an id.
     *  \param local Id of the global resource id in a local context.
     *  \param global Id of the resource in the adecuate store. (globaly accesible)
     *  \sa get(string name)
     */
    void insert(uint64_t local, uint64_t global) {
      auto it = l.find(local);
      if (it != l.end()) {
        SysError::setError(std::string("Local id ") + std::to_string(local) + std::string(" already in use."));
        return;
      } else if (local == 0) {
        SysError::setError("Using zero as id is potentialy dangerous");
      }
      l[local] = global;
    }

    /** \brief Returns the id of resource named "name".
     *  \param local Id of the global resource id in a local context.
     *  \return The resource id.
     *  \sa insert
     */
    uint64_t get(uint64_t local) {
      auto it = l.find(local);
      if (it == l.end()) {
        SysError::setError("Resource id not found:" + std::to_string(local));
        return (0);
      } else {
        return (it->second);
      }
    }

    /** \brief Removes an entry and returns its value.
     *  \param local id of the entry.
     *  \return The entry value.
     */
    uint64_t remove(uint64_t local) {
      auto it = l.find(local);
      if (it == l.end()) {
        SysError::setError("Resource id not found:" + std::to_string(local));
        return (0);
      } else {
        auto aux = it->second;
        l.erase(it);
        return (aux);
      }
    }

    /** \brief Clear the container.
    */
    void clear() {
      l.clear();
    }

  private:
    IdRsrcDictionary() : l() {};  //!< Needed for singleton.

    std::map<uint64_t, uint64_t> l;  //!< Map that associates resources with ids.
};


}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_RSRCDICTIONARY_H_
