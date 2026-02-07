#include "libcharsets/ascii/ascii_character.h"


//================================================================================================
// Internal Functions
//================================================================================================

static inline bool is_in_range(byte const c, byte const min, byte const max)
{
   return !(c < min || c > max);
}


//================================================================================================
// API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Validation functions
//------------------------------------------------------------------------------------------------

bool ascii_is_valid(byte const b)
{
   return is_in_range(b, 0x00, 0x7F);
}


//------------------------------------------------------------------------------------------------
// Identification functions
//------------------------------------------------------------------------------------------------

bool ascii_is_digit(ascii const c)
{
   return is_in_range(c, '0', '9');
}

bool ascii_is_digit_bin(ascii const c)
{
   return is_in_range(c, '0', '1');
}

bool ascii_is_digit_hex(ascii const c)
{
   return ascii_is_digit(c) || ascii_is_alpha_hex(c);
}

bool ascii_is_digit_oct(ascii const c)
{
   return is_in_range(c, '0', '7');
}

bool ascii_is_lower(ascii const c)
{
   return is_in_range(c, 'a', 'z');
}

bool ascii_is_lower_hex(ascii const c)
{
   return is_in_range(c, 'a', 'f');
}

bool ascii_is_upper(ascii const c)
{
   return is_in_range(c, 'A', 'Z');
}

bool ascii_is_upper_hex(ascii const c)
{
   return is_in_range(c, 'A', 'F');
}

bool ascii_is_alpha(ascii const c)
{
   return ascii_is_lower(c) || ascii_is_upper(c);
}

bool ascii_is_alpha_hex(ascii const c)
{
   return ascii_is_lower_hex(c) || ascii_is_upper_hex(c);
}

bool ascii_is_alphanum(ascii const c)
{
   return ascii_is_alpha(c) || ascii_is_digit(c);
}

bool ascii_is_decimal_point(ascii const c)
{
   return c == '.' || c == ',';
}

bool ascii_is_number_sign(ascii const c)
{
   return c == '-' || c == '+';
}

bool ascii_is_punctuation(ascii const c)
{
   return is_in_range(c, '!', '~') && !ascii_is_alphanum(c);
}

bool ascii_is_graphical(ascii const c)
{
   return ascii_is_alphanum(c) || ascii_is_punctuation(c);
}

bool ascii_is_printable(ascii const c)
{
   return ascii_is_graphical(c) || c == ' ';
}

bool ascii_is_blank(ascii const c)
{
   return c == ' ' || c == '\t';
}

bool ascii_is_whitespace(ascii const c)
{
   return ascii_is_blank(c) || is_in_range(c, '\n', '\r'); // \t' ' + \n\v\f\r
}

bool ascii_is_control(ascii const c)
{
   return is_in_range(c, '\0', '\x1F') || c == '\x7F'; // DEL
}


//------------------------------------------------------------------------------------------------
// Comparison functions
//------------------------------------------------------------------------------------------------

CharsetCompare ascii_compare(ascii const lhs, ascii const rhs)
{
   int const result = lhs - rhs;
   if (result < 0) return CharsetCompare_LESS_THAN;
   if (result > 0) return CharsetCompare_GREATER_THAN;
   else            return CharsetCompare_EQUAL;
}

CharsetCompare ascii_compare_insensitive(ascii const lhs, ascii const rhs)
{
   return ascii_compare(ascii_to_lower(lhs), ascii_to_lower(rhs));
}

bool ascii_equals(ascii const lhs, ascii const rhs)
{
   return ascii_compare(lhs, rhs) == CharsetCompare_EQUAL;
}

bool ascii_equals_insensitive(ascii const lhs, ascii const rhs)
{
   return ascii_compare_insensitive(lhs, rhs) == CharsetCompare_EQUAL;
}


//------------------------------------------------------------------------------------------------
// Conversion functions
//------------------------------------------------------------------------------------------------

ascii ascii_to_lower(ascii const c)
{
   return ascii_is_upper(c) ? (c + 32) : (c); // 32: 'a' - 'A' in ascii table.
}

ascii ascii_to_upper(ascii const c)
{
   return ascii_is_lower(c) ? (c - 32) : (c); // 32: 'a' - 'A' in ascii table.
}

int ascii_to_digit(ascii const c)
{
   return (int)(c - '0');
}

int ascii_to_digit_hex(ascii const c)
{
   if      (ascii_is_lower_hex(c)) return (int)(c - 'a' + 10);
   else if (ascii_is_upper_hex(c)) return (int)(c - 'A' + 10);
   else                            return ascii_to_digit(c);
}
