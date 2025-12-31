#define _POSIX_C_SOURCE 200809L // Necessary for getline

#include "codepoint_categories.h"
#include "parser.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CodePointInfo
{
   int32_t codeValue;
   char const *codeName;
   char const *oldCodeName;
   CodePointCategory category;
   bool isMirrored;
   int32_t optAssociatedLowercase;
   int32_t optAssociatedUppercase;
   int32_t optAssociatedTitlecase;
};

typedef struct CodePointInfo CodePointInfo;

static CodePointInfo s_cpsInfo[FIRST_PLANE_RANGE_LAST] = {};


static void write_header(FILE *fp)
{
   fprintf(fp,
      "#include \"../codepoint_properties.h\"\n"
      "\n"
      "struct CodePointProperties\n"
      "{\n"
      "   codepoint value;\n"
      "   ascii const *name;\n"
      "   CodePointCategory category;\n"
      "   codepoint optLowercase;\n"
      "   codepoint optUppercase;\n"
      "   codepoint optTitlecase;\n"
      "};\n"
      "typedef struct CodePointProperties CodePointProperties;\n"
      "\n"
      "\n"
      "// ===============================================================================================\n"
      "// Properties\n"
      "// ===============================================================================================\n"
      "\n"
      "static constexpr CodePointProperties S_PROPERTIES[] =\n"
      "{\n"
   );
}

static void write_footer(FILE *fp)
{
   fprintf(fp, 
      "};\n"
      "\n"
      "static_assert(sizeofA(S_PROPERTIES) == 0xFFFF);\n"
      "\n"
   );
}

static void write_optional_case_field(FILE *const fp, ascii const *fieldName, codepoint const value)
{
   if (value != INVALID_CODEPOINT)
   {
      fprintf(fp, "      .%s = 0x%04X,\n", fieldName, value);
   }
   else
   {
      fprintf(fp, "      .%s = %s,\n", fieldName, TO_STRING(INVALID_CODEPOINT));
   }
}

static void write_codepoint(FILE *const fp, CodePointInfo const *const info)
{
   fprintf(fp, "   [0x%04X] = (CodePointProperties)\n   {\n", info->codeValue);
   fprintf(fp, "      .value = 0x%04X,\n", info->codeValue);
   if (info->codeName)
   {
      if (info->oldCodeName)
         fprintf(fp, "      .name = \"%s (%s)\",\n", info->codeName, info->oldCodeName);
      else
         fprintf(fp, "      .name = \"%s\",\n", info->codeName);
   }
   else
   {
      fprintf(fp, "      .name = nullptr,\n");
   }
   fprintf(fp, "      .category = %s,\n", codepoint_category_enum_name(info->category));

   write_optional_case_field(fp, "optLowercase", info->optAssociatedLowercase);
   write_optional_case_field(fp, "optTitlecase", info->optAssociatedTitlecase);
   write_optional_case_field(fp, "optUppercase", info->optAssociatedUppercase);
   fprintf(fp, "   },\n");
}

static void write_missing_codepoint(FILE *const fp, codepoint const value)
{
   CodePointInfo const missing = (CodePointInfo) {
      .codeValue = value,
      .codeName = nullptr,
      .oldCodeName = nullptr,
      .category = CodePointCategory_INVALID,
      .isMirrored = false,
      .optAssociatedLowercase = INVALID_CODEPOINT,
      .optAssociatedTitlecase = INVALID_CODEPOINT,
      .optAssociatedUppercase = INVALID_CODEPOINT
   };

   write_codepoint(fp, &missing);
}


int parse_codepoints(ascii const *const filepath)
{
   FILE *const fp = fopen(filepath, "r");
   if (fp == nullptr)
   {
      fprintf(stderr, "FATAL: Failure to open the file [%s]\n", filepath);
      return EXIT_FAILURE;
   }

   char const *const filepathDest = "./generated/codepoint_properties.c";
   FILE *const fpDest = fopen(filepathDest, "w");
   if (fpDest == nullptr)
   {
      fprintf(stderr, "FATAL: Failure to create the destination file [%s]\n", filepathDest);
      return EXIT_FAILURE;
   }

   write_header(fpDest);

   ssize_t readCount = 0;
   size_t lineLength = 0;
   char *line = nullptr;

   bool lastWasRangeFirst = false;
   codepoint rangeFirstCodePoint = INVALID_CODEPOINT;
   int32_t codepointIdx = 0;

   while ((readCount = getline(&line, &lineLength, fp)) != -1)
   {
      char *lineIt = line;

      lineIt[readCount - 1] = '\0'; // Remove '/n' at the end of the line.

      // Field 0: Code value.
      char *token = utils_strsep(&lineIt, ';');
      codepoint const codeValue = (int32_t)strtol(token, nullptr, 16); // Hexadecimal

      while (!lastWasRangeFirst && codepointIdx < codeValue)
      {
         write_missing_codepoint(fpDest, codepointIdx);
         codepointIdx += 1;
      }

      // We only want to support the first Unicode plane (Basic Multilingual Plane)
      // Range if from U+0000 to U+FFFF
      if (codeValue > 0xFFFF)
         break;

      CodePointInfo *const cp = &s_cpsInfo[codeValue];
      assert(cp->codeValue == codeValue);

      // Field  1: Character Name.
      token = utils_strsep(&lineIt, ';');
      utils_update_case(token);
      cp->codeName = token;

      // Field  2: General Category
      token = utils_strsep(&lineIt, ';');
      cp->category = codepoint_category_from_ascii(token);

      // Field  3: Canonical combining classes
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  4: Bidirectional category
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  5: Character decomposition mapping
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  6: Decimal digit value
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  7: Digit value
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  8: Numeric value
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field  9: Mirrored
      token = utils_strsep(&lineIt, ';');
      cp->isMirrored = strcmp(token, "Y") == 0 ? true : false;

      // Field 10: Unicode 1.0 Name
      token = utils_strsep(&lineIt, ';');
      // The oldname has some value for controls (that are all just <controls> now).
      // However, keeping it for the rest of the list would just be confusing.
      bool const isControl = (cp->category == CodePointCategory_OTHER_CONTROL);
      if (isControl && token && *token != '\0')
      {
         utils_update_case(token);
         if (strcmp(cp->codeName, token) != 0)
         {
            cp->oldCodeName = token;
         }
      }

      // Field 11: ISO 10646 comment field
      token = utils_strsep(&lineIt, ';');
      // SKIPPED (at least for now)

      // Field 12: Uppercase mapping (if exist: hex codepoint, else empty)
      token = utils_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         cp->optAssociatedUppercase = (int32_t)strtol(token, nullptr, 16);
      }

      // Field 13: Lowercase mapping (if exist : hex codepoint, else empty)
      token = utils_strsep(&lineIt, ';');
      if (token && *token != '\0')
      {
         cp->optAssociatedLowercase = (int32_t)strtol(token, nullptr, 16);
      }

      // Field 14: Titlecase mapping (if exist: hex codepoint, else empty)
      token = utils_strsep(&lineIt, ';');
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
            write_codepoint(fpDest, cpInRange);
            codepointIdx += 1;
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
         write_codepoint(fpDest, cp);
         codepointIdx += 1;
      }
   }

   write_footer(fpDest);

   fclose(fpDest);
   fclose(fp);
   return EXIT_SUCCESS;
}
