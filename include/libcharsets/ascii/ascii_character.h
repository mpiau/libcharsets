#pragma once

#include "libcharsets/ascii/ascii_types.h"
#include "libcharsets/common/charset_common.h"


//================================================================================================
// API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Validation functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] CharsetValidity ascii_validate(ascii c);
[[nodiscard]] bool            ascii_is_valid(ascii c);


//------------------------------------------------------------------------------------------------
// Identification functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] bool ascii_is_digit(ascii c);     // Decimal
[[nodiscard]] bool ascii_is_digit_bin(ascii c); // Binary
[[nodiscard]] bool ascii_is_digit_hex(ascii c); // Hexadecimal
[[nodiscard]] bool ascii_is_digit_oct(ascii c); // Octal

[[nodiscard]] bool ascii_is_lower(ascii c);     // [a-z]
[[nodiscard]] bool ascii_is_lower_hex(ascii c); // [a-f]

[[nodiscard]] bool ascii_is_upper(ascii c);     // [A-Z]
[[nodiscard]] bool ascii_is_upper_hex(ascii c); // [A-F]

[[nodiscard]] bool ascii_is_alpha(ascii c);        // upper or lower
[[nodiscard]] bool ascii_is_alpha_hex(ascii c);    // [a-f] + [A-F]
[[nodiscard]] bool ascii_is_alphanumeric(ascii c); // alpha or digit

[[nodiscard]] bool ascii_is_decimal_point(ascii c); // '.' or ','
[[nodiscard]] bool ascii_is_number_sign(ascii c);   // '+' or '-'

[[nodiscard]] bool ascii_is_punctuation(ascii c);  // !"#$%&'()*+,\-./:;<=>?@\[\\\]^_`{|}~
[[nodiscard]] bool ascii_is_graphical(ascii c);    // Punctuation or Alphanumeric
[[nodiscard]] bool ascii_is_printable(ascii c);    // Graphical or space character
[[nodiscard]] bool ascii_is_blank(ascii c);        // space or tab
[[nodiscard]] bool ascii_is_whitespace(ascii c);   // Blank or \f\n\r\v.
[[nodiscard]] bool ascii_is_control(ascii c);


//------------------------------------------------------------------------------------------------
// Comparison functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] charsetCompare ascii_compare(ascii lhs, ascii rhs);
[[nodiscard]] charsetCompare ascii_compare_insensitive(ascii lhs, ascii rhs);

[[nodiscard]] bool ascii_equals(ascii lhs, ascii rhs);
[[nodiscard]] bool ascii_equals_insensitive(ascii lhs, ascii rhs);


//------------------------------------------------------------------------------------------------
// Size related functions
//------------------------------------------------------------------------------------------------

// Returns the number of bytes taken by an ascii character (aka 1 if valid, 0 otherwise).
// This function is mainly there to allow the usage of the generic charset_bytesize([...])
[[nodiscard]] size_t ascii_bytesize(ascii c);


//------------------------------------------------------------------------------------------------
// Conversion functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] ascii ascii_to_lower(ascii c);
[[nodiscard]] ascii ascii_to_upper(ascii c);

// Assumes that is_digit() returns true.
[[nodiscard]] int ascii_to_digit(ascii c);

// Assumes that is_digit_hex() returns true.
// Similar to to_digit but also takes into account [a-f][A-F] hexadecimal values.
[[nodiscard]] int ascii_to_digit_hex(ascii c);


//------------------------------------------------------------------------------------------------
// Descriptive functions
//------------------------------------------------------------------------------------------------

// Returns a short name of the given character (like "~" or "A")
// Returns "INV" if ascii invalid.
[[nodiscard]] ascii const *ascii_name(ascii c);

// Returns a descriptive name of the given character (like "Tilde" or "Uppercase Latin A")
// Returns "Invalid" if ascii invalid.
[[nodiscard]] ascii const *ascii_desc(ascii c);


//------------------------------------------------------------------------------------------------
// Display functions
//------------------------------------------------------------------------------------------------

// Write a character in the standard output. (fd = 1)
[[nodiscard]] size_t ascii_print(ascii c);

// Write a character in the error output. (fd = 2)
[[nodiscard]] size_t ascii_printerr(ascii c);

// Write a character in the specified output.
[[nodiscard]] size_t ascii_print_fd(int fd, ascii c);
