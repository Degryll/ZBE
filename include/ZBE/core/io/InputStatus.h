/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputStatus.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Ludo
 * @brief Single imput status representation.
 */

#ifndef CORE_IO_INPUTSTATUS_H
#define CORE_IO_INPUTSTATUS_H

#include <cstdint>

namespace zbe {

class InputStatus {
  public:

    InputStatus(uint32_t id,float status,uint64_t time):id(id),status(status),time(time){};

    /** \brief Returns the id of the input element.
     *  \return Id of the input element.
     */
    uint32_t getId() const { return id;} ;

    /** \brief Returns the status of the input source.
     *  \return Status of the input source.
     */
    float getStatus() const { return status;};

    /** \brief Returns the timestamp in which this state is reached.
     *  \return Timestamp in which this state is reached.
     */
    uint64_t getTime() const { return time;};

    /** \brief "Less than" operator overloading.
     *  \return true if left hand element is less than right hand one
     */
    bool operator<(const InputStatus& rhs) const {return time<rhs.getTime();}

  private:

    uint32_t id;
    float status;
    uint64_t time;
};

}

#endif //CORE_IO_INPUTSTATUS_H
