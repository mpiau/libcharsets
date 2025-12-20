#include "libcharsets/charset_ascii.h"
#include "libcharsets/charsets.h"

#include <assert.h>

// Compile it manually for the moment.
// gcc tests/main.c -Iinclude -L. -lcharsets -o test

int main()
{
   assert(ascii_seq_count("") == 0);
   assert(ascii_seq_count("a") == 1);
   assert(ascii_seq_count("abcdef") == 6);

   assert(ascii_seq_ncount("", 5) == 0);
   assert(ascii_seq_ncount("a", 5) == 1);
   assert(ascii_seq_ncount("abcdef", 5) == 5);
   assert(ascii_seq_ncount("1234567890",  0) ==  0);
   assert(ascii_seq_ncount("1234567890",  9) ==  9);
   assert(ascii_seq_ncount("1234567890", 10) == 10);
   assert(ascii_seq_ncount("1234567890", 11) == 10);

   return 0;
}