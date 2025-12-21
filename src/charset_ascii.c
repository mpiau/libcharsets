#include "libcharsets/charset_ascii.h"

#include <limits.h>


//================================================================================================
// Type definitions
//================================================================================================

struct AsciiName
{
   ascii const *const name;
   ascii const *const desc;
};
typedef struct AsciiName AsciiName;


//================================================================================================
// Constants
//================================================================================================

static constexpr AsciiName S_CHARACTERS[] =
{
   ['\0'] = (AsciiName){ .name = "NUL", .desc = "Null Terminator" },
   [0x01] = (AsciiName){ .name = "SOH", .desc = "Start of Heading" },
   [0x02] = (AsciiName){ .name = "STX", .desc = "Start of Text" },
   [0x03] = (AsciiName){ .name = "ETX", .desc = "End of Text" },
   [0x04] = (AsciiName){ .name = "EOT", .desc = "End of Transmission" },
   [0x05] = (AsciiName){ .name = "ENQ", .desc = "Enquiry" },
   [0x06] = (AsciiName){ .name = "ACK", .desc = "Acknowledge" },
   ['\a'] = (AsciiName){ .name = "BEL", .desc = "Bell" },
   ['\b'] = (AsciiName){ .name = "BS",  .desc = "Backspace" },
   ['\t'] = (AsciiName){ .name = "HT",  .desc = "Horizontal Tab" },
   ['\n'] = (AsciiName){ .name = "LF",  .desc = "New Line" },
   ['\v'] = (AsciiName){ .name = "VT",  .desc = "Vertical Tab" },
   ['\f'] = (AsciiName){ .name = "FF",  .desc = "Form Feed" },
   ['\r'] = (AsciiName){ .name = "CR",  .desc = "Carriage Net" },
   [0x0E] = (AsciiName){ .name = "SO",  .desc = "Shift Out/x-on" },
   [0x0F] = (AsciiName){ .name = "SI",  .desc = "Shift In/x-off" },
   [0x10] = (AsciiName){ .name = "DLE", .desc = "Data Link Escape" },
   [0x11] = (AsciiName){ .name = "DC1", .desc = "Device Control 1" },
   [0x12] = (AsciiName){ .name = "DC2", .desc = "Device Control 2" },
   [0x13] = (AsciiName){ .name = "DC3", .desc = "Device Control 3" },
   [0x14] = (AsciiName){ .name = "DC4", .desc = "Device Control 4" },
   [0x15] = (AsciiName){ .name = "NAK", .desc = "Negative acknowledgement" },
   [0x16] = (AsciiName){ .name = "SYN", .desc = "Synchronous idle" },
   [0x17] = (AsciiName){ .name = "ETB", .desc = "End of Transmission Block" },
   [0x18] = (AsciiName){ .name = "CAN", .desc = "Cancel" },
   [0x19] = (AsciiName){ .name = "EM",  .desc = "End of Medium" },
   [0x1A] = (AsciiName){ .name = "SUB", .desc = "Substitute" },
   [0x1B] = (AsciiName){ .name = "ESC", .desc = "Escape" },
   [0x1C] = (AsciiName){ .name = "FS",  .desc = "File Separator" },
   [0x1D] = (AsciiName){ .name = "GS",  .desc = "Group Separator" },
   [0x1E] = (AsciiName){ .name = "RS",  .desc = "Record Separator" },
   [0x1F] = (AsciiName){ .name = "US",  .desc = "Unit Separator" },
   [ ' '] = (AsciiName){ .name = " ",   .desc = "Space" },
   [ '!'] = (AsciiName){ .name = "!",   .desc = "Exclamation Mark" },
   [ '"'] = (AsciiName){ .name = "\"",  .desc = "Double quotes" },
   [ '#'] = (AsciiName){ .name = "#",   .desc = "Number (Hashtag)" },
   [ '$'] = (AsciiName){ .name = "$",   .desc = "Dollar" },
   [ '%'] = (AsciiName){ .name = "%",   .desc = "Percent" },
   [ '&'] = (AsciiName){ .name = "&",   .desc = "Ampersand" },
   ['\''] = (AsciiName){ .name = "'",   .desc = "Single quote" },
   [ '('] = (AsciiName){ .name = "(",   .desc = "Opening parenthesis" },
   [ ')'] = (AsciiName){ .name = ")",   .desc = "Closing parenthesis" },
   [ '*'] = (AsciiName){ .name = "*",   .desc = "Asterisk/Multiply" },
   [ '+'] = (AsciiName){ .name = "+",   .desc = "Plus" },
   [ ','] = (AsciiName){ .name = ",",   .desc = "Comma" },
   [ '-'] = (AsciiName){ .name = "-",   .desc = "Hyphen/Minus" },
   [ '.'] = (AsciiName){ .name = ".",   .desc = "Period/Dot" },
   [ '/'] = (AsciiName){ .name = "/",   .desc = "Slash/Divide" },
   [ '0'] = (AsciiName){ .name = "0",   .desc = "Zero" },
   [ '1'] = (AsciiName){ .name = "1",   .desc = "One" },
   [ '2'] = (AsciiName){ .name = "2",   .desc = "Two" },
   [ '3'] = (AsciiName){ .name = "3",   .desc = "Three" },
   [ '4'] = (AsciiName){ .name = "4",   .desc = "Four" },
   [ '5'] = (AsciiName){ .name = "5",   .desc = "Five" },
   [ '6'] = (AsciiName){ .name = "6",   .desc = "Six" },
   [ '7'] = (AsciiName){ .name = "7",   .desc = "Seven" },
   [ '8'] = (AsciiName){ .name = "8",   .desc = "Eight" },
   [ '9'] = (AsciiName){ .name = "9",   .desc = "Nine" },
   [ ':'] = (AsciiName){ .name = ":",   .desc = "Colon" },
   [ ';'] = (AsciiName){ .name = ";",   .desc = "Semicolon" },
   [ '<'] = (AsciiName){ .name = "<",   .desc = "Less Than" },
   [ '='] = (AsciiName){ .name = "=",   .desc = "Equals" },
   [ '>'] = (AsciiName){ .name = ">",   .desc = "Greater Than" },
   [ '?'] = (AsciiName){ .name = "?",   .desc = "Question Mark" },
   [ '@'] = (AsciiName){ .name = "@",   .desc = "At symbol" },
   [ 'A'] = (AsciiName){ .name = "A",   .desc = "Latin Uppercase A" },
   [ 'B'] = (AsciiName){ .name = "B",   .desc = "Latin Uppercase B" },
   [ 'C'] = (AsciiName){ .name = "C",   .desc = "Latin Uppercase C" },
   [ 'D'] = (AsciiName){ .name = "D",   .desc = "Latin Uppercase D" },
   [ 'E'] = (AsciiName){ .name = "E",   .desc = "Latin Uppercase E" },
   [ 'F'] = (AsciiName){ .name = "F",   .desc = "Latin Uppercase F" },
   [ 'G'] = (AsciiName){ .name = "G",   .desc = "Latin Uppercase G" },
   [ 'H'] = (AsciiName){ .name = "H",   .desc = "Latin Uppercase H" },
   [ 'I'] = (AsciiName){ .name = "I",   .desc = "Latin Uppercase I" },
   [ 'J'] = (AsciiName){ .name = "J",   .desc = "Latin Uppercase J" },
   [ 'K'] = (AsciiName){ .name = "K",   .desc = "Latin Uppercase K" },
   [ 'L'] = (AsciiName){ .name = "L",   .desc = "Latin Uppercase L" },
   [ 'M'] = (AsciiName){ .name = "M",   .desc = "Latin Uppercase M" },
   [ 'N'] = (AsciiName){ .name = "N",   .desc = "Latin Uppercase N" },
   [ 'O'] = (AsciiName){ .name = "O",   .desc = "Latin Uppercase O" },
   [ 'P'] = (AsciiName){ .name = "P",   .desc = "Latin Uppercase P" },
   [ 'Q'] = (AsciiName){ .name = "Q",   .desc = "Latin Uppercase Q" },
   [ 'R'] = (AsciiName){ .name = "R",   .desc = "Latin Uppercase R" },
   [ 'S'] = (AsciiName){ .name = "S",   .desc = "Latin Uppercase S" },
   [ 'T'] = (AsciiName){ .name = "T",   .desc = "Latin Uppercase T" },
   [ 'U'] = (AsciiName){ .name = "U",   .desc = "Latin Uppercase U" },
   [ 'V'] = (AsciiName){ .name = "V",   .desc = "Latin Uppercase V" },
   [ 'W'] = (AsciiName){ .name = "W",   .desc = "Latin Uppercase W" },
   [ 'X'] = (AsciiName){ .name = "X",   .desc = "Latin Uppercase X" },
   [ 'Y'] = (AsciiName){ .name = "Y",   .desc = "Latin Uppercase Y" },
   [ 'Z'] = (AsciiName){ .name = "Z",   .desc = "Latin Uppercase Z" },
   [ '['] = (AsciiName){ .name = "[",   .desc = "Opening Square Bracket" },
   ['\\'] = (AsciiName){ .name = "\\",  .desc = "Backslash" },
   [ ']'] = (AsciiName){ .name = "]",   .desc = "Closing Square Bracket" },
   [ '^'] = (AsciiName){ .name = "^",   .desc = "Caret - Circomflex" },
   [ '_'] = (AsciiName){ .name = "_",   .desc = "Underscore" },
   [ '`'] = (AsciiName){ .name = "`",   .desc = "Grave accent" },
   [ 'a'] = (AsciiName){ .name = "a",   .desc = "Latin Lowercase a" },
   [ 'b'] = (AsciiName){ .name = "b",   .desc = "Latin Lowercase b" },
   [ 'c'] = (AsciiName){ .name = "c",   .desc = "Latin Lowercase c" },
   [ 'd'] = (AsciiName){ .name = "d",   .desc = "Latin Lowercase d" },
   [ 'e'] = (AsciiName){ .name = "e",   .desc = "Latin Lowercase e" },
   [ 'f'] = (AsciiName){ .name = "f",   .desc = "Latin Lowercase f" },
   [ 'g'] = (AsciiName){ .name = "g",   .desc = "Latin Lowercase g" },
   [ 'h'] = (AsciiName){ .name = "h",   .desc = "Latin Lowercase h" },
   [ 'i'] = (AsciiName){ .name = "i",   .desc = "Latin Lowercase i" },
   [ 'j'] = (AsciiName){ .name = "j",   .desc = "Latin Lowercase j" },
   [ 'k'] = (AsciiName){ .name = "k",   .desc = "Latin Lowercase k" },
   [ 'l'] = (AsciiName){ .name = "l",   .desc = "Latin Lowercase l" },
   [ 'm'] = (AsciiName){ .name = "m",   .desc = "Latin Lowercase m" },
   [ 'n'] = (AsciiName){ .name = "n",   .desc = "Latin Lowercase n" },
   [ 'o'] = (AsciiName){ .name = "o",   .desc = "Latin Lowercase o" },
   [ 'p'] = (AsciiName){ .name = "p",   .desc = "Latin Lowercase p" },
   [ 'q'] = (AsciiName){ .name = "q",   .desc = "Latin Lowercase q" },
   [ 'r'] = (AsciiName){ .name = "r",   .desc = "Latin Lowercase r" },
   [ 's'] = (AsciiName){ .name = "s",   .desc = "Latin Lowercase s" },
   [ 't'] = (AsciiName){ .name = "t",   .desc = "Latin Lowercase t" },
   [ 'u'] = (AsciiName){ .name = "u",   .desc = "Latin Lowercase u" },
   [ 'v'] = (AsciiName){ .name = "v",   .desc = "Latin Lowercase v" },
   [ 'w'] = (AsciiName){ .name = "w",   .desc = "Latin Lowercase w" },
   [ 'x'] = (AsciiName){ .name = "x",   .desc = "Latin Lowercase x" },
   [ 'y'] = (AsciiName){ .name = "y",   .desc = "Latin Lowercase y" },
   [ 'z'] = (AsciiName){ .name = "z",   .desc = "Latin Lowercase z" },
   [ '{'] = (AsciiName){ .name = "{",   .desc = "Opening curly brace" },
   [ '|'] = (AsciiName){ .name = "|",   .desc = "Vertical bar" },
   [ '}'] = (AsciiName){ .name = "}",   .desc = "Closing curly brace" },
   [ '~'] = (AsciiName){ .name = "~",   .desc = "Tilde/Equivalence" },
   [0x7F] = (AsciiName){ .name = "DEL", .desc = "Delete" }
};


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

bool ascii_is_decimal_point(ascii const c)
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
      case SCHAR_MIN ... -1: return AsciiComp_LESS_THAN;    // left <  right
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


ascii const *ascii_name(ascii const c)
{
   return ascii_is_valid(c) ? S_CHARACTERS[(size_t)c].name : "INV";
}

ascii const *ascii_desc(ascii const c)
{
   return ascii_is_valid(c) ? S_CHARACTERS[(size_t)c].desc : "Invalid";
}
