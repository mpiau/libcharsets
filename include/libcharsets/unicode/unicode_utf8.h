#pragma once 

#include "libcharsets/unicode/unicode_types.h"

// Assume that first byte is the leading byte of an utf-8 encoded character.
unsigned utf8_next_character_size(utf8 const *);
