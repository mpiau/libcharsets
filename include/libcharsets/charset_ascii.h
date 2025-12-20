#pragma once

#include <stddef.h>


//================================================================================================
// Type definitions
//================================================================================================

typedef char ascii;


//================================================================================================
// Constants
//================================================================================================

// TODO


//================================================================================================
// API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Single character functions
//------------------------------------------------------------------------------------------------

[[nodiscard]] bool ascii_is_valid(ascii c);

[[nodiscard]] bool ascii_is_digit(ascii c);     // Decimal
[[nodiscard]] bool ascii_is_digit_bin(ascii c); // Binary
[[nodiscard]] bool ascii_is_digit_hex(ascii c); // Hexadecimal
[[nodiscard]] bool ascii_is_digit_oct(ascii c); // Octal

[[nodiscard]] bool ascii_is_lower(ascii c);
[[nodiscard]] bool ascii_is_upper(ascii c);
[[nodiscard]] bool ascii_is_alpha(ascii c);
[[nodiscard]] bool ascii_is_alphanumeric(ascii c);
[[nodiscard]] bool ascii_is_punctuation(ascii c);  // !"#$%&'()*+,\-./:;<=>?@\[\\\]^_`{|}~
[[nodiscard]] bool ascii_is_graphical(ascii c);    // Punctuation or Alphanumeric
[[nodiscard]] bool ascii_is_printable(ascii c);    // Graphical or space character
[[nodiscard]] bool ascii_is_blank(ascii c);        // space or tab
[[nodiscard]] bool ascii_is_whitespace(ascii c);   // Blank or \f\n\r\v.
[[nodiscard]] bool ascii_is_control(ascii c);

[[nodiscard]] ascii ascii_to_lower(ascii c);
[[nodiscard]] ascii ascii_to_upper(ascii c);


//------------------------------------------------------------------------------------------------
// Character sequence functions
//------------------------------------------------------------------------------------------------

// Returns true if all characters are valid ASCII. False otherwise.
[[nodiscard]] __attribute__((nonnull (1)))
bool ascii_seq_is_valid(ascii const *seq);

// Returns the number of characters in the given sequence, excluding '\0'.
[[nodiscard]] __attribute__((nonnull (1)))
size_t ascii_seq_count(ascii const *seq);

// Returns the number of characters in the given sequence (up to max), excluding '\0'.
[[nodiscard]] __attribute__((nonnull (1)))
size_t ascii_seq_ncount(ascii const *seq, size_t max);
