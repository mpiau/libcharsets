#include "libcharsets/charset_ascii.h"

//================================================================================================
// Type definitions
//================================================================================================

typedef bool(*characterCb)(ascii const c);


//================================================================================================
// Constants
//================================================================================================

//================================================================================================
// Private Functions
//================================================================================================

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

   while (*it != '\0')
   {
      if (ascii_is_digit(*it))
      {
         it += 1;
      }
      else if (ascii_is_decimal_point(*it) && decimalIt == nullptr && it != (seq + sign))
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

   // "" or "-" isn't a valid floating point number.
   // Ensures that the potential decimal sign isn't the last character of the string.
   bool const notEmpty = (it != seq + sign);
   bool const decimalNotLast = ((decimalIt == nullptr) || (decimalIt + 1 != it));
   return notEmpty && decimalNotLast;
}


AsciiComp ascii_seq_compare(ascii const *lSeq, ascii const *rSeq)
{
   while (*lSeq != '\0' && *rSeq != '\0')
   {
      if (*lSeq != *rSeq)
      {
         return ascii_compare(*lSeq, *rSeq);
      }
      lSeq += 1;
      rSeq += 1;
   }

   return ascii_compare(*lSeq, *rSeq);
}

AsciiComp ascii_seq_compare_insensitive(ascii const *lSeq, ascii const *rSeq)
{
   while (*lSeq != '\0' && *rSeq != '\0')
   {
      if (*lSeq != *rSeq)
      {
         return ascii_compare_insensitive(*lSeq, *rSeq);
      }
      lSeq += 1;
      rSeq += 1;
   }

   return ascii_compare_insensitive(*lSeq, *rSeq);
}

bool ascii_seq_equals(ascii const *lSeq, ascii const *rSeq)
{
   return ascii_seq_compare(lSeq, rSeq) == AsciiComp_EQUAL;
}

bool ascii_seq_equals_insensitive(ascii const *lSeq, ascii const *rSeq)
{
   return ascii_seq_compare_insensitive(lSeq, rSeq) == AsciiComp_EQUAL;
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

size_t ascii_seq_bytesize(ascii const *seq)
{
   return ascii_seq_count(seq); // in Ascii, 1 byte == 1 character.
}
