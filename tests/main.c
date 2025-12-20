#include "libcharsets/charset_ascii.h"
#include "libcharsets/charsets.h"

#include <assert.h>
#include <limits.h>

// Compile it manually for the moment.
// gcc tests/main.c -Iinclude -L. -lcharsets -o test


struct AsciiCharTest
{
   ascii c;
   bool isValid;
   bool isDigit;
   bool isDigitBin;
   bool isDigitHex;
   bool isDigitOct;
   bool isLower;
   bool isUpper;
   bool isAlpha;
   bool isAlphanum;
   bool isPunct;
   bool isGraph;
   bool isPrint;
   bool isBlank;
   bool isWhitespace;
   bool isCtrl;
};
typedef struct AsciiCharTest AsciiCharTest;

// Perhaps a bit radical, but at least everything will be tested.
static constexpr AsciiCharTest asciiChars[] = {
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x00] = { '\0', true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x01] = { 0x01, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x02] = { 0x02, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x03] = { 0x03, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x04] = { 0x04, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x05] = { 0x05, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x06] = { 0x06, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x07] = { '\a', true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x08] = { '\b', true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x09] = { '\t', true, false, false, false, false, false, false, false, false, false, false, false,  true,  true,  true },
   [0x0A] = { '\n', true, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true },
   [0x0B] = { '\v', true, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true },
   [0x0C] = { '\f', true, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true },
   [0x0D] = { '\r', true, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true },
   [0x0E] = { 0x0E, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x0F] = { 0x0F, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x10] = { 0x10, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x11] = { 0x11, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x12] = { 0x12, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x13] = { 0x13, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x14] = { 0x14, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x15] = { 0x15, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x16] = { 0x16, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x17] = { 0x17, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x18] = { 0x18, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x19] = { 0x19, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1A] = { 0x1A, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1B] = { 0x1B, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1C] = { 0x1C, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1D] = { 0x1D, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1E] = { 0x1E, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
   [0x1F] = { 0x1F, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x20] = {  ' ', true, false, false, false, false, false, false, false, false, false, false,  true,  true,  true, false },
   [0x21] = {  '!', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x22] = {  '"', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x23] = {  '#', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x24] = {  '$', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x25] = {  '%', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x26] = {  '&', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x27] = { '\'', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x28] = {  '(', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x29] = {  ')', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2A] = {  '*', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2B] = {  '+', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2C] = {  ',', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2D] = {  '-', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2E] = {  '.', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x2F] = {  '/', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x30] = {  '0', true,  true,  true,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x31] = {  '1', true,  true,  true,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x32] = {  '2', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x33] = {  '3', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x34] = {  '4', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x35] = {  '5', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x36] = {  '6', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x37] = {  '7', true,  true, false,  true,  true, false, false, false,  true, false,  true,  true, false, false, false },
   [0x38] = {  '8', true,  true, false,  true, false, false, false, false,  true, false,  true,  true, false, false, false },
   [0x39] = {  '9', true,  true, false,  true, false, false, false, false,  true, false,  true,  true, false, false, false },
   [0x3A] = {  ':', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x3B] = {  ';', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x3C] = {  '<', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x3D] = {  '=', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x3E] = {  '>', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x3F] = {  '?', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x40] = {  '@', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x41] = {  'A', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x42] = {  'B', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x43] = {  'C', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x44] = {  'D', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x45] = {  'E', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x46] = {  'F', true, false, false,  true, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x47] = {  'G', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x48] = {  'H', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x49] = {  'I', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4A] = {  'J', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4B] = {  'K', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4C] = {  'L', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4D] = {  'M', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4E] = {  'N', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x4F] = {  'O', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x50] = {  'P', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x51] = {  'Q', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x52] = {  'R', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x53] = {  'S', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x54] = {  'T', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x55] = {  'U', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x56] = {  'V', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x57] = {  'W', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x58] = {  'X', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x59] = {  'Y', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x5A] = {  'Z', true, false, false, false, false, false,  true,  true,  true, false,  true,  true, false, false, false },
   [0x5B] = {  '[', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x5C] = { '\\', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x5D] = {  ']', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x5E] = {  '^', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x5F] = {  '_', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x60] = {  '`', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x61] = {  'a', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x62] = {  'b', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x63] = {  'c', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x64] = {  'd', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x65] = {  'e', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x66] = {  'f', true, false, false,  true, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x67] = {  'g', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x68] = {  'h', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x69] = {  'i', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6A] = {  'j', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6B] = {  'k', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6C] = {  'l', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6D] = {  'm', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6E] = {  'n', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x6F] = {  'o', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
//  Idx       Char  Valid Digit  Bin    Hex    Oct    Lower  Upper  Alpha  Alnum  Punct  Graph  Print  Blank  WSpace Ctrl
   [0x70] = {  'p', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x71] = {  'q', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x72] = {  'r', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x73] = {  's', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x74] = {  't', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x75] = {  'u', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x76] = {  'v', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x77] = {  'w', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x78] = {  'x', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x79] = {  'y', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x7A] = {  'z', true, false, false, false, false,  true, false,  true,  true, false,  true,  true, false, false, false },
   [0x7B] = {  '{', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x7C] = {  '|', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x7D] = {  '}', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x7E] = {  '~', true, false, false, false, false, false, false, false, false,  true,  true,  true, false, false, false },
   [0x7F] = { 0x7F, true, false, false, false, false, false, false, false, false, false, false, false, false, false,  true },
};

static void test_suite_ascii_characters(void)
{
   size_t const arrSize = sizeof(asciiChars) / sizeof(*asciiChars);
   for (size_t i = 0; i < arrSize; ++i)
   {
      AsciiCharTest const *const charTest = &asciiChars[i];
      ascii const c = charTest->c;

      assert(ascii_is_valid(c) == charTest->isValid);
      assert(ascii_is_digit(c) == charTest->isDigit);
      assert(ascii_is_digit_bin(c) == charTest->isDigitBin);
      assert(ascii_is_digit_hex(c) == charTest->isDigitHex);
      assert(ascii_is_digit_oct(c) == charTest->isDigitOct);
      assert(ascii_is_lower(c) == charTest->isLower);
      assert(ascii_is_upper(c) == charTest->isUpper);
      assert(ascii_is_alpha(c) == charTest->isAlpha);
      assert(ascii_is_alphanumeric(c) == charTest->isAlphanum);
      assert(ascii_is_punctuation(c) == charTest->isPunct);
      assert(ascii_is_graphical(c) == charTest->isGraph);
      assert(ascii_is_printable(c) == charTest->isPrint);
      assert(ascii_is_blank(c) == charTest->isBlank);
      assert(ascii_is_whitespace(c) == charTest->isWhitespace);
      assert(ascii_is_control(c) == charTest->isCtrl);
   }
}

void test_suite_ascii_characters_validity(void)
{
   for (int c = SCHAR_MIN; c <= SCHAR_MAX; ++c)
   {
      assert(ascii_is_valid((ascii)c) == (c >= 0));
   }
}


int main()
{
   test_suite_ascii_characters();
   test_suite_ascii_characters_validity();

   assert(ascii_seq_count("") == 0);
   assert(ascii_seq_count("a") == 1);
   assert(ascii_seq_count("abcdef") == 6);

   assert(ascii_seq_ncount("", 5) == 0);
   assert(ascii_seq_ncount("a", 5) == 1);
   assert(ascii_seq_ncount("abcdef", 5) == 5);
   assert(ascii_seq_ncount("1234567890",  0) ==  0);
   assert(ascii_seq_ncount("1234567890",  9) ==  9);
   assert(ascii_seq_ncount("1234567890", 10) == 10);
   assert(ascii_seq_ncount("1234567890", 11) == 10);

   return 0;
}