#include "libcharsets/ascii/ascii_string.h"
#include "libcharsets/ascii/ascii_character.h"


//================================================================================================
// API Functions
//================================================================================================

bool ascii_str_validate(byte const *str)
{
   if (str == nullptr)
   {
      return false;
   }

   while (*str)
   {
      if (!ascii_validate(*str))
      {
         return false;
      }
      str += 1;
   }

   return true;
}
