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

namespace zbe {

/** \brief A class that translate a name to a globaly accesible resource id.
 */
class NameRsrcDictionary {
  public:
    NameRsrcDictionary(NameRsrcDictionary const&)    = delete;  //!< Needed for singleton.
    void operator=(NameRsrcDictionary const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the NameRsrcDictionary.
     */
    static NameRsrcDictionary& getInstance() {
      static NameRsrcDictionary instance;
      return (instance);
    }

    /** \brief Associates a string with an id.
     *  \param name Name to identify the resource.
     *  \param id Id of the resource in the adecuate store.
     *  \sa get(string name)
     */
    void insert(std::string name, uint64_t id) {
      auto it = l.find(name);
      if (it != l.end()) {
        SysError::setError("Name " + name + " already in use.");
        return;
      } else if (id == 0) {
        SysError::setError("Using zero as id is potentialy dangerous");
      }
      l[name] = id;
    }

    /** \brief Returns the id of resource named "name".
     *  \param name Name to identify the resource.
     *  \return The resource id.
     *  \sa insert
     */
    uint64_t get(std::string name) {
      auto it = l.find(name);
      if (it == l.end()) {
        SysError::setError("Resource id not found.");
        return (0);
      } else {
        return (it->second);
      }
    }

    /** \brief Clear the container.
     */
    void clear() {
      l.clear();
    }

  private:
    NameRsrcDictionary() : l() {};  //!< Needed for singleton.

    std::map<std::string, uint64_t> l;  //!< Map that associates resources with ids.
};

/** \brief A class that translate a local resource id to a globaly accesible resource id.
 */
class IdRsrcDictionary {
  public:
    IdRsrcDictionary(IdRsrcDictionary const&)    = delete;  //!< Needed for singleton.
    void operator=(IdRsrcDictionary const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the NameRsrcDictionary.
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
        SysError::setError("Resource id not found.");
        return (0);
      } else {
        return (it->second);
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