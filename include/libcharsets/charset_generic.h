#pragma once

#include "charset_ascii.h"
#include "charset_utf8.h"
#include "charset_utf16.h"

// Provide generic defines that will automatically choose the correct function
// depending on the provided input.
// ascii -> ascii_[...]
// utf8  -> utf8_[...]
// utf16 -> utf16_[...]


#define charset_seq_count(str)          \
   _Generic((str),                      \
      ascii const *: ascii_seq_count,   \
   )(str)

#define charset_seq_ncount(str)         \
   _Generic((str),                      \
      ascii const *: ascii_seq_ncount,  \
   )(str)
