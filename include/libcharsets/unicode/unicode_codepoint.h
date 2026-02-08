#pragma once

#include "libcharsets/unicode/unicode_types.h"

bool codepoint_validate(codepoint);
bool codepoint_into_utf8(codepoint, utf8 [static 5]); // maximum 4 bytes + \0.

// Return the number of bytes used to generate the next codepoint.
unsigned codepoint_from_utf8(utf8 const *, codepoint *);
