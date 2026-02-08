#include "libcharsets/unicode/unicode_utf8.h"

/*
   utf-8 encoding bytes
   1 byte : 0xxxxxxx                            (0x000000 -> 0x00007F)
   2 bytes: 110xxxxx 10xxxxxx                   (0x000080 -> 0x0007FF)
   3 bytes: 1110xxxx 10xxxxxx 10xxxxxx          (0x000800 -> 0x00FFFF)
   4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (0x010000 -> 0x10FFFF)
*/
unsigned utf8_next_character_size(utf8 const *string)
{
   switch(string[0])
   {
      case 0b0000'0000 ... 0b0111'1111: return 1;
      case 0b1100'0000 ... 0b1101'1111: return 2;
      case 0b1110'0000 ... 0b1110'1111: return 3;
      case 0b1111'0000 ... 0b1111'0111: return 4;

      default: return 0;
   }
}
