/**
 * Copyright 2011 Batis Degryll Ludo
 * @file TicketedForwardList.h
 * @since 2015-02-08
 * @date 2018-03-25
 * @author Degryll Batis Ludo
 * @brief A wrapper for c++ forward_list using Tickets.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TICKETEDFORWARDLIST_H_
#define ZBE_CORE_TOOLS_CONTAINERS_TICKETEDFORWARDLIST_H_

#include <forward_list>
#include <memory>
#include <type_traits>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/Ticket.h"

namespace zbe {

/** \brief Iterator for a ticketed forward list.
 *
 */
template <typename T, typename UnqualifiedType = std::remove_cv<T> >
class TicketedForwardListIterator;

/** \brief A wrapper for c++ forward_list using Tickets.
 *
 *  Stored elements with an state.
 *  \sa Ticket
 */
template <typename T>
class TicketedForwardList {
public:
  TicketedForwardList(const TicketedForwardList&) = delete;
  void operator=(const TicketedForwardList&) = delete;

  using iterator = TicketedForwardListIterator<T>; //!< Definition of iterator used.

  /** \brief Empty constructor.
   */
  TicketedForwardList() : l() {}

  /** \brief Inserts a new element at the beginning of the forward_list, right before its current first element. The content of val is copied (or moved) to the inserted element.
   *  \param val Value to be copied (or moved) to the inserted element.
   */
  std::shared_ptr< TicketedElement<T> > push_front(std::shared_ptr<T> val) {
    std::shared_ptr< TicketedElement<T> > t =std::make_shared<TicketedElement<T> >(val);
    l.push_front(t);
    return (t);
  }

  /** \brief Returns an iterator pointing to the first element in the forward_list container.
   *  \return An iterator to the beginning of the sequence container.
   */
  iterator begin() {
    auto p = l.before_begin();
    auto i = l.begin();
    auto e = l.end();
    return (iterator(&l, p, i, e));
  }

  /** \brief Returns an iterator referring to the past-the-end element in the forward_list container.
   *  \return An iterator to the element past the end of the sequence.
   */
  iterator end() {
    auto e = l.end();
    return (iterator(&l, e, e, e));
  }

  /** \brief Returns an iterator referring to the past-the-end element in the forward_list container.
   *  \return An iterator to the element past the end of the sequence.
   */
  bool empty() {
    return (this->begin() == this->end());
  }

  /** \brief Removes all elements from the container (which are destroyed), and leaving the container with a size of 0.
   */
  void clear() {
    for(auto it = this->begin(); it != this->end(); ++it) {
      it.setERASED();
    }
    begin();
  }

private:

  std::forward_list< std::shared_ptr< TicketedElement<T> > > l;  //!< The STL forward list
};

template <typename T, typename UnqualifiedType>
class TicketedForwardListIterator : public std::iterator<std::forward_iterator_tag,
                                           UnqualifiedType,
                                           std::ptrdiff_t,
                                           T*,
                                           T&> {
public:

  /** \brief Empty constructor.
   */
  TicketedForwardListIterator()
  : fl(nullptr),
    p(typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator()),
    i(typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator()),
    e(typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator()) {}

  /** \brief Parametrized constructor.
   *  \param fl The STL forward list.
   *  \param pre An iterator before it.
   *  \param it The iterator of the STL forward list.
   *  \param end An iterator to the end of the STL forward list.
   */
  TicketedForwardListIterator(std::forward_list< std::shared_ptr< TicketedElement<T> > >* fl,
                            typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator pre,
                            typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator it,
                            typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator end) : fl(fl), p(pre), i(it), e(end) {
    checkForACTIVE();
  }

  /** \brief Forward the iterator to the next ACTIVE element (or the end of the container).
   *  \return The forwarded iterator.
   */
  TicketedForwardListIterator& operator++ () {
    ++p;
    ++i;
    checkForACTIVE();
    return *this;
  }

  /** \brief Forward the iterator to the next ACTIVE element (or the end of the container).
   *  \return The iterator before the forward operation.
   */
  TicketedForwardListIterator operator++ (int) {
    TicketedForwardListIterator result(*this);
    operator++();
    return result;
  }

  /** \brief Compare if two iterators are equals. Can compare const and no const iterators.
   *  \return True if the iterators are equals (False otherwise).
   */
  template<class OtherType>
  bool operator == (const TicketedForwardListIterator<OtherType>& rhs) const {
    return (i == rhs.i);
  }

  /** \brief Compare if two iterators are different. Can compare const and no const iterators.
   *  \return True if the iterators are different (False otherwise).
   */
  template<class OtherType>
  bool operator != (const TicketedForwardListIterator<OtherType>& rhs) const {
    return (i != rhs.i);
  }

  /** \brief Dereference the iterator.
   *  \return The element pointed by the iterator.
   */
  std::shared_ptr<T> operator* () {
    checkForACTIVE();
    return (i->get()->getElement());
  }

  /** \brief Dereference the iterator.
   *  \return The element pointed by the iterator.
   */
  std::shared_ptr<T> operator-> () {
    checkForACTIVE();
    return (i->get()->getElement());
  }

  /** \brief Construct a constant iterator from an iterator.
   *  \return The const iterator.
   */
  operator TicketedForwardListIterator<const T>() const {
    return (TicketedForwardListIterator<const T>(fl, p, i, e));
  }

  /** \brief Marks the current item as erased.
   *
   */
  void setERASED() {
    if (i != e) {
      i->get()->setERASED();
    }
  }

protected:
  /** brief Moves the iterator to the next active element.
   *
  */
  void checkForACTIVE() {
    while(i != e && i->get()->isNotACTIVE()) {
      if(i->get()->isERASED()) {
        i = fl->erase_after(p);
      } else {
        ++p;
        ++i;
      }
    }  // while is not ACTIVE
  }

private:
  std::forward_list< std::shared_ptr< TicketedElement<T> > >* fl;          //!< A pointer to the STL forward list
  typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator p;  //!< An iterator before the real iterator
  typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator i;  //!< The real iterator (the one that points to the right element)
  typename std::forward_list< std::shared_ptr< TicketedElement<T> > >::iterator e;  //!< An iterator to the end of the list.
};

  /** \brief An alias to the TicketedForwardListIterator.
   */
  template <typename T>
  using TicketedFLIterator = TicketedForwardListIterator<T>;
  /** \brief An alias to the constant TicketedForwardListIterator.
   */
  template <typename T>
  using TicketedFLConstIterator = TicketedForwardListIterator<T const>;

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TICKETEDFORWARDLIST_H_
