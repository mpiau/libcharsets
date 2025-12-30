#include "macro_indexed_enum.h"
#define _POSIX_C_SOURCE 200809L // for strnlen

#include "codepoint_categories.h"
#include "codepoint_properties.h"

#include <assert.h>
#include <string.h> // strnlen


bool codepoint_category_is_letter(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_mark(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_number(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_separator(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_punctuation(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_symbol(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_other(codepoint const cp)
{
   return false; // TODO
}

bool codepoint_category_is_assigned(codepoint const cp)
{
   return false; // TODO
}


//================================================================================================
// Conversion API functions
//================================================================================================

struct CategoryInfo
{
   ascii const *name;
   ascii const *desc;
};
typedef struct CategoryInfo CategoryInfo;


static constexpr CategoryInfo S_CATEGORIES_INFO[] = 
{
#define CG_CAT_INFO(pEnumV, pName, pDesc) \
   [pEnumV] = (CategoryInfo) { .name = pName, .desc = pDesc }

   CG_CAT_INFO(CodePointCategory_INVALID, "Inv", "Invalid")

   , CG_CAT_INFO(CodePointCategory_LETTER_LOWERCASE, "Ll", "Letter (Lowercase)")
   , CG_CAT_INFO(CodePointCategory_LETTER_TITLECASE, "Lt", "Letter (Titlecase)")
   , CG_CAT_INFO(CodePointCategory_LETTER_UPPERCASE, "Lu", "Letter (Uppercase)")
   , CG_CAT_INFO(CodePointCategory_LETTER_MODIFIER,  "Lm", "Letter (Modifier)")
   , CG_CAT_INFO(CodePointCategory_LETTER_OTHER,     "Lo", "Letter (Other)")

   , CG_CAT_INFO(CodePointCategory_MARK_SPACING_COMBINING, "Mc", "Mark (Spacing combining)")
   , CG_CAT_INFO(CodePointCategory_MARK_ENCLOSING,         "Me", "Mark (Enclosing)")
   , CG_CAT_INFO(CodePointCategory_MARK_NON_SPACING,       "Mn", "Mark (Non spacing)")

   , CG_CAT_INFO(CodePointCategory_NUMBER_DECIMAL_DIGIT, "Nd", "Number (Decimal digit)")
   , CG_CAT_INFO(CodePointCategory_NUMBER_LETTER,        "Nl", "Number (Letter)")
   , CG_CAT_INFO(CodePointCategory_NUMBER_OTHER,         "No", "Number (Other)")

   , CG_CAT_INFO(CodePointCategory_SEPARATOR_LINE,      "Zl", "Separator (Line)")
   , CG_CAT_INFO(CodePointCategory_SEPARATOR_SPACE,     "Zs", "Separator (Space)")
   , CG_CAT_INFO(CodePointCategory_SEPARATOR_PARAGRAPH, "Zp", "Separator (Paragraph)")

   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_CONNECTOR,     "Pc", "Punctuation (Connector)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_DASH,          "Pd", "Punctuation (Dash)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_OPEN,          "Ps", "Punctuation (Open)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_CLOSE,         "Pe", "Punctuation (Close)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_INITIAL_QUOTE, "Pi", "Punctuation (Initial Quote)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_FINAL_QUOTE,   "Pf", "Punctuation (Final Quote)")
   , CG_CAT_INFO(CodePointCategory_PUNCTUATION_OTHER,         "Po", "Punctuation (Other)")

   , CG_CAT_INFO(CodePointCategory_SYMBOL_MATH,     "Sm", "Symbol (Math)")
   , CG_CAT_INFO(CodePointCategory_SYMBOL_CURRENCY, "Sc", "Symbol (Currency)")
   , CG_CAT_INFO(CodePointCategory_SYMBOL_MODIFIER, "Sk", "Symbol (Modifier)")
   , CG_CAT_INFO(CodePointCategory_SYMBOL_OTHER,    "So", "Symbol (Other)")

   , CG_CAT_INFO(CodePointCategory_OTHER_CONTROL,      "Cc", "Other (Control)")
   , CG_CAT_INFO(CodePointCategory_OTHER_FORMAT,       "Cf", "Other (Format)")
   , CG_CAT_INFO(CodePointCategory_OTHER_NOT_ASSIGNED, "Cn", "Other (Not assigned)")
   , CG_CAT_INFO(CodePointCategory_OTHER_PRIVATE_USE,  "Co", "Other (Private use)")
   , CG_CAT_INFO(CodePointCategory_OTHER_SURROGATE,    "Cs", "Other (Surrogate)")

#undef CG_CAT_INFO
};

#define sizeofA(array) (sizeof(array) / sizeof(*array))

static_assert( sizeofA(S_CATEGORIES_INFO) == CodePointCategory_Count);


CodePointCategory codepoint_category_from_ascii(ascii const *const str)
{
   if (str == nullptr)
      return CodePointCategory_INVALID;

   if (strnlen(str, 3) != 2) // Category is always 2 ascii characters.
      return CodePointCategory_INVALID;

   foreach_enum_indexed(category, CodePointCategory)
   {
      if (strcmp(codepoint_category_name(category), str) == 0)
      {
         return category;
      }
   }

   return CodePointCategory_INVALID;
}

ascii const * codepoint_category_name(CodePointCategory const category)
{
   return enum_indexed_in_range(category, CodePointCategory)
      ? S_CATEGORIES_INFO[category].name
      : S_CATEGORIES_INFO[CodePointCategory_INVALID].name;
}

ascii const * codepoint_category_desc(CodePointCategory const category)
{
   return enum_indexed_in_range(category, CodePointCategory)
      ? S_CATEGORIES_INFO[category].desc
      : S_CATEGORIES_INFO[CodePointCategory_INVALID].desc;
}
