#define _POSIX_C_SOURCE 200809L // Necessary for getline
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "codepoint_categories.h"

static constexpr codepoint INVALID_CODEPOINT = INT32_MAX;

struct CodePointInfo
{
   int32_t codeValue;
   char const *codeName;
   char const *oldCodeName; // Do we want to keep it ? Seems redundant for other code than controls.
   CodePointCategory category;
   bool isMirrored;
   int32_t optAssociatedLowercase;
   int32_t optAssociatedUppercase;
   int32_t optAssociatedTitlecase;
};

typedef struct CodePointInfo CodePointInfo;

static CodePointInfo s_cpsInfo[0xFFFF] = {};

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

// Change the "SMALL TEXT TO SHOW THE ISSUE" into "Small Text To Show The Issue"
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

static void print_codepoint_info(FILE *fp, CodePointInfo const *const cp)
{
   static size_t lineCount = 0;

   fprintf(fp, "[%05lu]: 0x%04X [%s] %s",
      lineCount, cp->codeValue, codepoint_category_desc(cp->category), cp->codeName
   );

   if (cp->oldCodeName)
   {
      fprintf(fp, " (%s)", cp->oldCodeName);
   }

   if (cp->isMirrored)
   {
      fprintf(fp, " <Mirrored>");
   }

   if (cp->optAssociatedLowercase != INVALID_CODEPOINT)
   {
      fprintf(fp, " [Lower: 0x%04X]", cp->optAssociatedLowercase);
   }
   if (cp->optAssociatedUppercase != INVALID_CODEPOINT)
   {
      fprintf(fp, " [Upper: 0x%04X]", cp->optAssociatedUppercase);
   }
   if (cp->optAssociatedTitlecase != INVALID_CODEPOINT)
   {
      fprintf(fp, " [Title: 0x%04X]", cp->optAssociatedTitlecase);
   }
   fprintf(fp, "\n");

   lineCount += 1;
}

static int generate_codepoints(char const *const filepath)
{
   FILE *fp = fopen(filepath, "r");
   if (fp == nullptr)
   {
      fprintf(stderr, "FATAL: Failure to open the file [%s]\n", filepath);
      return EXIT_FAILURE;
   }

   char const *const filepathDest = "./generated/output.txt";
   FILE *fpDest = fopen(filepathDest, "w");
   if (fpDest == nullptr)
   {
      fprintf(stderr, "FATAL: Failure to create the destination file [%s]\n", filepathDest);
      return EXIT_FAILURE;
   }

   for (size_t idx = 0; idx < 0xFFFF; ++idx)
   {
      s_cpsInfo[idx] = (CodePointInfo) {
         .codeValue = idx,
         .codeName = nullptr,
         .oldCodeName = nullptr,
         .category = CodePointCategory_INVALID,
         .isMirrored = false,
         .optAssociatedLowercase = INVALID_CODEPOINT,
         .optAssociatedTitlecase = INVALID_CODEPOINT,
         .optAssociatedUppercase = INVALID_CODEPOINT
      };
   }

   ssize_t readCount = 0;
   size_t lineLength = 0;
   char *line = nullptr;

   bool lastWasRangeFirst = false;
   codepoint rangeFirstCodePoint = INVALID_CODEPOINT;

   while ((readCount = getline(&line, &lineLength, fp)) != -1)
   {
      char *lineIt = line;

      lineIt[readCount - 1] = '\0'; // Remove '/n' at the end of the line.

      // Field 0: Code value.
      char *token = custom_strsep(&lineIt, ';');
      codepoint const codeValue = (int32_t)strtol(token, nullptr, 16); // Hexadecimal

      // We only want to support the first Unicode plane (Basic Multilingual Plane)
      // Range if from U+0000 to U+FFFF
      if (codeValue > 0xFFFF)
         break;

      CodePointInfo *const cp = &s_cpsInfo[codeValue];
      assert(cp->codeValue == codeValue);

      // Field  1: Character Name.
      token = custom_strsep(&lineIt, ';');
      update_case(token);
      cp->codeName = token;

      // Field  2: General Category
      token = custom_strsep(&lineIt, ';');
      cp->category = codepoint_category_from_ascii(token);

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
      cp->isMirrored = strcmp(token, "Y") == 0 ? true : false;

      // Field 10: Unicode 1.0 Name
      token = custom_strsep(&lineIt, ';');
      // The oldname has some value for controls (that are all just <controls> now).
      // However, keeping it for the rest of the list would just be confusing.
      bool const isControl = (cp->category == CodePointCategory_OTHER_CONTROL);
      if (isControl && token && *token != '\0')
      {
         update_case(token);
         if (strcmp(cp->codeName, token) != 0)
         {
            cp->oldCodeName = token;
         }
      }

      // Field 11: ISO 10646 comment field
      token = custom_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field 12: Uppercase mapping (if exist: hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         cp->optAssociatedUppercase = (int32_t)strtol(token, nullptr, 16);
      }

      // Field 13: Lowercase mapping (if exist : hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         cp->optAssociatedLowercase = (int32_t)strtol(token, nullptr, 16);
      }

      // Field 14: Titlecase mapping (if exist: hex codepoint, else empty)
      token = custom_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         cp->optAssociatedTitlecase = (int32_t)strtol(token, nullptr, 16);
      }

      // ========= HANDLE RANGES ============
      // Seems like there are also some ranges inside UnicodeData.txt file.
      // There are not under X..Y form but the following:
      // "[...];<CJK Ideograph, First>;[...]"
      // "[...];<CJK Ideograph, Last>;[...]"

      if (lastWasRangeFirst)
      {
         assert(strstr(cp->codeName, ", Last>") != nullptr);

         cp->codeName = cp->codeName + 1; // Remove first "<"
         *(strstr(cp->codeName, ",")) = '\0'; // Remove everything starting from ','

         for (codepoint cpRange = rangeFirstCodePoint; cpRange <= cp->codeValue; ++cpRange)
         {
            CodePointInfo *cpInRange = &s_cpsInfo[cpRange];
            memcpy(cpInRange, cp, sizeof(*cp));
            cpInRange->codeValue = cpRange;
            char *finalName = malloc(strlen(cp->codeName) + 8);
            sprintf(finalName, "%s-%04X", cp->codeName, cpInRange->codeValue);
            cpInRange->codeName = finalName;
            print_codepoint_info(fpDest, cpInRange);
         }
         lastWasRangeFirst = false;
      }
      else if (strstr(cp->codeName, ", First>"))
      {
         lastWasRangeFirst = true;
         rangeFirstCodePoint = cp->codeValue;
         // Don't print the codepoint here, wait for the ", Last>" being parsed first.
      }
      else
      {
         print_codepoint_info(fpDest, cp);
      }
   }

   fclose(fpDest);
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