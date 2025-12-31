#pragma once

#include "core.h"


enum CodePointCategory
{
   // Mainly used for error handling.
   CodePointCategory_INVALID

   // Letters
   // -------
   , CodePointCategory_LETTER_LOWERCASE // Ll
   , CodePointCategory_LETTER_TITLECASE // Lt
   , CodePointCategory_LETTER_UPPERCASE // Lu
   , CodePointCategory_LETTER_MODIFIER  // Lm
   , CodePointCategory_LETTER_OTHER     // Lo

   // Marks
   // -----
   , CodePointCategory_MARK_SPACING_COMBINING // Mc
   , CodePointCategory_MARK_ENCLOSING         // Me
   , CodePointCategory_MARK_NON_SPACING       // Mn

   // Numbers
   // -------
   , CodePointCategory_NUMBER_DECIMAL_DIGIT // Nd
   , CodePointCategory_NUMBER_LETTER        // Nl
   , CodePointCategory_NUMBER_OTHER         // No

   // Separators
   // ----------
   , CodePointCategory_SEPARATOR_LINE      // Zl
   , CodePointCategory_SEPARATOR_SPACE     // Zs
   , CodePointCategory_SEPARATOR_PARAGRAPH // Zp

   // Punctuations
   // ------------
   , CodePointCategory_PUNCTUATION_CONNECTOR     // Pc
   , CodePointCategory_PUNCTUATION_DASH          // Pd
   , CodePointCategory_PUNCTUATION_OPEN          // Ps
   , CodePointCategory_PUNCTUATION_CLOSE         // Pe
   , CodePointCategory_PUNCTUATION_INITIAL_QUOTE // Pi
   , CodePointCategory_PUNCTUATION_FINAL_QUOTE   // Pf
   , CodePointCategory_PUNCTUATION_OTHER         // Po

   // Symbols
   // -------
   , CodePointCategory_SYMBOL_MATH     // Sm
   , CodePointCategory_SYMBOL_CURRENCY // Sc
   , CodePointCategory_SYMBOL_MODIFIER // Sk
   , CodePointCategory_SYMBOL_OTHER    // So

   // Others
   // ------
   , CodePointCategory_OTHER_CONTROL      // Cc
   , CodePointCategory_OTHER_FORMAT       // Cf
   , CodePointCategory_OTHER_NOT_ASSIGNED // Cn
   , CodePointCategory_OTHER_PRIVATE_USE  // Co
   , CodePointCategory_OTHER_SURROGATE    // Cs


   // ===============================================================================================
   // Enum util values
   // ===============================================================================================

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory,
      CodePointCategory_INVALID,
      CodePointCategory_OTHER_SURROGATE
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Letter,
      CodePointCategory_LETTER_LOWERCASE,
      CodePointCategory_LETTER_OTHER
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Mark,
      CodePointCategory_MARK_SPACING_COMBINING,
      CodePointCategory_MARK_NON_SPACING
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Number,
      CodePointCategory_NUMBER_DECIMAL_DIGIT,
      CodePointCategory_NUMBER_OTHER
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Separator,
      CodePointCategory_SEPARATOR_LINE,
      CodePointCategory_SEPARATOR_PARAGRAPH
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Punctuation,
      CodePointCategory_PUNCTUATION_CONNECTOR,
      CodePointCategory_PUNCTUATION_DASH
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Symbol,
      CodePointCategory_SYMBOL_MATH,
      CodePointCategory_SYMBOL_OTHER
   )

   CG_ENUM_INDEXED_MEMBERS( CodePointCategory_Other,
      CodePointCategory_OTHER_CONTROL,
      CodePointCategory_OTHER_SURROGATE
   )
};
typedef enum CodePointCategory CodePointCategory;


//================================================================================================
// Identification API functions
//================================================================================================

[[nodiscard]] bool codepoint_category_is_letter(codepoint cp);
[[nodiscard]] bool codepoint_category_is_mark(codepoint cp);
[[nodiscard]] bool codepoint_category_is_number(codepoint cp);
[[nodiscard]] bool codepoint_category_is_separator(codepoint cp);
[[nodiscard]] bool codepoint_category_is_punctuation(codepoint cp);
[[nodiscard]] bool codepoint_category_is_symbol(codepoint cp);
[[nodiscard]] bool codepoint_category_is_other(codepoint cp);

[[nodiscard]] bool codepoint_category_is_assigned(codepoint cp);


//================================================================================================
// Conversion API functions
//================================================================================================

// ASCII param must match the category name, not its description.
[[nodiscard]] CodePointCategory codepoint_category_from_ascii(ascii const *str);

// Example: "Ll" for CodePointCategory_LETTER_LOWERCASE
[[nodiscard]] ascii const * codepoint_category_name(CodePointCategory category);

// Example: "Letter (lowercase)" for CodePointCategory_LETTER_LOWERCASE
[[nodiscard]] ascii const * codepoint_category_desc(CodePointCategory category);

// Useful for code generation.
// Example: "CodePointCategory_LETTER_LOWERCASE" for CodePointCategory_LETTER_LOWERCASE
[[nodiscard]] ascii const * codepoint_category_enum_name(CodePointCategory category);
