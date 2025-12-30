#define _POSIX_C_SOURCE 200809L // Necessary for getline
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static constexpr int32_t INVALID_CODEPOINT = INT32_MAX;

struct CodePointLine
{
   int32_t codeValue;
   char const *codeName;
   char const *oldCodeName; // Do we want to keep it ? Seems redundant for other code than controls.
   char const *generalCategory;
   bool isMirrored;
   int32_t optAssociatedLowercase;
   int32_t optAssociatedUppercase;
   int32_t optAssociatedTitlecase;
};

typedef struct CodePointLine CodePointLine;

// Implementing my own strsep because it strtok doesn't support empty fields
// and it seems that strsep doesn't exist for me. However I used a char instead of
// a char * for the delimiter as we don't need to handle a string delimiter.
static char *custom_strsep(char **const strPtr, const char sep)
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


static void update_case(char *const str)
{
   char *it = str;

   while (*it != '\0')
   {
      if (isupper(*it) && (it != str && !isspace(*(it - 1))))
      {
         *it = tolower(*it);
      }

      it += 1;
   }
}

static int generate_codepoints(char const *const filepath)
{
   FILE *fp = fopen(filepath, "r");
   if (fp == nullptr)
   {
      fprintf(stderr, "FATAL: Failure to open the file [%s]\n", filepath);
      return EXIT_FAILURE;
   }

   ssize_t readCount = 0;
   size_t lineLength = 0;
   char *line = nullptr;

   size_t lineIdx = 0;
   while ((readCount = getline(&line, &lineLength, fp)) != -1)
   {
      char *lineIt = line;

      lineIt[readCount - 1] = '\0'; // Remove '/n' at the end of the line.

      CodePointLine cp = {};

      // Field 0: Code value.
      char *token = custom_strsep(&lineIt, ';');
      cp.codeValue = (int32_t)strtol(token, nullptr, 16); // Hexadecimal

      // We only want to support the first Unicode plane (Basic Multilingual Plane)
      // Range if from U+0000 to U+FFFF
      if (cp.codeValue > 0xFFFF)
         break;

      // Field  1: Character Name.
      token = custom_strsep(&lineIt, ';');
      update_case(token);
      cp.codeName = token;

      // Field  2: General Category
      token = custom_strsep(&lineIt, ';');
      cp.generalCategory = token;

      // Field  3: Canonical combining classes
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  4: Bidirectional category
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  5: Character decomposition mapping
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  6: Decimal digit value
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  7: Digit value
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  8: Numeric value
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  9: Mirrored
      token = custom_strsep(&lineIt, ';');
      cp.isMirrored = strcmp(token, "Y") == 0 ? true : false;

      // Field 10: Unicode 1.0 Name
      token = custom_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         update_case(token);
         if (strcmp(cp.codeName, token) != 0)
         {
            cp.oldCodeName = token;
         }
         else
         {
            cp.oldCodeName = nullptr;
         }
      }

      // Field 11: ISO 10646 comment field
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field 12: Uppercase mapping (if exist: hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      cp.optAssociatedUppercase = (token && *token != '\0')
         ? (int32_t)strtol(token, nullptr, 16)
         : INVALID_CODEPOINT;

      // Field 13: Lowercase mapping (if exist : hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      cp.optAssociatedLowercase = (token && *token != '\0')
         ? (int32_t)strtol(token, nullptr, 16)
         : INVALID_CODEPOINT;

      // Field 14: Titlecase mapping (if exist: hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      cp.optAssociatedTitlecase = (token && *token != '\0')
         ? (int32_t)strtol(token, nullptr, 16)
         : INVALID_CODEPOINT;


      // ========= DISPLAY THE EXTRACTED VALUES ==========


      printf("[%05lu]: 0x%04X [%s] %s", lineIdx, cp.codeValue, cp.generalCategory, cp.codeName);
      if (cp.oldCodeName)
      {
         printf(" (%s)", cp.oldCodeName);
      }

      if (cp.isMirrored)
      {
         printf(" <Mirrored>");
      }

      if (cp.optAssociatedLowercase != INVALID_CODEPOINT)
      {
         printf(" [Lower: 0x%04X]", cp.optAssociatedLowercase);
      }
      if (cp.optAssociatedUppercase != INVALID_CODEPOINT)
      {
         printf(" [Upper: 0x%04X]", cp.optAssociatedUppercase);
      }
      if (cp.optAssociatedTitlecase != INVALID_CODEPOINT)
      {
         printf(" [Title: 0x%04X]", cp.optAssociatedTitlecase);
      }
      printf("\n");

      lineIdx += 1;
   }

   fclose(fp);
   return EXIT_SUCCESS;
}


int main(int argc, char **argv)
{
   if (argc != 2)
   {
      fprintf(stderr,
         "Wrong numbers of arguments received.\n"
         "[./executable] [unicodeData.txt path]\n"
      );
      return EXIT_FAILURE;
   }

   return generate_codepoints(argv[1]);
}