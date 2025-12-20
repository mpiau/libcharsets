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

// Returns the number of characters in the given string, excluding '\0'.
[[nodiscard]] __attribute__((nonnull (1)))
size_t ascii_count(ascii const *str);

// Returns the number of characters in the given string (up to max), excluding '\0'.
[[nodiscard]] __attribute__((nonnull (1)))
size_t ascii_ncount(ascii const *str, size_t max);


// TODO
