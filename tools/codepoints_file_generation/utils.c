#include "utils.h"

#include <ctype.h>

void utils_update_case(char *str)
{
   char const *const start = str;

   while (*str != '\0')
   {
      if (isupper(*str) && (str != start && !isspace(*(str - 1))))
      {
         *str = tolower(*str);
      }

      str += 1;
   }
}

char *utils_strsep(char **const strPtr, char const sep)
{
   if (strPtr == nullptr)
      return nullptr;

   char const *const tokenStart = *strPtr;
   char *tokenEnd = *strPtr;

   while (*tokenEnd != sep)
   {
      if (*tokenEnd == '\0')
      {
         *strPtr = tokenEnd;
         return (tokenStart != tokenEnd) ? (char *)tokenStart : nullptr;
      }
      tokenEnd += 1;
   }

   *tokenEnd = '\0';
   *strPtr = tokenEnd + 1;
   return (char *)tokenStart;
}
