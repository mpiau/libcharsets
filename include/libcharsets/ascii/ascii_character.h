#pragma once

#include "libcharsets/charset_types.h"


//================================================================================================
// API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Validation functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] bool ascii_is_valid(byte);


//------------------------------------------------------------------------------------------------
// Identification functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] bool ascii_is_digit(ascii);     // Decimal
[[nodiscard]] bool ascii_is_digit_bin(ascii); // Binary
[[nodiscard]] bool ascii_is_digit_hex(ascii); // Hexadecimal
[[nodiscard]] bool ascii_is_digit_oct(ascii); // Octal

[[nodiscard]] bool ascii_is_lower(ascii);     // [a-z]
[[nodiscard]] bool ascii_is_lower_hex(ascii); // [a-f]

[[nodiscard]] bool ascii_is_upper(ascii);     // [A-Z]
[[nodiscard]] bool ascii_is_upper_hex(ascii); // [A-F]

[[nodiscard]] bool ascii_is_alpha(ascii);     // upper or lower
[[nodiscard]] bool ascii_is_alpha_hex(ascii); // [a-f] + [A-F]
[[nodiscard]] bool ascii_is_alphanum(ascii);  // alpha or digit

[[nodiscard]] bool ascii_is_decimal_point(ascii); // '.' or ','
[[nodiscard]] bool ascii_is_number_sign(ascii);   // '+' or '-'

[[nodiscard]] bool ascii_is_punctuation(ascii); // !"#$%&'()*+,\-./:;<=>?@\[\\\]^_`{|}~
[[nodiscard]] bool ascii_is_graphical(ascii);   // Punctuation or Alphanum
[[nodiscard]] bool ascii_is_printable(ascii);   // Graphical or space character
[[nodiscard]] bool ascii_is_blank(ascii);       // space or tab
[[nodiscard]] bool ascii_is_whitespace(ascii);  // Blank or \f\n\r\v.
[[nodiscard]] bool ascii_is_control(ascii);


//------------------------------------------------------------------------------------------------
// Comparison functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] CharsetCompare ascii_compare(ascii, ascii);
[[nodiscard]] CharsetCompare ascii_compare_insensitive(ascii, ascii);

[[nodiscard]] bool ascii_equals(ascii, ascii);
[[nodiscard]] bool ascii_equals_insensitive(ascii, ascii);


//------------------------------------------------------------------------------------------------
// Conversion functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] ascii ascii_to_lower(ascii);
[[nodiscard]] ascii ascii_to_upper(ascii);

[[nodiscard]] int ascii_to_digit(ascii);
[[nodiscard]] int ascii_to_digit_hex(ascii);
