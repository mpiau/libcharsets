#include "libcharsets/charset_ascii.h"

#include <limits.h>


//================================================================================================
// Type definitions
//================================================================================================

typedef bool(*characterCb)(ascii const c);


//================================================================================================
// Private Functions
//================================================================================================

[[nodiscard]] static inline
bool is_in_range(ascii const c, ascii const min, ascii const max)
{
   return !(c < min || c > max);
}

[[nodiscard]] static inline
bool foreach_character_in_seq(ascii const *seq, characterCb const cb)
{
   while (*seq != '\0')
   {
      if (!cb(*seq))
      {
         return false;
      }
      seq += 1;
   }

   return true;
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
   return ascii_is_digit(c) || ascii_is_upper_hex(c) || ascii_is_lower_hex(c);
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

bool ascii_is_decimal_sign(ascii const c)
{
   return c == '.' || c == ',';
}

bool ascii_is_number_sign(ascii const c)
{
   return c == '-' || c == '+';
}


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


AsciiComp ascii_compare(ascii const leftC, ascii const rightC)
{
   switch (leftC - rightC)
   {
      case SCHAR_MIN ... -1: return AsciiComp_LESSER_THAN;  // left <  right
      case 0:                return AsciiComp_EQUAL;        // left == right
      case +1 ... SCHAR_MAX: return AsciiComp_GREATER_THAN; // left >  right 

      default: unreachable();
   }
}

AsciiComp ascii_compare_insensitive(ascii leftC, ascii rightC)
{
   return ascii_compare(ascii_to_lower(leftC), ascii_to_lower(rightC));
}


bool ascii_equals(ascii const leftC, ascii const rightC)
{
   return ascii_compare(leftC, rightC) == AsciiComp_EQUAL;
}

bool ascii_equals_insensitive(ascii const leftC, ascii const rightC)
{
   return ascii_compare_insensitive(leftC, rightC) == AsciiComp_EQUAL;
}


//------------------------------------------------------------------------------------------------
// Character sequence functions
//------------------------------------------------------------------------------------------------

bool ascii_seq_is_valid(ascii const *seq)
{
   return foreach_character_in_seq(seq, ascii_is_valid);
}

bool ascii_seq_is_number(ascii const *seq)
{
   bool const sign = ascii_is_number_sign(*seq);
   return *(seq + sign) && foreach_character_in_seq(seq + sign, ascii_is_digit);
}

bool ascii_seq_is_number_bin(ascii const *seq)
{
   return *seq && foreach_character_in_seq(seq, ascii_is_digit_bin);
}

bool ascii_seq_is_number_hex(ascii const *seq)
{
   return *seq && foreach_character_in_seq(seq, ascii_is_digit_hex);
}

bool ascii_seq_is_number_oct(ascii const *seq)
{
   return *seq && foreach_character_in_seq(seq, ascii_is_digit_oct);
}

bool ascii_seq_is_number_float(ascii const *const seq)
{
   bool const sign = ascii_is_number_sign(*seq);
   ascii const *it = (seq + sign);
   ascii const *decimalIt = nullptr;

   if (*it == '\0')
   {
      return false; // "" or "-" isn't a valid floating point number.
   }

   while (*it != '\0')
   {
      if (ascii_is_digit(*it))
      {
         it += 1;
      }
      else if (ascii_is_decimal_sign(*it) && decimalIt == nullptr && it != (seq + sign))
      {
         // Ensures that we only encounter one dot in the whole number
         // and that the dot isn't the first character
         decimalIt = it++;
      }
      else
      {
         return false;
      }
   }

   // Ensures that the potential decimal sign isn't the last character of the string.
   return (decimalIt == nullptr) || (decimalIt + 1 != it);
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


