/**
 * Copyright 2012 Batis Degryll Ludo
 * @file utf8.h
 * @since 2014-08-23
 * @date 2014-08-23
 * @author Degryll
 * @brief To work with UTF-8.
 */

#ifndef CORE_UTF8_H_
#define CORE_UTF8_H_

#include <string>

namespace zbe {

// Unicode constants
const uint16_t LEAD_SURROGATE_MIN  = 0xd800u;
const uint16_t LEAD_SURROGATE_MAX  = 0xdbffu;
const uint16_t TRAIL_SURROGATE_MIN = 0xdc00u;
const uint16_t TRAIL_SURROGATE_MAX = 0xdfffu;
const uint16_t LEAD_OFFSET         = LEAD_SURROGATE_MIN - (0x10000 >> 10);
const uint32_t SURROGATE_OFFSET    = 0x10000u - (LEAD_SURROGATE_MIN << 10) - TRAIL_SURROGATE_MIN;

// Maximum valid value for a Unicode code point
const uint32_t CODE_POINT_MAX      = 0x0010ffffu;

int next(const char* &it, unsigned int &code_point);

int utf8to16(unsigned short *dst, const char* src);

template <typename u16bit_iterator>
int utf8to16 (u16bit_iterator result, const char* src) {
  const char *it = src;
  unsigned int cp;
  bool err = false;

  while (it[0] != 0 && !(err = next(it,cp))) {
    if (cp > 0xffff) { //make a surrogate pair
      *result++ = static_cast<uint16_t>((cp >> 10)   + LEAD_OFFSET);
      *result++ = static_cast<uint16_t>((cp & 0x3ff) + TRAIL_SURROGATE_MIN);
    } else {
      *result++ = static_cast<uint16_t>(cp);
    }
  }  // while
    return err;
}

}  // namespace zbe

#endif  // CORE_SYSTEM_SYSERROR_H_
