#include "libcharsets/charset_ascii.h"


size_t ascii_count(ascii const *str)
{
   ascii const *const begin = str;
   while (*str++);

   return (str - begin) - 1; // -1 for '\0'
}


size_t ascii_ncount(ascii const *str, size_t const max)
{
   ascii const *const begin = str;

   for (size_t i = 0; i <= max && *str++; ++i);

   return (str - begin) -1; // - 1 for '\0'
}
