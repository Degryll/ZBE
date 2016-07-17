/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ListManager.h
 * @since 2016/03/31
 * @date 2016/03/31
 * @author Degryll
 * @brief A class that relates an id with a list.
 */

#ifndef CORE_TOOLS_CONTAINERS_LISTMANAGER_H_
#define CORE_TOOLS_CONTAINERS_LISTMANAGER_H_

#include <map>
#include "ZBE/core/system/SysError.h"

namespace zbe {

/** \brief A class that relates an id with a list.
 */
template <typename T>
class ListManager {
  public:
    ListManager(ListManager const&)    = delete;  //!< Needed for singleton.
    void operator=(ListManager const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the ListManager.
     */
    static ListManager& getInstance() {
      static ListManager<T> instance;
      return (instance);
    }

    /** \brief Associates a list with an id.
     *  \param id Id to identify the list.
     *  \param list The list.
     */
    void insert(uint64_t id, T *list) {l[id] = list;}

    /** \brief Returns the list identify by the id.
     *  \param id Id to identify the list.
     *  \return The list.
     */
    T* get(uint64_t id);

  private:
    ListManager() {};  //!< Needed for singleton.

    std::map<uint64_t, T*> l;  //!< Map that associates list with ids.
};

template <typename T>
T* ListManager<T>::get(uint64_t id) {
  auto it = l.find(id);
  if (it == l.end()) {
    SysError::setError("List is not found.");
    return (0);
  } else {
    return (it->second);
  }
}

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_LISTMANAGER_H_
