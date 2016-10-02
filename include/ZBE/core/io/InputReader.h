/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputReader.h
 * @since 2016-03-27
 * @date 2016-04-06
 * @author Ludo
 * @brief Imput reader base.
 */

#ifndef CORE_IO_INPUTREADER_H
#define CORE_IO_INPUTREADER_H

#include <cstdint>
#include <list>

namespace zbe {

/** \brief Abstract class for input readers.
 */
class InputReader {
  public:
    /** \brief Empty destructor.
     */
    virtual ~InputReader() {}

    /** Return a list of key ids that has changed.
     */
    virtual std::list<uint32_t>* changes() = 0;

    /** Get the state of an specific key.
     */
    virtual float getStatus(uint32_t keyid) = 0;

    /** Get the time of an specific key change.
     */
    virtual uint64_t getTime(uint32_t keyid) = 0;
};

} // namespace zbe

#endif // CORE_IO_INPUTREADER_H
