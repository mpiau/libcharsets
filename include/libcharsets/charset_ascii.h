#pragma once

#include <stddef.h>


//================================================================================================
// Type definitions
//================================================================================================

typedef char ascii;

enum AsciiComp : int
{
     AsciiComp_LESS_THAN    = -1
   , AsciiComp_EQUAL        =  0
   , AsciiComp_GREATER_THAN =  1
};
typedef enum AsciiComp AsciiComp;


//================================================================================================
// API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Single character validation functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] bool ascii_is_valid(ascii c);

[[nodiscard]] bool ascii_is_digit(ascii c);     // Decimal
[[nodiscard]] bool ascii_is_digit_bin(ascii c); // Binary
[[nodiscard]] bool ascii_is_digit_hex(ascii c); // Hexadecimal
[[nodiscard]] bool ascii_is_digit_oct(ascii c); // Octal

[[nodiscard]] bool ascii_is_lower(ascii c);
[[nodiscard]] bool ascii_is_lower_hex(ascii c); // [a-f]
[[nodiscard]] bool ascii_is_upper(ascii c);
[[nodiscard]] bool ascii_is_upper_hex(ascii c); // [A-F]
[[nodiscard]] bool ascii_is_alpha(ascii c);
[[nodiscard]] bool ascii_is_alpha_hex(ascii c); // [a-f] + [A-F]
[[nodiscard]] bool ascii_is_alphanumeric(ascii c);
[[nodiscard]] bool ascii_is_punctuation(ascii c);  // !"#$%&'()*+,\-./:;<=>?@\[\\\]^_`{|}~
[[nodiscard]] bool ascii_is_graphical(ascii c);    // Punctuation or Alphanumeric
[[nodiscard]] bool ascii_is_printable(ascii c);    // Graphical or space character
[[nodiscard]] bool ascii_is_blank(ascii c);        // space or tab
[[nodiscard]] bool ascii_is_whitespace(ascii c);   // Blank or \f\n\r\v.
[[nodiscard]] bool ascii_is_control(ascii c);
[[nodiscard]] bool ascii_is_decimal_point(ascii c); // '.' or ','
[[nodiscard]] bool ascii_is_number_sign(ascii c);   // '+' or '-'


//------------------------------------------------------------------------------------------------
// Single character conversion functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] ascii ascii_to_lower(ascii c);
[[nodiscard]] ascii ascii_to_upper(ascii c);

// Assumes that is_digit() returns true.
[[nodiscard]] int ascii_to_digit(ascii c);
// Assumes that is_digit_hex() returns true.
// Similar to to_digit but also takes into account [a-f][A-F] hexadecimal values.
[[nodiscard]] int ascii_to_digit_hex(ascii c);


//------------------------------------------------------------------------------------------------
// Single character comparison functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] AsciiComp ascii_compare(ascii leftC, ascii rightC);
[[nodiscard]] AsciiComp ascii_compare_insensitive(ascii leftC, ascii rightC);

[[nodiscard]] bool ascii_equals(ascii leftC, ascii rightC);
[[nodiscard]] bool ascii_equals_insensitive(ascii leftC, ascii rightC);


//------------------------------------------------------------------------------------------------
// Single character size functions
//------------------------------------------------------------------------------------------------

// Returns the number of bytes taken by an ascii character (aka 1 if valid, 0 otherwise).
// This function is useful to allow the usage of the generic charset_bytesize([...])
[[nodiscard]] size_t ascii_bytesize(ascii c);


//------------------------------------------------------------------------------------------------
// Single character name functions
//------------------------------------------------------------------------------------------------

// Returns a short name of the given character (like "~" or "A")
// Returns "INV" if ascii invalid.
[[nodiscard]] ascii const *ascii_name(ascii c);

// Returns a descriptive name of the given character (like "Tilde" or "Uppercase Latin A")
// Returns "Invalid" if ascii invalid.
[[nodiscard]] ascii const *ascii_desc(ascii c);


//------------------------------------------------------------------------------------------------
// Character sequence validation functions
//------------------------------------------------------------------------------------------------

// Returns true if all characters are valid ASCII. False otherwise.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_valid(ascii const *seq);

// Accounts for the optional sign
// Returns true only if the whole sequence is a valid number.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_number(ascii const *seq);

// Returns true only if the whole sequence is a valid number.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_number_bin(ascii const *seq);

// Returns true only if the whole sequence is a valid number.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_number_hex(ascii const *seq);

// Returns true only if the whole sequence is a valid number.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_number_oct(ascii const *seq);

// Accounts for the optional sign and a decimal point somewhere
// Returns true only if the whole sequence is a valid number.
// Note: "5." isn't considered valid. "5.0" is.
// Note: ",5" isn't considered valid. "0,5" is.
[[nodiscard]] __attribute__((nonnull(1)))
bool ascii_seq_is_number_float(ascii const *seq);


//------------------------------------------------------------------------------------------------
// Character sequence comparison functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] __attribute__((nonnull(1, 2)))
AsciiComp ascii_seq_compare(ascii const *lSeq, ascii const *rSeq);
[[nodiscard]] __attribute__((nonnull(1, 2)))
AsciiComp ascii_seq_compare_insensitive(ascii const *lSeq, ascii const *rSeq);

[[nodiscard]] __attribute__((nonnull(1, 2)))
bool ascii_seq_equals(ascii const *lSeq, ascii const *rSeq);
[[nodiscard]] __attribute__((nonnull(1, 2)))
bool ascii_seq_equals_insensitive(ascii const *lSeq, ascii const *rSeq);


//------------------------------------------------------------------------------------------------
// Character sequence size functions
//------------------------------------------------------------------------------------------------

// Returns the number of characters in the given sequence, excluding '\0'.
[[nodiscard]] __attribute__((nonnull(1)))
size_t ascii_seq_count(ascii const *seq);

// Returns the number of characters in the given sequence (up to max), excluding '\0'.
[[nodiscard]] __attribute__((nonnull(1)))
size_t ascii_seq_ncount(ascii const *seq, size_t max);

// Returns the number of bytes used in the given sequence, excluding '\0'.
[[nodiscard]] __attribute__((nonnull(1)))
size_t ascii_seq_bytesize(ascii const *seq);


//------------------------------------------------------------------------------------------------
// Character sequence search functions
//------------------------------------------------------------------------------------------------

