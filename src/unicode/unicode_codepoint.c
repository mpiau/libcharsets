#include "libcharsets/unicode/unicode_codepoint.h"


static constexpr codepoint CODEPOINT_MAX_VALUE = 0x10FFFF;

static constexpr codepoint CODEPOINT_SURROGATES_MIN = 0xD800;
static constexpr codepoint CODEPOINT_SURROGATES_MAX = 0xDFFF;


bool codepoint_validate(codepoint const cp)
{
   // Check the full range
   if (cp > CODEPOINT_MAX_VALUE)
      return false;

   // Check that value not a utf16 surrogate
   if (cp >= CODEPOINT_SURROGATES_MIN && cp <= CODEPOINT_SURROGATES_MAX)
      return false;

   // TODO Check if codepoint is assigned.
   // We don't have any category data for now.

   return true;
}

/*
   utf-8 encoding bytes
   1 byte : 0xxxxxxx                            (0x000000 -> 0x00007F)
   2 bytes: 110xxxxx 10xxxxxx                   (0x000080 -> 0x0007FF)
   3 bytes: 1110xxxx 10xxxxxx 10xxxxxx          (0x000800 -> 0x00FFFF)
   4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (0x010000 -> 0x10FFFF)
*/
bool codepoint_into_utf8(codepoint const cp, utf8 out[static 5])
{
   if (!codepoint_validate(cp))
      return false;

   unsigned idx = 0u;
   if (cp <= 0x7F)
   {
      out[idx++] = (utf8)cp;
   }
   else if (cp <= 0x7FF)
   {
      out[idx++] = 0b1100'0000 | (cp >>  6 & 0b0001'1111);
      out[idx++] = 0b1000'0000 | (cp       & 0b0011'1111);
   }
   else if (cp <= 0xFFFF)
   {
      out[idx++] = 0b1110'0000 | (cp >> 12 & 0b0000'1111);
      out[idx++] = 0b1000'0000 | (cp >>  6 & 0b0011'1111);
      out[idx++] = 0b1000'0000 | (cp       & 0b0011'1111);
   }
   else
   {
      out[idx++] = 0b1111'0000 | (cp >> 18 & 0b0000'0111);
      out[idx++] = 0b1000'0000 | (cp >> 12 & 0b0011'1111);
      out[idx++] = 0b1000'0000 | (cp >>  6 & 0b0011'1111);
      out[idx++] = 0b1000'0000 | (cp       & 0b0011'1111);
   }

   out[idx] = '\0';
   return true;
}
