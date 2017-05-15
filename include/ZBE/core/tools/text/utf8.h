/**
 * Copyright 2012 Batis Degryll Ludo
 * @file utf8.h
 * @since 2014-08-23
 * @date 2017-05-15
 * @author Degryll
 * @brief To work with UTF-8.
 * Based on the work of Nemanja Trifunovic.
 */

// Copyright 2006 Nemanja Trifunovic

/*
Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef ZBE_CORE_TOOLS_TEXT_UTF8_H_
#define ZBE_CORE_TOOLS_TEXT_UTF8_H_

#include <string>

namespace zbe {

// Unicode constants
const uint16_t LEAD_SURROGATE_MIN  = 0xd800u;  //!< Minimum value of the UTF 16 lead surrogate.
const uint16_t LEAD_SURROGATE_MAX  = 0xdbffu;  //!< Maximum value of the UTF 16 lead surrogate.
const uint16_t TRAIL_SURROGATE_MIN = 0xdc00u;  //!< Minimum value of the UTF 16 trail surrogate.
const uint16_t TRAIL_SURROGATE_MAX = 0xdfffu;  //!< Maximum value of the UTF 16 trail surrogate.
const uint16_t LEAD_OFFSET         = LEAD_SURROGATE_MIN - (0x10000 >> 10);  //!< UTF 16 lead offset.
const uint32_t SURROGATE_OFFSET    = 0x10000u - (LEAD_SURROGATE_MIN << 10) - TRAIL_SURROGATE_MIN;  //!< UTF 16 surrogate offset.

const uint32_t CODE_POINT_MAX      = 0x0010ffffu;  //!< Maximum valid value for a Unicode code point

/** \brief Read the next code point of a UTF8 string.
 *
 * \param it Iterator to the string sequence. Modified after a successful read.
 * \param code_point On a successful read, stores the code point.
 * \return 0 on success.
 */
int next(const char* &it, unsigned int &code_point);

/** \brief Converts a UTF8 string to UTF16.
 *
 * \param dst An unsigned short array to store the UTF16 codification.
 * \param src Original message in UTF8.
 * \return 0 on success.
 */
int utf8to16(unsigned short *dst, const char* src);

/** \brief Converts a UTF8 string to UTF16.
 *
 *  Used to convert a char* UTF8 to a wstring UTF16.
 *
 * \param dst Iterator to a 16bit container to store the UTF16 codification.
 * \param src Original message in UTF8.
 * \return 0 on success.
 */
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

#endif  // ZBE_CORE_TOOLS_TEXT_UTF8_H_
