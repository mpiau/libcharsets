#include "libcharsets/charset_ascii.h"
#include "libcharsets/charsets.h"

#include <assert.h>

// Compile it manually for the moment.
// gcc tests/main.c -Iinclude -L. -lcharsets -o test

int main()
{
   assert(ascii_count("") == 0);
   assert(ascii_count("a") == 1);
   assert(ascii_count("abcdef") == 6);

   assert(ascii_ncount("", 5) == 0);
   assert(ascii_ncount("a", 5) == 1);
   assert(ascii_ncount("abcdef", 5) == 5);
   assert(ascii_ncount("1234567890",  0) ==  0);
   assert(ascii_ncount("1234567890",  9) ==  9);
   assert(ascii_ncount("1234567890", 10) == 10);
   assert(ascii_ncount("1234567890", 11) == 10);

   return 0;
}