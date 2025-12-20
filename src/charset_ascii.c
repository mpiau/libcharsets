#include "libcharsets/charset_ascii.h"


//================================================================================================
// Private Functions
//================================================================================================

[[nodiscard]] static inline
bool is_in_range(ascii const c, ascii const min, ascii const max)
{
   return !(c < min || c > max);
}


//================================================================================================
// Public API Functions
//================================================================================================

//------------------------------------------------------------------------------------------------
// Single character functions
//------------------------------------------------------------------------------------------------

bool ascii_is_valid(ascii const c)
{
   return !(c < 0);
}

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
   return ascii_is_digit(c) || is_in_range(c, 'A', 'F') || is_in_range(c, 'a', 'f');
}

bool ascii_is_digit_oct(ascii const c)
{
   return is_in_range(c, '0', '7');
}

bool ascii_is_lower(ascii const c)
{
   return is_in_range(c, 'a', 'z');
}

bool ascii_is_upper(ascii const c)
{
   return is_in_range(c, 'A', 'Z');
}

bool ascii_is_alpha(ascii const c)
{
   return ascii_is_lower(c) || ascii_is_upper(c);
}

bool ascii_is_alphanumeric(ascii const c)
{
   return ascii_is_alpha(c) || ascii_is_digit(c);
}

bool ascii_is_punctuation(ascii const c)
{
   return is_in_range(c, '!', '~') && !ascii_is_alphanumeric(c);
}

bool ascii_is_graphical(ascii const c)
{
   return ascii_is_alphanumeric(c) || ascii_is_punctuation(c);
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


ascii ascii_to_lower(ascii const c)
{
   return ascii_is_upper(c) ? (c + 32) : (c); // 32: 'a' - 'A' in ascii table.
}

ascii ascii_to_upper(ascii const c)
{
   return ascii_is_lower(c) ? (c - 32) : (c); // 32: 'a' - 'A' in ascii table.
}

//------------------------------------------------------------------------------------------------
// Character sequence functions
//------------------------------------------------------------------------------------------------

bool ascii_seq_is_valid(ascii const *seq)
{
   while (*seq != '\0')
   {
      if (!ascii_is_valid(*seq++))
      {
         return false;
      }
   }
   return true;
}

size_t ascii_seq_count(ascii const *seq)
{
   ascii const *const begin = seq;

   while (*seq != '\0')
   {
      seq += 1;
   }

   return seq - begin;
}

size_t ascii_seq_ncount(ascii const *seq, size_t const max)
{
   ascii const *const begin = seq;
   ascii const *const end   = begin + max;

   while (*seq != '\0' && seq < end)
   {
      seq += 1;
   }

   return seq - begin;
}


