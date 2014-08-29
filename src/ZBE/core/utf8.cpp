/**
 * Copyright 2012 Batis Degryll Ludo
 * @file utf8.cpp
 * @since 2014-08-23
 * @date 2014-08-23
 * @author Degryll
 * @brief To work with UTF-8.
 */

#include <string>

#include "ZBE/core/utf8.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

inline size_t sequence_length(unsigned char lead) {
  if (lead < 0x80)
    return 1;
  else if ((lead >> 5) == 0x6)
    return 2;
  else if ((lead >> 4) == 0xe)
    return 3;
  else if ((lead >> 3) == 0x1e)
    return 4;
  else
    return 0;
}

inline unsigned char mask8(char oc) {
    return static_cast<unsigned char>(0xff & oc);
}

inline int increase_safely(const char* &it) {
  it++;
  if (*it == 0) {
    zbe::SysError::setError("UTF-8 ERROR: Not enough room.");
    return -1;
  }

  if (!((mask8(*it) >> 6) == 0x2)) {
    zbe::SysError::setError("UTF-8 ERROR: Incomplete sequence.");
    return -1;
  }

  return 0;
}

inline int get_sequence_2(const char* &it, unsigned int& code_point) {
  code_point = mask8(*it);

  if (increase_safely(it)) {
    return -1;
  }

  code_point = ((code_point << 6) & 0x7ff) + (mask8(*it) & 0x3f);

  return 0;
}

inline int get_sequence_3(const char* &it, unsigned int& code_point) {
  code_point = mask8(*it);

  if (increase_safely(it)) {
    return -1;
  }

  code_point = ((code_point << 12) & 0xffff) + ((mask8(*it) << 6) & 0xfff);

  if (increase_safely(it)) {
    return -1;
  }

  code_point += mask8(*it) & 0x3f;

  return 0;
}

inline int get_sequence_4(const char* &it, unsigned int& code_point) {
  code_point = mask8(*it);

  if (increase_safely(it)) {
    return -1;
  }

  code_point = ((code_point << 18) & 0x1fffff) + ((mask8(*it) << 12) & 0x3ffff);

  if (increase_safely(it)) {
    return -1;
  }

  code_point += (mask8(*it) << 6) & 0xfff;

  if (increase_safely(it)) {
    return -1;
  }

  code_point += mask8(*it) & 0x3f;

  return 0;
}

inline bool is_surrogate(unsigned short cp) {
    return (cp >= LEAD_SURROGATE_MIN && cp <= TRAIL_SURROGATE_MAX);
}

inline bool is_code_point_valid(unsigned int cp) {
    return (cp <= CODE_POINT_MAX && !is_surrogate(cp));
}

inline bool is_overlong_sequence(unsigned int cp, size_t length) {
    if (cp < 0x80) {
        if (length != 1)
            return true;
    }
    else if (cp < 0x800) {
        if (length != 2)
            return true;
    }
    else if (cp < 0x10000) {
        if (length != 3)
            return true;
    }

    return false;
}

int next(const char* &it, unsigned int &code_point) {
  const char* original_it = it;
  uint32_t cp = 0;
  size_t length = sequence_length(*it);

  int err = 0;
  switch (length) {
    case 0:
      zbe::SysError::setError("UTF-8 ERROR: Invalid lead.");
      return -1;
    case 1:
      cp = it[0];
      break;
    case 2:
      err = get_sequence_2(it, cp);
    break;
    case 3:
      err = get_sequence_3(it, cp);
    break;
    case 4:
      err = get_sequence_4(it, cp);
    break;
  }

  if (!is_code_point_valid(cp)) {
    zbe::SysError::setError("UTF-8 ERROR: Invalid code point.");
    err = -1;
  } else if (is_overlong_sequence(cp, length)) {
    zbe::SysError::setError("UTF-8 ERROR: Overlong sequence.");
    err = -1;
  }

  if (err != 0) {
    it = original_it;
  } else {
    code_point = cp;
    ++it;
  }

  return err;
}

int utf8to16(unsigned short *dst, const char* src) {
  const char *it = src;
  unsigned int cp;
  bool err = false;

  while (it[0] != 0 && !(err = next(it,cp))) {
    if (cp > 0xffff) { //make a surrogate pair
      *dst++ = static_cast<unsigned short>((cp >> 10)   + LEAD_OFFSET);
      *dst++ = static_cast<unsigned short>((cp & 0x3ff) + TRAIL_SURROGATE_MIN);
    } else {
      *dst++ = static_cast<unsigned short>(cp);
    }
  }  // while
  return err;
}

}  // namespace zbe
